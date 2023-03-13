#include "ListaD.h"

int lista_actualizar_insertar(t_lista* pl, const t_dato_lista* pd, t_cmp cmp, t_actualizar actualizar)
{
    t_nodod* ant, *sig;
    t_nodod* nuevo;
    t_nodod* act;

    act=*pl;
    sig=ant=NULL;
    ///Busco el valor
    if(act)
    {
        while(act->psig && cmp(pd,&act->info)>0)
            act=act->psig;
        while(act->pant && cmp(pd,&act->info)<0)
            act=act->pant;
        int comp=cmp(pd,&act->info);
        if(comp>0)
        {
            ant=act;
            sig=act->psig;
        }
        else if(comp<0)
        {
            sig=act;
            ant=act->pant;
        }
        else
        {
            actualizar(&act->info,pd);
            return DUPLICADO;
        }
    }
    ///Ahora desengancho
    nuevo=(t_nodod*)malloc(sizeof(t_nodod));
    if(!nuevo)
        return SIN_MEM;
    nuevo->pant=ant;
    nuevo->psig=sig;
    nuevo->info=*pd;
    if(ant!=NULL)
        ant->psig=nuevo;
    if(sig!=NULL)
        sig->pant=nuevo;
    *pl=nuevo;
    return TODO_OK;
}

int lista_vacia(const t_lista* pl)
{
    return *pl==NULL;
}

int lista_sacar_primero(t_lista* pl, t_dato_lista* pd)
{
    if(!*pl)
        return SIN_MEM;
    t_nodod *act= *pl;

    while(act->pant)
        act = act->pant;

    *pl=act->psig; ///para que quede apuntando a algo.
    *pd = act->info;
    if(act->psig)
        act->psig->pant=NULL;

    free(act);
    return TODO_OK;
}
/** otra opción
void ordenarLista(t_lista* pLista,t_dato* dato,t_cmp cmp)
{
    t_nodo** cursor;
    t_nodo** menor;
    t_lista pLord;
    t_nodo** ultimo = &pLord;
    while(*pLista)
    {
        menor = pLista;
        cursor = &(*pLista)->sig;
        while(*cursor)
        {
            if(funcionComparacion(&(*pLista)->info,&(*cursor)->info)>0)
                menor = cursor;
            cursor = &(*cursor)->sig;
        }
        *ultimo = *menor;
        ultimo = &(*ultimo)->sig;
        menor = &(*menor)->sig;
    }
    *pLista= pLord;
}
**/

void ordenar_lista_2(t_lista* pl,t_cmp cmp)
{
    if(!*pl)
        return;

    t_nodod* act = *pl;
    t_nodod* anterior=NULL;
    t_nodod* menor;
    t_dato_lista aux;
    ///t_buscar buscarM = (orden==ASC ? buscar_menor : buscar_mayor);

    while(act->pant) ///llego al principio de la lista
        act=act->pant;

    while(act->psig)
    {
        menor=buscar_menor(&act,cmp);
        if(act==menor)
            act=act->psig;
        else
        {
            aux=act->info;
            act->info=menor->info;
            menor->info=aux;
            act=act->psig;
        }

        if(menor->psig)
            menor->psig->pant=menor->pant;

        if(menor->pant)
            menor->pant->psig=menor->psig;

        if(anterior)
            anterior->psig=menor;
    }
    act->pant=anterior;

    if(anterior)
        anterior->psig=act;
    act->psig=NULL;
    *pl=act;
}

t_nodod* buscar_menor(t_lista* pl, t_cmp cmp)
{
    t_nodod* m = *pl;
    ///t_nodod* act=&(*pl)->psig;
    while((*pl)->psig)
    {
        if(cmp(&(*pl)->info,&m->info)<0)
            m=*pl;
        pl=&(*pl)->psig;
    }
    return m;
}

t_nodod** buscar_mayor(t_lista* pl, t_cmp cmp)
{
    t_nodod** m = pl;
    t_nodod** act=&(*pl)->psig;
    while(*act)
    {
        if(cmp(&(*act)->info,&(*m)->info)>0)
            m=act;
        act=&(*act)->psig;
    }
    return m;
}


void actualizar(void* dato1, const void* dato2)
{
    t_facturasImpagasFueraTerm* d1 = (t_facturasImpagasFueraTerm*) dato1;
    t_facturasImpagasFueraTerm* d2 = (t_facturasImpagasFueraTerm*) dato2;
    d1->cantFactImpagasFueraTerm += d2->cantFactImpagasFueraTerm;
}
