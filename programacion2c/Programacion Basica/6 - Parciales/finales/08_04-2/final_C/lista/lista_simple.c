#include <stdlib.h>
#include <string.h>
#include "lista_simple.h"

void crearLista(tLista *lista)
{
	*lista = NULL;
}


void vaciarLista(tLista *lista)
{
	while(*lista) {
		tNodo *aux = *lista;
		*lista = aux->sig;
		free(aux->data);
		free(aux);
	}
}


int lista_insertarOrdenado(tLista *lista, const void *data,
						unsigned bytes, comparar cmp, acumular sum)
{
	tNodo *nuevo;

	while((*lista) && cmp((*lista)->data, data) < 0) {
		lista = &(*lista)->sig;
	}

	if((*lista) && cmp((*lista)->data, data) == 0) {
		if(sum != NULL) {
			return sum((*lista)->data, data);
		}
	}

	nuevo = (tNodo *)malloc(sizeof(tNodo));
	if(!nuevo || !(nuevo->data = malloc(bytes))) {
		free(nuevo);
		return 0;
	}

	nuevo->bytes = bytes;
	memcpy(nuevo->data, data, bytes);
	nuevo->sig = *lista;
	*lista = nuevo;

	return 1;
}


void lista_mostrar(const tLista *lista, mostrar print, FILE *stream)
{
	while(*lista) {
		print((*lista)->data, stream);
		lista = &(*lista)->sig;
	}
}
