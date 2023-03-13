/* ------------------------------------------------------------------------- */
/*                           lista simple | lista.c                          */
/* ------------------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define minimo( X, Y )     ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )


void crearLista(tLista *list)
{
    *list = NULL;
}


int listaVacia(const tLista *list)
{
    return *list == NULL;
}


int listaLlena(const tLista *list, unsigned cantBytes)
{
    tNodo   *aux = (tNodo *)malloc(sizeof(tNodo));
    void    *data = malloc(cantBytes);

    free(aux);
    free(data);
    return aux == NULL || data == NULL;
}


int vaciarLista(tLista *list)
{
    int cant = 0;
    while(*list)
    {
        tNodo *aux = *list;
        *list = aux->sig;
        free(aux->data);
        free(aux);
        cant++;
    }
    return cant;
}


int lista_insertarInicio(tLista *list, const void *data, unsigned cantBytes)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if( !nuevo || !(nuevo->data = malloc(cantBytes)) ) {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->data, data, cantBytes);
    nuevo->cantBytes = cantBytes;
    nuevo->sig = *list;
    *list = nuevo;

    return 1;
}


int lista_removerPrimero(tLista *list, void *data, unsigned cantBytes)
{
    tNodo *aux = *list;

    if(aux == NULL) {
        return 0;
    }

    *list = aux->sig;
    memcpy(data, aux->data, minimo(cantBytes, aux->cantBytes));
    free(aux->data);
    free(aux);
    return 1;
}


int lista_verPrimero(const tLista *list, void *data, unsigned cantBytes)
{
    if(*list == NULL) {
        return 0;
    }
    memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));
    return 1;
}


int lista_insertarFinal(tLista *list, const void *data, unsigned cantBytes)
{
    tNodo  *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if( !nuevo || !(nuevo->data = malloc(cantBytes)) ) {
        free(nuevo);
        return 0;
    }

    while(*list) {
        list = &(*list)->sig;
    }

    memcpy(nuevo->data, data, cantBytes);
    nuevo->cantBytes = cantBytes;
    nuevo->sig = NULL;
    *list = nuevo;

    return 1;
}


int lista_removerUltimo(tLista *list, void *data, unsigned cantBytes)
{
    if(*list == NULL) {
        return 0;
    }

    while((*list)->sig) {
        list = &(*list)->sig;
    }

    memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));
    free((*list)->data);
    free(*list);
    *list = NULL;

    return 1;
}


int lista_verUltimo(const tLista *list, void *data, unsigned cantBytes)
{
    if(*list == NULL) {
        return 0;
    }

    while((*list)->sig) {
        list = &(*list)->sig;
    }

    memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));
    return 1;
}


int lista_mostrar(const tLista *list, mostrar mostrar, FILE *stream)
{
    int cant = 0;
    while(*list) {
        mostrar((*list)->data, stream);
        list = &(*list)->sig;
        cant++;
    }
    return cant;
}


int lista_mostrarInvertido(const tLista *list, mostrar mostrar, FILE *stream)
{
    if(*list) {
        int n = lista_mostrarInvertido(&(*list)->sig, mostrar, stream);

        mostrar((*list)->data, stream);
        return n + 1;
    }
    return 0;
}


int lista_insertarOrdenado(tLista *list, const void *data, unsigned cantBytes,
        comparar comparar, acumular acumular)
{
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if( !nuevo || !(nuevo->data = malloc(cantBytes))) {
        free(nuevo);
        return 0;
    }

    /* Si comparar < 0 entonces el dato es mas grande que el actual en lista */
    while(*list && comparar((*list)->data, data) < 0) {
        list = &(*list)->sig;
    }

    if(*list && comparar((*list)->data, data) == 0) {
        if(acumular != NULL) {
            int rc = acumular((*list)->data, (*list)->cantBytes, 
                              data, cantBytes);
            free(nuevo->data);
            free(nuevo);
            return rc;
        }
    }

    memcpy(nuevo->data, data, cantBytes);
    nuevo->cantBytes = cantBytes;
    nuevo->sig = *list;
    *list = nuevo;

    return 1;
}


void lista_ordenar(tLista *list, comparar comparar)
{
    int ordenado = 0;
    tLista *first = list;

    if(*list == NULL) {
        return;
    }

    do {
        list = first;
        ordenado = 0;
        while((*list)->sig) {

            if(comparar((*list)->data, (*list)->sig->data) > 0) {
                tLista aux = *list;
                (*list) = (*list)->sig;
                aux->sig = (*list)->sig;
                (*list)->sig = aux;
                ordenado = 1;
            }
            list = &(*list)->sig;
        }
    } while(ordenado);
}


void lista_filtrar(tLista *list, int (*filtro) (const void *))
{
    if(*list == NULL) {
        return;
    }

    while((*list)) {
        if(!filtro((*list)->data)) {
            tLista temp = *list;
            (*list) = (*list)->sig;

            free(temp->data);
            free(temp);
        }
        else {
            list = &(*list)->sig;
        }
    }
}


int lista_insertarPosicion(tLista *list, const void *data, unsigned cantBytes,
        unsigned pos)
{
    size_t i;
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

    if( !nuevo || !(nuevo->data = malloc(cantBytes)) ) {
        free(nuevo);
        return 0;
    }

    for(i = 0; i < pos && *list ; i++) {
        list = &(*list)->sig;
    }

    memcpy(nuevo->data, data, cantBytes);
    nuevo->cantBytes = cantBytes;
    nuevo->sig = *list;
    *list = nuevo;

    return 1;
}


int lista_removerPosicion(tLista *list, void *data, unsigned cantBytes, 
                unsigned pos)
{
    size_t i;
    tLista eliminar;

    for(i = 0; i < pos && *list ; i++) {
        list = &(*list)->sig;
    }

    if(*list == NULL) {
        return 0;
    }

    memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));

    
    eliminar = *list;
    (*list) = (*list)->sig;

    free(eliminar->data);
    free(eliminar);
    
    return 1;
}


int lista_verPosicion(const tLista *list, void *data, unsigned cantBytes, 
        unsigned pos)
{
    size_t i;

    for(i = 0; i < pos && *list ; i++) {
        list = &(*list)->sig;
    }
    
    if(*list == NULL) {
        return 0;
    }

    memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));

    return 1;
}


void lista_removerDuplicados(tLista *list, const void *data, unsigned cantBytes,
        comparar comparar)
{
    int primer_copia = 0;

     while(*list && !primer_copia) {
        if(comparar((*list)->data, data) == 0) {
            primer_copia = 1;
        }
        list = &(*list)->sig;
     }

    while(*list) {
        if(comparar((*list)->data, data) == 0) {
            tLista eliminar;
            eliminar = *list;
            (*list) = (*list)->sig;

            free(eliminar->data);
            free(eliminar);
        }
        else {
            list = &(*list)->sig;
        }
    }
}


void lista_recorrer(const tLista *list, accion accion)
{
    while(*list) {
        accion((*list)->data);
        list = &(*list)->sig;
    }
}


size_t lista_buscar(const tLista *list, const void *data, unsigned cantBytes,
                comparar comparar)
{
    size_t pos = 0;

    while(*list && comparar((*list)->data, data) != 0) {
        list = &(*list)->sig;
        pos++;
    }

    if(*list == NULL) {
        pos = -1;
    }

    return pos;
}


size_t lista_contar(const tLista *list)
{
    size_t total = 0;

    while(*list) {
        list = &(*list)->sig;
        total++;
    }

    return total;
}


void lista_recorrerInvertido(const tLista *list, accion accion)
{
    tNodo *aux = *list;
    if(!aux) {
        return;
    }
    lista_recorrerInvertido(&aux->sig, accion);
    accion(aux->data);
}


tNodo **lista_buscarMenor(tLista *list, comparar comparar)
{
    tLista *menor;
    tNodo *aux = *list;
    
    if(!aux || !(aux->sig)) {
        return (aux)? list : NULL;
    }

    menor = lista_buscarMenor(&aux->sig, comparar);

    return (comparar(aux->data, (*menor)->data) < 0)? list : menor;
}


void lista_ordenarSeleccion(tLista *list, comparar comparar)
{
    tLista *menor;
    tNodo *aux;

    if(!(*list)) {
        return;
    }

    menor = lista_buscarMenor(list, comparar);

    aux = (*menor);
    (*menor) = (*menor)->sig;
    aux->sig = (*list);
    (*list) = aux;

    lista_ordenarSeleccion(&(*list)->sig, comparar);
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

/* ------------------------------------------------------------------------- */
