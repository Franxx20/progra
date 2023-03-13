/* ------------------------------------------------------------------------- */
/*                            lista doble | lista.c                          */
/* ------------------------------------------------------------------------- */

#include "lista.h"
#include <stdlib.h>
#include <string.h>

#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

void crearLista(tLista *list) { *list = NULL; }

int listaVacia(const tLista *list) { return *list == NULL; }

int listaLlena(const tLista *list, unsigned cantBytes) {
  tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
  void *data = malloc(cantBytes);

  free(aux);
  free(data);
  return aux == NULL || data == NULL;
}

int vaciarLista(tLista *list) {
  int cant = 0;
  tNodo *act = *list;

  if (act) {
    while (act->ant) {
      act = act->ant;
    }
    while (act) {
      tNodo *aux = act;
      act = aux->sig;
      free(aux->data);
      free(aux);
      cant++;
    }
    *list = NULL;
  }

  return cant;
}

int lista_insertarInicio(tLista *list, const void *data, unsigned cantBytes) {
  tNodo *act = *list;
  tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

  if (!nuevo || !(nuevo->data = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  if (act) {
    while (act->ant) {
      act = act->ant;
    }
  }

  memcpy(nuevo->data, data, cantBytes);
  nuevo->cantBytes = cantBytes;
  nuevo->sig = act;
  nuevo->ant = NULL;

  if (act) {
    act->ant = nuevo;
  }

  *list = nuevo;

  return 1;
}

int lista_removerPrimero(tLista *list, void *data, unsigned cantBytes) {
  tNodo *aux, *act = *list;

  if (!act) {
    return 0;
  }

  while (act->ant) {
    act = act->ant;
  }

  aux = act;
  act = act->sig;
  act->ant = NULL;
  (*list) = act;

  memcpy(data, aux->data, minimo(cantBytes, aux->cantBytes));

  free(aux->data);
  free(aux);

  return 1;
}

int lista_verPrimero(const tLista *list, void *data, unsigned cantBytes) {
  if (!(*list)) {
    return 0;
  }

  while ((*list)->ant) {
    list = &(*list)->ant;
  }

  memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));
  return 1;
}

int lista_insertarFinal(tLista *list, const void *data, unsigned cantBytes) {
  tNodo *act = *list;
  tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

  if (!nuevo || !(nuevo->data = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  if (act) {
    while (act->sig) {
      act = act->sig;
    }
  }

  memcpy(nuevo->data, data, cantBytes);
  nuevo->cantBytes = cantBytes;
  nuevo->sig = NULL;
  nuevo->ant = act;

  if (act) {
    act->sig = nuevo;
  }

  *list = nuevo;

  return 1;
}

int lista_removerUltimo(tLista *list, void *data, unsigned cantBytes) {
  tNodo *eliminar, *act = *list;

  if (!act) {
    return 0;
  }

  while (act->sig) {
    act = act->sig;
  }

  memcpy(data, act->data, minimo(cantBytes, act->cantBytes));

  eliminar = act;
  act = act->ant;
  act->sig = NULL;
  (*list) = act;

  free(eliminar->data);
  free(eliminar);

  return 1;
}

int lista_verUltimo(const tLista *list, void *data, unsigned cantBytes) {
  if (!(*list)) {
    return 0;
  }

  while ((*list)->sig) {
    list = &(*list)->sig;
  }

  memcpy(data, (*list)->data, minimo(cantBytes, (*list)->cantBytes));
  return 1;
}

int lista_mostrar(const tLista *list, mostrar mostrar, FILE *stream) {
  int cant = 0;
  if (*list) {
    while ((*list)->ant) {
      list = &(*list)->ant;
    }
    while (*list) {
      mostrar((*list)->data, stream);
      list = &(*list)->sig;
      cant++;
    }
  }
  return cant;
}

int lista_mostrarInvertido(const tLista *list, mostrar mostrar, FILE *stream) {
  int cant = 0;
  if (*list) {
    while ((*list)->sig) {
      list = &(*list)->sig;
    }
    while (*list) {
      mostrar((*list)->data, stream);
      list = &(*list)->ant;
      cant++;
    }
  }
  return cant;
}

int lista_insertarOrdenado(tLista *list, const void *data, unsigned cantBytes,
                           comparar comparar, acumular acumular) {
  tNodo *act = *list, *n_sig = NULL, *n_ant = NULL,
        *nuevo = (tNodo *)malloc(sizeof(tNodo));

  if (!nuevo || !(nuevo->data = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  if (act) {
    int aux;

    /* Si comparar < 0 entonces el dato es mas grande que el actual en lista */
    while (act->sig && comparar(act->data, data) < 0) {
      act = act->sig;
    }
    while (act->ant && comparar(act->data, data) > 0) {
      act = act->ant;
    }

    aux = comparar(act->data, data);

    if (aux == 0 && acumular != NULL) {
      int rc = acumular(act->data, data);
      free(nuevo->data);
      free(nuevo);
      return rc;
    } else if (aux < 0) {
      n_ant = act;
      n_sig = act->sig;
    } else {
      n_ant = act->ant;
      n_sig = act;
    }
  }

  memcpy(nuevo->data, data, cantBytes);
  nuevo->cantBytes = cantBytes;
  nuevo->sig = n_sig;
  nuevo->ant = n_ant;

  if (n_sig) {
    n_sig->ant = nuevo;
  }

  if (n_ant) {
    n_ant->sig = nuevo;
  }

  *list = nuevo;

  return 1;
}

void lista_ordenar(tLista *list, comparar comparar) {
  int ordenado;
  tNodo *act = *list;

  if (*list == NULL) {
    return;
  }

  do {
    while (act->ant) {
      act = act->ant;
    }

    ordenado = 0;
    while (act->sig) {
      if (comparar(act->data, act->sig->data) > 0) {
        void *data = act->data;
        unsigned bytes = act->cantBytes;

        act->data = act->sig->data;
        act->sig->data = data;
        act->cantBytes = act->sig->cantBytes;
        act->sig->cantBytes = bytes;

        ordenado = 1;
      }
      act = act->sig;
    }
  } while (ordenado);
}

void lista_filtrar(tLista *list, int (*filtro)(const void *)) {
  tNodo *act = *list;

  if (act == NULL) {
    return;
  }

  while (act->ant) {
    act = act->ant;
  }

  while (act) {
    if (!filtro(act->data)) {
      tNodo *ant = act->ant, *sig = act->sig, *temp = act;

      if (ant) {
        ant->sig = sig;
      }
      if (sig) {
        sig->ant = ant;
        *list = sig;
      } else {
        *list = ant;
      }

      act = sig;
      free(temp->data);
      free(temp);
    } else {
      act = act->sig;
    }
  }
}

int lista_insertarPosicion(tLista *list, const void *data, unsigned cantBytes,
                           unsigned pos) {
  size_t i;
  tNodo *act = *list;
  tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));

  if (!nuevo || !(nuevo->data = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  memcpy(nuevo->data, data, cantBytes);
  nuevo->cantBytes = cantBytes;

  if (act) {
    while (act->ant) {
      act = act->ant;
    }

    for (i = 0; i < pos && act->sig; i++) {
      act = act->sig;
    }

    /* Si lo insertamos despues del actual o antes */
    if (!act->sig && i + 1 <= pos) {
      nuevo->ant = act;
      nuevo->sig = NULL;
      act->sig = nuevo;
    } else {
      nuevo->sig = act;
      nuevo->ant = act->ant;
      if (act->ant) {
        act->ant->sig = nuevo;
      }
      act->ant = nuevo;
    }
  } else {
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    (*list) = nuevo;
  }

  return 1;
}

int lista_removerPosicion(tLista *list, void *data, unsigned cantBytes,
                          unsigned pos) {
  size_t i;
  tNodo *act = *list, *eliminar;

  while (act->ant) {
    act = act->ant;
  }

  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  if (act == NULL) {
    return 0;
  }

  memcpy(data, act->data, minimo(cantBytes, act->cantBytes));

  eliminar = act;

  if (eliminar->ant) {
    eliminar->ant->sig = eliminar->sig;
  }

  if (act->sig) {
    act = act->sig;
    act->ant = eliminar->ant;
    (*list) = act;
  } else {
    (*list) = eliminar->ant;
  }

  free(eliminar->data);
  free(eliminar);

  return 1;
}

int lista_verPosicion(const tLista *list, void *data, unsigned cantBytes,
                      unsigned pos) {
  size_t i;
  tNodo *act = *list;

  while (act->ant) {
    act = act->ant;
  }

  for (i = 0; i < pos && act; i++) {
    act = act->sig;
  }

  if (act == NULL) {
    return 0;
  }

  memcpy(data, act->data, minimo(cantBytes, act->cantBytes));

  return 1;
}

void lista_removerDuplicados(tLista *list, const void *data, unsigned cantBytes,
                             comparar comparar) {
  tNodo *act = *list;
  int primer_copia = 0;

  while (act->ant) {
    act = act->ant;
  }

  while (act && !primer_copia) {
    if (comparar(act->data, data) == 0) {
      primer_copia = 1;
    }
    act = act->sig;
  }

  while (act) {
    if (comparar(act->data, data) == 0) {
      tLista eliminar;
      eliminar = act;

      if (eliminar->ant) {
        eliminar->ant->sig = eliminar->sig;
      }

      if (act->sig) {
        act = act->sig;
        act->ant = eliminar->ant;
        (*list) = act;
      } else {
        (*list) = eliminar->ant;
      }

      free(eliminar->data);
      free(eliminar);
    } else {
      act = act->sig;
    }
  }
}

void lista_recorrer(const tLista *list, accion accion) {
  tNodo *act = *list;

  while (act->ant) {
    act = act->ant;
  }

  while (act) {
    accion(act->data);
    act = act->sig;
  }
}

size_t lista_buscar(const tLista *list, const void *data, unsigned cantBytes,
                    comparar comparar) {
  size_t pos = 0;
  tNodo *act = *list;

  while (act->ant) {
    act = act->ant;
  }

  for (pos = 0; act && comparar(act->data, data); pos++) {
    act = act->sig;
  }

  if (act == NULL) {
    pos = -1;
  }

  return pos;
}

size_t lista_contar(const tLista *list) {
  size_t total;
  tNodo *act = *list;

  while (act->ant) {
    act = act->ant;
  }

  for (total = 0; act; total++) {
    act = act->sig;
  }

  return total;
}

/* ------------------------------------------------------------------------- */
