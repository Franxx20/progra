#include "ColaDinamica.h"
#include <stdlib.h>
#include <string.h>
void crearCola(Cola *c) {
  c->frente = NULL;
  c->fondo = NULL;
}
void vaciarCola(Cola *c) {
  while (c->frente) {
    Nodo *auxNodo = c->fondo;
    c->fondo = auxNodo->sig;
    free(auxNodo->dato);
    free(auxNodo);
  }
  c->frente = NULL;
}

bool colaLlena(const Cola *c, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);
  free(auxNodo);
  free(auxDato);

  return !auxNodo || !auxDato;
}

bool colaVacia(const Cola *c) { return c->frente == NULL; }

bool ponerEnCola(Cola *c, const void *dato, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  if (!auxNodo || !(auxNodo->dato = malloc(sizeof(tamDato)))) {
    free(auxNodo->dato);
    free(auxNodo);
    return false;
  }

  memcpy(auxNodo->dato, dato, tamDato);
  auxNodo->tamDato = tamDato;

  if (c->fondo)
    c->fondo->sig = auxNodo;
  else
    c->frente = auxNodo;

  c->fondo = auxNodo;
  return true;
}

bool verPrimeroCola(const Cola *c, void *dato, unsigned tamDato) {

  if (!(c->frente))
    return false;

  memcpy(dato, c->frente->dato, MIN(tamDato, c->frente->tamDato));

  return true;
}

bool sacarCola(Cola *c, void *dato, unsigned tamDato) {
  // verificamos que la cola no este vacia
  if (!c->frente)
    return false;

  Nodo *auxNodo = c->frente;
  c->frente = c->frente->sig;

  memcpy(dato, auxNodo->dato, MIN(tamDato, auxNodo->tamDato));
  free(auxNodo->dato);
  free(auxNodo);

  if (c->frente == NULL)
    c->fondo = NULL;

  return true;
}
