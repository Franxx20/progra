#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef int (*Cmp)(const void *d1, const void *d2);
typedef void (*Actualizar)(void *actualizado, const void *actualizador);
typedef void (*Accion)(void *Accion, void *DatosAccion);

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

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaInicio(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnListaPorPos(Lista *l, const void *dato, unsigned tamDato,
                           int pos);

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaPorPosOrd(Lista *l, void *dato, unsigned tamDato, int pos);

bool verInicioLista(Lista *l, void *dato, unsigned tamDato);
bool verFinalLista(Lista *l, void *dato, unsigned tamDato);
bool verListaPorPor(Lista *l, void *dato, unsigned tamDato, int pos);

void ordenarLista(Lista *l, Cmp cmp);

int buscarDatoEnListaOrd(Lista *l, const void *dato, unsigned tamDato, Cmp cmp);
int buscarDatoEnListaDes(Lista *l, const void *dato, unsigned tamDato, Cmp cmp);

void recorrerLista(Lista *l, Accion accion, void *datosAccion);
#endif // LISTA_H_INCLUDED
