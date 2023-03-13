#include"ListaDoble.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato =malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}

void destruirNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(dato != NULL)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);

}


void crearLista(Lista *l)
{
    *l = NULL;
}

void vaciarLista(Lista *l)
{
    Nodo * act = *l;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            Nodo * nae = act;
            act = nae->sig;
            free(nae->dato);
            free(nae);
        }
        *l = NULL;
    }
}



bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue = (Nodo* )malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);

    free(dato);
    free(nue);

    return nue == NULL || dato== NULL;
}

bool listaVacia(const Lista *l)
{
    return *l == NULL;
}


bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(nue == NULL)
        return false;



    return true;
}
