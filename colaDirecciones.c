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
        d->sig = c->ini;
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
        d->sig = NULL;
        d->ant = NULL;
    }else
        printf("No se puede desencolar cola vacia\n");
}

celdaCola * desencolarLRU(tipoCola *c) {
    if (!esNulaCola(*c)) {
        celdaCola *aux;
        if (c->fin == c->ini)
            c->ini = NULL;
        aux = c->fin;
        c->fin = aux->ant;
        if(c->fin != NULL)
            (c->fin)->sig = NULL;
        aux->sig = NULL;
        aux->ant = NULL;
        return aux;
    } else {
        printf("No se puede desencolar cola vaciaLRU\n");
        return NULL;
    }
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