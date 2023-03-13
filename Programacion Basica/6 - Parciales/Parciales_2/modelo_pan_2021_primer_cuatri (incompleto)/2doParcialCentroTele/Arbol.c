#include "../include/Arbol.h"

int cargar_arbol_de_archivo_ordenado(t_arbol* pa, const char* path)
{
    int fin, result;
    FILE* pf=fopen(path,"rb");
    if(!pf)
        return ERROR_ARCHIVO;
    fseek(pf,0L,SEEK_END);
    fin=ftell(pf)/sizeof(t_dato_arbol);
    result=cargar_arbol_de_archivo_ordenado_recur(pa,pf,0,fin-1,cmpIdx);
    fclose(pf);
    return result;
}

int cargar_arbol_de_archivo_ordenado_recur(t_arbol* pa, FILE* pf, int li, int ls, t_cmp cmpIdx)
{
    t_dato_arbol pd;
    if(ls<li)
        return TODO_OK;

    int medio=(li+ls)/2;

    fseek(pf,medio*sizeof(t_dato_arbol),SEEK_SET);
    fread(&pd,sizeof(t_dato_arbol),1,pf);
    insertar_en_arbol_bin_busq(pa,&pd,cmpIdx);
    cargar_arbol_de_archivo_ordenado_recur(pa,pf,li,medio-1,cmpIdx);
    cargar_arbol_de_archivo_ordenado_recur(pa,pf,medio+1,ls,cmpIdx);
    return TODO_OK;
}


int insertar_en_arbol_bin_busq(t_arbol* pa, const t_dato_arbol* pd, t_cmp cmp)
{
    int cmpIdx;
    if(!*pa)
    {
        *pa=(t_nodo_arbol*)malloc(sizeof(t_nodo_arbol));
        if(!*pa)
            return SIN_MEM;
        (*pa)->pizq = NULL;
        (*pa)->pder = NULL;
        (*pa)->info = *pd;

        return TODO_OK;
    }
    cmpIdx=cmp(pd,&(*pa)->info);
    if(cmpIdx<0)
        return insertar_en_arbol_bin_busq(&(*pa)->pizq,pd,cmp);
    if(cmpIdx>0)
        return insertar_en_arbol_bin_busq(&(*pa)->pder,pd,cmp);
    return DUPLICADO;
}

int buscar_en_arbol_bin_busq(const t_arbol* pa, t_dato_arbol* pd, t_cmp cmp)
{
    if(!*pa)
        return SIN_MEM;

    int comparacion=cmp(pd,&(*pa)->info);
    if(comparacion==0)
        *pd=(*pa)->info;
    if(comparacion<0)
        return buscar_en_arbol_bin_busq(&(*pa)->pizq,pd,cmp);
    if(comparacion>0)
        return buscar_en_arbol_bin_busq(&(*pa)->pder,pd,cmp);

    return TODO_OK;
}

int cmpIdx(const void* dato1, const void* dato2)
{
    t_dato_arbol* d1 = (t_dato_arbol*) dato1;
    t_dato_arbol* d2 = (t_dato_arbol*) dato2;
    return d1->nroCliente - d2->nroCliente;
}
