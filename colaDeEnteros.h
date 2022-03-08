#ifndef IVV_COLA_DE_ENTEROS_H
#define IVV_COLA_DE_ENTEROS_H
/**
 *	MODULO: colaDeEnteros
 *	FICHERO: colaDeEnteros.h
 *	VERSION: 1.0.0
 *	HISTORICO:
 *		Creado por Igor Volodimir Vons el 29/04/21.
 * DESCRIPCION: Este modulo exporta la funcionalidad necesaria para trabajar
 * 	con el concepto de cola de enteros.
 */
#include <stdbool.h> // para el tipo booleano

// Definicion de las celdas de la cola
typedef struct nodoDeColaDeEnteros {
    int e;
    struct nodoDeColaDeEnteros *s;
} NodoDeColaDeEnteros;
// Deficnicion de la cola de celdas
typedef struct colaDeEnteros{
    NodoDeColaDeEnteros *i;
    NodoDeColaDeEnteros *f;
} ColaDeEnteros;

	// Prototipos de la funcionalidad exportada

//Inicializa la cola
void nuevaColaDeEnteros(ColaDeEnteros *);

//Introduce un nuevo elemento en la cola
void pideTurnoColaDeEnteros(ColaDeEnteros *, int);

//Elimina el primer elemento de la cola
void avanceColaDeEnteros(ColaDeEnteros *);

//Devuelve el primer valor de la cola
void primeroColaDeEnteros(ColaDeEnteros, int *);

//Indica mediate booleano si la cola esta vacia
bool esNulaColaDeEnteros(ColaDeEnteros);
#endif //IVV_COLA_DE_ENTEROS H
