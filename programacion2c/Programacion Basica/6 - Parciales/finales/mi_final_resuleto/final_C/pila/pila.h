#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>

typedef struct sNodo {
    void *data;
    unsigned tam;
    struct sNodo *sig;
} tNodo;
typedef tNodo *tPila;
typedef void (*mostrar)(const void *data, FILE *stream);

void crear_pila(tPila *pila);
void vaciar_pila(tPila *pila);
int pila_vacia(tPila *pila);
int pila_insertar(tPila *pila, const void *p_data, unsigned p_tam);
int pila_eliminar(tPila *pila, void *p_data, unsigned p_tam);

#endif // PILA_H_INCLUDED
