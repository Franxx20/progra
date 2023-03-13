/* ------------------------------------------------------------------------- */
/*                           pila dinamica | pila.c                          */
/* ------------------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include "pila.h"

#define minimo(X,Y)     ((X) <= (Y)? (X) : (Y))

void crearPila(tPila *pila)
{
    *pila = NULL;
}

void vaciarPila(tPila *pila)
{
    while(*pila) {
        tNodo *aux = *pila;

        *pila = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int ponerEnPila(tPila *pila, const void *data, unsigned cantBytes)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo) {
        return 0;
    }

    nuevo->info = malloc(cantBytes);
    if(!nuevo->info) {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, data, cantBytes);
    nuevo->tamInfo = cantBytes;
    nuevo->sig = *pila;
    *pila = nuevo;

    return 1;
}

int sacarDePila(tPila *pila, void *data, unsigned cantBytes)
{
    tNodo *aux = *pila;
    if(!aux) {
        return 0;
    }

    *pila = aux->sig;

    memcpy(data, aux->info, minimo(cantBytes, aux->tamInfo));
    
    free(aux->info);
    free(aux);
    
    return 1;
}

int pilaLlena(const tPila *pila, unsigned cantBytes)
{
    tNodo *aux  = (tNodo *)malloc(sizeof(tNodo));
    void  *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int pilaVacia(const tPila *pila)
{
    return *pila == NULL;
}

int verTope(const tPila *pila, void *data, unsigned cantBytes)
{
    if(!*pila) {
        return 0;
    }

    memcpy(data, (*pila)->info, minimo(cantBytes, (*pila)->tamInfo));
    return 1;
}

/* ------------------------------------------------------------------------- */