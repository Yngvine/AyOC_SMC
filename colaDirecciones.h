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

//Inicializacion de la cola
void nuevaColaDoble(tipoCola *, int);

//Se encola una nueva direccion
void encolarDireccion(tipoCola *, etiquetaDireccion);

//Se encola una celda que contiene una direccion
void encolarCelda(tipoCola *, celdaCola *);

//Se extrae una celda en particular de la cola
void desencolarCelda(tipoCola *, celdaCola *);

//Se desencola la Least Recently Used celda y se devuelve su direccion
celdaCola * desencolarLRU(tipoCola *);

//Se devuelve la direccion de la celda que contiene la direccion, en caso contrario NULL
celdaCola * posicionDireccion(tipoCola , etiquetaDireccion);

//Comprueba si la cola esta vacia
bool esNulaCola(tipoCola);

//Comprueba si la cola esta llena
bool estaLlenaCola(tipoCola);

#endif //UNTITLED1_COLADOBLECARACTERES_H