#include<lista.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void crear_lista(t_lista *plista)
{
    *plista=NULL;
}
int instertar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*), void(*acum)(t_info *, const t_info*))
{
    int cmp;
    t_nodo* nue;
    while(*plista && (cmp=comp(pinfo,&(*plista)->info))>0)
        plista=&(*plista)->psig;
    if(!cmp)
        {
            acum(&(*plista)->info,pinfo);
            return OK;
        }
    nue=(t_nodo*)malloc(sizeof(t_nodo));
    if(!nue)
        return LISTA_LLENA;
    nue->info=*pinfo;
    nue->psig=*plista;
    *plista=nue;
    return OK;
}
int lista_vacia(t_lista *plista)
{
    return *plista==NULL;
}
int sacar_primero_lista(t_lista * plista, t_info * pinfo)
{
    t_nodo *aux;
    if(!*plista)
        return LISTA_VACIA;
    aux=*plista;
    *pinfo=aux->info;
    *plista=aux->psig;
    free(aux);
    return OK;
}

void imprimir_lista(const t_lista * plista)
{
    puts("**********************************Lista**********************************");
    while(*plista)
    {
        printf("\n%s\t%c\t%.2f",(*plista)->info.cod_cta,(*plista)->info.tipo_mov,(*plista)->info.importe);
        plista=&(*plista)->psig;
    }
}
void vaciar_lista(t_lista * plista)
{
    t_nodo *aux;
    while(*plista)
    {
        aux=*plista;
        plista=&aux->psig;
        free(aux);
    }
}
