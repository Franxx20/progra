#include <string.h>
#include <stdlib.h>
#include "pila.h"
#define MIN(X,Y) (((X) <= (Y))? (X) : (Y))

void crear_pila(tPila *pila) {
    *pila = NULL;
}

void vaciar_pila(tPila *pila) {
    while(*pila) {
        tNodo *aux = *pila;
        (*pila) = aux->sig;
        free(aux->data);
        free(aux);
    }
}

int pila_vacia(tPila *pila) {
    return *pila == NULL;
}

int pila_insertar(tPila *pila, const void *p_data, unsigned p_tam) {
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));
    if(!nuevo || !(nuevo->data = malloc(p_tam))) {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->data, p_data, p_tam);
    nuevo->tam = p_tam;
    nuevo->sig = *pila;
    *pila = nuevo;
    return 1;
}

int pila_eliminar(tPila *pila, void *p_data, unsigned p_tam) {
    tNodo *aux = *pila;

    if(!aux) {
        return 0;
    }

    *pila = aux->sig;
    memcpy(p_data, aux->data, MIN(aux->tam, p_tam));

    free(aux->data);
    free(aux);
    return 1;
}
