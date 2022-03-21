#include <stdio.h>
#include <stdlib.h>
#define MAX 100


int main(void) {
    double v[MAX], res;
    FILE *f;
    f = fopen("traza.txt","w");
    for (int i = 0; i < MAX; i++) {
        res = res + v[i];
        fprintf(f, "%p ", &v[i]);
    }
    return(0);
}

