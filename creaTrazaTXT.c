#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define FILENAME "../traza.txt"

void ex1();
void ex2();

int main(void) {
    //ex1();
    ex2();

    return(0);
}

void ex1() {
    double v[MAX], res;
    FILE *f;
    f = fopen(FILENAME,"w");
    for (int i = 0; i < MAX; i++) {
        res = res + v[i];
        fprintf(f, "%p ", &v[i]);
    }
    fclose(f);
}

void ex2() {
    FILE *f;
    f = fopen(FILENAME,"w");
    unsigned long dirBase = 0x0000;
    int columnas = 1024, filas =4;

    for (int j=0; j<columnas; j++)
        for ( int i=0; i<filas; i++){
            fprintf(f, "0x%lX ", dirBase+j*8+columnas*i*8);
        }
    fclose(f);
}