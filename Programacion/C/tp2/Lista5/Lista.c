#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    free(nue);
    return NULL;
  }
  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->sig = NULL;

  return nue;
}

void destruirNodo(Nodo *nae, void *dato, unsigned tamDato) {
  if (!nae)
    return;

  if (dato != NULL && tamDato != -1)
    memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));
  free(nae->dato);
  free(nae);
}

void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  while (*l) {
    Nodo *nae = *l;
    *l = nae->sig;
    destruirNodo(nae, NULL, -1);
  }
}

bool listaLlena(const Lista *l, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  void *nueDato = malloc(tamDato);

  free(nue);
  free(nueDato);

  return !nue || !nueDato;
}

bool listaVacia(const Lista *l) { return *l == NULL; }

bool insertarEnListaInicio(Lista *l, const void *dato, unsigned tamDato) {

  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  nue->sig = *l;
  *l = nue;

  return true;
}

bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;
  // movemos el puntero hasta el ultimo puesto de la lista
  while (*l)
    l = &(*l)->sig;

  *l = nue;
  return true;
}

bool insertarEnListaPorPos(Lista *l, const void *dato, unsigned tamDato,
                           int pos) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;
  // movemos el puntero hasta la posicion indicada
  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }

  if (*l == NULL || pos > 0) {
    destruirNodo(nue, NULL, tamDato);
    return false;
  }
  nue->sig = *l;
  *l = nue;

  return true;
}

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *nae = *l;
  *l = nae->sig;
  destruirNodo(nae, dato, tamDato);

  return true;
}

bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  // Movemos el puntero hasta el ultimo nodo
  while ((*l)->sig)
    l = &(*l)->sig;

  Nodo *nae = *l;
  destruirNodo(nae, dato, tamDato);

  return true;
}

bool eliminarDeListaPorPosOrd(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;

  // movemos el puntero hasta la posición indicada
  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }
  if (*l == NULL || pos > 0)
    return false;

  Nodo *nae = *l;
  *l = nae->sig;
  destruirNodo(nae, dato, tamDato);

  return true;
}

bool verInicioLista(Lista *l, void *dato, unsigned tamDato) {
  if (*l)
    return false;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  return true;
}

bool verFinalLista(Lista *l, void *dato, unsigned tamDato) {
  if (*l)
    return false;

  while ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  return true;
}

bool verListaPorPor(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (*l)
    return false;

  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }

  if (*l == NULL || pos > 0)
    return false;
  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  return true;
}

void ordenarLista(Lista *l, Cmp cmp) {
  Lista lOrd;
  Lista *plOrd;
  Nodo *nodo;

  while (*l) {
    nodo = *l;
    plOrd = &lOrd;

    while (*plOrd && cmp(nodo->dato, (*plOrd)->dato) > 0)
      plOrd = &(*plOrd)->sig;

    nodo->sig = *plOrd;
    *plOrd = nodo;
  }
  *l = lOrd;
}

int buscarDatoEnListaOrd(Lista *l, const void *dato, unsigned tamDato,
                         Cmp cmp) {
  int pos = 0;
  if (!*l)
    return pos = -1;

  // 1 2 4 6 7 || 5
  while (*l && cmp((*l)->dato, dato) < 0) {
    l = &(*l)->sig;
    pos++;
  }

  if (*l == NULL || cmp((*l)->dato, dato) > 0)
    pos = -1;

  return pos;
}

int buscarDatoEnListaDes(Lista *l, const void *dato, unsigned tamDato,
                         Cmp cmp) {
  int pos = 0;
  if (!*l)
    return pos = -1;

  while (*l && cmp((*l)->dato, dato) != 0) {
    l = &(*l)->sig;
    pos++;
  }
  if (*l == NULL || cmp((*l)->dato, dato) != 0)
    pos = -1;

  return pos;
}

void recorrerLista(Lista *l, Accion accion, void *datosAccion) {
  while (*l) {
    accion((*l)->dato, datosAccion);
    l = &(*l)->sig;
  }
}

void ordenarLista2(Lista *l, Cmp cmp){
  Nodo * nodo;
  Lista lOrd=NULL;
  Lista * plOrd;

  while(*l)
  {
    nodo = *l;
    plOrd = &lOrd;
    while(*plOrd && cmp(nodo->dato,(*plOrd)->dato)>0)
      plOrd = &(*plOrd)->sig;
    nodo->sig = *plOrd;
    *plOrd = nodo;
  }
  *l = lOrd;

}