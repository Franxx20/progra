#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NodoA *crearNodo(void *dato, unsigned tamDato);
void vaciarNodo(NodoA *nae, void *dato, unsigned tamDato);

Arbol *buscarNodo(Arbol *t, void *dato, Cmp cmp);
void eliminarNodo(Arbol *pnae);
int alturaArbol(const Arbol *t);
Arbol *mayorNodo(Arbol *t);
Arbol *menorNodo(Arbol *t);

NodoA *crearNodo(void *dato, unsigned tamDato) {
  NodoA *nue = (NodoA *)malloc(sizeof(NodoA));
  if (!nue || !(nue->dato = malloc(tamDato))) {
    free(nue);
    return NULL;
  }

  memcpy(nue->dato, dato, tamDato);
  nue->tamDato = tamDato;
  nue->hIzq = NULL;
  nue->hDer = NULL;

  return nue;
}

void vaciarNodo(NodoA *nae, void *dato, unsigned tamDato) {
  if (!nae)
    return;

  memcpy(dato, nae->dato, MIN(nae->tamDato, tamDato));
  free(nae->dato);
  free(nae);
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
  // caso base si el nodo a eliminar es un nodo hoja
  if (!(*pnae)->hDer && !(*pnae)->hIzq) {
    free((*pnae));

    (*pnae) = NULL;

    return;
  }

  // caso contrario comparamos las alturas de las dos ramas y elegimos la mas
  // alta para reemplazar
  int hi = alturaArbol(&(*pnae)->hIzq);
  int hd = alturaArbol(&(*pnae)->hDer);

  Arbol *pnareemp =
      hi > hd ? mayorNodo(&(*pnae)->hIzq) : menorNodo(&(*pnae)->hDer);

  // reemplazamos los punteros del nodo a eliminar con los del nodo a reemplazar
  (*pnae)->dato = (*pnareemp)->dato;
  (*pnae)->tamDato = (*pnareemp)->tamDato;

  // hacemos lo mismo para el nodo de reemplazo
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
  if (!*t)
    return NULL;

  while ((*t)->hDer)
    t = &(*t)->hDer;

  return t;
}

Arbol *menorNodo(Arbol *t) {
  if (!*t)
    return NULL;

  while ((*t)->hIzq)
    t = &(*t)->hIzq;

  return t;
}

void crearArbol(Arbol *t) { *t = NULL; }

int vaciarArbol(Arbol *t) {
  int cne = 0;
  if (!*t)
    return cne;

  cne += vaciarArbol(&(*t)->hIzq);
  cne += vaciarArbol(&(*t)->hDer);

  free((*t)->dato);
  free(*t);
  *t = NULL;

  return cne + 1;
}

bool arbolLleno(Arbol *t, unsigned tamDato) {
  NodoA *nue = (NodoA *)malloc(sizeof(NodoA));
  void *dato = malloc(tamDato);

  free(nue);
  free(dato);

  return !nue || !dato;
}

bool arbolVacio(Arbol *t) { return *t == NULL; }

int insertarEnArbol(Arbol *t, void *dato, unsigned tamDato, Cmp cmp,
                    Actualizar actualizar) {
  // // si el arbol esta vacio y no tiene elementos
  // if (!*t) {
  //   *t = crearNodo(dato, tamDato);
  //   if (!*t)
  //     return SIN_MEM;

  //   return TODO_OK;
  // }
  // // caso contrario tendremos que buscar la posición correcta para insertarlo
  // int res = cmp(dato, (*t)->dato);

  // if (res == 0) {
  //   if (actualizar)
  //     actualizar((*t)->dato, dato);
  //   else
  //     return DUPLICADO;
  // }

  // return insertarEnArbol(res < 0 ? &(*t)->hIzq : &(*t)->hDer, dato, tamDato,
  //                        cmp, actualizar);
  //
  // caso base si el arbol esta vacio
  if (!*t) {
    *t = crearNodo(dato, tamDato);
    return !*t ? SIN_MEM : TODO_OK;
  }

  // caso contrario vamos a tener que buscar la posicion para insertarlo
  int res = cmp(dato, (*t)->dato);

  if (res == 0) {
    if (actualizar)
      actualizar((*t)->dato, dato);
    else
      return DUPLICADO;
  }

  return insertarEnArbol(res < 0 ? &(*t)->hIzq : &(*t)->hDer, dato, tamDato,
                         cmp, actualizar);
}

bool eliminarDeArbol(Arbol *t, void *dato, unsigned tamDato, Cmp cmp) {
  if (!*t)
    return false;
  Arbol *pnae = buscarNodo(t, dato, cmp);

  if (!pnae)
    return false;

  memcpy(dato, (*pnae)->dato, MIN(tamDato, (*pnae)->tamDato));
  free((*pnae)->dato);

  eliminarNodo(pnae);

  return true;
}

bool buscarEnArbol(const Arbol *t, void *dato, unsigned tamDato, Cmp cmp) {
  // if (!*t)
  //   return false;

  // Arbol *pnab = buscarNodo((Arbol *)t, dato, cmp);
  // if (!pnab)
  //   return false;

  // return true;
  //
  if (!*t)
    return false;

  int res = cmp(dato, (*t)->dato);
  if (res == 0) {
    memcpy(dato, (*t)->dato, MIN(tamDato, (*t)->tamDato));

    return true;
  }

  return buscarEnArbol(res < 0 ? &(*t)->hIzq : &(*t)->hDer, dato, tamDato, cmp);
}

void recorrerArbolPre(Arbol *t, Accion accion, void *datosAccion) // R - I - D
{
  if (*t) {
    accion((*t)->dato, datosAccion);
    recorrerArbolPre(&(*t)->hIzq, accion, datosAccion);
    recorrerArbolPre(&(*t)->hDer, accion, datosAccion);
  }
}

void recorrerArbolEn(Arbol *t, Accion accion, void *datosAccion) // I - R - D
{
  if (*t) {
    recorrerArbolEn(&(*t)->hIzq, accion, datosAccion);
    accion((*t)->dato, datosAccion);
    recorrerArbolEn(&(*t)->hDer, accion, datosAccion);
  }
}
void recorrerArbolPos(Arbol *t, Accion accion, void *datosAccion) // I - D - R
{
  if (*t) {
    recorrerArbolPos(&(*t)->hIzq, accion, datosAccion);
    recorrerArbolPos(&(*t)->hDer, accion, datosAccion);
    accion((*t)->dato, datosAccion);
  }
}
bool cargarEnArbolDeUnArchivoOrdenado(Arbol *t, unsigned tamDato,
                                      const char *nombreArch, Cmp cmp,
                                      Actualizar actualizar) {
  FILE *fp = fopen(nombreArch, "rb");

  if (!fp)
    return false;

  fseek(fp, 0L, SEEK_END);

  int ls = ((ftell(fp)) / sizeof(tamDato)) - 1;

  cargarEnArbolDeUnArchivoOrdenadoRec(t, 0, ls, tamDato, fp, cmp, actualizar);

  fclose(fp);
  return true;
}

bool cargarEnArbolDeUnArchivoOrdenadoRec(Arbol *t, int li, int ls, int tamDato,
                                         FILE *fp, Cmp cmp,
                                         Actualizar actualizar) {
  if (li > ls)
    return false;

  int mitad = (li + ls) / 2;
  fseek(fp, mitad * tamDato, SEEK_SET);

  void *registro = malloc(tamDato);

  if (!registro)
    return false;

  fread(registro, tamDato, 1, fp);
  insertarEnArbol(t, registro, tamDato, cmp, actualizar);

  cargarEnArbolDeUnArchivoOrdenadoRec(t, li, mitad - 1, tamDato, fp, cmp,
                                      actualizar);
  cargarEnArbolDeUnArchivoOrdenadoRec(t, mitad + 1, ls, tamDato, fp, cmp,
                                      actualizar);

  return true;
}

void graficarArbolRec(const Arbol *t, Mostrar mostrar, int nivel) {
  if (!*t)
    return;

  graficarArbolRec(&(*t)->hIzq, mostrar, nivel + 1);
  mostrar((*t)->dato, nivel);
  graficarArbolRec(&(*t)->hDer, mostrar, nivel + 1);
}

void graficarArbol(const Arbol *t, Mostrar mostrar) {
  graficarArbolRec(t, mostrar, 0);
}
