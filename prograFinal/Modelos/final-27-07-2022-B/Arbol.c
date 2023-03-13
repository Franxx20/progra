#include"Arbol.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void mostrarArbolRec(const Arbol *t, Mostrar mostrar,int nivel);
NodoA * crearNodoA(const void * dato, unsigned tamDato);


NodoA * crearNodoA(const void * dato, unsigned tamDato)
{
    NodoA * nue = (NodoA*)malloc(sizeof(NodoA));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->hIzq = NULL;
    nue->hDer = NULL;


    return nue;
}

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar)
{
    int res;
    if(!*t)
    {
        *t = crearNodoA(dato,tamDato);
        if(!*t)
            return SIN_MEM;
    }

    res = cmp(dato,(*t)->dato);
    if(res == 0)
    {
        if(actualizar)
            actualizar((*t)->dato,(void*)dato);
        return DUPLICADO;
    }

    return insertarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp,actualizar);
}
void crearArbol(Arbol *t)
{
    *t = NULL;
}
int vaciarArbol(Arbol*t)
{
    int cne =0;
    if(!*t)
        return cne;

    cne += vaciarArbol(&(*t)->hIzq);
    cne += vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free((*t));
    *t = NULL;

    return cne+1;
}
void mostrarArbolRec(const Arbol *t, Mostrar mostrar,int nivel)
{
    if(!*t)
        return ;

    mostrarArbolRec(&(*t)->hDer,mostrar,nivel+1);
    mostrar((*t)->dato,nivel);
    mostrarArbolRec(&(*t)->hIzq,mostrar,nivel+1);
}

void mostrarArbol(const Arbol *t, Mostrar mostrar)
{
    if(!*t)
        return;

    mostrarArbolRec(t,mostrar,0);
}
