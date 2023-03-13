#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>

typedef struct sNodo {
    void *data;
    unsigned tam;
    struct sNodo *sig;
} tNodo;

typedef tNodo* tLista;

typedef int (*comparar)(const void *data_1, const void *data_2);
typedef int (*acumular)(void *data_1, const void *data_2);
typedef void (*mostrar)(const void *data, FILE *stream);

void crear_lista(tLista *lista);
void vaciar_lista(tLista *lista);
int lista_insertar(tLista *lista, const void *data, unsigned tam);
int lista_insertar_ordenado(tLista *lista, const void *data, unsigned tam,
        comparar cmp, acumular sum);
int lista_buscar(tLista *lista, const void *data, comparar cmp);
int lista_contar(tLista *lista);
void lista_mostrar(const tLista *list, mostrar mostrar, FILE *stream);
int lista_eliminar_ultimos_n(tLista *lista, const int n);

#endif
