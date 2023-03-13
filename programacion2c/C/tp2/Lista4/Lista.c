#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nue = malloc(sizeof(Nodo));
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
  if (dato != NULL)
    memcpy(dato, nae->dato, MIN(tamDato, nae->tamDato));

  free(nae->dato);
  free(nae);
}

void crearLista(Lista *l) { *l = NULL; }

void vaciarLista(Lista *l) {
  while (*l) {
    Nodo *nae = *l;
    *l = nae->sig;
    free(nae->dato);
    free(nae);
  }
}

bool insertarEnListaAlInicio(Lista *l, const void *dato, unsigned tamDato) {
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

  while (*l)
    l = &(*l)->sig;

  *l = nue;

  return true;
}

bool insertarEnPosicionLista(Lista *l, const void *dato, unsigned tamDato,
                             int pos) {

  while (*l && pos > 0) {
    l = &(*l)->sig;
    pos--;
  }

  Nodo *nue = crearNodo(dato, tamDato);

  if ((*l == NULL || pos > 0) || !nue) {
    free(nue->dato);
    free(nue);
    return false;
  }

  nue->sig = *l;
  *l = nue;

  return true;
}

bool eliminarDeListaAlPricipio(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;

  Nodo *nae = *l;
  *l = nae->sig;
  destruirNodo(nae, &dato, tamDato);

  return true;
}

bool eliminarDeListaAlFinal(Lista *l, void *dato, unsigned tamDato) {
  if (!*l)
    return false;
  while ((*l)->sig)
    l = &(*l)->sig;

  Nodo *nae = *l;
  destruirNodo(nae, &dato, tamDato);
  return true;
}

bool eliminarDePosicionLista(Lista *l, void *dato, unsigned tamDato, int pos) {
  if (!*l)
    return false;
  while ((*l)->sig && pos > 0) {
    pos--;
    l = &(*l)->sig;
  }
  if (!*l || pos > 0)
    return false;

  Nodo *nae = *l;
  *l = nae->sig;
  destruirNodo(nae, &dato, tamDato);

  return true;
}
bool eliminarDuplicadosLista(Lista *l, unsigned tamDato, Cmp cmp) {
  if (!*l)
    return false;

  while (*l) {
    Lista *lSig = &(*l)->sig;
    while (*lSig) {
      if (cmp((*l)->dato, (*lSig)->dato) == 0) {
        Nodo *nae = *lSig;
        (*lSig) = nae->sig;
        free(nae->dato);
        free(nae);
      } else {
        lSig = &(*lSig)->sig;
      }
    }
    l = &(*l)->sig;
  }

  return true;
}

int buscarEnListaOrd(const Lista *l, void *dato, unsigned tamDato, Cmp cmp) {
  int pos = 0;
  // se avanza mientas haya nodos y el dato de la lista sea menor al dato
  // buscado
  while (*l && cmp((*l)->dato, dato) < 0) {
    l = &(*l)->sig;
    pos++;
  }

  // si no hay mas nodos o el dato de la la lista es mayor al dato buscado
  // significa que el dato buscado no existe en la lista

  if (*l == NULL || cmp((*l)->dato, dato) > 0)
    pos = -1;

  return pos;
}

int buscarEnListaDes(const Lista *l, void *dato, unsigned tamDato, Cmp cmp) {
  int pos = 0;
  while (*l && cmp((*l)->dato, dato) != 0) {
    l = &(*l)->sig;
    pos++;
  }

  if (*l == NULL || cmp((*l)->dato, dato) != 0)
    pos = -1;

  return pos;
}
void ordenarLista(Lista *l, Cmp cmp) {
  Lista lOrd = NULL;
  Lista *plOrd;
  Nodo *nodo;

  while (*l) {
    // desengancho el nodo de la lista actual
    nodo = *l;
    *l = nodo->sig;

    plOrd = &lOrd;
    while (*plOrd && cmp(nodo->dato, (*plOrd)->dato) > 0)
      plOrd = &(*plOrd)->sig;

    nodo->sig = *plOrd;
    *plOrd = nodo;
  }

  *l = lOrd;
}

void recorrerLista(Lista *l, Accion accion, void *datosAccion) {
  while (*l) {
    accion((*l)->dato, datosAccion);
    l = &(*l)->sig;
  }
}
