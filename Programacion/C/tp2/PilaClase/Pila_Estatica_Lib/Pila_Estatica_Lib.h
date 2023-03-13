#ifndef PILA_ESTATICA_LIB_H_INCLUDED
#define PILA_ESTATICA_LIB_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>

#define TAM_PILA 42
#define min(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
  char vPila[TAM_PILA];
  unsigned tope;
} Pila;

#define PILA_EST
#include "../TDA_Pila/TDA_PILA.h"

#endif // PILA_ESTATICA_LIB_H_INCLUDED
