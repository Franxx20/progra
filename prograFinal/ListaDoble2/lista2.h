#ifndef LISTA2_H_INCLUDED
#define LISTA2_H_INCLUDED
#include <stdbool.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
  struct sNodo *ant;
} Nodo;

typedef int (*Cmp)(void *d1, void *d2);
typedef void (*Actualizar)(void *actualizado, const void *actualizador);
typedef void (*Accion)(void *accion, void *datosAccion);

typedef Nodo *Lista;

void crearLista(Lista *l);
int vaciarLista(Lista *l);

bool listaVacia(const Lista *l);
bool listaLlena(const Lista *l, unsigned tamDato);

bool insertarEnListaAlInicio(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaPorPos(Lista *l, const void *dato, unsigned tamDato,
                           int pos);

bool verEnListaAlInicio(const Lista *l, void *dato, unsigned tamDato);
bool verEnListaAlFinal(const Lista *l, void *dato, unsigned tamDato);
bool verEnListaPorPos(const Lista *l, void *dato, unsigned tamDato, int pos);

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaPorPos(Lista *l, void *dato, unsigned tamDato, int pos);

void ordenarLista(Lista *l, Cmp cmp);

bool insertarEnlistaOrdenado(Lista *l, const void *dato, unsigned tamDato,
                             Cmp cmp, Actualizar actualizar);

void recorrerLista(Lista *l, Accion accion, void *datosAccion);

bool buscarEnListaOrdenada(const Lista *l, void *dato, unsigned tamDato,
                           Cmp cmp);
bool buscarEnListaDesordenada(const Lista *l, void *dato, unsigned tamDato,
                              Cmp cmp);

int eliminarDuplicadosListaOrdenada(Lista *l, Cmp cmp, Actualizar actualizar);
int eliminarDuplicadosListaDesordenada(Lista *l, Cmp cmp,
                                       Actualizar actualizar);

#endif // LISTA2_H_INCLUDED
