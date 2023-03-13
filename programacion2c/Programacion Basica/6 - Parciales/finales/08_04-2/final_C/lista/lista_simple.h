#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <stdio.h>

typedef struct sNodo {

	void *data;
	unsigned bytes;
	struct sNodo *sig;

} tNodo;
typedef tNodo* tLista;

typedef void (*mostrar)(const void *data, FILE *stream);
typedef int  (*comparar)(const void *data_1, const void *data_2);
typedef int  (*acumular)(void *data_1, const void *data_2);


void crearLista(tLista *lista);
void vaciarLista(tLista *lista);
int lista_insertarOrdenado(tLista *lista, const void *data, unsigned bytes,
									comparar cmp, acumular sum);
void lista_mostrar(const tLista *lista, mostrar print, FILE *stream);

#endif
