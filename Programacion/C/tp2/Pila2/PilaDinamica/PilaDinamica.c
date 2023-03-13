#define PILA_DINAMICA
#include "../Pila/Pila.h"
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

bool pilaLlena(const Pila *p, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);

  free(auxDato);
  free(auxNodo);

  return !auxNodo || !auxDato;
}

bool pilaVacia(const Pila *p) { return *p == NULL; }

// apila un dato en la lista
bool apilar(Pila *p, const void *dato, unsigned tamDato) {
  // verificamos que la pila no este llena
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  void *nueDato = malloc(tamDato);
  if (!nue || !nueDato) {
    free(nue);
    free(nueDato);
    return false;
  }

  memcpy(nueDato, dato, tamDato);
  nue->dato = nueDato;
  nue->tamDato = tamDato;

  nue->sig = *p;
  *p = nue;

  return true;
}

bool desapilar(Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este vacia
  if (!(*p))
    return false;

  Nodo *aux = *p;
  *p = aux->sig;

  memcpy(dato, aux->dato, MIN(tamDato, aux->tamDato));

  free(aux->dato);
  free(aux);

  return true;
}

// muestra el tope de la pila
bool verTope(const Pila *p, void *dato, unsigned tamDato) {
  // verificamos que la pila no este vacia
  if (!(*p))
    return false;
  memcpy(dato, (*p)->dato, MIN(tamDato, (*p)->tamDato));

  return true;
}
