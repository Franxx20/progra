#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED
#include <stdbool.h>
typedef struct {
  char Cod[5];
  char Desc[20];
  int Stock;
  float Precio;
} Producto;

typedef struct {
  char Cod[5];
  int Cant;
} Movimiento;

bool escribirArchivos(const char *productos, const char *movimientos);
bool actualizarProds(const char *productosA, const char *movimientosA);
bool mostrarArchivo(const char *producto);

#endif // MERGE_H_INCLUDED
