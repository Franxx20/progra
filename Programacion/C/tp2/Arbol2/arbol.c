#include"arbol.h"

#include<string.h>
#include<stdlib.h>

Arbol *buscarNodo( Arbol *t, void * dato,  Cmp cmp);
void eliminarNodo(Arbol *pnae);
int alturaArbol(Arbol *t);
Arbol * mayorNodo(Arbol *t);
Arbol * menorNodo(Arbol *t);

Nodo* crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->hDer = NULL;
    nue->hIzq = NULL;

    return nue;
}



void crearArbol(Arbol *t)
{
    *t =  NULL;
}

int vaciarArbol(Arbol *t)
{
    if(*t == NULL)
        return 0;

    int cne  =0;
    cne += vaciarArbol(&(*t)->hIzq);
    cne +=vaciarArbol(&(*t)->hDer);

    free((*t)->dato);
    free(*t);
    *t = NULL;

    return    cne +1;
}

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato,Cmp cmp,Actualizar actualizar )
{
    // si el arbol esta vacio
    if(!*t)
    {
        *t = crearNodo(dato,tamDato);
        if(!*t)
            return SIN_MEM;

        return TODO_OK;
    }

    int res = cmp(dato, (*t)->dato);

    if(res == 0)

    {
        actualizar((*t)->dato, dato);
        return DUPLICADO;
    }

    return insertarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp,actualizar);

}

bool buscarEnArbol(const Arbol *t, void * dato, unsigned tamDato, Cmp cmp)
{
    if(!*t)
        return false;

    int res = cmp(dato, (*t)->dato);

    if(res == 0)
    {
        memcpy(dato, (*t)->dato,MIN(tamDato,(*t)->tamDato));
        return true;
    }

    return buscarEnArbol(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

bool eliminarDeArbol(Arbol *t, void * dato, unsigned tamDato, Cmp cmp, Actualizar actualizar)
{
    Arbol *pnae = buscarNodo(t,dato, cmp);
    if(!pnae)
        return false;

    memcpy(dato,(*pnae)->dato,MIN(tamDato,(*pnae)->tamDato));
    free((*pnae)->dato);

    eliminarNodo(pnae);

    return true;

}

Arbol *buscarNodo( Arbol *t, void * dato, Cmp cmp)
{
    if(!*t)
        return NULL;


    int res = cmp(dato, (*t)->dato);

    if(res == 0)
        return t;

    return buscarNodo(res<0?&(*t)->hIzq:&(*t)->hDer,dato,cmp);
}

void eliminarNodo(Arbol *pnae)
{
    if(!(*pnae)->hIzq && !(*pnae)->hDer)
    {
        free(*pnae);
        *pnae = NULL;
        return;
    }
    int hi = alturaArbol(&(*pnae)->hIzq);
    int hd = alturaArbol(&(*pnae)->hDer);

    Arbol * pnremp = hi>=hd?mayorNodo(&(*pnae)->hIzq):menorNodo(&(*pnae)->hDer);

    (*pnae)->dato = (*pnremp)->dato;
    (*pnae)->tamDato = (*pnremp)->tamDato;

    eliminarNodo(pnremp);


}

int alturaArbol(Arbol *t)
{
    if(!*t)
        return 0;
    int hi = alturaArbol(&(*t)->hIzq);
    int hd = alturaArbol(&(*t)->hDer);

    return (hi>=hd?hi:hd) +1 ;
}

Arbol * mayorNodo(Arbol *t)
{
    while((*t)->hDer)
        t = &(*t)->hDer;

    return t;
}


Arbol * menorNodo(Arbol *t)
{
    while((*t)->hIzq)
        t = &(*t)->hIzq;

    return t;
}


void recorrerArbolPre( Arbol *t, Accion accion, void * dAccion)
{
    if(*t)
    {
        accion((*t)->dato,dAccion);
        recorrerArbolPre(&(*t)->hIzq,accion,dAccion);
        recorrerArbolPos(&(*t)->hDer,accion,dAccion);
    }

}

void recorrerArbolIn( Arbol *t, Accion accion, void * dAccion)
{
    if(*t)
    {

        recorrerArbolIn(&(*t)->hIzq,accion,dAccion);
        accion((*t)->dato,dAccion);
        recorrerArbolIn(&(*t)->hDer,accion,dAccion);
    }
}

void recorrerArbolPos( Arbol *t, Accion accion,void * dAccion)
{
    if(*t)
    {

        recorrerArbolPos(&(*t)->hIzq,accion,dAccion);
        recorrerArbolPos(&(*t)->hDer,accion,dAccion);
        accion((*t)->dato,dAccion);
    }
}

bool cargarEnArbolDeUnArchivoOrdenado(Arbol *t, int li,int ls, int tamDato, FILE *fp, Cmp cmp,Actualizar actualizar)
{
    if(li>ls)
        return false;

    int mitad = (li + ls)/2;
    fseek(fp,mitad * tamDato,SEEK_SET);

    void *registro = malloc(tamDato);

    if(!registro)
    {
        free(registro);
        return false;
    }
    fread(registro,tamDato,1,fp);
    insertarEnArbol(t,registro,tamDato,cmp,actualizar);

    cargarEnArbolDeUnArchivoOrdenado(t,li,mitad-1,tamDato,fp,cmp,actualizar);
    cargarEnArbolDeUnArchivoOrdenado(t,mitad+1,ls,tamDato,fp,cmp,actualizar);

    return true;

}

int podarArbol(Arbol *t, int nivel)
{
    if(!*t)
        return 0;

    if(nivel ==0)
        return vaciarArbol(t);

    return podarArbol(&(*t)->hIzq,nivel-1) + podarArbol(&(*t)->hDer,nivel-1);
}

int contarNodoArbol(const Arbol *t)
{
    if(!*t)
        return 0;

    return contarNodoArbol(&(*t)->hIzq)  + contarNodoArbol(&(*t)->hDer ) +1;
}
