/* ------------------------------------------------------------------------- */
/*                           cola dinamica | cola.c                          */
/* ------------------------------------------------------------------------- */

#include "cola.h"
#include <stdlib.h>
#include <string.h>

#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

void crearCola(tCola *cola) {
  cola->pri = NULL;
  cola->ult = NULL;
}

void vaciarCola(tCola *cola) {
  tNodo *aux;

  while (cola->pri) {
    aux = cola->pri;
    cola->pri = aux->sig;
    free(aux->info);
    free(aux);
  }
  cola->ult = NULL;
}

int ponerEnCola(tCola *cola, const void *data, unsigned cantBytes) {
  tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

  if (!nuevo || !(nuevo->info = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  memcpy(nuevo->info, data, cantBytes);

  nuevo->sig = NULL;
  nuevo->tamInfo = cantBytes;

  if (!cola->pri) {
    cola->pri = nuevo;
  } else {
    cola->ult->sig = nuevo;
  }

  cola->ult = nuevo;

  return 1;
}

int sacarDeCola(tCola *cola, void *data, unsigned cantBytes) {
  tNodo *aux = cola->pri;

  if (aux == NULL) {
    return 0;
  }

  memcpy(data, aux->info, minimo(aux->tamInfo, cantBytes));
  cola->pri = aux->sig;

  free(aux->info);
  free(aux);

  if (cola->pri == NULL) {
    cola->ult = NULL;
  }

  return 1;
}

int colaLlena(const tCola *cola, unsigned cantBytes) {
  tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
  void *info = malloc(cantBytes);
  free(aux);
  free(info);
  return (aux == NULL || info == NULL);
}

int colaVacia(const tCola *cola) { return cola->pri == NULL; }

int verFrente(const tCola *cola, void *data, unsigned cantBytes) {
  if (cola->pri == NULL) {
    return 0;
  }

  memcpy(data, cola->pri->info, minimo(cantBytes, cola->pri->tamInfo));
  return 1;
}

/* ------------------------------------------------------------------------- */
