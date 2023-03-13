#include "lista2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato);
void vaciarNodo(Nodo *nae, void *dato, unsigned tamDato);

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    free(nue);
    return NULL;
  }
  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->sig = NULL;
  nue->ant = NULL;

  return nue;
}

void vaciarNodo(Nodo *nae, void *dato, unsigned tamDato) {
  if (!nae)
    return;

  memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));
  free(nae->dato);
  free(nae);
}

void crearLista(Lista *l) { *l = NULL; }

int vaciarLista(Lista *l) {
  int cne = 0;
  if (!*l)
    return cne;
  Nodo *act = *l;
  Nodo *nae;

  while (act->ant)
    act = act->ant;

  while (act) {
    nae = act;
    act = nae->sig;
    cne++;

    free(nae->dato);
    free(nae);
  }
  *l = NULL;

  return cne;
}

bool listaVacia(const Lista *l) { return *l == NULL; }

bool listaLlena(const Lista *l, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  void *dato = malloc(tamDato);
  free(nue);
  free(dato);

  return !nue || !dato;
}

bool insertarEnListaAlInicio(Lista *l, const void *dato, unsigned tamDato) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  Nodo *act = *l;
  if (act)
    while (act->ant)
      act = act->ant;

  nue->sig = act;

  if (act)
    act->ant = nue;

  *l = nue;

  return true;
}

bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  Nodo *act = *l;
  if (act)
    while (act->sig)
      act = act->sig;

  nue->ant = act;
  if (act)
    act->sig = nue;

  *l = nue;

  return true;
}

bool insertarEnListaPorPos(Lista *l, const void *dato, unsigned tamDato,
                           int pos) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  int i;
  Nodo *act = *l;

  if (act) {

    while (act->ant)
      act = act->ant;

    for (i = 0; i < pos && act->sig; i++) {
      act = act->sig;
    }

    if (i + 1 < pos)
      return false;

    if (act->sig) {
      nue->sig = act;
      nue->ant = act->ant;

      if (act->ant)
        act->ant->sig = nue;

      act->ant = nue;
    } else {
      act->sig = nue;
      nue->ant = act;
    }
  }
  *l = nue;

  return true;
}

bool verEnListaAlInicio(const Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *act = *l;
  while (act->ant)
    act = act->ant;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool verEnListaAlFinal(const Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;
  Nodo *act = *l;
  while (act->sig)
    act = act->sig;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool verEnListaPorPos(const Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;

  int i;
  Nodo *act = *l;
  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;
  Nodo *act = *l;
  Nodo *nae;

  while (act->ant)
    act = act->ant;

  nae = act;
  act = nae->sig;

  if (act)
    act->ant = NULL;

  if (nae == *l)
    *l = nae->sig;

  vaciarNodo(nae, dato, tamDato);

  return true;
}

bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *act = *l;
  Nodo *nae;

  while (act->sig)
    act = act->sig;

  nae = act;
  act = nae->ant;

  if (act)
    act->sig = NULL;

  if (nae == *l)
    *l = nae->ant;

  vaciarNodo(nae, dato, tamDato);

  return true;
}

bool eliminarDeListaPorPos(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;
  int i;

  Nodo *act = *l;
  Nodo *nae;

  while (act->ant)
    act = act->ant;

  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  if (act == NULL)
    return false;

  nae = act;
  act = nae->sig;

  if (act)
    act->ant = nae->ant;

  if (nae->ant)
    nae->ant->sig = act;

  if (nae == *l)
    *l = nae->sig;

  vaciarNodo(nae, dato, tamDato);

  return true;
}

void ordenarLista(Lista *l, Cmp cmp) {
  if (!*l)
    return;

  Nodo *act = *l;
  int ordenado;

  do {
    while (act->ant)
      act = act->ant;
    ordenado = 0;
    while (act->sig) {
      if (cmp(act->dato, act->sig->dato) < 0) {
        void *auxDato = act->dato;
        unsigned auxTam = act->tamDato;

        act->dato = act->sig->dato;
        act->tamDato = act->sig->tamDato;

        act->sig->dato = auxDato;
        act->sig->tamDato = auxTam;

        ordenado = 1;
      }

      act = act->sig;
    }

  } while (ordenado);
}

bool insertarEnlistaOrdenado(Lista *l, const void *dato, unsigned tamDato,
                             Cmp cmp, Actualizar actualizar) {
  Nodo *nue = crearNodo(dato,tamDato);
  if (!nue)
    return false;

  Nodo *act = *l;
  Nodo *sig = NULL;
  Nodo *ant = NULL;

  if (act) {
    while (act->ant && cmp((void *)dato, act->dato) < 0)
      act = act->ant;

    while (act->sig && cmp((void *)dato, act->dato) > 0)
      act = act->sig;

    int res = cmp((void *)dato, act->dato);

    if (res == 0 && actualizar)
      actualizar(act->dato, dato);

    if (res < 0) {
      sig = act;
      ant = act->ant;
    } else {
      sig = act->sig;
      ant = act;
    }
  }

  nue->sig = sig;
  nue->ant = ant;

  if (ant)
    ant->sig = nue;

  if (sig)
    sig->ant = nue;

  *l = nue;

  return true;
}

void recorrerLista(Lista *l, Accion accion, void *datosAccion) {
  if (!*l)
    return;
  Nodo *act = *l;
  while (act->ant)
    act = act->ant;

  while (act) {
    accion(act->dato, datosAccion);
    act = act->sig;
  }
}

bool buscarEnListaOrdenada(const Lista *l, void *dato, unsigned tamDato,
                           Cmp cmp) {
  if (!*l)
    return false;

  Nodo *act = *l;

  while (act->ant && cmp(dato, act->dato) < 0)
    act = act->ant;
  while (act->sig && cmp(dato, act->dato) > 0)
    act = act->sig;

  int res = cmp(dato, act->dato);

  if (res != 0)
    return false;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool buscarEnListaDesordenada(const Lista *l, void *dato, unsigned tamDato,
                              Cmp cmp) {
  if (!*l)
    return false;

  Nodo *act = *l;

  while (act->ant)
    act = act->ant;

  while (act->sig && cmp(dato, act->dato) != 0)
    act = act->sig;

  if (cmp(dato, act->dato) != 0)
    return false;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

int eliminarDuplicadosListaOrdenada(Lista *l, Cmp cmp, Actualizar actualizar) {
  if (!*l)
    return 0;

  int cne = 0;
  Nodo *act = *l;
  Nodo *sig;
  Nodo *nae;

  while (act->ant)
    act = act->ant;

  while (act) {
    sig = act->sig;
    while (sig && cmp(act->dato, sig->dato) == 0) {
      nae = sig;
      sig = nae->sig;

      if (nae == *l)
        *l = nae->ant ? nae->ant : nae->sig;

      if (nae->ant)
        nae->ant->sig = nae->sig;
      if (nae->sig)
        nae->sig->ant = nae->ant;

      if (actualizar)
        actualizar(act->dato, nae->dato);

      free(nae->dato);
      free(nae);
      cne++;
    }
    act = act->sig;
  }

  return cne;
}
int eliminarDuplicadosListaDesordenada(Lista *l, Cmp cmp,
                                       Actualizar actualizar) {
  if (!*l)
    return 0;

  int cne = 0;
  Nodo *act = *l;
  Nodo *nae;
  Nodo *sig;

  while (act->ant)
    act = act->ant;

  while (act) {
    sig = act->sig;
    while (sig) {
      if (cmp(act->dato, sig->dato) == 0) {
        nae = sig;
        sig = nae->sig;

        if (nae == *l)
          *l = nae->ant ? nae->ant : nae->sig;

        if (nae->ant)
          nae->ant->sig = nae->sig;
        if (nae->sig)
          nae->sig->ant = nae->ant;

        if (actualizar)
          actualizar(act->dato, nae->dato);

        free(nae->dato);
        free(nae);
        cne++;

      } else {
        sig = sig->sig;
      }
    }
    act = act->sig;
  }

  return cne;
}
