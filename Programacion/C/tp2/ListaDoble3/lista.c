#include"lista.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Nodo * crearNodo(const void *dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->ant = NULL;
    nue->sig = NULL;

    return nue;
}

void destruirNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(dato != NULL)
        memcpy(dato, nae->dato,MIN(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);

}

void crearLista(Lista *l)
{
    *l = NULL;
}

void vaciarLista(Lista *l)
{
    if(*l)
    {
        while((*l)->ant)
            l =&(*l)->ant;

        while(*l)
        {
            Nodo * nae = *l;
            *l =nae->sig;
            free(nae->dato);
            free(nae);
        }
    }

}


bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nodo = (Nodo *)(sizeof(Nodo));
    void * dato = malloc(tamDato);
    free(nodo);
    free(dato);

    return !nodo || !dato;
}

bool listaVacia(const Lista *l)
{
    return *l == NULL;
}


bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    if(*l)
    {
        while((*l)->ant)
            l =&(*l)->ant;

        nue->sig = *l;
        nue->ant = NULL;

        if(*l)
            (*l)->ant = nue;

        *l = nue;
    }


    return true;
}

bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    if(*l)
    {
        while((*l)->sig)
            l =&(*l)->sig;
    }


    nue->ant = *l;

    if(*l)
        (*l)->sig = nue;

    *l = nue;

    return true;
}

bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos)
{
    Nodo *nue = crearNodo(dato,tamDato);
    int i = 0;
    if(!nue)
        return false;



    if(*l)
    {
        while((*l)->ant)
            l = &(*l)->ant;

        for ( i =0 ; i<pos && (*l)->sig ; i++ )
        {
            l = &(*l)->sig;
        }

        if(i+1 < pos)
            return 0;

        // si no hay nodo siguiente esta en la posicion final
        if((*l)->sig == NULL)
        {
            nue->ant = *l;
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
        *l = nue;
    }



    return true;
}

bool eliminarDeListaAlInicio(Lista *l, void * dato, unsigned tamDato)
{
    Nodo * nae;
    if(!*l)
        return false;

    while((*l)->ant)
        l =&(*l)->ant;

    nae = *l;
    *l = nae->sig;

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
    Nodo * nae;
    int i = 0;
    if(!*l)
        return false;

    while((*l)->ant)
        l = &(*l)->ant;

    for ( i=0; i<pos && (*l) ; i++ )
    {
        l = &(*l)->sig;
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
    while((*l)->sig )
        l =&(*l)->sig;

    memcpy(dato,(*l)->dato, MIN(tamDato,(*l)->tamDato));

    return true;
}

bool verEnListaPorPos(const Lista *l, void * dato, unsigned tamDato, int pos)
{
    if(!*l)
        return false;

    while((*l)->ant)
        l =&(*l)->ant;
    for (int i =0; i<pos && (*l) ; i++ )
        l = &(*l)->sig;

    memcpy(dato,(*l)->dato,MIN(tamDato,(*l)->tamDato));

    return true;
}

void listaOrdenar(Lista *l, Cmp cmp)
{
    int desordenado;
    if(!*l)
        return;

    do
    {
        while ((*l)->ant)
            l =&(*l)->ant;

        desordenado =0;
        while ((*l)->sig)
        {
            if (cmp((*l)->dato,(*l)->sig->dato)>0)
            {
                void * dato = (*l)->dato;
                unsigned tamDato = tamDato;

                (*l)->dato = (*l)->sig->dato;
                (*l)->tamDato = (*l)->sig->tamDato;
                (*l)->sig->dato = dato;
                (*l)->sig->tamDato = tamDato;

                desordenado = 1;
            }
            l = &(*l)->sig;
        }

    }
    while (desordenado);

}

int listaBuscar(const Lista *l, void * dato, unsigned tamDato, Cmp cmp)
{
    int pos = 0;
    while((*l)->ant)
        l =&(*l)->ant;

    for (pos  = 0; *l && cmp(dato, (*l)->dato)!= 0 ; pos++ )
    {
        l = &(*l)->sig;
    }

    if(*l == NULL)
        pos = -1;

    return pos;
}

bool eliminarDuplicadosListaOrdenada(Lista *pl, Cmp cmp,Actualizar actualizar)
{
//    if(!*l)
//        return false;
//
//
//    while((*l)->ant)
//        l =&(*l)->ant;
//
//    Nodo * nae;
//    while ((*l))
//    {
//        while ((*l)->sig && cmp((*l)->dato, (*l)->sig->dato)==0)
//        {
//            nae = (*l)->sig;
//            (*l)->sig = nae->sig;
//            (*l)->sig->ant = *l;
//
//            if(actualizar)
//                actualizar((*l)->dato,nae->dato);
//
//            free(nae->dato);
//            free(nae);
//
//        }
//        (*l)->sig =
//    }
//
//    return true;
 if(*pl == NULL)
        return 0;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    Nodo* act = *pl;
    Nodo* recorre;
    Nodo* nae;

    while(act)
    {
        recorre = act->sig;

        while(recorre && cmp(act->dato, recorre->dato) == 0)
        {
            nae = recorre;
            recorre = nae->sig;

            if(actualizar)
                actualizar((*pl)->dato,nae->dato);

            free(nae->dato);
            free(nae);
        }

        act->sig = recorre;

        if(recorre)
            recorre->ant = act;

        act = act->sig;
    }

    return 1;
}

bool eliminarDuplicadosListaDesordenada(Lista *pl, Cmp cmp, Actualizar actualizar)
{
//    if(!*l)
//        return false;
//
//    while ((*l)->ant)
//        l = &(*l)->ant;
//
//    Nodo * nae;
//    Lista *lSig;
//
//    while (*l)
//    {
//        lSig =&(*l)->sig;
//        while (*lSig)
//        {
//            if(cmp((*l)->dato,(*lSig)->dato)==0)
//            {
//                nae = *lSig;
//
//                if(nae->ant)
//                    nae->ant->sig = nae->sig;
//
//                if(nae->sig)
//                    nae->sig->ant = nae->ant;
//
//                *lSig = nae->sig;
//
//                free(nae->dato);
//                free(nae);
//            }
//            else
//            {
//                lSig =&(*lSig)->sig;
//            }
//
//        }
//          l =&(*l)->sig;
//    }
//    return true;
 if(*pl == NULL)
        return 0;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    Nodo* act = *pl;
    Nodo* recorre = act->sig;
    Nodo* ant;
    Nodo* nae;

    while(act)
    {
        if(recorre)
            ant = recorre->ant;

        if(recorre && cmp(act->dato, recorre->dato) == 0)
        {
            nae = recorre;
            recorre = nae->sig;
            free(nae->dato);
            free(nae);
            ant->sig = recorre;
            if(recorre)
                recorre->ant = ant;
        }
        else if(recorre)
        {
            recorre = recorre->sig;
        }
        else
        {
            act = act->sig;
            if(act)
                recorre = act->sig;
        }

    }

    return 1;
}


void recorrerLista(const Lista *l, Accion accion,void * datosAccion)
{
    while((*l)->ant)
        l  = &(*l)->ant;

    while ((*l))
    {
        accion((*l)->dato,datosAccion);
        l =&(*l)->sig;
    }
}
