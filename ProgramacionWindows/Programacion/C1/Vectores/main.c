#include <stdio.h>
#include <stdlib.h>
#include"Vectores.h"
#define TAM 10
#define TAM2 16
int main() {
  int vec[TAM] = {1, 2, 5, 6, 9, 11, 13, 14, 16}, ce = 9, elem;
  elem = 10;
  mostrarVector(vec, ce);
  char *cad = "SE PROCEDE A INSERTAR";
  puts(cad);

  InsertarOrdElemento(vec, &ce, TAM, elem);
  mostrarVector(vec, ce);
  char *cad2 = "SE PROCEDE A ELIMINAR";
  puts(cad2);
  EliminarOrdElemento(vec, &ce, TAM, elem);
  // EliminarRepetido(vec,&ce);
  mostrarVector(vec, ce);

  int vec2[TAM2] = {1, 2, 5, 6, 9, 11, 13, 14, 14, 14, 14, 14, 14, 16, 17, 18},
      ce2 = 16;
  puts(" \n");
  mostrarVector(vec2, ce2);
  EliminarOrdRepetido(vec2, &ce2);
  mostrarVector(vec2, ce2);
  return 0;
}

