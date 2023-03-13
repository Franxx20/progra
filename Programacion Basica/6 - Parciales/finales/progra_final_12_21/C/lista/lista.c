#include <stdlib.h>
#include <string.h>
#include "lista.h"

void crear_lista(tLista *lista)
{
    *lista = NULL;
}


void vaciar_lista(tLista *lista)
{
    while(*lista) {
        tNodo *aux = *lista;
        *lista = (aux)->sig;
        free(aux->data);
        free(aux);
    }
}


int lista_insertar_ordenado(tLista *lista, const void *data, unsigned tam, 
        comparar cmp, acumular sum)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo || !(nuevo->data = (void *)malloc(tam))) {
        free(nuevo);
        return 0;
    }

    while(*lista && cmp((*lista)->data, data) < 0) {
        lista = &(*lista)->sig;
    }

    if(*lista && cmp((*lista)->data, data) == 0) {
        if(sum != NULL) {
            int rc = sum((*lista)->data, data);
            free(nuevo->data);
            free(nuevo);
            return rc;
        }
    }

    memcpy(nuevo->data, data, tam);
    nuevo->tam = tam;
    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}


int lista_contar(tLista *lista)
{
    int tam = 0;

    while(*lista) {
        lista = &(*lista)->sig;
        tam++;
    }

    return tam;
}


int lista_eliminar_ultimos_n(tLista *lista, const int n)
{
    int lista_tam = lista_contar(lista);
    int i;

    if(n <= 0 || !lista || lista_tam < n) {
        return 0;
    }

    for(i = lista_tam; i > n; i--) {
        lista = &(*lista)->sig;
    }

    while(*lista) {
        tNodo *aux = *lista;
        *lista = (aux)->sig;
        free(aux->data);
        free(aux);
    }

    return 1;
}

void lista_mostrar(const tLista *list, mostrar mostrar, FILE *stream)
{
    while(*list) {
        mostrar((*list)->data, stream);
        list = &(*list)->sig;
    }
}
