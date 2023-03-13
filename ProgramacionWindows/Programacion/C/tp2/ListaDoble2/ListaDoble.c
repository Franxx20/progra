#include"ListaDoble.h"
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>


Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *) malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;

    }
    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->ant = NULL;
    nue->sig = NULL;

    return nue;
}

void destruirNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(dato!=NULL)
        memcpy(dato, nae->dato,MIN(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);
}

void crearLista(Lista *l)
{
    *l = NULL;
}

void vaciarLista(Lista *l, unsigned tamDato)
{

    while((*l)->ant)
        l =&(*l)->ant;

    while(*l)
    {
        Nodo * nae = *l;
        *l = nae->sig;
        free(nae->dato);
        free(nae);
    }
}


bool listaVacia(const Lista *l)
{
    return *l == NULL;
}

bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue = (Nodo * )malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);
    free(nue);
    free(dato);

    return ! nue || !dato;
}

bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    if(*l)
        while((*l)->ant)
            l = &(*l)->ant;

    nue->sig = *l;
    nue->ant = NULL;

    // el nodo que va a dejar de ser el primero ahora va a tener al nodo nuevo como el anterior

    if(*l)
        (*l)->ant = nue;

    *l = nue;


    return true;
}

bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    if(*l)
        while((*l)->sig)
            l =&(*l)->sig;

    nue->ant = *l;

    if(*l)
        (*l)->sig = nue;

    *l = nue;

    return true;
}

//bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos)
//{
//    Nodo * nue = crearNodo(dato,tamDato);
//    int i = 0;
//    if(!nue)
//        return false;
//
//    if(*l)
//    {
//        while((*l)->ant)
//            l =&(*l)->ant;
//
//        for (i = 0; i<pos && (*l)->sig ; i++)
//        {
//            l  = &(*l)->sig;
//        }
//
//        // si lo insertamos despues del actual o antes
//        if (!(*l)->sig && i+1 <= pos)
//        {
//            nue->ant = *l;
//            nue->sig = NULL;
//            (*l)->sig = nue;
//        }
//        else
//        {
//            nue->sig = *l;
//            nue->ant = (*l)->ant;
//            if((*l)->ant)
//                (*l)->ant->sig = nue;
//        }
//
//    }
//    else
//    {
//        nue->sig = NULL;
//        nue->ant = NULL;
//        (*l) = nue;
//    }
//
//
//    return true;
//}

bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos)
{
    Nodo * nue = crearNodo(dato,tamDato);

    int i = 0;
    if(!nue)
        return false;

    while(*l)
    {
        while((*)->ant)
            l = &(*l)->sig;

        if(*l)
        {
            while((*l)->ant)
                l = &(*l)->ant;

            for (i = 0 ; i<pos && (*l)->sig ; i++ )
            {
                l = &(*l)->sig;
            }

            if(i+1< pos )
                return 0;

            if(!(*l)->sig)
            {
                nue->ant = *l;
                nue->sig = NULL;
                (*l)->sig = nue;
            }
            else
            {
                nue->sig = *l;
                nue->ant = (*l)->ant;
                if((*l)->ant)
                    (*l)->ant->sig = nue;

            }
        }
        else
        {
            nue->sig = NULL;
            nue->ant = NULL;
            (*l) = nue;
        }
    }

    return true;
}

bool eliminarDeListaAlInicio(Lista *l, void * dato, unsigned tamDato)
{
    Nodo * nae;

    if(!*l)
        return false;

    while((*l)->ant)
        l =&(*l)->sig;

    nae = *l;
    *l = nae->sig;
    (*l)->ant = NULL;

    destruirNodo(nae,dato,tamDato);



    return true;
}

bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato)
{
    Nodo * nae;
    if(!*l)
        return false;
    while((*l)->sig)
        l =&(*l)->sig;


    nae = *l;
    *l = nae->ant;
    (*l)->sig = NULL;


    destruirNodo(nae,dato,tamDato);

    return true;
}

bool eliminarDeListaPorPos(Lista *l, void * dato, unsigned tamDato, int pos)
{
    Nodo *nae;
    int i;
    if(!*l)
        return false;

    while((*l)->ant)
        l = &(*l)->ant;

    for ( i =0; i<pos && (*l); i++ )
    {
        l=&(*l)->sig;
    }

    nae = *l;


    if(nae->ant)
        nae->ant->sig = nae->sig;

    if(nae->sig)
    {
        *l = nae->sig;
        (*l)->ant = nae->ant;
    }
    else
        *l = nae->ant;

    destruirNodo(nae,dato,tamDato);

    return true;
}

bool verEnListaAlInicio(const Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    while((*l)->ant)
        l =&(*l)->ant;
    memcpy(dato,(*l)->dato, MIN(tamDato,(*l)->tamDato));

    return true;
}


bool verEnlistaAlFinal(const Lista *l, void * dato, unsigned tamDato)
{

    if(!*l)
        return false;

    while((*l)->sig)
        l=&(*l)->sig;

    memcpy(dato,(*l)->dato,MIN(tamDato,(*l)->tamDato));

    return true;
}


bool verEnListaPorPos(const Lista *l, void * dato, unsigned tamDato, int pos)
{
    if(!*l)
        return false;

    while((*l)->ant)
        l = &(*l)->ant;


    for (int i = 0; i<pos && (*l) ; i++ )
    {
        l = &(*l)->sig;
    }

    memcpy(dato,(*l)->dato,MIN(tamDato,(*l)->tamDato));
    return true;
}

void listaOrdenar(Lista *l, Cmp cmp)
{
    int ordenado;
    if(!*l)
        return;
    do
    {
        while ((*l)->ant)
            l =&(*l)->ant;
        ordenado =0;
        while((*l)->sig)
        {
            if(cmp((*l)->dato, (*l)->sig->dato)>0)
            {
                void * dato = (*l)->dato;
                unsigned tamDato = (*l)->tamDato;

                (*l)->dato = (*l)->sig->dato;
                (*l)->sig->dato = dato;
                (*l)->tamDato = (*l)->sig->tamDato;
                (*l)->sig->tamDato = tamDato;

                ordenado =1 ;
            }
            *l = (*l)->sig;
        }

    }
    while (ordenado);
}

bool eliminarDuplicados(Lista *l, const void * dato, unsigned tamDato, Cmp cmp)
{

    return true;
}


void recorrerLista(const Lista *l, Accion accion, void * datosAccion )
{
    while((*l)->ant)
        l= &(*l)->ant;

    while(*l)
    {
        accion((*l)->dato,datosAccion );
        l = &(*l)->sig;
    }
}
