#ifndef UNTITLED1_COLADOBLECARACTERES_H
#define UNTITLED1_COLADOBLECARACTERES_H

#include <stdbool.h>

typedef unsigned long long etiquetaDireccion;
typedef struct celdaC{
    etiquetaDireccion elem;
    struct celdaC *ant;
    struct celdaC *sig;
} celdaCola;
typedef struct tipoC{
    celdaCola* ini;
    celdaCola* fin;
    int tamMax;
} tipoCola;

void nuevaColaDoble(tipoCola *, int);

void encolarDireccion(tipoCola *, etiquetaDireccion);

void encolarCelda(tipoCola *, celdaCola *);

void desencolarCelda(tipoCola *, celdaCola *);

celdaCola * desencolarLRU(tipoCola *);

celdaCola * posicionDireccion(tipoCola , etiquetaDireccion);

bool esNulaCola(tipoCola);

bool estaLlenaCola(tipoCola);

#endif //UNTITLED1_COLADOBLECARACTERES_H