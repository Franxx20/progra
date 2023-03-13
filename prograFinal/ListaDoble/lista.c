#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato);
void destruirNodo(Nodo *nae, void *dato, unsigned tamDato);

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  if (!nodo || !(nodo->dato = malloc(sizeof(tamDato)))) {
    free(nodo);
    return NULL;
  }
  memcpy(nodo->dato, dato, tamDato);
  nodo->tamDato = tamDato;
  nodo->sig = NULL;
  nodo->ant = NULL;

  return nodo;
}

void destruirNodo(Nodo *nae, void *dato, unsigned tamDato) {
  if (nae)
    memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));

  free(nae->dato);
  free(nae);
}

void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  Nodo *act = *l;
  Nodo *nae;

  if (!act)
    return;

  while (act->ant)
    act = act->ant;

  while (act) {
    nae = act;
    act = nae->sig;

    free(nae->dato);
    free(nae);
  }

  *l = NULL;
}
bool listaVacia(const Lista *l) { return *l == NULL; }

bool listaLlena(const Lista *l, unsigned tamDato) {
  void *nueNodo = (Nodo *)malloc(sizeof(Nodo));
  void *dato = malloc(tamDato);
  // si la memoria esta llena entonces alguno de los punteros va a tener un NULL

  free(nueNodo);
  free(dato);
  // si se hace free sobre un puntero nulo  la funcion no va a hacer nada

  // va va a ser verdadero si alguno de los punteros era NULL
  return !nueNodo || !dato;
}

bool insertarEnListaAlInicio(Lista *l, const void *dato, unsigned tamDato) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  Nodo *act = *l;
  if (act) {
    while (act->ant)
      act = act->ant;
  }

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
  if (act) {
    while (act->sig)
      act = act->sig;
  }

  nue->ant = act;
  if (act)
    act->sig = nue;

  *l = nue;

  return true;
}

bool insertarEnListaPorPos(Lista *l, const void *dato, unsigned tamDato,
                           int pos) {
  Nodo *nue = crearNodo(dato, tamDato);
  int i;

  if (!nue)
    return false;
  Nodo *act = *l;

  if (act) {
    while (act->ant)
      act = act->ant;

    for (i = 0; i < pos && act->sig; i++) {
      act = act->sig;
    }

    if (i + 1 < pos)
      return false;

    if (act->sig == NULL) {
      act->sig = nue;
      nue->ant = act;
    } else {
      nue->sig = act;
      nue->ant = act->ant;

      if (act->ant)
        act->ant->sig = nue;

      act->ant = nue;
    }
  }

  *l = nue;

  return true;
}

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;
  Nodo *act = *l;

  while (act->ant)
    act = act->ant;

  Nodo *nae = act;
  act = nae->sig;

  if (act)
    act->ant = NULL;

  if (nae == *l)
    *l = nae->sig;

  destruirNodo(nae, dato, tamDato);

  return true;
}

bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *act = *l;

  while (act->sig)
    act = act->sig;

  Nodo *nae = act;
  act = nae->ant;

  if (act)
    act->sig = NULL;

  if (nae == *l)
    *l = nae->ant;

  destruirNodo(nae, dato, tamDato);

  return false;
}

bool eliminarDeListaPorPos(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;
  int i;

  Nodo *act = *l;

  while (act->ant)
    act = act->ant;

  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  if (act == NULL)
    return false;

  Nodo *nae = act;
  act = nae->sig;

  if (nae->ant)
    nae->ant->sig = act;

  if (act)
    act->ant = nae->ant;

  if (nae == *l)
    *l = nae->sig;

  destruirNodo(nae, dato, tamDato);

  return true;
}

bool verEnListaAlInicio(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *act = *l;

  while (act->ant)
    act = act->ant;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool verEnListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *act = *l;
  while (act->sig)
    act = act->sig;

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

  return true;
}

bool verEnListaPosPos(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;

  int i;
  Nodo *act = *l;
  while (act->ant)
    act = act->ant;

  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  memcpy(dato, act->dato, MIN(tamDato, act->tamDato));

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
        unsigned auxTamdato = act->tamDato;

        act->dato = act->sig->dato;
        act->tamDato = act->sig->tamDato;

        act->sig->dato = auxDato;
        act->sig->tamDato = auxTamdato;

        ordenado = 1;
      }
      act = act->sig;
    }

  } while (ordenado);
}

bool insertarEnListaOrdenada(Lista *l, void *dato, unsigned tamDato, Cmp cmp,
                             Actualizar actualizar) {
  Nodo *nue = crearNodo(dato, tamDato);
  if (!nue)
    return false;

  Nodo *act = *l;
  Nodo *sig = NULL;
  Nodo *ant = NULL;

  if (act) {
    while (act->ant && cmp(dato, act->dato) < 0)
      act = act->ant;

    while (act->sig && cmp(dato, act->sig) > 0)
      act = act->sig;

    int res = cmp(dato, act->dato);
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

bool buscarEnListaOrdenada(const Lista *l, void *dato, unsigned tamDato,
                           Cmp cmp) {
  if (!*l)
    return false;
  Nodo *act = *l;

  while (act->ant && cmp(dato, act->dato) < 0)
    act = act->ant;

  while (act->sig && cmp(dato, act->dato) > 0)
    act = act->sig;

  if (cmp(dato, act->dato) != 0)
    return false;

  memcpy(dato, act->dato, MIN(act->tamDato, tamDato));

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

  memcpy(dato, act->dato, MIN(act->tamDato, tamDato));

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

int eliminarDuplicadosListaOrd(Lista *l, Cmp cmp, Actualizar actualizar) {
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
int eliminarDuplicadosListaDes(Lista *l, Cmp cmp, Actualizar actualizar) {
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
