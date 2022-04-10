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
    //ex1();
    //ex2();
    ex3();

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