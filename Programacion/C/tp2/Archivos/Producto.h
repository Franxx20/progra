#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

typedef struct {
  char codigo[20];
  char descripcion[40];
  float precio;
  int cant;
} Producto;

typedef struct {
  char codigo[20];
  int pos;
} Indice;

#endif // PRODUCTO_H_INCLUDED
