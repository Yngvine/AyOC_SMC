#include "colaEnteros.h"
#include <stdio.h>
#include <stdlib.h>

void nuevaCola(tipoCola *p){
    p->ini = NULL;
    p->fin = NULL;
}

void encolar(tipoCola *p, tipoElementoCola ele){
    celdaCola *nueva;
    nueva=(celdaCola*)malloc(sizeof(celdaCola));
    nueva->elem = ele;
    nueva->sig = NULL;
    if (esNulaCola(*p)){
        p->ini = nueva;
        p->fin = nueva;
    }
    else{
        p->fin->sig = nueva;
        p->fin = nueva;
    }
}

void desencolar(tipoCola *p){
    if (esNulaCola(*p)){
        printf("\n\n\nERROR en el modulo pilas: intentando desencolar una pila vacía. \n");
    }
    else{
        celdaCola *aux;
        aux = p->ini;
        p->ini = p->ini->sig;
        if (p->fin == aux)
            p->fin = NULL;
        free(aux);
    }
}

tipoElementoCola frente(tipoCola p){
    if (esNulaCola(p)){
        printf("\n\n\nERROR en el modulo pilas: no existe frente en una pila vacía. \n");
        return -1;
    }
    else{
        return (p.ini->elem);
    }
}

bool esNulaCola(tipoCola p){
    return (p.fin == NULL);
}
