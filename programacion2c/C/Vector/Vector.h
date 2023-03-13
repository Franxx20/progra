#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdbool.h>

int InsertarOrdElemento(int *vec, int *ce, int TAM, int elem);
bool EliminarOrdElemento(int *vec, int *ce, int TAM, int elem);
void mostrarVector(int *vec, int TAM);
bool EliminarOrdRepetido(int *vec, int *ce);

void eliminarDuplicados(int *vec, int *ce);

#endif // VECTOR_H_INCLUDED
