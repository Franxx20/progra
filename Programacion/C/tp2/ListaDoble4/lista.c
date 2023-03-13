#include"lista.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

Nodo * crearNodo(const void * dato, unsigned tamDato);
void destuirNodo(Nodo * nae, void * dato, unsigned tamDato);


Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato, dato,tamDato);
    nue->tamDato = tamDato;
    nue->ant = NULL;
    nue->sig = NULL;

    return nue;
}

void destuirNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(dato)
        memcpy(dato,nae->dato, MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);

}

void crearLista(Lista *l)
{
    *l = NULL;
}

void vaciarLista(Lista *l)
{
    NodoD * nae;
    NodoD * act = *l;
        if(act)
    {
        while(act->ant)
            act = act->ant;
    }
    while(*l)
    {
        Nodo * nae = *l;
        *l =nae->sig;
        free(nae->dato);
        free(nae);
    }
}

bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nueNodo = (Nodo *)malloc(sizeof(Nodo));
    void * nueDato =malloc(tamDato);
    free(nueNodo);
    free(nueDato);

    return !nueNodo || !nueDato;
}

bool listaVacia(const Lista *l)
{
    return  *l == NULL;
}

bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{

    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    Nodo * act = *l;
    if(act)
    {
        while(act->ant)
            act = act->ant;
    }

    nue->sig = act;

    if(act)
        act->ant = nue;

    *l =nue;



    return true;
}

bool insertarEnListaALFinal(Lista *l, const void * dato,  unsigned tamDato)
{
    Nodo * nue = crearNodo(dato, tamDato);
    if(!nue)
        return false;

    Nodo * act = *l;
    if(act)
    {
        while(act->sig)
            act = act->sig;
    }

    nue->ant = act;

    if(act)
        act->sig =nue;

    *l = nue;

    return true;
}

bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;
    int i =0;

    Nodo * act = *l;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        for (i=0; i<pos && act->sig ; i++ )
            act= act->sig;


        if(i+1<pos)
            return 0;

        if(act->sig == NULL)
            nue->ant = act;
        else
        {
            nue->sig = act;
            nue->ant = act->ant;
            if(act->ant)
            {
                act->ant->sig = nue;
            }
            act->ant = nue;
        }
    }

    *l = nue;
    return true;
}

bool verPrimeroDeLista(const Lista *l, void * dato, unsigned tamDato)
{
    Nodo * act = *l;
    if(!act)
        return false;


    while(act->ant)
        act = act->ant;

    memcpy(dato,act->dato, (tamDato,act->tamDato));



    return true;
}

bool verUltimoDelista(const Lista *l, void * dato, unsigned tamDato)
{
    Nodo * act = *l;
    if(!act)
        return false;

    while(act->sig)
        act = act->sig;

    memcpy(dato,act->dato,(tamDato,act->tamDato));

    return true;
}

bool verPosicionLista(const Lista *l, void * dato, unsigned tamDato)
{
    Nodo * act = *l;

    if(!act)
        return false;

    for (int i =0; i<pos && act; i++)
        act = act->sig;

    if(act == NULL)
        return false;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));
    return true;
}

bool eliminarDeListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * act = *l;

    if(!act)
        return false;

    while (act->Ant)
        act = act->ant;

    Nodo * nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l = nae->sig;

    destuirNodo(nae,dato,tamDato);


    return true;
}

bool eliminarDelistaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * act = *l;

    if(!act)
        return false;

    while(act->sig)
        act = act->sig;

    Nodo * nae = act;
    act = nae->sig;
    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l =nae->sig;
}

bool eliminarDeListaPorPos(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * act = *l;
    if(!act)
        return false;

    while (act->ant)
        act = act->ant;

    for (int i = 0; i<pos && act; i++ )
        act = act->sig;

    if(act == NULL)
        return false;

    Nodo * nae = act;
    act = nae->sig;

    if(nae->ant)
        nae->ant->sig = act;

    if(act)
    {
        act->ant = nae->ant;
    }



    destuirNodo(nae,dato,tamDato);
    return true;
}
