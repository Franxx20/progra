#include<stdlib.h>
#include"Lista.h"
#include<string.h>
#include<stdio.h>
Nodo * crearNodo(const void * dato, unsigned tamDato)
{
    Nodo * nue = malloc(sizeof(Nodo));
    if(!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato, dato, tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;

    return nue;
}

void destruirNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(dato != NULL)
        memcpy(dato,nae->dato, MIN(nae->tamDato, tamDato));

    free(nae->dato);
    free(nae);
}

void crearLista(Lista *l)
{
    *l = NULL;
}

void vaciarLista(Lista *l)
{
    Nodo * nae;

    while(*l)
    {
        nae = *l;
        *l = nae->sig;
        free(nae->dato);
        free(nae);
    }
}

bool listaLlena(const Lista *l, unsigned tamDato)
{
    Nodo * nue = malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);

    free(nue);
    free(dato);

    return nue==NULL || dato == NULL;
}


bool listaVacia(const Lista *l)
{
    return *l == NULL;
}

bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato, tamDato);
    if(nue == NULL)
        return false;

    nue->sig = *l;
    *l= nue;

    return true;
}

bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato)
{
    Nodo * nue = crearNodo(dato, tamDato);

    if(nue == NULL)
        return false;

    while(*l)
        l = &(*l)->sig;


    *l = nue;

    return true;
}

bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos)
{
    Nodo * nue = crearNodo(dato, tamDato);
    if(nue == NULL)
        return false;

    while(*l && pos >0)
    {

        l = &(*l)->sig;
        pos--;
    }

    if(*l == NULL || pos >0)
    {
        free(nue->dato);
        free(nue);
        return false;
    }
    nue->sig= *l;
    *l = nue;

    return true;
}

bool eliminarDeListaAlPrincipio(Lista *l,void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    Nodo * nae = *l;
    *l = nae->sig;

    destruirNodo(nae,dato,tamDato);

    return true;
}
bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    while((*l)->sig)
        l = &(*l)->sig;

    Nodo * nae = *l;
    *l = nae->sig;
    destruirNodo(nae,dato, tamDato);

    return true;
}
bool eliminarDeListaPorPos(Lista *l,void * dato, unsigned tamDato, int pos)
{
    if(!*l)
        return false;
    while((*l) && pos > 0)
    {
        l = &(*l)->sig;
        pos--;
    }
    if(*l == NULL || pos>0)
    {
        return false;
    }
    Nodo * nae = *l;
    *l = nae->sig;
    destruirNodo(nae, dato, tamDato);


    return true;
}

bool verEnListaAlPrincipio(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    memcpy(dato, (*l)->dato, MIN(tamDato,(*l)->tamDato));

    return true;
}

bool verEnListaAlFinal(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    while((*l)->sig)
        l  = &(*l)->sig;

    memcpy(dato, (*l)->dato, MIN((*l)->tamDato,tamDato));

    return true;
}

bool verEnListaPorPor(Lista *l, void * dato, unsigned tamDato,int pos)
{
    if(!(*l))
        return false;
    while(*l && pos>0)
    {

        l = &(*l)->sig;
        pos--;
    }
    if(*l == NULL || pos>0)
        return false;

    memcpy(dato, (*l)->dato, MIN((*l)->tamDato, tamDato));

    return true;
}


int buscarEnListaOrd(Lista *l, void * dato, unsigned tamDato, Cmp cmp)
{
    int pos =0;

// se avanza mientras haya nodos y el nodo de la lista sea menor al nodo dato a buscar
    while(*l && cmp ((*l)->dato, dato)<0)
    {

        l =&(*l)->sig;
        pos++;
    }
    if(*l == NULL || cmp((*l)->dato, dato)>0)
        pos = -1;

    return pos;
}

int buscarEnListaDes(Lista *l, void * dato, unsigned tamDato, Cmp cmp)
{
    int pos = 0;
// se avanza mientras haya nodos y el nodo de lista sea distinto al nodo dato a buscar
    while(*l && cmp((*l)->dato, dato)!=0)
    {
        l= &(*l)->sig;
        pos++;

    }
    if(*l == NULL || cmp((*l)->dato, dato)!=0)
        pos=-1;
    return pos;
}


void ordenarLista(Lista *l, Cmp cmp)
{
    Lista lOrd= NULL;
    Lista *plOrd;
    Nodo * aux;

    while(*l)
    {
        aux = *l;
        *l = aux->sig;
        plOrd = &lOrd;
        while(*plOrd && cmp((*plOrd)->dato,aux->dato)<0 )
            plOrd =&(*plOrd)->sig;

        aux->sig = *plOrd;
        *plOrd = aux;
    }
    *l = lOrd;
}


void ordenarListaInsersion(Lista *l, Cmp cmp)
{
    Lista lOrd;
    Lista *ult = &lOrd;
    Lista *menor;

    while(*l)
    {
        menor = buscarMenorDeLista(l, cmp);
        *ult = *menor;
        *menor = (*menor)->sig;
        ult= &(*ult)->sig;
    }

    *l = lOrd;
}

Lista *buscarMenorDeLista(Lista *l, Cmp cmp)
{
    Lista *lMenor = l;
    Lista *act = &(*l)->sig;
    while(*act)
    {
        if (cmp((*lMenor)->dato,(*act)->dato)>0)
            lMenor = act;
        act = &(*act)->sig;

    }

    return lMenor;
}

void recorrerLista(Lista *l, Accion accion, void *datosAccion)
{
    while(*l)
    {
        accion((*l)->dato, datosAccion);
        l = &(*l)->sig;
    }
}

//bool eliminarDuplicadosListaOrdConAcum(Lista *l, Cmp cmp, Actualizar actualizar)
//{
//    if(!*l)
//        return false;
//    Nodo * sig;
//    while(*l)
//    {
//        sig = (*l)->sig;
//        while(sig && cmp((*l)->dato,sig->dato)==0)
//        {
//            Nodo * nae = sig;
//            if(actualizar != NULL)
//                actualizar((*l)->dato, nae->dato);
//            sig = nae->sig;
//            free(nae->dato);
//            free(nae);
//        }
//        (*l)->sig = sig;
//        l = &(*l)->sig;
//    }
//    return true;
//}
bool eliminarDuplicadosListaOrdConAcum(Lista *l, Cmp cmp, Actualizar actualizar)
{
    if(!*l)
    return false;

    Nodo * nae;

    while(*l)
    {
        while((*l)->sig && cmp((*l)->dato,(*l)->sig->dato)==0)
        {
            nae = (*l)->sig;
            (*l)->sig = nae->sig;

            if(actualizar)
                actualizar((*l)->dato, nae->dato);

            free(nae->dato);
            free(nae);

        }
        l = &(*l)->sig;
    }

    return true;
}

//bool eliminarDuplicadosListaDesConAcum(Lista *l, Cmp cmp, Actualizar actualizar)
//{
//    if(!*l)
//        return false;
//
//
//    while(*l)
//    {
//        Lista *lSig = &(*l)->sig;
//        while(*lSig)
//        {
//            if(cmp((*l)->dato,(*lSig)->dato)==0)
//            {
//                Nodo * nae = *lSig;
//                (*lSig) = nae->sig;
//                free(nae->dato);
//                free(nae);
//            }
//            else
//            {
//                lSig =&(*lSig)->sig;
//            }
//        }
//        l = &(*l)->sig;
//    }
//    return true;
//}

bool eliminarDuplicadosListaDesConAcum(Lista *l, Cmp cmp, Actualizar actualizar)
{
    if(!*l)
        return false;

    Nodo *nae;
    Lista *lSig;

    while(*l)
    {
        lSig = &(*l)->sig;
        while(*lSig)
        {
            if(cmp((*l)->dato,(*lSig)->dato)==0)
            {
                nae = *lSig;
                *lSig = nae->sig;

                free(nae->dato);
                free(nae);
            }
            else
            {
                lSig = &(*lSig)->sig;
            }

        }
        l = &(*l)->sig;
    }
    return true;
}

bool insertarEnListaOrdConAcum(Lista *l, const void * dato, unsigned tamDato,Cmp cmp, Actualizar actualizar)
{
    Nodo * nue= crearNodo(dato,tamDato);
    if(nue == NULL)
        return false;

    while(*l && cmp((*l)->dato, dato)<0)
        l =&(*l)->sig;

    if(*l && cmp ((*l)->dato,dato)==0)
    {
        if(actualizar!= NULL)
        {
            actualizar((*l)->dato, dato);
            free(nue->dato);
            free(nue);
            return true;
        }
    }
    nue->sig  = *l;
    *l = nue;



    return true;
}
bool insertarEnListaDesConAcum(Lista *l, const void * dato, unsigned tamDato, Cmp cmp, Actualizar actualizar)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(nue == NULL)
        return false;

    while(*l && cmp((*l)->dato,dato)!= 0)
        l = &(*l)->sig;

    if(*l && cmp((*l)->dato,dato)== 0)
    {
        if(actualizar != NULL)
        {
            actualizar((*l)->dato,dato);
            free(nue->dato);
            free(nue);
            return true;
        }
    }
    nue->sig = *l;
    *l = nue;
    return true;
}
