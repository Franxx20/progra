#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool listaLlena(const Lista *l, unsigned tamDato) {
  Nodo *auxNodo = (Nodo *)malloc(sizeof(Nodo));
  void *auxDato = malloc(tamDato);

  free(auxNodo);
  free(auxDato);

  return !auxDato || !auxNodo;
}

bool ListaVacia(const Lista *l) { return *l == NULL; }

bool ponerAlComienzo(Lista *l, const void *dato, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  nue->dato = malloc(tamDato);

  if (!nue || !nue->dato) {
    free(nue);
    return false;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->sig = *l;
  *l = nue;

  return true;
}

bool sacarPrimeroLista(Lista *l, void *dato, unsigned tamDato) {
  Nodo *aux = *l;
  if (aux == NULL)
    return false;
  *l = aux->sig;
  memcpy(dato, aux->dato, MIN(aux->tamDato, tamDato));
  free(aux->dato);
  free(dato);

  return true;
}

bool verPrimeroLista(const Lista *l, void *dato, unsigned tamDato) {
  if (*l == NULL)
    return false;
  Nodo *aux = *l;

  memcpy(dato, aux->dato, MIN(aux->tamDato, tamDato));

  return true;
}

bool ponerAlFinal(Lista *l, const void *dato, unsigned tamDato) {
  // crear el nodo y el espacio para dato
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  nue->dato = malloc(tamDato);

  // verifica que el nodo y el dato se hayan creado correctamente
  if (!nue || !nue->dato) {
    free(nue->dato);
    free(nue);
    return false;
  }

  // mueve el puntero de la lista hasta el ultimo nodo(porque es como una cola)
  while (*l)
    l = &(*l)->sig;

  // copia el dato en el nuevo nodo y su tamañó
  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  // el elemento siguiente al nuevo nodo va a ser nulo
  nue->sig = NULL;
  *l = nue;
  return true;
}

int ponerAlFinalAcum(Lista *l, const void *dato, unsigned int tamDato, Cmp cmp,
                     Acumular acum) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  nue->dato = malloc(tamDato);

  if (!nue || !nue->dato) {
    free(nue->dato);
    free(nue);
    return false;
  }

  while (*l) {
    // si retorna cero significa que ambos son iguales
    if (!cmp((*l)->dato, dato))
      if (acum != NULL) {
        int rc = acum((*l)->dato, (*l)->tamDato, dato, tamDato);
        free(nue->dato);
        free(nue);
        return rc;
      }
    l = &(*l)->sig;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->sig = NULL;
  *l = nue;

  return true;
}

bool sacarUltimoLista(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;
  while ((*l)->sig)
    l = &(*l)->sig;
  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));

  free((*l)->dato);
  free((*l));

  return true;
}

bool verUltimoLista(const Lista *l, void *dato, unsigned tamDato) {
  // lo mismo que sacarUltimoLista solamente que no liberamos el ultimo nodo
  if (!*l)
    return false;

  while ((*l)->sig)
    l = &(*l)->sig;
  memcpy(dato, (*l)->dato, MIN(tamDato, (*l)->tamDato));

  return true;
}

bool insertarEnListaOrdSinDup(Lista *l, const void *dato, unsigned tamDato,
                              Cmp cmp) {

  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || (nue->dato = malloc(tamDato)) == NULL) {
    free(nue->dato);
    free(nue);
    return false;
  }

  while (*l && cmp(dato, (*l)->dato) > 0)
    l = &(*l)->sig;

  // si el elemento es duplicado
  if (*l && cmp(dato, (*l)->dato) == 0) {
    fprintf(stderr, "ERROR ELEMENTO DUPLICADO\n");
    return false;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;

  nue->sig = *l;
  *l = nue;

  return true;
}

bool insertarEnListaOrdConDup(Lista *l, const void *dato, unsigned int tamDato,
                              Cmp cmp) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || (nue->dato = malloc(sizeof(tamDato))) == NULL) {
    free(nue->dato);
    free(nue);
    return false;
  }

  while (*l && cmp(dato, (*l)->dato) > 0)
    l = &(*l)->sig;

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;

  nue->sig = *l;
  *l = nue;

  return true;
}

void ordenarListaInsercion(Lista *l, Cmp cmp) {
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
}

Lista *buscarMenorDeLista(Lista *l, Cmp cmp) {
  Lista *lMenor = l;
  Lista *lAct = &(*lMenor)->sig;
  while (*l) {
    if (cmp((*lAct)->dato, (*lMenor)->dato) < 0)
      lMenor = lAct;
    lAct = &(*lAct)->sig;
  }
  return lMenor;
}

void ordenarListaBurbujeo(Lista *l, Cmp cmp) {
  int ordenado;
  Lista *lFirst = l;
  if (!*l)
    return;
  do {
    l = lFirst;
    ordenado = 0;
    while ((*l)->sig)
      if (cmp((*l)->dato, (*l)->sig->dato) > 0) {
        Lista aux = *l;
        (*l) = (*l)->sig;
        aux->sig = (*l)->sig;
        (*l)->sig = aux;
        ordenado = 1;
      }
    l = &(*l)->sig;
  } while (ordenado);
}

bool mostrarLista(const Lista *l, int ce, Mostrar mostrar, FILE *stream) {

  for (int i = 0; i < ce; i++) {
    mostrar((*l)->dato, stream);
    l = &(*l)->sig;
  }

  return true;
}
