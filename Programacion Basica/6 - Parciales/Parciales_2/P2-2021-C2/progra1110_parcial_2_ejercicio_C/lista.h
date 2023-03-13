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

void crearLista(tLista *lista);
void vaciarLista(tLista *lista);
int lista_insertar(tLista *lista, const void *data, unsigned tam);
int lista_insertarOrdenado(tLista *lista, const void *data, unsigned tam,
            comparar cmp, acumular sum);
int lista_buscar(tLista *lista, const void *data, comparar cmp);
size_t lista_contar(tLista *lista);
int lista_mostrarN_Ultimos(tLista *lista, size_t n, mostrar mostrar, FILE* stream);

#endif
