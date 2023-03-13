#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <TipoTDA.h>
#include <PunterosAFuncion.h>


typedef struct s_nodo
{
	t_dato_lista info;
	struct s_nodo* psig;
}
t_nodo;


typedef t_nodo* t_lista;


void crear_lista(t_lista* plista);
void crear_lista_res(t_lista* plista);
int lista_insertar_en_orden_asc(t_lista* plista, const t_dato_lista* pd, t_cmp cmp);
int lista_insertar_en_orden_asc_res(t_lista* plista, const t_dato_lista* pd, t_cmp cmp);
int lista_insertar_al_final(t_lista* plista, const t_dato_lista* pd);
int lista_insertar_al_final_res(t_lista* plista, const t_dato_lista* pd);
int eliminar_de_lista(t_lista* plista, t_dato_lista* pd, t_cmp cmp);
int eliminar_de_lista_res(t_lista* plista, t_dato_lista* pd, t_cmp cmp);
void eliminar_duplicados_de_lista_ord(t_lista* plista, t_cmp cmp, t_actualizar actualizar);
void eliminar_duplicados_de_lista_ord_res(t_lista* plista, t_cmp cmp, t_actualizar actualizar);
int lista_sacar_primero(t_lista* plista, t_dato_lista* pd);
int lista_sacar_primero_res(t_lista* plista, t_dato_lista* pd);
int lista_buscar(const t_lista* plista, t_dato_lista* pd, t_cmp cmp);
int lista_buscar_res(const t_lista* plista, t_dato_lista* pd, t_cmp cmp);
int lista_actualizar_insertar(t_lista* plista, const t_dato_lista* pd, t_cmp cmp, t_actualizar actualizar);
int lista_actualizar_insertar_res(t_lista* plista, const t_dato_lista* pd, t_cmp cmp, t_actualizar actualizar);
int lista_vacia(const t_lista* plista);
int lista_vacia_res(const t_lista* plista);
int lista_llena(const t_lista* plista);
int lista_llena_res(const t_lista* plista);
void lista_ordenar_asc(t_lista* plista, t_cmp cmp);
void lista_ordenar_asc_res(t_lista* plista, t_cmp cmp);
void vaciar_lista(t_lista* plista);
void vaciar_lista_res(t_lista* plista);
void recorrer_lista(const t_lista* plista, t_accion accion, void* datos_accion);
void recorrer_lista_res(const t_lista* plista, t_accion accion, void* datos_accion);

#endif // LISTAENLAZADA_H
