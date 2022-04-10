#ifndef UNTITLED1_COLADOBLECARACTERES_H
#define UNTITLED1_COLADOBLECARACTERES_H

#include <stdbool.h>
//Se almacena la #lineaMP de una direccion
typedef unsigned long long etiquetaDireccion;
//celdaC se corresponde con una linea dentro de un conjunto
typedef struct celdaC{
    etiquetaDireccion elem;
    struct celdaC *ant;
    struct celdaC *sig;
} celdaCola;
//tipoCola se corresponde con un conjunto
typedef struct tipoC{
    celdaCola* ini;
    celdaCola* fin;
    int tamMax;
} tipoCola;

//Inicializacion del conjunto
void nuevaColaDoble(tipoCola *, int);

//Se encola una nueva linea correspondiente a una direccion
void encolarDireccion(tipoCola *, etiquetaDireccion);

//Se encola una linea correspondiente a una direccion ya cargada previamente
void encolarCelda(tipoCola *, celdaCola *);

//Se extrae una linea en particular del conjunto
void desencolarCelda(tipoCola *, celdaCola *);

//Se desencola la Least Recently Used linea y se devuelve su referencia
celdaCola * desencolarLRU(tipoCola *);

//Se devuelve la direccion de la linea que correspondiante a la etiqueda de la direccion, en caso contrario NULL
celdaCola * posicionDireccion(tipoCola , etiquetaDireccion);

//Comprueba si el conjunto esta vacio
bool esNulaCola(tipoCola);

//Comprueba si el conjunto esta lleno
bool estaLlenaCola(tipoCola);

#endif //UNTITLED1_COLADOBLECARACTERES_H