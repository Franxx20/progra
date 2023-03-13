#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>

#define ERRDUP -3

#define MIN(a, b) ((a) < (b) ? (a) : (b))
typedef int (*Cmp)(const void *d1, const void *d2);
typedef void (*Mostrar)(const void *dato, FILE *stream);
typedef void (*Actualizar)(void *actualizado, const void *actualizador);

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Lista;

Nodo *crearNodo(const void *dato, unsigned tamDato);
void eliminarNodo(Nodo *nae, void *dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaVacia(const Lista *l);
bool listaLlena(const Lista *l, unsigned tamDato);

bool insertarAlFrente(Lista *l, const void *dato, unsigned tamDato);
bool insertarAlFondo(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaOrdSinDup(Lista *l, const void *dato, unsigned tamDato,
                              Cmp cmp, Actualizar act);

bool verAlFrente(const Lista *l, void *dato, unsigned tamDato);
bool verAlFondo(const Lista *l, void *dato, unsigned tamDato);

bool eliminarAlFrente(Lista *l, void *dato, unsigned tamDato);
bool eliminarAlFondo(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaPorValor(Lista *l, void *dato, unsigned tamDato, Cmp cmp);

// ORDENADO
int insertarOrdenado(Lista *l, const void *dato, unsigned tamDato, Cmp cmp);
int eliminarDeListaOrdenado(Lista *l, void *dato, unsigned tamDato, Cmp cmp);
void ordenarSeleccion(Lista *l, Cmp cmp);
Lista *buscarMenor(Lista *l, Cmp cmp);

int buscarEnListaOrd(Lista *l, void *dato, unsigned tamDato, Cmp cmp);

#endif // LISTA_H_INCLUDED
