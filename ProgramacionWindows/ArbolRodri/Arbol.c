#include "Arbol.h"

#include <stdlib.h>
#include <string.h>

void crearArbol(Arbol *pa)
{
    *pa = NULL;
}

int insertarArbol(Arbol *pa, void* elem, size_t tamElem, Cmp cmp)
{
    tNodo* nue = malloc(sizeof(tNodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue);
        free(nue->elem);
        return -3;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pa)
    {
        *pa = nue;
        (*pa)->hDer = NULL;
        (*pa)->hIzq = NULL;
    }

    else
        insertarArbol(cmp((*pa)->elem,elem) < 0 ? &(*pa)->hDer : &(*pa)->hIzq,elem,tamElem,cmp);

    return 1;
}

int podarArbol(Arbol* pa, int nivel)
{
    if(!*pa)
        return 0;
    if(nivel== 0)
        return vaciarArbol(pa);
    return podarArbol(&(*pa)->hIzq, nivel-1) + podarArbol(&(*pa)->hDer,nivel-1);
}

int vaciarArbol(Arbol *pa)
{
    if(!*pa)
        return 0;
    int cne = 0;
    cne+= vaciarArbol(&(*pa)->hIzq);
    cne+= vaciarArbol(&(*pa)->hDer);
    free((*pa)->elem);
    free((*pa));
    *pa = NULL;
    return cne +1;
}

void recorrerArbolPre(Arbol *pa, Accion accion, void* dAcc)
{
    if(!*pa)
        return;
    accion((*pa)->elem,dAcc);
    recorrerArbolPre(&(*pa)->hIzq,accion,dAcc);
    recorrerArbolPre(&(*pa)->hDer,accion,dAcc);
}
void recorrerArbolPos(Arbol *pa, Accion accion, void* dAcc)
{
    if(!*pa)
        return;
    recorrerArbolPos(&(*pa)->hIzq,accion,dAcc);
    recorrerArbolPos(&(*pa)->hDer,accion,dAcc);
    accion((*pa)->elem,dAcc);
}
void recorrerArbolEn(Arbol *pa, Accion accion, void* dAcc)
{
    if(!*pa)
        return;
    recorrerArbolEn(&(*pa)->hIzq,accion,dAcc);
    accion((*pa)->elem,dAcc);
    recorrerArbolEn(&(*pa)->hDer,accion,dAcc);
}

void cargarArbolDeArchivoOrd(Arbol *pa, FILE *pf, size_t tamElem, int li, int ls, Cmp cmp, Insertar insertar)
{
    if(li > ls)
        return;

    int m = (li+ls)/2;
    fseek(pf,m*tamElem,SEEK_SET);

    void* reg = malloc(tamElem);
    if(!reg)
    {
        free(reg);
        return;
    }

    fread(reg,tamElem,1,pf);
    insertarArbol(pa,reg,tamElem,cmp);
    ///insertar(pa,pf,tamElem,cmp);
    cargarArbolDeArchivoOrd(pa,pf,tamElem,li,m-1,cmp,insertar);
    cargarArbolDeArchivoOrd(pa,pf,tamElem,m+1,ls,cmp,insertar);
}
