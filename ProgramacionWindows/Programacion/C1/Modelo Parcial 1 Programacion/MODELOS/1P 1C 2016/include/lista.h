#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<tipos.h>
#define OK 1
#define LISTA_LLENA 2
#define SIN_MEMORIA 0

typedef int (*t_cmp_lista)(const t_info *, const t_info*);

typedef struct s_nodo{
    t_info info;
    struct s_nodo * psig;
}t_nodo;

typedef t_nodo * t_lista;

void crear_lista_res(t_lista * plista);
int lista_llena_res(const t_lista * plista);
int instertar_prim5_lista_res(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*));
int instertar_prim5_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*));
void imprimir_lista_res(const t_lista * plista);
void vaciar_lista_res(t_lista * plista);
int comparar(const t_info * dato1,const t_info *dato2);

#endif // LISTA_H_INCLUDED
