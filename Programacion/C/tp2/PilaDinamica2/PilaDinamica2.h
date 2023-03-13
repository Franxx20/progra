#ifndef PILADINAMICA2_H_INCLUDED
#define PILADINAMICA2_H_INCLUDED

#include <stdbool.h>
#define MENOR(a, b) ((a) < (b) ? (a) : (b))

typedef struct Snodo {
  void *dato;
  unsigned tamDato;
  struct Snodo *sig;
} Nodo;

typedef Nodo *Pila;

void crearPila(Pila *p);
void vaciarPila(Pila *p);

bool pilaLlena(const Pila *p, unsigned tamDato);
bool pilaVacia(const Pila *p);

bool insertarEnPila(Pila *p, const void *dato, unsigned tamDato);
bool verTopePila(const Pila *p, void *dato, unsigned tamDato);

bool sacarDePila(Pila *p, void *dato, unsigned tamDato);

#endif // PILADINAMICA2_H_INCLUDED
