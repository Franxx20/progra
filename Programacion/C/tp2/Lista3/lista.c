#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(void *dato, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato)))
    return NULL;

  return nue;
}

void eliminarNodo(Nodo *nae, void *dato, unsigned tamDato) {}

void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  Nodo *aux;
  while (*l) {
    aux = *l;
    (*l) = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

bool listaLlena(const Lista *l, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);

  free(auxDato);
  free(auxNodo);

  return !auxDato || !auxNodo;
}

bool listaVacia(const Lista *l) { return *l == NULL; }

bool insertarEnListaAlPrincipio(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la pila no este llena
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    fprintf(stderr, "Lista llena");
    free(nue);
    return false;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;

  nue->sig = *l;
  *l = nue;

  return true;
}

bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la lista no este llena

  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    fprintf(stderr, "Lista llena");
    free(nue);
    return false;
  }

  while (*l) {
    l = &(*l)->sig;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->sig = NULL;
  *l = nue;

  return true;
}

bool insertarEnPosicionDeLista(Lista *l, const void *dato, unsigned tamDato,
                               int pos) {
  // verificamos que la lista no este llena
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    fprintf(stderr, "Lista llena");
    free(nue);
    return false;
  }

  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }
  if ((*l) == NULL || pos > 0)
    return false;

  Nodo *nae = *l;
  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;

  nue->sig = *l;
  *l = nue;

  return true;
}

int buscarEnListaOrd(const Lista *l, void *dato, unsigned tamDato, Cmp cmp) {
  int pos = 0;

  // se avanza mientras haya nodos y el dato de la lista lista sea menor al dato
  // buscado
  while (*l && cmp((*l)->dato, dato) < 0) {
    l = &(*l)->sig;
    pos++;
  }

  // si ya no hay mas nodos o el dato de la lista es mayor al buscado lo que
  // significa que el dato buscado no existe en la lista
  if (*l == NULL || cmp((*l)->dato, dato) > 0)
    return pos = -1;

  return pos;
}

void ordenarListaInsercion(Lista *l, Cmp cmp) {
  // lista local que se borra al final
  Lista ord;
  Lista *ult = &ord;
  Lista *menor;

  while (*l) {
    menor = buscarMenorDeLista(l, cmp);
    *ult = *menor;
    *menor = (*menor)->sig;
    ult = &(*ult)->sig;
  }
  *l = ord;
}

Lista *buscarMenorDeLista(Lista *l, Cmp cmp) {
  Lista *lMenor = l;
  Lista *act = &(*l)->sig;
  while (*act) {
    if (cmp((*lMenor)->dato, (*act)->dato) > 0)
      lMenor = act;
    act = &(*act)->sig;
  }

  return lMenor;
}

bool eliminarDeListaAlPrincipio(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  Nodo *nae = *l;
  *l = nae->sig;
  memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));
  free(nae->dato);
  free(nae);

  return true;
}

bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  // nos movemos  hasta el ultimo nodo
  if ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  free((*l)->dato);
  free((*l));
  *l = NULL;

  return true;
}

bool eliminarDePosicionDeLista(Lista *l, void *dato, unsigned tamDato,
                               int pos) {
  // verificamos que la lista no este vacia
  if (!(*l) || pos < 0)
    return false;

  // nos movemos hasta el nodo indicado
  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }

  if ((*l) == NULL || pos > 0)
    return false;

  Nodo *nae = *l;
  *l = nae->sig;

  memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));
  free(nae->dato);
  free(nae);

  return true;
}

bool verEnListaAlPrincipio(const Lista *l, void *dato, unsigned tamDato) {

  // verificamos que la lista no este vacia
  if (*l == NULL)
    return false;
  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  return true;
}

bool verEnListaAlFinal(const Lista *l, void *dato, unsigned tamDato) {

  // verificamos que la lista no este vacia
  if (*l == NULL)
    return false;

  // nos movemos hasta el ultimo nodo de la lista
  while ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  return true;
}

bool verEnPosicionDeLista(const Lista *l, void *dato, int pos) {
  // verificamos que la lista no este vacia
  if (*l == NULL || pos < 0)
    return false;

  // movemos el puntero lista hasta la posición
  while (*l && pos > 0) {
  }
  return true;
}
