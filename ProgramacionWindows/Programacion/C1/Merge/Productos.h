#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <stdbool.h>

#define tamCod 5
#define tamProd 10

typedef struct {
char cod[tamCod];
char desc[tamProd];
int cant;
float precio;

} Producto;

typedef struct {
char cod[tamCod];
int cant;
}Movimiento;

typedef int (Cmp *) (const void *, const void *);

void  ordenarSeleccion();
void *buscarMenor(const void *, const void *, unsigned tamDato, Cmp cmp);
void intercambiar(void *, void*, unsigned tamDato);




#endif // PRODUCTOS_H_INCLUDED
