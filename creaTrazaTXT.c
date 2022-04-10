#include <stdio.h>

#define MAX 100
#if defined(__linux__) || defined(__unix__) //Direccion en linux
#define TRAZAFILEPATH "traza.txt"
#elif defined(_WIN32) || defined(_WIN64) //Direccion en windows
#define TRAZAFILEPATH "../traza.txt"
#endif

void ex1();
void ex2();
void ex3();

int main(void) {
    printf("Elija una de las opciones para crear el fichero de traza\n"
           "1.Acceso secuencial a un vector de %d elementos double\n"
           "2.Acceso a matriz de 4x1024 elementos double recorriendola\n por columnas\n"
           "3.Acceso a matriz de 5x8 elemtos double recorriendola por\n columnas\n",MAX);
    int resp;
    scanf("%d", &resp);

    if (resp == 1)
        ex1();
    else if (resp == 2)
        ex2();
    else if (resp == 3)
        ex3();
    else
        printf("ERROR: Opcion fuera de rango");

    return(0);
}

void ex1() {
    double v[MAX], res;
    FILE *f;
    f = fopen(TRAZAFILEPATH,"w");
    for (int i = 0; i < MAX; i++) {
        res = res + v[i];
        fprintf(f, "%p ", &v[i]);
    }
    fclose(f);
}

void ex2() {
    FILE *f;
    f = fopen(TRAZAFILEPATH,"w");
    unsigned long dirBase = 0x0000;
    int columnas = 1024, filas =4;

    for (int j=0; j<columnas; j++)
        for ( int i=0; i<filas; i++){
            fprintf(f, "0x%lX ", dirBase+j*8+columnas*i*8);
        }
    fclose(f);
}

void ex3() {
    FILE *f;
    f = fopen(TRAZAFILEPATH,"w");
    unsigned long dirBase = 0x0000;
    int columnas = 8, filas = 5;

    for (int j=0; j<columnas; j++)
        for ( int i=0; i<filas; i++){
            fprintf(f, "0x%lX ", dirBase+j*8+columnas*i*8);
        }
    fclose(f);
}