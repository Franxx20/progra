#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo *crearNodo(const void *dato, unsigned tamDato);
Arbol *buscarNodo(Arbol *t, void *dato, Cmp cmp);
void eliminarNodo(Arbol *pnae);
int alturaArbol(const Arbol *t);
Arbol *mayorNodo(Arbol *t);
Arbol *menorNodo(Arbol *t);

Nodo *crearNodo(const void *dato, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    free(nue);
    return NULL;
  }
  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->hDer = NULL;
  nue->hIzq = NULL;

  return nue;
}

Arbol *buscarNodo(Arbol *t, void *dato, Cmp cmp) {
  if (!*t)
    return NULL;
  int res = cmp(dato, (*t)->dato);

  if (res == 0)
    return t;

  return buscarNodo(res < 0 ? &(*t)->hIzq : &(*t)->hDer, dato, cmp);
}

void eliminarNodo(Arbol *pnae) {
  // CASO BASE SI EL NODO ES UNA HOJA
  if (!(*pnae)->hIzq && !(*pnae)->hDer) {
    free(*pnae);
    *pnae = NULL;
    return;
  }
  // CASO CONTRARIO SE COMPARA LA ALTURA DE LAS DOS ARMAS Y SE BUSCA EL
  // REEMPLAZO EN LA RAMA DE MAYOR ALTURA
  int hi = alturaArbol(&(*pnae)->hIzq);
  int hd = alturaArbol(&(*pnae)->hDer);

  Arbol *pnareemp =
      hi > hd ? mayorNodo(&(*pnae)->hIzq) : menorNodo(&(*pnae)->hDer);

  // COPIAMOS LOS DATOS DEL NODO A REEMPLAZO EN EL NODO A ELIMINAR
  (*pnae)->dato = (*pnareemp)->dato;
  (*pnae)->tamDato = (*pnareemp)->tamDato;

  // REPETIMOS EL PROCESO POR SI EL NODO REEMPLAZO TIENE HIJOS
  eliminarNodo(pnareemp);
}

int alturaArbol(const Arbol *t) {
  if (!*t)
    return 0;
  int hi = alturaArbol(&(*t)->hIzq);
  int hd = alturaArbol(&(*t)->hDer);

  return (hi >= hd ? hi : hd) + 1;
}

Arbol *mayorNodo(Arbol *t) {

  while ((*t)->hDer)
    t = &(*t)->hDer;

  return t;
}

Arbol *menorNodo(Arbol *t) {

  while ((*t)->hIzq)
    t = &(*t)->hIzq;

  return t;
}

void crearArbol(Arbol *t) { *t = NULL; }

int vaciarArbol(Arbol *t) {
  int cne = 0;
  if (!*t)
    return 0;

  cne += vaciarArbol(&(*t)->hIzq);
  cne += vaciarArbol(&(*t)->hDer);

  free((*t)->dato);
  free(*t);
  *t = NULL;

  return cne + 1;
}

bool arbolLleno(const Arbol *t, unsigned tamDato) {
  Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
  void *dato = malloc(tamDato);
  free(nue);
  free(dato);

  return !nue || !dato;
}

bool arbolVacio(const Arbol *t) { return *t == NULL; }

int insertarEnArbol(Arbol *t, const void *dato, unsigned tamDato, Cmp cmp,
                    Actualizar actualizar) {
  // CASO BASE SI EL ARBOL ESTA VACIO
  if (!*t) {
    *t = crearNodo(dato, tamDato);
    if (!*t)
      return SIN_MEM;
    return TODO_OK;
  }

  // CASO CONTRARIO SE BUSCARA LA POSICION CORRECTA PARA INSERTARLO
  int res = cmp(dato, (*t)->dato);

  if (res == 0) {
    actualizar((*t)->dato, dato);
    return DUPLICADO;
  }

  return insertarEnArbol(res < 0 ? &(*t)->hIzq : &(*t)->hDer, dato, tamDato,
                         cmp, actualizar);
}

bool eliminarDeArbol(Arbol *t, void *dato, unsigned tamDato, Cmp cmp) {
  Arbol *pnae = buscarNodo(t, dato, cmp);

  memcpy(dato, (*pnae)->dato, MIN(tamDato, (*pnae)->tamDato));
  free((*pnae)->dato);

  eliminarNodo(pnae);

  return true;
}

bool buscarEnArbol(const Arbol *t, void *dato, unsigned tamDato, Cmp cmp);

void recorrerArbolPre(Arbol *t, Accion accion, void *datosAccion) {
  if (!*t)
    return;
  accion((*t)->dato, datosAccion);
  recorrerArbolPre(&(*t)->hIzq, accion, datosAccion);
  recorrerArbolPre(&(*t)->hDer, accion, datosAccion);
}

void recorrerArbolEn(Arbol *t, Accion accion, void *datosAccion) {
  if (!*t)
    return;

  recorrerArbolPre(&(*t)->hIzq, accion, datosAccion);
  accion((*t)->dato, datosAccion);
  recorrerArbolPre(&(*t)->hDer, accion, datosAccion);
}

void recorrerArbolPos(Arbol *t, Accion accion, void *datosAccion) {
  if (!*t)
    return;

  recorrerArbolPre(&(*t)->hIzq, accion, datosAccion);
  recorrerArbolPre(&(*t)->hDer, accion, datosAccion);
  accion((*t)->dato, datosAccion);
}
