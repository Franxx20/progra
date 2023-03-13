#include "arbol.h"
#include<string.h>
#include<stdlib.h>

Nodo * crearNodo(void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo* )malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->hDer =NULL;
    nue->hIzq  = NULL;



    return nue;
}

void crearArbol(Arbol *t)
{
    *t = NULL;
}
int vaciarArbol(Arbol *t)
{
    int cne =0;
    if(!*t)
        return cne;

    cne+= vaciarArbol(&(*t)->hIzq);
    cne+=vaciarArbol(&(*t)->hDer);

    free((*t)->hIzq);
    free((*t)->hDer);

    *t = NULL;

    return cne;
}



int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp)
{
    int res;
    if(!*t)
    {
        *t = crearNodo((Nodo*)dato,tamDato);
        if(!*t)
            return ERR_SIN_MEM;
        return TODO_OK;

    }
    res = cmp(dato,(*t)->dato);
    if(res == 0)
    {
        return ERR_DUPLICADO;
    }



    return insertarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}
int buscarEnArbol(const Arbol *t, void * dato, unsigned tamDato, Cmp cmp)
{
    int res;
    if(!*t)
        return ERR_NODO;
    res = cmp(dato,(*t)->dato);
    if(res ==0)
    {
        memcpy(dato,(*t)->dato,MIN(tamDato,(*t)->tamDato));
        return TODO_OK;
    }

    return buscarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

int arbolLleno(const Arbol *t, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);

    free(nue);
    free(dato);

    return !nue || !dato;

}


int recorrerArbolEnOrden(const Arbol *t,Accion accion, void * datosAccion)
{
    if(!*t)
        return ERR_NODO;

    recorrerArbolEnOrden(&(*t)->hIzq,accion,datosAccion);

    recorrerArbolEnOrden(&(*t)->hDer,accion,datosAccion);
    accion((*t)->dato,datosAccion);


    return TODO_OK;
}

int mostrarArbolEnOrden(const Arbol *t, Mostrar mostrar)
{
    if(!*t)
        return ERR_NODO;

    mostrarArbolEnOrdenRec(t,mostrar,0);

    return TODO_OK;
}

int mostrarArbolEnOrdenRec(const Arbol *t, Mostrar mostrar, int nivel)
{
    if(!*t)
        return ERR_NODO;

    mostrarArbolEnOrdenRec(&(*t)->hIzq,mostrar,nivel +1 );
    mostrar((*t)->dato,nivel);
    mostrarArbolEnOrdenRec(&(*t)->hDer,mostrar,nivel +1);

    return TODO_OK;
}
