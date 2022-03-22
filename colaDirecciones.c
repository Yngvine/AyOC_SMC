//
// Created by igor on 21/10/21.
//
#include "colaDirecciones.h"
#include <stdio.h>
#include <stdlib.h>

void nuevaColaDoble(tipoCola *c, int t) {
    c->ini = NULL;
    c->fin = NULL;
    c->tamMax = t;
}

void encolarDireccion(tipoCola *c, etiquetaDireccion e) {
    celdaCola *aux = (celdaCola *)malloc(sizeof(celdaCola));
    aux->elem = e;
    aux->ant = NULL;
    aux->sig = c->ini;
    if(esNulaCola(*c)) {
        c->ini = aux;
        c->fin = aux;
    }else {
        c->ini->ant = aux;
        c->ini = aux;
    }
}

void encolarCelda(tipoCola * c, celdaCola * d) {
    if (esNulaCola(*c)){
        c->fin = d;
        c->ini = d;
    } else {
        c->ini->ant = d;
        c->ini = d;
    }
}

void desencolarCelda(tipoCola *c, celdaCola *d) {
    if(!esNulaCola(*c)){
        if (c->ini == d)
            c->ini = d->sig;
        else
            d->ant->sig = d->sig;
        if (c->fin == d)
            c->fin = d->ant;
        else
            d->sig->ant = d->ant;
    }else
        printf("No se puede desencolar cola vacia\n");
}

void desencolarLRU(tipoCola *c) {
    if (!esNulaCola(*c)) {
        celdaCola *aux;
        aux = c->fin;
        c->fin = (c->fin)->ant;
        if(c->fin != NULL)
            (c->fin)->sig = NULL;
        free(aux);
    } else
        printf("No se puede desencolar cola vaciaLRU\n");
}

celdaCola * posicionDireccion(tipoCola c, etiquetaDireccion e) {
    celdaCola * d;
    d = c.ini;
    while (d != NULL && d->elem != e)
        d = d->sig;
    return d;
}

bool esNulaCola(tipoCola c) {
    return(c.ini==NULL || c.fin==NULL);
}

bool estaLlenaCola(tipoCola c) {
    int tam = 0;
    celdaCola *aux = c.ini;
    while (aux != 0) {
        tam++;
        aux = aux->sig;
    }
    return(tam >= c.tamMax);
}