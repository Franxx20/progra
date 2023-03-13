#include <stdlib.h>
#include <string.h>

#include "ListaDoble.h"

#define MINIMO(a,b) ((a) < (b) ? (a) : (b))

void crearLista(Lista* pl)
{
    *pl = NULL;
}


void vaciarLista(Lista* pl)
{
    Nodo* act = *pl;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
                Nodo* aux = act;
                act = aux->sig;
                free(aux->elem);
                free(aux);
        }
        *pl = NULL;
    }

}


int listaVacia(const Lista* pl)
{
    return *pl == NULL;
}


int listaLlena(const Lista* pl, size_t tamDato)
{
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    void* info = malloc(tamDato);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}


int insertarEnListaAlInicio(Lista *pl, const void* dato, size_t tamDato)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(nue == NULL || (nue->elem = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    Nodo* act = *pl;

    if(act)
    {
        while(act->ant)
            act = act->ant;
    }

    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;
    nue->ant = NULL;
    nue->sig = act;

    if(act)
        act->ant = nue;

    *pl = nue;

    return 1;
}


int insertarEnListaAlFinal(Lista* pl, const void* dato, size_t tamDato)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(nue == NULL || (nue->elem = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    Nodo* act = *pl;

    if(act)
    {
        while(act->sig)
            act = act->sig;
    }

    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;
    nue->ant = act;
    nue->sig = NULL;

    if(act)
        act->sig = nue;

    *pl = nue;
    return 1;
}


int insertarEnListaPosicion(Lista* pl, const void* dato, size_t tamDato, unsigned pos)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(nue == NULL || (nue->elem = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;

    Nodo* act = *pl;
    int i;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        for(i = 0; i < pos && act->sig; i++)
            act = act->sig;

        if(i+1 < pos)
            return 0;

        if(act->sig == NULL)// && i+1 <= pos)
        {
            nue->ant = act;
            nue->sig = NULL;
        }
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
    else
    {
        nue->sig = NULL;
        nue->ant = NULL;
    }
    *pl = nue;
    return 1;
}


int insertarEnListaOrd(Lista* pl, const void* dato, size_t tamDato, Cmp cmp)
{
    Nodo* act = *pl;
    Nodo* ant = NULL;
    Nodo* sig = NULL;

    if(act)
    {
        while(act->ant && cmp(act->elem, dato) > 0)
            act = act->ant;

        while(act->sig && cmp(act->elem, dato) < 0)
            act = act->sig;

        int comp = cmp(act->elem, dato);

        if(comp == 0)
            return 0;

        if(comp > 0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(nue == NULL || (nue->elem = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->elem, dato, tamDato);
    nue->tamElem = tamDato;
    nue->ant = ant;
    nue->sig = sig;

    if(ant)
        ant->sig = nue;

    if(sig)
        sig->ant = nue;

    *pl = nue;

    return 1;
}


int verPrimeroDeLista(const Lista* pl, void* dato, size_t tamDato)
{
    if(*pl == NULL)
        return 0;

    Nodo* act = *pl;

    while(act->ant)
        act = act->ant;

    memcpy(dato, act->elem, MINIMO(act->tamElem, tamDato));
    return 1;
}


int verUltimoDeLista(const Lista* pl, void* dato, size_t tamDato)
{
    if(*pl == NULL)
        return 0;

    Nodo* act = *pl;

    while(act->sig)
        act = act->sig;

    memcpy(dato, act->elem, MINIMO(act->tamElem, tamDato));
    return 1;
}


int verPosicionDeLista(const Lista* pl, void* dato, size_t tamDato, unsigned pos);


int eliminarPrimeroDeLista(Lista* pl, void* dato, size_t tamDato)
{
    Nodo* act = *pl;

    if(act == NULL)
        return 0;

    while(act->ant)
        act = act->ant;

    Nodo* nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *pl)
        *pl = nae->sig;

    memcpy(dato, nae->elem, MINIMO(nae->tamElem, tamDato));
    free(nae->elem);
    free(nae);
    return 1;
}


int eliminarUltimoDeLista(Lista* pl, void* dato, size_t tamDato)
{
    Nodo* act = *pl;

    if(act == NULL)
        return 0;

    while(act->sig)
        act = act->sig;

    Nodo* nae = act;
    act = nae->ant;

    if(act)
        act->sig = NULL;

    if(nae == *pl)
    {
        *pl = nae->ant;
    }

    memcpy(dato, nae->elem, MINIMO(nae->tamElem, tamDato));
    free(nae->elem);
    free(nae);
    return 1;
}


int eliminarPosicionDeLista(Lista* pl, void* dato, size_t tamDato, unsigned pos);


int eliminarDeListaOrd(Lista* pl, void* dato, size_t tamDato, Cmp cmp)
{
    if(*pl == NULL)
        return 0;

    Nodo* nae = *pl;

    while(nae->ant && cmp(nae->elem, dato) > 0)
        nae = nae->ant;

    while(nae->sig && cmp(nae->elem, dato) < 0)
        nae = nae->sig;

    if(cmp(nae->elem, dato) != 0)
        return 0;

    if(nae->ant)
        nae->ant->sig = nae->sig;

    if(nae->sig)
        nae->sig->ant = nae->ant;

    if(nae == *pl)
    {
        if(nae->sig)
            *pl = nae->sig;
        else
            *pl = nae->ant;
    }

    memcpy(dato, nae->elem, MINIMO(nae->tamElem, tamDato));
    free(nae->elem);
    free(nae);

    return 1;
}

int eliminarDupDeListaOrd(Lista* pl, Cmp cmp)
{
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

        while(recorre && cmp(act->elem, recorre->elem) == 0)
        {
            nae = recorre;
            recorre = nae->sig;
            free(nae->elem);
            free(nae);
        }

        act->sig = recorre;

        if(recorre)
            recorre->ant = act;

        act = act->sig;
    }

    return 1;
}


int eliminarDupDeListaDes(Lista* pl, Cmp cmp)
{
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

        if(recorre && cmp(act->elem, recorre->elem) == 0)
        {
            nae = recorre;
            recorre = nae->sig;
            free(nae->elem);
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


void recorrerLista(Lista* pl, Accion accion, void* datosAccion)
{
    Nodo* act = *pl;

    if(!act)
        return;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        accion(act->elem, datosAccion);
        act = act->sig;
    }
}


void recorrerListaInvertido(Lista* pl, Accion accion, void* datosAccion)
{
    Nodo* act = *pl;

    if(!act)
        return;

    while(act->sig)
        act = act->sig;

    while(act)
    {
        accion(act->elem, datosAccion);
        act = act->ant;
    }

}


int buscarEnListaOrd(const Lista* pl, void* dato, size_t tamDato, Cmp cmp)
{
    if(*pl == NULL)
       return 0;

    Nodo* act = *pl;

    while(act->ant && cmp(act->elem, dato) > 0)
        act = act->ant;

    while(act->sig && cmp(act->elem, dato) < 0)
        act = act->sig;

    if(cmp(act->elem, dato) != 0)
        return 0;

    memcpy(dato, act->elem, MINIMO(act->tamElem, tamDato));
    return 1;
}


void ordenarLista(Lista* pl, Cmp cmp)
{
    int ordenado;
    Nodo* act = *pl;

    if(*pl == NULL)
        return;

    do
    {
        while(act->ant)
            act = act->ant;

        ordenado = 0;

        while(act->sig)
        {
            if(cmp(act->elem, act->sig->elem) > 0)
            {
                void* aux = act->elem;
                size_t cantBytes = act->tamElem;

                act->elem = act->sig->elem;
                act->sig->elem = aux;
                act->tamElem = act->sig->tamElem;
                act->sig->tamElem = cantBytes;

                ordenado = 1;
            }
            act = act->sig;
        }
    }while(ordenado);
}
