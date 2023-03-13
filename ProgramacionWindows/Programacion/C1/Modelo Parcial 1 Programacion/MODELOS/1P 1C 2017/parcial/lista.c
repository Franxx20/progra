#include<lista.h>
#include<stdlib.h>

void crear_lista(t_lista * plista)
{

}

int lista_llena(const t_lista * plista)
{
    return OK;
}

int lista_vacia(const t_lista *plista)
{
    return OK;
}

int insertar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*))
{
    return OK;
}

int actualizar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*), void(*act)(t_info *, const t_info*))
{
    return OK;
}

int sacar_primero_lista(t_lista * plista, t_info * pinfo)
{
    return OK;
}


void vaciar_lista(t_lista * plista)
{

}

void recorrer_lista(const t_lista * plista, void (*acc)(t_info*, void*), void* param)
{

}
