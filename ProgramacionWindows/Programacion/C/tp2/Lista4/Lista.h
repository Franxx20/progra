#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef int (*Cmp)(const void *d1, const void *d2);
typedef void (*Actualizar)(void *actualizado, const void *actualizador);
typedef void (*Accion)(void *d1, void *d2);

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Lista;

Nodo *crearNodo(const void *dato, unsigned tamDato);
void destruirNodo(Nodo *nae, void *dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(Lista *l);
bool listaVacia(Lista *l, unsigned tamDato);

bool insertarEnListaAlInicio(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnPosicionLista(Lista *l, const void *dato, unsigned tamDato,
                             int pos);

bool eliminarDeListaAlPricipio(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato);
bool eliminarDePosicionLista(Lista *l, void *dato, unsigned tamDato, int pos);
bool eliminarDuplicadosLista(Lista *l, unsigned tamDato, Cmp cmp);

int buscarEnListaOrd(const Lista *l, void *dato, unsigned tamDato, Cmp cmp);
int buscarEnListaDes(const Lista *l, void *dato, unsigned tamDato, Cmp cmp);

bool verEnListaAlPrincipio(const Lista *l, void *dato, unsigned tamDato);
bool verEnListaAlFinal(const Lista *l, void *dato, unsigned tamDato);
bool verEnPosicionLista(const Lista *l, void *dato, unsigned tamDato);

void ordenarLista(Lista *l, Cmp cmp);
void ordenarListaInsercion(Lista *l, Cmp cmp);
Lista *buscarMenorDeLista(Lista *l, Cmp cmp);

void recorrerLista(Lista *l, Accion accion, void *datosAccion);

#endif // LISTA_H_INCLUDED
