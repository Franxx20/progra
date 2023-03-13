#include"lista.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


Nodo * crearNodo(const void * dato, unsigned tamDato);
void destruirNodo(Nodo * nodo, void *dato, unsigned tamDato);

Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(sizeof(Nodo))))
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
void destruirNodo(Nodo * nodo, void *dato, unsigned tamDato)
{
    if(dato)
        memcpy(dato,nodo->dato,MIN(nodo->tamDato,tamDato));

    free(nodo->dato);
    free(nodo);

}


void crearLista( Lista *l)
{
    *l = NULL;
}

void vaciarLista( Lista *l)
{
    Nodo * nae;
    Nodo * act = *l;
    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            nae = act;
            act = nae->sig;

            free(nae->dato);
            free(nae);
        }
        *l = NULL;
    }
}


bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue =(Nodo *)malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);
    free(nue);
    free(dato);

    return !nue || !dato;
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
    Nodo * act =*l;
    if(act)
    {
        while(act->ant)
            act = act->ant;
    }

    nue->sig = act;
    if(act)
        act->ant = nue;

    *l = nue;

    return true;
}

bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    Nodo * act = *l;
    if(act)
        while(act->sig)
            act  = act->sig;

    nue->ant = act;
    if(act)
        act->sig = nue;
    *l = nue;


    return true;
}

bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato,int pos)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    Nodo * act = *l;
    int i;
    if(act)
    {

        while(act->ant)
            act =act->ant;
        for (i=0; i<pos && act->sig ; i++ )
            act = act->sig;

        if(i+1<pos)
            return false;

        if(act->sig == NULL)
        {
            nue->ant = act;
        }
        else
        {
            nue->sig = act;
            nue->ant = act->ant;

            if(act->ant)
                act->ant->sig = nue;

            act->ant = nue;

        }

    }

    *l = nue;
    return true;
}


bool verEnListaAlInicio(const Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    Nodo * act = *l;

    while(act->ant)
        act = act->ant;

    memcpy(dato,act->dato,MIN(act->tamDato,tamDato));

    return true;
}

bool verEnListaAlFinal(const Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    Nodo * act = *l;

    while(act->sig)
        act = act->sig;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));

    return true;
}

bool verEnListaPorPos(const Lista *l, void * dato, unsigned tamDato, int pos)
{
    if(!*l)
        return false;

    Nodo* act = *l;
    while(act->ant)
        act =act->ant;

    for (int i =0; i<pos && act ; i++ )
        act =act->sig;

    if(!act)
        return false;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));

    return true;
}

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato)
{
    if(!*l)
        return false;
    Nodo * act = *l;

    while(act->ant)
        act = act->ant;

    Nodo * nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l = nae->sig;

    destruirNodo(nae,dato,tamDato);




    return true;
}

bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;
    Nodo * act  = *l;

    while(act->sig)
        act = act->sig;

    Nodo * nae = act;
    act = nae->ant;

    if(act)
        act->sig = NULL;

    if(nae == *l)
        *l = nae->ant;

    destruirNodo(nae,dato,tamDato);

    return true;
}

bool eliminarDeListaPorPos(Lista *l, void * dato, unsigned tamDato, int pos)
{
    if(!*l)
        return false;
    Nodo *act = *l;
    while(act->ant)
        act = act->ant;
    for (int i =0 ; i<pos && act; i++ )
        act = act->sig;

    if(act == NULL)
        return false;
    Nodo * nae = act;
    act = nae->sig;

    if(nae->ant)
        nae->ant->sig = act;

    if(act)
        act->ant = nae->ant;

    if(nae == *l)
        *l = nae->sig;

    destruirNodo(nae,dato,tamDato);

    return true;
}

void ordenarLista(Lista *l, Cmp cmp)
{
    if(!*l)
        return;

    Nodo * act = *l;
    int ordenado;

    do
    {
        while(act->ant)
            act = act->ant;
        ordenado =0;

        while(act->sig)
        {
            if(cmp(act->dato,act->sig->dato)> 0)
            {
                // cambio
                void * auxDato = act->dato;
                unsigned auxTam = act->tamDato;

                act->dato = act->sig->dato;
                act->tamDato =act->sig->tamDato;

                act->sig->dato = auxDato;
                act->sig->tamDato =auxTam;
                ordenado = 1;

            }
            act =act->sig;
        }
    }
    while (ordenado);

}

bool insertarEnListaOrdenada(Lista *l, void * dato, unsigned tamDato,Cmp cmp,Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return false;

    Nodo * act  = *l;
    Nodo * sig = NULL;
    Nodo * ant = NULL;

    if(act)
    {
        while(act->ant && cmp(dato,act->dato)<0)
            act = act->ant;

        while(act->sig && cmp(dato,act->dato)>0)
            act = act->sig;

        int res = cmp(dato,act->dato);

        if(res == 0 && actualizar)
            actualizar(act->dato,dato);

        // el dato a insertar es mas chico que el actual
        if(res < 0 )
        {
            sig = act;
            ant = act->ant;
        }
        else //el dato a insertar es mas grande que el actual
        {
            sig = act->sig;
            ant = act;
        }
    }

    nue->ant = ant;
    nue->sig = sig;

    if(ant)
        ant->sig =nue;
    if(sig)
        sig->ant = nue;

    *l = nue;

    return true;
}

bool buscarEnListaOrdenada(const Lista *l, void * dato, unsigned tamDato, Cmp cmp)
{
    if(!*l)
        return  false;

    Nodo * act = *l;

    while(act->ant && cmp(dato,act->dato)<0)
        act = act->ant;

    while(act->sig && cmp(dato,act->dato)>0)
        act =act->sig;

    if(cmp(dato,act->dato)!=0)
        return false;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));


    return true;
}

bool buscarEnListaDesordenada(const Lista *l, void * dato, unsigned tamDato,Cmp cmp)
{
    if(!*l)
        return false;

    Nodo * act = *l;

    while(act->ant)
        act = act->ant;

    while(act->sig && cmp(dato,act->dato)!= 0)
        act = act->sig;

    if(cmp(dato,act->dato)!=0)
        return false;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));

    return true;
}

void recorrerLista(Lista *l, Accion accion,void *datosAccion)
{
    if(!*l)
        return;

    Nodo * act = *l;
    while(act->ant)
        act = act->ant;

    while(act->sig)
    {
        accion(act->dato,datosAccion);
        act = act->sig;
    }
}


int eliminarDuplicadosListaOrd(Lista *l, Cmp cmp,Actualizar actualizar)
{
    if(!*l)
        return 0;
    Nodo * act = *l;
    Nodo * sig;
    Nodo * nae;
    int cne =0;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        sig = act->sig;
        while(sig && cmp(act->dato,sig->dato)==0)
        {
            nae = sig;
            sig = nae->sig;

            if(nae == *l)
                *l = nae->ant?nae->ant:nae->sig;

            if(nae->ant)
                nae->ant->sig = nae->sig;

            if(nae->sig)
                nae->sig->ant = nae->ant;

            if(actualizar)
                actualizar(act->dato,nae->dato);
            free(nae->dato);
            free(nae);
            cne++;
        }
        act = act->sig;
    }


    return cne;
}

int eliminarDuplicadosListaDes(Lista *l,Cmp cmp,Actualizar actualizar)
{
    if(!*l)
        return 0;
    Nodo * act = *l;
    Nodo * sig;
    Nodo * nae;
    int cne =0;


    while(act->ant)
        act =act->ant;

    while(act)
    {
        sig = act->sig;
        while(sig)
        {
            if(cmp(act->dato,sig->dato )==0)
            {
                nae = sig;
                sig = nae->sig;
                if(nae == *l)
                    *l =nae->ant?nae->ant:nae->sig;
                if(nae->ant)
                    nae->ant->sig = nae->sig;
                if(nae->sig)
                    nae->sig->ant = nae->ant;
                if(actualizar)
                    actualizar(act->dato,nae->dato);
                free(nae->dato);
                free(nae);
                cne++;
            }
            else
            {
                sig = sig->sig;
            }
        }
        act = act->sig;
    }
    return cne;
}
