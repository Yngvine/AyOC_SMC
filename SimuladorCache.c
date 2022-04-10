#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "colaDirecciones.h"

#if defined(__linux__) || defined(__unix__) //Direcciones en linux
#define CONFIGFILEPATH "config.txt"
#define TRAZAFILEPATH "traza.txt"
#elif defined(_WIN32) || defined(_WIN64) //Direcciones en windows
#define CONFIGFILEPATH "../config.txt"
#define TRAZAFILEPATH "../traza.txt"
#endif

//Funcion ofrecida para extraer partes de la una direccion, modificada para soportar direcciones de 64 bits
unsigned long long int rangobits (int bitmenor, int bitmayor, unsigned long int n);
//Funcion simple que devuelve del log en base 2 de un numero
int LOG2(int n);

int main(void) {
    FILE * f;
    int Nlin, Tlin, Asoc, VC, accesos = 0, fallos = 0;

    //Apertura del fichero de configuracion
    if ((f = fopen(CONFIGFILEPATH, "r")) == NULL) {
        perror("ERROR: Apertura fichero config.txt fallida\n");
        exit(-1);
    }
    //Lectura de datos del fichero de configuracion
    fscanf (f, "Nlin: %d\n", &Nlin);
    fscanf (f, "Tlin: %d\n", &Tlin);
    fscanf (f, "Asoc: %d\n", &Asoc);
    fscanf (f, "VC: %d", &VC);
    fclose(f);

    int indiceBit = LOG2(Tlin)-1; //Indice superior del #bit
    int numeroConjuntos = Nlin/Asoc;
    int indiceConjunto = LOG2(numeroConjuntos) + indiceBit; //Indice superior del #set

    tipoCola * memoriaCache, victimCache;//MC puede ser uno o muchos conjuntos, pero VC es uno solo

    celdaCola * lineaMC, * lineaVC; //Punteros auxiliares para tratar las lineas de MC y VC

    // Inicializacion de MC y VC
    memoriaCache = (tipoCola *) malloc(sizeof(tipoCola) * numeroConjuntos);
    for (int i=0; i<numeroConjuntos; i++)
        nuevaColaDoble(&(memoriaCache[i]), Asoc);
    if (VC > 0)
        nuevaColaDoble(&victimCache, VC);

    //Para evitar conflictos en algunos sistemas con direcciones mas largas se declaran como unsigned long long
    unsigned long long direccion, etiquetayset;
    unsigned long numeroConjunto;
    char buffer[20]; //Buffer de lectura para el fichero
    memset(buffer, 0, sizeof(buffer));

    //Apertura del fichero de traza
    if ((f = fopen(TRAZAFILEPATH, "r")) == NULL) {
        perror("ERROR: Apertura fichero config.txt fallida\n");
        exit(-1);
    }

    int c = 0;//VARIABLE PARA DEBUGGING
    while (fscanf(f,"%s ", buffer) > 0) {
        c++;
        direccion = strtoull(buffer, NULL, 16); //Traduccion de char* a unsigned long long
        memset(buffer, 0, sizeof(buffer));

        if (numeroConjuntos > 1) //MC NO es totalmente asociativa
            numeroConjunto = rangobits(indiceBit+1, indiceConjunto, direccion);
        else                     //MC SI es totalmente asociativa
            numeroConjunto = 0;

        //Una direccion es identificable por la linea en MP a la que pertenece el byte determinado por la direccion
        //Una linea de MP dentro de un conjunto puede ser inequivocamente diferenciada de otras con solo la etiqueta,
        //pero dado que la VC almacena direcciones dirigidas a cualquier conjunto, para evitar confusion entre
        //etiquetas iguales que pertenezcan a distintos conjuntos almacenamos tanto la etiqueta como el #set
        //por mucho que sea redundante en un mismo set en la MC
        etiquetayset = rangobits(indiceBit+1, 47, direccion);

        lineaMC = posicionDireccion(memoriaCache[numeroConjunto], etiquetayset); //Comprobamos si la direccion ya esta cargada en MC
        accesos++; //ACCESO
        if (lineaMC != NULL) { //Linea SI en MC
            //Reencolamos la linea para actualizar el LRU
            desencolarCelda(&memoriaCache[numeroConjunto], lineaMC);
            encolarCelda(&memoriaCache[numeroConjunto], lineaMC);

        } else { //Linea NO en MC
            if (VC > 0) { //SI existe VC
                lineaVC = posicionDireccion(victimCache, etiquetayset); //Comprobamos si esta la direccion ya cargada en VC

                if (lineaVC != NULL) { //Linea SI en VC
                    if (estaLlenaCola(memoriaCache[numeroConjunto])) { //Conjunto en MC SI lleno
                        //Extraemos LRU de MC, la introducimos en VC y la linea hallada en VC pasa a MC
                        lineaMC = desencolarLRU(&memoriaCache[numeroConjunto]);
                        desencolarCelda(&victimCache, lineaVC);
                        encolarCelda(&victimCache, lineaMC);
                        encolarCelda(&memoriaCache[numeroConjunto], lineaVC);

                    } else { //Conjunto en MC NO lleno
                        desencolarCelda(&victimCache, lineaVC);
                        encolarCelda(&memoriaCache[numeroConjunto], lineaVC);
                    }

                } else { //Linea NO en VC y NO en MC
                    fallos++; //FALLO
                    if (estaLlenaCola(memoriaCache[numeroConjunto])) {//Conjunto en MC lleno
                        lineaMC = desencolarLRU(&memoriaCache[numeroConjunto]); //Extraemos linea LRU de MC para pasarla a VC
                        if (estaLlenaCola(victimCache)) //VC llena
                            free(desencolarLRU(&victimCache));
                        encolarCelda(&victimCache, lineaMC);
                    }

                    encolarDireccion(&memoriaCache[numeroConjunto], etiquetayset); //Cargamos linea desde MP a MC
                }

            } else { //NO existe VC
                fallos++; //FALLO
                if (estaLlenaCola(memoriaCache[numeroConjunto])) //MC llena
                    free(desencolarLRU(&memoriaCache[numeroConjunto]));
                encolarDireccion(&memoriaCache[numeroConjunto], etiquetayset); //Cargamos linea desde MP a MC
            }
        }
    }

    fclose(f); //Cerrado de fichero traza.txt

    //printf de resultados de ejecucion
    printf("Accesos realizados: %d\nFallos encontrados: %d\nTasa de fallos: %.2f%%\n", accesos, fallos, ((float)fallos/(float)accesos)*100);
}


unsigned long long int rangobits (int bitmenor, int bitmayor, unsigned long int n) {
    unsigned long long int bit2=1, bit1=1;
    if (bitmenor<0 || bitmenor>63) {
        printf("Error en Bitmenor: %d\n", bitmenor);
        exit(0);
    } else if (bitmayor<0 || bitmayor>63) {
        printf("Error en Bitmayor: %d\n", bitmayor);
        exit(0);
    } else if (bitmenor>bitmayor) {
        printf("Error en Orden\n");
        exit(0);
    } else if(bitmayor-bitmenor+1<64 ) {
        /** calcula valor 2 elevado a bitmenor **/
        bit1 = bit1 << bitmenor;
        /** calcula valor 2 elevado a (bitmayor-bitmenor + 1) **/
        bit2 = bit2 << (bitmayor-bitmenor + 1);
        n=n / bit1;
        n=n % bit2;
    }
    return n;
}


int LOG2(int n) {
    int r = 0;
    while (n > 1) {
        n /= 2;
        r++;
    }
    return r;
}
