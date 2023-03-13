#ifndef LISTA_H
#define LISTA_H

#include <TipoTDA.h>
#include <Defs.h>
#include <PunterosAFuncion.h>
#include <stdio.h>
#include <stdlib.h>

#define ASC 1
#define DESC 2


typedef struct s_nodod
{
	t_dato_lista info;
	struct s_nodod* pant;
	struct s_nodod* psig;
}
t_nodod;


typedef t_nodod* t_lista;
typedef t_nodod** (*t_buscar)(t_lista*, t_cmp);

void crear_lista(t_lista* pl);
int insertar_en_lista_ord(t_lista* pl, const t_dato_lista* pd, t_cmp cmp);
int insertar_en_lista_ord_dup(t_lista* pl, const t_dato_lista* pd, t_cmp cmp);
int lista_actualizar_insertar(t_lista* pl, const t_dato_lista* pd, t_cmp cmp, t_actualizar actualizar);
int insertar_en_lista_al_final(t_lista* pl, const t_dato_lista* pd);
int lista_vacia(const t_lista* pl);
void lista_consolidar(t_lista* pl, t_cmp cmp, t_actualizar actualizar); ///Elimina los duplicados, fusionando los datos.
void lista_desordenada_eliminar_duplicados(t_lista* pl, t_cmp cmp, t_actualizar actualizar); ///Elimina los duplicados, fusionando los datos.
void recorrer_lista(const t_lista* pl, t_accion accion, void* datos_accion);
int lista_sacar_primero(t_lista* pl, t_dato_lista* pd);
void eliminar_de_lista_elementos_bajo_condicion(t_lista* pl, t_condicion condicion);
void vaciar_lista(t_lista* pl);
void ordenar_lista(t_lista* pl, t_cmp cmp, int orden);

void crear_lista_res(t_lista* pl);
int insertar_en_lista_ord_res(t_lista* pl, const t_dato_lista* pd, t_cmp cmp);
int insertar_en_lista_ord_dup_res(t_lista* pl, const t_dato_lista* pd, t_cmp cmp);
int lista_actualizar_insertar_res(t_lista* pl, const t_dato_lista* pd, t_cmp cmp, t_actualizar actualizar);
int insertar_en_lista_al_final_res(t_lista* pl, const t_dato_lista* pd);
int lista_vacia_res(const t_lista* pl);
void lista_consolidar_res(t_lista* pl, t_cmp cmp, t_actualizar actualizar); ///Elimina los duplicados, fusionando los datos.
void lista_desordenada_eliminar_duplicados_res(t_lista* pl, t_cmp cmp, t_actualizar actualizar); ///Elimina los duplicados, fusionando los datos.
void recorrer_lista_res(const t_lista* pl, t_accion accion, void* datos_accion);
int lista_sacar_primero_res(t_lista* pl, t_dato_lista* pd);
void eliminar_de_lista_elementos_bajo_condicion_res(t_lista* pl, t_condicion condicion);
void vaciar_lista_res(t_lista* pl);
void ordenar_lista_res(t_lista* pl, t_cmp cmp, int orden);
void ordenar_lista_2(t_lista* pLista,t_cmp cmp);

void actualizar(void* dato1, const void* dato2);
t_nodod* buscar_menor(t_lista* pl, t_cmp cmp);
t_nodod** buscar_mayor(t_lista* pl, t_cmp cmp);

#endif // LISTA_H
