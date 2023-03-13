#include<lista.h>
#include<stdlib.h>
#include<stdio.h>
#include <string.h>

void crear_lista(t_lista * plista)
{
    *plista = NULL;
}


//int instertar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*), void(*acum)(t_info *, const t_info*))
//{
//    return 0;
//}

int insertarEnLista(t_lista* plista, const t_info* pinfo)
{
    t_nodo* nuevo = malloc(sizeof(t_nodo));
    t_info* elemNodo = malloc(sizeof(t_info);

    nuevo = *plista;
    *plista = nuevo->psig;

    memcpy(elemNodo, pinfo, sizeof(t_info));
    nuevo->info = elemNodo;
    return 0;
}

void recorrerLista(t_lista* lista, t_ Accion accion)
{
    while(*lista)
    {
        accion((*lista)->info, );
        lista = &(*lista)->psig;
    }
}

int sacar_primero_lista(t_lista * plista, t_info * pinfo)
{
    return 0;
}

