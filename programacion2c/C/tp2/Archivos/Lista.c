#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  // mientras haya un nodo
  while (*l) {
    Nodo *aux = *l;
    *l = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

bool listaVacia(const Lista *l) { return *l == NULL; }

bool listaLlena(const Lista *l, unsigned tamDato) {
  // verificamos que la lista no este llena
  Nodo *nodoAux = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);

  free(nodoAux);
  free(auxDato);

  return !nodoAux || !auxDato;
}

bool insertarAlFinal(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la lista no este llena
  Nodo *nodoAux = (Nodo *)malloc(sizeof(Nodo));

  if (!nodoAux || !(nodoAux->dato = malloc(tamDato))) {
    free(nodoAux);
    return false;
  }

  while (*l) {
    l = &(*l)->sig;
  }

  memcpy(nodoAux->dato, dato, tamDato);
  nodoAux->tamDato = tamDato;
  nodoAux->sig = NULL;
  *l = nodoAux;

  return true;
}

bool insertarAlInicio(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la lista no este llena
  Nodo *nodoAux = (Nodo *)malloc(sizeof(Nodo));

  if (!nodoAux || !(nodoAux->dato = malloc(tamDato))) {
    free(nodoAux);
    return false;
  }

  memcpy(nodoAux->dato, dato, tamDato);
  nodoAux->tamDato = tamDato;
  nodoAux->sig = *l;
  *l = nodoAux;

  return true;
}

bool verInicioLista(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  Nodo *nodoAux = *l;
  if (!nodoAux) {
    printf("Lista vacia");
    return false;
  }

  // copiamos el dato del primer nodo para poder verlo
  memcpy(dato, nodoAux->dato, MIN(tamDato, nodoAux->tamDato));

  return true;
}

bool verFinalLista(Lista *l, void *dato, unsigned tamDato) {

  // verificamos que la lista no este vacia

  // si no hay un nodo entonces la lista esta vacia
  if (!(*l)) {
    printf("Lista vacia");
    return false;
  }

  // muevo el puntero hasta el ultimo nodo de la lista
  while (*l) {
    l = &(*l)->sig;
  }

  // copiamos el dato del ultimo nodo para poder verlo
  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));

  // rajamos
  return true;
}

bool sacarAlInicio(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l)) {
    printf("Lista vacia");
    return false;
  }
  Nodo *auxNodo = *l;
  memcpy(dato, auxNodo->dato, MIN(tamDato, auxNodo->tamDato));
  *l = auxNodo->sig;

  free(auxNodo->dato);
  free(auxNodo);

  return true;
}
bool sacarAlFinal(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l)) {
    printf("Lista vacia");
    return false;
  }
  // nos movemos hasta el ultimo nodo de la lista
  while ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  free((*l)->dato);
  free((*l));

  return true;
}

bool ordenarListaSeleccion(Lista *l, Cmp cmp) {
  Lista lord;
  Lista *ult = &lord;
  Lista *lmenor;

  while (*l) {
    lmenor = buscarMenorDeLista(l, cmp);
    *ult = *lmenor;
    *lmenor = (*lmenor)->sig;
    ult = &(*ult)->sig;
  }
  *l = lord;

  return true;
}

Lista *buscarMenorDeLista(Lista *l, Cmp cmp) {
  Lista *lmenor = l;
  Lista *lAct = &(*lmenor)->sig;
  while (*lAct) {
    if (cmp((*lAct)->dato, (*lmenor)->dato) < 0)
      lmenor = lAct;
    lAct = &(*lAct)->sig;
  }

  return lmenor;
}
