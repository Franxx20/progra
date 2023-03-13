#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Pila;

#endif // PILA_H_INCLUDED
