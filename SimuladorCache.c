#include <stdio.h>
#include <stdlib.h>
#include "colaDirecciones.h"
unsigned long int rangobits (int bitmenor, int bitmayor, unsigned long int n);
int LOG2(int n);

int main(void) {
    FILE * f;
    int Nlin, Tlin, Asoc, VC, accesos = 0, fallos = 0;
    f = fopen("config.txt", "r");
    fscanf (f, "Nlin: %d\n", &Nlin);
    fscanf (f, "Tlin: %d\n", &Tlin);
    fscanf (f, "Asoc: %d\n", &Asoc);
    fscanf (f, "VC: %d", &VC);
    fclose(f);

    int indiceBit = LOG2(Tlin)-1;
    int numeroConjuntos = Nlin/Asoc;
    int indiceConjunto = LOG2(numeroConjuntos) + indiceBit;
    tipoCola * memoriaCache;
    celdaCola * lineaMC;
    memoriaCache = (tipoCola *) malloc(sizeof(tipoCola) * numeroConjuntos);
    for (int i=0; i<numeroConjuntos; i++)
        nuevaColaDoble(&(memoriaCache[i]), Asoc);
    unsigned long direccion;
    unsigned long numeroConjunto;
    unsigned long etiqueta;
    f = fopen("traza.txt", "r");
    char buffer[11];
    while (fread(buffer, 11, 1, f)) {
        direccion = strtol(buffer, NULL, 16);
        numeroConjunto = rangobits(indiceBit+1, indiceConjunto, direccion);
        etiqueta = rangobits(indiceConjunto+1, 47, direccion);

        lineaMC = posicionDireccion(memoriaCache[numeroConjunto], etiqueta);
        if (lineaMC != NULL) {
            accesos++;
            desencolarCelda(&memoriaCache[numeroConjunto], lineaMC);
            encolarCelda(&memoriaCache[numeroConjunto], lineaMC);
        } else {
            accesos++;
            fallos++;
            if (estaLlenaCola(memoriaCache[numeroConjunto]))
                desencolarLRU(&memoriaCache[numeroConjunto]);
            encolarDireccion(&memoriaCache[numeroConjunto], etiqueta);
        }
    }
    fclose(f);
    printf("Accesos realizados: %d\nFallos encontrados: %d", accesos, fallos);
}

unsigned long int rangobits (int bitmenor, int bitmayor, unsigned long int n) {
    unsigned long int bit2=1, bit1=1;
    if (bitmenor<0 || bitmenor>47) {
        printf("Error en Bitmenor: %d\n", bitmenor);
        exit(0);
    } else if (bitmayor<0 || bitmayor>47) {
        printf("Error en Bitmayor: %d\n", bitmayor);
        exit(0);
    } else if (bitmenor>bitmayor) {
        printf("Error en Orden\n");
        exit(0);
    } else if(bitmayor-bitmenor+1<48 ) {
        /** calcula valor 2 elevado a bitmenor **/
        bit1= bit1 << bitmenor;
        /** calcula valor 2 elevado a (bitmayor-bitmenor + 1) **/
        bit2 =bit2 << (bitmayor-bitmenor + 1);
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