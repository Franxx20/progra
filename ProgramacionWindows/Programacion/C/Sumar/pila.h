#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Pila;

void crearPila(Pila *p);
void vaciarPila(Pila *p);

bool PilaVacia(const Pila *p);
bool PilaLlena(const Pila *p, unsigned tamDato);

bool ponerEnPila(Pila *p, const void *dato, unsigned tamDato);
bool sacarDePila(Pila *p, void *dato, unsigned tamDato);

bool verTope(const Pila *p, void *dato, unsigned tamDato);

#endif // PILA_H_INCLUDED
