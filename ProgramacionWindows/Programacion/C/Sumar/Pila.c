
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearPila(Pila *p) { *p = NULL; }

void vaciarPila(Pila *p) {
  Nodo *aux;
  while (*p) {
    aux = *p;
    *p = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

bool PilaVacia(const Pila *p) { return *p == NULL; }

bool PilaLlena(const Pila *p, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);

  free(auxNodo);
  free(auxDato);

  return !auxNodo || !auxDato;
}

bool ponerEnPila(Pila *p, const void *dato, unsigned tamDato) {
  // verificamos que la pila no este llena
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  auxNodo->dato = malloc(tamDato);
  if (!auxNodo || !(auxNodo->dato)) {
    free(auxNodo);
    return false;
  }

  memcpy(auxNodo->dato, dato, tamDato);
  auxNodo->tamDato = tamDato;

  auxNodo->sig = *p;
  *p = auxNodo;

  return true;
}

bool sacarDePila(Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este Vacia
  if (!(*p))
    return false;

  Nodo *aux = *p;
  *p = aux->sig;

  memcpy(dato, aux->dato, MIN(tamDato, aux->tamDato));
  free(aux->dato);
  free(aux);

  return true;
}

bool verTope(const Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este vacia
  if (!(*p))
    return false;

  memcpy(dato, (*p)->dato, MIN(tamDato, (*p)->tamDato));

  return true;
}
