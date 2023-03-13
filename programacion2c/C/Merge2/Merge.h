#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  char cod[5];
  char desc[20];
  int stock;
  float precio;
} Producto;

typedef struct {
  char cod[5];
  int cant;
} Movimiento;

typedef int (*Cmp)(const void *, const void *);

bool escribirArchivos(const char *productos, const char *movimientos);
bool actualizarProductos(const char *productos, const char *movimientos);
bool mostrarArchivo(const char *productos);

void ordenarSeleccion(void *vec, unsigned tamDato, int ce, Cmp cmp);
void *buscarMenor(void *ini, void *fin, unsigned tamElem, Cmp cmp);
void intercambiar(void *a, void *b, unsigned tamDato);

int compararProdPorCodigo(const void *p1, const void *p2);
int compararMovPorCodigo(const void *m1, const void *m2);

bool convertirTxtABin(const char *nombreTxt, char tipoFormato,
                      const char *nombreBin);

bool parsearCadenaVar(char *linea, Producto *prod);
bool parsearCadenaFijo(char *linea, Producto *prod);

bool cambiarExtension(const char *nombreOriginal, char *nombreCambiado,
                      const char *extension);

#endif
