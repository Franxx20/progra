#include"listaDoble.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2


Nodo * crearNodo(const void * dato, unsigned tamDato);
void eliminarNodo(Nodo * nae, void * dato, unsigned tamDato);



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
    nue->sig = NULL;
    nue->ant = NULL;


    return nue;
}

void eliminarNodo(Nodo * nae, void * dato, unsigned tamDato)
{
    if(!nae)
        return;
    if(dato)
        memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));

    free(nae->dato);
    free(nae);

}



void crearLista(Lista *l)
{
    *l = NULL;
}


void vaciarLista(Lista *l)
{
    Nodo * act = *l;
    Nodo * nae;


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

int insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato){
  Nodo *nue = crearNodo(dato, tamDato);
    Nodo *act = *l;
  if (!nue)
    return SIN_MEM;


  if (act)
    while (act->sig)
      act = act->sig;

  nue->ant = act;
  if (act)
    act->sig = nue;

  *l = nue;

  return TODO_OK;
}

int insertarEnListaOrd(Lista *l, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar)
{
    Nodo * act = *l;
    Nodo * sig = NULL;
    Nodo * ant = NULL;
    Nodo * nue;
    int res;

    nue = crearNodo(dato,tamDato);
    if(!nue)
        return SIN_MEM;


    if(act)
    {
        while (act->ant && cmp(dato,act->dato)<0)
            act =act->ant;

        while(act->sig && cmp(dato,act->dato)>0)
            act =act->sig;

        res = cmp(dato,act->dato);

        if(res == 0)
        {
            if(actualizar)
                actualizar(act->dato,(void*)dato);

            return DUPLICADO;
        }

        if(res<0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            sig = act->sig;
            ant = act;
        }

    }
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
        sig->ant = nue;

    if(ant)
        ant->sig = nue;

    *l = nue;

    return TODO_OK;
}

int eliminarPrimeroDeLista(Lista *l, void * dato,  unsigned tamDato)
{
    Nodo * nae;
    Nodo * act = *l;

    if(!act)
        return SIN_NODOS;

    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;


    if(nae ==*l)
        *l = nae->sig;


    eliminarNodo(nae,dato,tamDato);

    return TODO_OK;
}

int listaLlena(const Lista *l, unsigned tamDato)
{
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  void *dato = malloc(tamDato);
  free(nue);
  free(dato);

  return !nue || !dato;
}
int listaVacia(const Lista *l){
 return *l == NULL;}
