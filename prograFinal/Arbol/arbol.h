#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2

typedef int (*Cmp)(const void *d1, const void *d2);
typedef void (*Actualizar)(void *actualizado, const void *actualizador);
typedef void (*Accion)(void *accion, void *datosAccion);
typedef void (*Mostrar)(const void *dato, int nivel);

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *hIzq;
  struct sNodo *hDer;
} NodoA;

typedef NodoA *Arbol;

void crearArbol(Arbol *t);
int vaciarArbol(Arbol *t);

bool arbolLleno(Arbol *t, unsigned tamDato);
bool arbolVacio(Arbol *t);

int insertarEnArbol(Arbol *t, void *dato, unsigned tamDato, Cmp cmp,
                    Actualizar actualizar);
bool eliminarDeArbol(Arbol *t, void *dato, unsigned tamDato, Cmp cmp);

bool buscarEnArbol(const Arbol *t, void *dato, unsigned tamDato, Cmp cmp);

void recorrerArbolPre(Arbol *t, Accion accion, void *datosAccion); // R - I - D
void recorrerArbolEn(Arbol *t, Accion accion, void *datosAccion);  // I - R - D
void recorrerArbolPos(Arbol *t, Accion accion, void *datosAccion); // I - D - R
                                                                   //
                                                                   //
bool cargarEnArbolDeUnArchivoOrdenadoRec(Arbol *t, int li, int ls, int tamDato,
                                         FILE *fp, Cmp cmp,
                                         Actualizar actualizar);

bool cargarEnArbolDeUnArchivoOrdenado(Arbol *t, unsigned tamDato,
                                      const char *nombreArch, Cmp cmp,
                                      Actualizar actualizar);

void graficarArbol(const Arbol *t, Mostrar mostrar);
void graficarArbolRec(const Arbol *t, Mostrar mostrar, int nivel);
#endif // ARBOL_H_INCLUDED
