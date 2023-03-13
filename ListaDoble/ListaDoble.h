#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include <stddef.h>


typedef struct sNodo
{
    void* elem;
    size_t tamElem;
    struct sNodo* ant,
                * sig;
}Nodo;

typedef Nodo* Lista;
typedef int(*Cmp)(const void* dato1, const void* dato2);
typedef void(*Accion)(void* accion, void* datosAccion);

void crearLista(Lista* pl);
void vaciarLista(Lista* pl);
int listaVacia(const Lista* pl);
int listaLlena(const Lista* pl, size_t tamDato);

int insertarEnListaAlInicio(Lista *pl, const void* dato, size_t tamDato);
int insertarEnListaAlFinal(Lista* pl, const void* dato, size_t tamDato);
int insertarEnListaPosicion(Lista* pl, const void* dato, size_t tamDato, unsigned pos);
int insertarEnListaOrd(Lista* pl, const void* dato, size_t tamDato, Cmp cmp);

int verPrimeroDeLista(const Lista* pl, void* dato, size_t tamDato);
int verUltimoDeLista(const Lista* pl, void* dato, size_t tamDato);
int verPosicionDeLista(const Lista* pl, void* dato, size_t tamDato, unsigned pos);

int eliminarPrimeroDeLista(Lista* pl, void* dato, size_t tamDato);
int eliminarUltimoDeLista(Lista* pl, void* dato, size_t tamDato);
int eliminarPosicionDeLista(Lista* pl, void* dato, size_t tamDato, unsigned pos);
int eliminarDeListaOrd(Lista* pl, void* dato, size_t tamDato, Cmp cmp);

int eliminarDupDeListaOrd(Lista* pl, Cmp cmp);
int eliminarDupDeListaDes(Lista* pl, Cmp cmp);

void recorrerLista(Lista* pl, Accion accion, void* datosAccion);
void recorrerListaInvertido(Lista* pl, Accion accion, void* datosAccion);

int buscarEnListaOrd(const Lista* pl, void* dato, size_t tamDato, Cmp cmp);

void ordenarLista(Lista* pl, Cmp cmp);


#endif // LISTADOBLE_H_INCLUDED
