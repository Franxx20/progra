#include<lista.h>
#include<stdlib.h>
#include<stdio.h>
#include "lista.h"

void crearLista(t_lista *pl)
{
    *pl=NULL;
}

int lista_llena(const t_lista *plista)

{
    t_nodo * aux=(t_nodo*)malloc(sizeof(t_nodo));
    free(aux);
    return aux==NULL;
}


int listaVacia(const t_lista *pl)
{
    return *pl==NULL;
}

int insertar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*))
{
t_nodo *pnue;

while(*plista&&comp(pinfo,&(*plista)->info)>0)
    plista=&(*plista)->psig;

if(*plista&&comp(pinfo,&(*plista)->info)==0)
        return DUPLICADO;

pnue = (t_nodo*)malloc(sizeof(t_nodo));

if(!pnue)
return LISTA_LLENA;


pnue->info=*pinfo;
pnue->psig=*plista;
*plista=pnue;


return 1;

}

void recorrer_lista(const t_lista * plista, void (*acc)(t_info*, void*), void* param)
{

    while(*plista)
    {
        acc(&(*plista)->info,param);
        plista=&(*plista)->psig;
    }
}

int sacar_primero_lista(t_lista * plista, t_info * pinfo)
{
    t_nodo *aux;
    while(*plista)
        plista=&(*plista)->psig;

    aux=*plista;
    *pinfo=aux->info;
    *plista=aux->psig;
    free(aux);
    return 1;
}

void vaciarLista(t_lista * plista)
{
    t_nodo *aux;
    while(*plista)
    {
        aux=*plista;
        *plista=aux->psig;
        free(aux);
    }
}
