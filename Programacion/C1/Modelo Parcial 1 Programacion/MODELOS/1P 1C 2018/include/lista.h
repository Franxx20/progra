#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<tipos.h>
#define OK 1
#define LISTA_LLENA 2
#define LISTA_VACIA 3

typedef int (*t_cmp_lista)(const t_info *, const t_info*);

typedef struct s_nodo{
    t_info info;
    struct s_nodo * psig;
}t_nodo;

typedef t_nodo * t_lista;

void recorrerLista(t_lista* lista, Accion accion);
void crear_lista_res(t_lista * plista);
void crear_lista(t_lista * plista);
int insertarEnLista(t_lista* plista, const t_info* pinfo);
int lista_llena_res(const t_lista * plista);
int instertar_lista_res(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*), void(*acum)(t_info *, const t_info*));
int instertar_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*), void(*acum)(t_info *, const t_info*));
int sacar_primero_lista_res(t_lista * plista, t_info * pinfo);
int sacar_primero_lista(t_lista * plista, t_info * pinfo);
void imprimir_lista_res(const t_lista * plista);
void imprimir_lista(const t_lista * plista);
void vaciar_lista_res(t_lista * plista);
void vaciar_lista(t_lista * plista);

#endif // LISTA_H_INCLUDED
