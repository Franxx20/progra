#include "PilaDinamica2.h"
#include <stdlib.h>
#include <string.h>
void crearPila(Pila *p) { *p = NULL; }

void vaciarPila(Pila *p) {

  Nodo *auxNodo;
  while (*p) {
    auxNodo = *p;
    *p = auxNodo->sig;
    free(auxNodo->dato);
    free(auxNodo);
  }
}

bool pilaLlena(const Pila *p, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(sizeof(tamDato));

  free(auxNodo);
  free(auxDato);

  return !auxNodo || !auxDato;
}

bool pilaVacia(const Pila *p) { return *p == NULL; }

bool insertarEnPila(Pila *p, const void *dato, unsigned tamDato) {
  // verificamos que la pila no este llena
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  if (auxNodo == NULL || (auxNodo->dato = malloc(sizeof(tamDato))) == NULL) {
    free(auxNodo->dato);
    free(auxNodo);
    return false;
  }

  memcpy(auxNodo->dato, dato, tamDato);
  auxNodo->tamDato = tamDato;

  auxNodo->sig = *p;
  *p = auxNodo;

  return true;
}

bool verTopePila(const Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este vacia
  if (!(*p))
    return false;
  memcpy(dato, (*p)->dato, MENOR(tamDato, (*p)->tamDato));

  return true;
}

bool sacarDePila(Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este vacia
  if (!(*p))
    return false;

  Nodo *auxNodo = *p;
  *p = auxNodo->sig;

  memcpy(dato, auxNodo->dato, MENOR(auxNodo->tamDato, tamDato));
  free(auxNodo->dato);
  free(auxNodo);

  return true;
}
