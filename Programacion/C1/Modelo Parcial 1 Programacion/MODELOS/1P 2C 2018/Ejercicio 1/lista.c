#include<lista.h>
#include<stdlib.h>
#include<string.h>

void crear_lista(t_lista *plista){
    *plista = NULL;
}

int lista_llena(const t_lista *plista){
    t_nodo *aux = (t_nodo*)malloc(sizeof(t_nodo));
    free(aux);
    return aux==NULL;
}

int lista_vacia(const t_lista *plista){
    return *plista==NULL;
}

int insertar_lista(t_lista *plista,const t_info *pinfo,int (*comp)(const t_info *, const t_info*)){
    t_nodo *nue = (t_nodo*)malloc(sizeof(t_nodo));
    if(nue == NULL)
        return LISTA_LLENA;
    while(*plista && comp(&(*plista)->info,pinfo)<0)
        plista = &(*plista)->psig;
    nue->info = *pinfo;
    nue->psig = *plista;
    *plista = nue;
    return OK;
}

int sacar_primero_lista(t_lista *plista,t_info *pinfo){
    t_nodo *elim;
    if(*plista == NULL)
        return LISTA_VACIA;
    elim = *plista;
    *pinfo = elim->info;
    *plista = elim->psig;
    free(elim);
    return OK;
}

void vaciar_lista(t_lista *plista){
    while(*plista!=NULL){
        t_nodo *elim;
        elim = *plista;
        *plista = elim->psig;
        free(elim);
    }
}

int comparar(const t_info *p1,const t_info *p2){
    return strcmp(p1->apyn,p2->apyn);
}

