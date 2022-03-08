/**
 *	MODULO: colaDeEnteros
 *	FICHERO: colaDeEnteros.c
 *	VERSION: 1.0.0
 *	HISTORICO:
 *		Creado por Igor Volodimir Vons el 29/04/21.
 * DESCRIPCION: Este modulo exporta la funcionalidad necesaria para implementar
 * 	una cola de enteros.
 */
#include <stdio.h>
#include "colaDeEnteros.h"
#include <stdlib.h> // para conocer exit y malloc
// Prototipos de la funcionalidad exportada

//Indica un error e interrumpe la ejecucion del programa
void errorColaDeEnteros(char s[]){
    printf("\n\n\nERROR en el modulo colas: %s \n", s);
    while (true)
    exit(-1);
}

//Inicializa la cola
void nuevaColaDeEnteros(ColaDeEnteros *c){
    c->i = NULL;
    c->f= NULL;
}

//Introduce un nuevo elemento en la cola
void pideTurnoColaDeEnteros(ColaDeEnteros *c, int x){
    NodoDeColaDeEnteros * q;
    if ((q=malloc(sizeof(NodoDeColaDeEnteros)))==NULL)
        errorColaDeEnteros("no hay memoria para pideTurno");
    q->e = x;
    q->s = NULL;
    if (c->f == NULL)
        c->i = q;
    else
        c->f->s=q;
    c->f=q;
}

//Elimina el primer elemento de la cola
void avanceColaDeEnteros(ColaDeEnteros *c){
    NodoDeColaDeEnteros * q;
    if (esNulaColaDeEnteros(*c))
        errorColaDeEnteros("avanzando en cola nula");
    q= c->i;
    c->i = c->i->s;
    if (c->i == NULL)
        c->f = NULL;
    free(q);
}

//Devuelve el primer valor de la cola
void primeroColaDeEnteros (ColaDeEnteros c, int *x){
    if (esNulaColaDeEnteros(c))
        errorColaDeEnteros("primero en cola nula");
    *x = c.i->e; //cuidado con el tipo int
}

//Indica mediate booleano si la cola esta vacia
bool esNulaColaDeEnteros (ColaDeEnteros c){
    return (c.i == NULL);
}
