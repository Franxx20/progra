#include"arbol.h"
#include<stdlib.h>
#include<string.h>
Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
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
        *t = crearNodo(dato,tamDato);
        if(!*t)
            return SIN_MEM;
    }

    res = cmp(dato,(*t)->dato);

    if(res == 0 )
    {
        if(actualizar)
            actualizar((*t)->dato,(void *)dato);

        return DUPLICADO;
    }

    return insertarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp,actualizar);
}

void mostrarArbolSegunNivel(const Arbol *t, Mostrar mostrar,int nivel)
{
    if(!*t)
        return;

    mostrarArbolSegunNivel(&(*t)->hIzq,mostrar,nivel-1);
    if(nivel == 0 && mostrar)
    {
        mostrar((*t)->dato,nivel);
    }
    mostrarArbolSegunNivel(&(*t)->hDer,mostrar,nivel-1);

}

int vaciarArbol(Arbol *t)
{
    int cne = 0;
    if(!*t)
        return cne;

    cne+= vaciarArbol(&(*t)->hIzq);
    cne+= vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free((*t));
    *t = NULL;

    return cne+1;

}

void crearArbol(Arbol *t)
{
    *t = NULL;
}
