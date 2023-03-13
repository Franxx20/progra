#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Lista;

typedef int (*Cmp)(const void *, const void *);
typedef void (*Mostrar)(const void *, FILE *stream);
typedef int (*Acum)(void *destino, unsigned tamOrigen, const void *origen,
                    unsigned tamDestino);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaVacia(const Lista *l);
bool listaLlena(const Lista *l, unsigned tamDato);

bool insertarAlFinal(Lista *l, const void *dato, unsigned tamDato);
bool insertarAlInicio(Lista *l, const void *dato, unsigned tamDato);

bool verInicioLista(Lista *l, void *dato, unsigned tamDato);
bool verFinalLista(Lista *l, void *dato, unsigned tamDato);

bool sacarAlInicio(Lista *l, void *dato, unsigned tamDato);
bool sacarAlFinal(Lista *l, void *dato, unsigned tamDato);

bool ordenarListaSeleccion(Lista *l, Cmp cmp);
Lista *buscarMenorDeLista(Lista *l, Cmp cmp);

#endif // LISTA_H_INCLUDED
