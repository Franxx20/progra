#ifndef TDALISTA_H
#define TDALISTA_H

#include <stddef.h>

#define TODO_OK 0
#define DUPLICADO 1
#define SIN_MEMORIA 2

#define MIN(x,y) (x<y)? (x) : (y)

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Actualizar)(void* actualizado, const void* actualizador);
typedef int (*Condicion)(const void* e);
typedef void (*Accion)(void* elem, void* datosAccion);

void crear(Lista* pl);
void vaciar(Lista* pl);

int vacia(const Lista* pl);
int llena(const Lista *pl, size_t tam);
int verPrimeroLista(Lista *pl, void *dato, size_t tam);
int verUltimoLista(Lista *pl, void *dato, size_t tam);

int contarElementos(const Lista *pl);
int contarElementosPorClaveOrd(const Lista *pl, const void* dato, Cmp cmp);
int contarElementosPorClaveDesord(const Lista *pl, const void* dato, Cmp cmp);

int insertarListaOrdSinDupli(Lista* pl, const void* dato, size_t tam, Cmp cmp);
int insertarOActualizarListaOrd(Lista* pl, const void* dato, size_t tam, Cmp cmp, Actualizar act);
int insertarListaAlFinal(Lista* pl, const void* dato, size_t tam);
int insertarListaAlPrincipio(Lista* pl, const void* dato, size_t tam);
int insertarListaEnPos(Lista* pl, const void* dato, size_t tam, unsigned pos);

int buscarPosLista(const Lista* pl, const void* dato, size_t tam, Cmp cmp);
int buscarMenor(Lista *pl, Cmp cmp, void *dato, size_t tam);
int buscarMayor(Lista *pl, Cmp cmp, void *dato, size_t tam);
int buscarPorClaveGuardaDatos(const Lista* pl, void* dato, size_t tam, Cmp cmp);

int eliminarOrdPorClave(Lista* pl, void* dato, size_t tam, Cmp cmp);
int eliminarDesordPorClave(Lista* pl, void* dato, size_t tam, Cmp cmp);
int eliminarPorCondicion(Lista* pl, Condicion condicion);
int eliminarDePos(Lista* pl, void* dato, size_t tam, unsigned pos);
int eliminarPrimero(Lista* pl, void* dato, size_t tam);
int eliminarUltimo(Lista* pl, void* dato, size_t tam);
int eliminarDuplicadosListaOrdAct(Lista* pl, Cmp cmp, Actualizar actualizar);
int eliminarDuplicadosListaNoOrdAct(Lista* pl, Cmp cmp, Actualizar actualizar);
int eliminarDuplicadosListaOrd(Lista* pl, Cmp cmp);
int eliminarDuplicadosListaNoOrd(Lista* pl, Cmp cmp);

void recorrer(Lista* pl, Accion accion, void* datosAccion);

int ordenarAsc(Lista* pl, Cmp cmp);
int ordenarDesc(Lista* pl, Cmp cmp);

int top5 (Lista* pl, Cmp);


#endif // TDALISTA_H
