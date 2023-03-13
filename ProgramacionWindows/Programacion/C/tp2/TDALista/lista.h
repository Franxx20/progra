#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#include <stdbool.h>
#include <stdio.h>

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Lista;

typedef struct {
  Nodo *primero;
  Nodo *actual;

} Iterador;

typedef int (*Cmp)(const void *, const void *);
typedef void (*Mostrar)(const void *, FILE *stream);
typedef int (*Grabar)(void *, unsigned, const void *, unsigned);
typedef int (*Acumular)(void *, unsigned, const void *, unsigned);
typedef int (*Accion)(const void *dato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool ponerAlComienzo(Lista *l, const void *dato, unsigned tamDato);
bool sacarPrimerLista(Lista *l, void *dato, unsigned tamDato);

bool verPrimeroLista(const Lista *l, void *dato, unsigned tamDato);
bool verUltimoLista(const Lista *l, void *dato, unsigned tamDato);

bool ponerAlFinal(Lista *l, const void *dato, unsigned tamDato);
int ponerAlFinalAcum(Lista *l, const void *dato, unsigned tamDato, Cmp cmp,
                     Acumular acum);
bool sacarUltimoLista(Lista *l, void *dato, unsigned tamDato);

bool mostrarLista(const Lista *l, int ce, Mostrar mostrar, FILE *stream);
unsigned contarElemLista(const Lista *l);

bool insertarEnListaOrd(Lista *l, const void *dato, unsigned tamDato, Cmp cmp);
bool insertarEnListaOrdSinDup(Lista *l, const void *dato, unsigned tamDato,
                              Cmp cmp);
bool insertarEnListaOrdConDup(Lista *l, const void *dato, unsigned tamDato,
                              Cmp cmp);
bool insertarEnListaOrdAcum(Lista *l, const void *dato, unsigned tamDato,
                            Cmp comparar, Acumular acumular);

bool buscarEnListaOrd(Lista *l, void *dato, unsigned tamDato, Cmp cmp);

void ordenarListaInsercion(Lista *l, Cmp cmp);
void ordenarListaBurbujeo(Lista *l, Cmp cmp);
Lista *buscarMenorDeLista(Lista *l, Cmp cmp);

bool eliminarDuplicadosDeListaOrd(Lista *l, Cmp cmp);

// desordenada

bool colocarEnPosicion(Lista *l, const void *dato, unsigned tamDato, bool pos);
bool sacarEnPosicion(Lista *l, void *dato, unsigned tamDato, bool pos);

bool verPosLista(Lista *l, void *dato, unsigned tamDato, bool pos);
bool ActualizarNodoPorPos(Lista *l, void *dato, unsigned tamDAto, bool pos,
                          Accion accion);

bool eliminarNultimosDeLista(Lista *l, unsigned n);
bool eliminarNprimerosDeLista(Lista *l, unsigned n);

bool buscarEnListaDes(Lista *l, void *dato, unsigned tamDato, Cmp cmp);

bool eliminarDeListaDesord(Lista *l, void *dato, unsigned tamDato, Cmp cmp);

bool eliminarDuplicadosDeListaDesord(Lista *l, Cmp cmp);
bool eliminarYmostrarYgrabarDupDeListaDesord(Lista *l, Cmp cmp, Mostrar mostrar,
                                             Grabar grabar, FILE *fp);
// void recorrerLista(Lista *l, Accion accion, void * datosAccion);

// Iterador
bool crearIterador(Iterador *it, const Lista *l);
bool primerDeLista(Iterador *it, void *dato, unsigned tamDato);
bool siguienteDeLista(Iterador *it, void *dato, unsigned tamDato);
bool haySiguienteDeLista(Iterador *it, void *elem, unsigned tamDato);
bool finLista(Iterador *it);

#endif // LISTA_H_INCLUDED
