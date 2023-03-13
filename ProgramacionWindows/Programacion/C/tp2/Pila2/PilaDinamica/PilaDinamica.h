#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef Nodo *Pila;

#endif // PILADINAMICA_H_INCLUDED
