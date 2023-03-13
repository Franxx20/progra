#include"arbol.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void crearArbol(Arbol *t)
{
    *t = NULL;
}

int vaciarArbol(Arbol *t)
{
    if (!*t)
        return 0;

    int cne=0;
    cne+= vaciarArbol(&(*t)->hIzq);
    cne+=vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free((*t));

    *t = NULL;

    return cne+1;
}

int insertarEnArbol(Arbol * t, const void * dato, unsigned tamDato, Cmp cmp)
{
    Nodo * nue;
    int res;
    while (*t)
    {
        res = cmp((*t)->dato,dato);
        if(res>0)
            t = &(*t)->hIzq;

        else if(res<0)
            t = &(*t)->hDer;
        else return 0;
    }

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato=malloc(tamDato)))
    {
        free(nue);
        return 0;
    }
    nue->tamDato =tamDato;
    memcpy(nue->dato,dato,tamDato);
    nue->hIzq= NULL;
    nue->hDer = NULL;
    *t = nue;



    return 1;
}

int insertarEnArbolRec(Arbol *t, const void* dato, unsigned tamDato, Cmp cmp)
{

    Nodo * nue;
    int res;
    if(*t)
    {
        res = cmp((*t)->dato,dato);
        if(res>0)
            return insertarEnArbolRec(&(*t)->hIzq,dato, tamDato, cmp);
        if(res<0)
            return insertarEnArbolRec(&(*t)->hDer,dato,tamDato,cmp);
        return 0;
    }
    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato=malloc(tamDato)))
    {
        free(nue);
        return 0;
    }
    nue->tamDato =tamDato;
    memcpy(nue->dato,dato,tamDato);
    nue->hIzq= NULL;
    nue->hDer = NULL;
    *t = nue;

    return 1;
}

void recorrerArbolPre(Arbol *t, Accion accion, void * dAccion);
void recorrerArbolIn(Arbol *t, Accion accion, void * dAccion)
{
    if(!*t)
        return;

    recorrerArbolIn(&(*t)->hIzq,accion,dAccion);
    accion((*t)->dato,dAccion);
    recorrerArbolIn(&(*t)->hDer,accion,dAccion);
}

void recorrerArbolPos(Arbol *t, Accion accion, void * dAccion);

int podarArbol(Arbol *t, int nivel);
int contarNodosArbol(const Arbol *t);

int cargarEnArbolDeUnArchivoOrdenado(Arbol *t, int li, int ls, int tamDato, FILE *fp,Cmp cmp)
{
    if(li > ls)
        return 1;

    int m = (li+ls)/2;
    fseek(fp,m*tamDato,SEEK_SET);

    void * reg = malloc(tamDato);
    if(!reg)
    {
        free(reg);
        return 1;
    }

    fread(reg,tamDato,1,fp);
    insertarEnArbolRec(t,reg,tamDato,cmp);

    cargarEnArbolDeUnArchivoOrdenado(t,li,m-1,tamDato,fp,cmp);

    cargarEnArbolDeUnArchivoOrdenado(t,m+1,ls,tamDato,fp,cmp);

    return 0;
}

int eliminarNodoArbol(Arbol *t, void *dato, unsigned tamDato,Cmp cmp);
int eliminarRaizArbol(Arbol *t, void *dato);

Arbol * buscarEnArbol(const Arbol *t, void *dato, unsigned tamDato, Cmp cmp);


