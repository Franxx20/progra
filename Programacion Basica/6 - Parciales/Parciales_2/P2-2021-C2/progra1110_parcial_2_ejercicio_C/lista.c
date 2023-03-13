#include <stdlib.h>
#include <string.h>
#include "lista.h"

void crearLista(tLista *lista)
{
    *lista = NULL;
}


void vaciarLista(tLista *lista)
{
    while(*lista) {
        tNodo *aux = *lista;
        *lista = (aux)->sig;
        free(aux->data);
        free(aux);
    }
}


int lista_insertar(tLista *lista, const void *data, unsigned tam)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo || !(nuevo->data = (void *)malloc(tam))) {
        free(nuevo);
        return 0;
    }

    while((*lista)) {
        lista = &(*lista)->sig;
    }

    memcpy(nuevo->data, data, tam);
    nuevo->tam = tam;
    nuevo->sig = NULL;
    (*lista) = nuevo;

    return 1;
}


int lista_insertarOrdenado(tLista *lista, const void *data, unsigned tam,
            comparar cmp, acumular sum)
{
    tNodo *nuevo;
    tNodo *aux = *lista;

    while(aux && cmp(aux->data, data) < 0) {
        aux = aux->sig;
    }

    if(aux &&  cmp(aux->data, data) == 0) {
        if(sum) {
            return sum(aux->data, data);
        }
    }

    nuevo = (tNodo *)malloc(sizeof(tNodo));

    if(!nuevo || !(nuevo->data = (void *)malloc(tam))) {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->data, data, tam);
    nuevo->tam = tam;

    nuevo->sig = aux->sig;
    aux->sig = nuevo;

    return 1;
}


int lista_buscar(tLista *lista, const void *data, comparar cmp)
{
    int pos = 0;

    while((*lista) && cmp((*lista)->data, data) != 0) {
        lista = &(*lista)->sig;
        pos++;
    }

    if(!(*lista)) {
        pos = -1;
    }
    return pos;
}


size_t lista_contar(tLista *lista)
{
    size_t tam = 0;

    if(!(*lista)) {
        return 0;
    }

    while((*lista)->sig) {
        lista = &(*lista)->sig;
        tam++;
    }

    return tam;
}


int lista_mostrarN_Ultimos(tLista *lista, size_t n, mostrar mostrar, FILE* stream)
{
    size_t lista_tam = lista_contar(lista);
    size_t i;

    if(!lista || lista_tam < n) {
        return 0;
    }

    for(i = lista_tam; i > n; i--) {
        lista = &(*lista)->sig;
    }

    while((*lista)->sig) {
        mostrar((*lista)->data, stream);
        lista = &(*lista)->sig;
    }

    return 1;
}
