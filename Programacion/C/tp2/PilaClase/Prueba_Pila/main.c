#include <stdio.h>
#include <stdlib.h>

#define PILA_EST
#include "../Pila_Estatica_Lib/Pila_Estatica_Lib.h"

int main() {
  Pila pila1;
  crearPila(&pila1);

  int num;

  while (!pilaLlena(&pila1, sizeof(int))) {
    puts("Insertar numero");
    scanf("%d", &num);
    apilar(&pila1, &num, sizeof(int));
  }
  puts("Pila llena");
  topeDePila(&pila1, &num, sizeof(int));
  printf("Tope de la pila %d\n", num);

  vaciarPila(&pila1);

  if (pilaVacia(&pila1))
    puts("La pila esta vacia");
  else
    puts("La pila no esta vacia");

  return 0;
}
