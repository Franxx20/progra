#ifndef VECTORES_H_INCLUDED
#define VECTORES_H_INCLUDED
#include <stdbool.h>

int InsertarOrdElemento(int *vec, int *ce, int TAM, int elem);
bool EliminarOrdElemento(int *vec, int *ce, int TAM, int elem);
bool EliminarOrdRepetido(int *vec, int *ce);
void mostrarVector(int *vec, int TAM);
#endif // VECTORES_H_INCLUDED
