#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  if (!nodo || !(nodo->dato = malloc(tamDato)))
    return NULL;

  return nodo;
}

void eliminarNodo(Nodo *nae, void *dato, unsigned tamDato) {
  memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));
  free(nae->dato);
  free(nae);
}

void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  Nodo *aux;
  while (*l) {
    aux = *l;
    *l = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

bool listaVacia(const Lista *l) { return *l == NULL; }

bool listaLlena(const Lista *l, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);
  free(auxNodo);
  free(auxDato);

  return !auxNodo || !auxDato;
}

bool insertarAlFrente(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la lista no este llena
  Nodo *nueNodo = (Nodo *)malloc(sizeof(Nodo));
  void *nueDato = malloc(tamDato);
  if (!nueNodo || !nueDato) {
    free(nueNodo);
    free(nueDato);
    return false;
  }

  nueNodo->sig = *l;
  *l = nueNodo;

  memcpy(nueDato, dato, tamDato);
  nueNodo->dato = nueDato;
  nueNodo->tamDato = tamDato;

  return true;
}
bool insertarAlFondo(Lista *l, const void *dato, unsigned tamDato) {
  // verificamos que la lista no este llena
  Nodo *nueNodo = (Nodo *)malloc(sizeof(Nodo));
  void *nueDato = malloc(tamDato);
  if (!nueNodo || !nueDato) {
    free(nueNodo);
    free(nueDato);
    return false;
  }

  while (*l)
    l = &(*l)->sig;

  (*l)->sig = nueNodo;
  nueNodo->sig = NULL;

  memcpy(nueDato, dato, tamDato);
  nueNodo->dato = nueDato;
  nueNodo->tamDato = tamDato;

  return true;
}

bool insertarEnListaOrdSinDup(Lista *l, const void *dato, unsigned tamDato,
                              Cmp cmp, Actualizar act) {
  while (*l && cmp(dato, (*l)->dato) > 0)
    l = &(*l)->sig;

  if (*l && cmp(dato, (*l)->dato) == 0) {
    act((*l)->dato, dato);
    return false;
  }

  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  nue->sig = *l;
  *l = nue;

  return true;
}

bool verAlFrente(const Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));

  return true;
}

bool verAlFondo(const Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  while ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN((*l)->tamDato, tamDato));

  return true;
}

bool eliminarAlFrente(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  Nodo *aux = *l;
  *l = aux->sig;

  memcpy(dato, aux->dato, MIN(tamDato, aux->tamDato));
  free(aux->dato);
  free(aux);

  return true;
}

bool eliminarAlFondo(Lista *l, void *dato, unsigned tamDato) {
  // verificamos que la lista no este vacia
  if (!(*l))
    return false;

  while ((*l)->sig)
    l = &(*l)->sig;

  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));
  free((*l)->dato);
  free(*l);

  return true;
}

bool eliminarDeListaPorValor(Lista *l, void *dato, unsigned tamDato, Cmp cmp) {

  // verificamos que la lista no este vacia
  if (!*l)
    return false;

  while (*l && cmp(dato, (*l)->dato) > 0) {
    l = &(*l)->sig;
  }

  if (!(*l) || cmp(dato, (*l)->dato) < 0)
    return false;
  ;

  Nodo *nae = *l;
  *l = nae->sig;
  eliminarNodo(nae, dato, tamDato);

  return true;
}

int insertarOrdenado(Lista *l, const void *dato, unsigned tamDato, Cmp cmp) {
  // verificamos que la lista no este llena
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));

  if (!nue || !(nue->dato = malloc(tamDato))) {
    free(nue);
    fprintf(stderr, "ERROR LISTA LLENA");
    return -1;
  }

  while (*l && cmp(dato, (*l)->dato) > 0) {
    l = &(*l)->sig;
  }
  // verificamos que el elemento no sea duplicado
  if (cmp(dato, (*l)->dato) == 0) {
    fprintf(stderr, "ERROR AL INSERTAR POR DATO DUPLICADO");
    return ERRDUP;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;

  nue->sig = *l;
  *l = nue;

  return 1;
}

int eliminarDeListaOrdenado(Lista *l, void *dato, unsigned tamDato, Cmp cmp) {
  // verificamos que la lista no este vacia
  if (!(*l)) {
    fprintf(stderr, "ERROR LISTA VACIA");
    return -1;
  }
  while (*l && cmp(dato, (*l)->dato) > 0)
    l = &(*l)->sig;
  // si el dato no se enceuntra en la lista o ya no quedan mas nodos
  if (!(*l)->dato || cmp(dato, (*l)->dato) < 0)
    return 0;

  Nodo *nae = *l;
  *l = nae->sig;

  memcpy(dato, nae->dato, MIN(nae->tamDato, tamDato));

  free(nae->dato);
  free(nae);

  return 1;
}

void ordenarSeleccion(Lista *l, Cmp cmp) {
  Lista lOrd;
  Lista *ult = &lOrd;
  Lista *lMenor;

  while (*l) {
    lMenor = buscarMenor(l, cmp);
    *ult = *lMenor;
    *lMenor = (*lMenor)->sig;
    ult = &(*ult)->sig;
  }
  *l = lOrd;
}

Lista *buscarMenor(Lista *l, Cmp cmp) {
  Lista *lMenor = l;
  Lista *lActual = &(*l)->sig;

  while (*lActual) {
    if (cmp((*lMenor)->dato, (*lActual)) > 0)
      lMenor = lActual;

    lActual = &(*lActual)->sig;
  }

  return lMenor;
}

int buscarEnListaOrd(Lista *l, void *dato, unsigned tamDato, Cmp cmp) {
  int pos = 0;

  while (*l && cmp(dato, ((*l)->dato)) > 0) {
    l = &(*l)->sig;
    pos++;
  }

  if (!(*l) || cmp(dato, ((*l)->dato)) < 0) {
    fprintf(stderr, "DATO NO ENCONTRADO");
    return pos = -1;
  }

  return pos;
}
