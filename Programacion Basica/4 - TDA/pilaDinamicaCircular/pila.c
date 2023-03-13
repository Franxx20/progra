/* ------------------------------------------------------------------------- */
/*                  pila dinamica circular | pila.h                          */
/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define minimo( X , Y )     ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )

void crearPila(tPila *pila)
{
    *pila = NULL;
}

int pilaLlena(const tPila *pila, unsigned cantBytes)
{
    tNodo *aux  = (tNodo *)malloc(sizeof(tNodo));
    void  *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnPila(tPila *pila, const void *data, unsigned cantBytes)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo || (nuevo->info = malloc(cantBytes)) == NULL) {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, data, cantBytes);
    nuevo->tamInfo = cantBytes;
    
	if(*pila == NULL) {
		nuevo->sig = nuevo;
		*pila = nuevo;
	}
	else {
		nuevo->sig = (*pila)->sig;
		(*pila)->sig = nuevo;
	}

    return 1;
}

int verTope(const tPila *pila, void *data, unsigned cantBytes)
{
    if(*pila == NULL) {
        return 0;
    }

    memcpy(data, (*pila)->sig->info, minimo(cantBytes, (*pila)->sig->tamInfo));
    return 1;
}

int pilaVacia(const tPila *pila)
{
    return *pila == NULL;
}

int sacarDePila(tPila *pila, void *data, unsigned cantBytes)
{
    tNodo *aux;

    if(*pila == NULL) {
        return 0;
    }

    aux = (*pila)->sig;
    memcpy(data, aux->info, minimo(cantBytes, aux->tamInfo));

	if(aux == *pila) {
		*pila = NULL;
    }
	else {
		(*pila)->sig = aux->sig;
    }
		
    free(aux->info);
    free(aux);
    
    return 1;
}

void vaciarPila(tPila *pila)
{
    while(*pila) {
        tNodo *aux = (*pila)->sig;

		if(*pila == aux) {
			*pila = NULL;
        }
		else {
			(*pila)->sig = aux->sig;
        }
		
        free(aux->info);
        free(aux);
    }
}

/* ------------------------------------------------------------------------- */