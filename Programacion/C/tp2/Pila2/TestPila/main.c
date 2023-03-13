#include <stdio.h>
#include <stdlib.h>
#define PILA_DINAMICA
#include "../Pila/Pila.h"

int main() {
  Pila p1;
  crearPila(&p1);
  int num;

  while (!pilaLlena(&p1, sizeof(int)) && num != -1) {
    puts("Insertar numero");
    scanf("%d", &num);
    apilar(&p1, &num, sizeof(int));
  }
  puts("Pila llena");
  verTope(&p1, &num, sizeof(int));
  printf("Tope de la pila %d\n", num);

  vaciarPila(&p1);
  if (pilaVacia(&p1))
    puts("La pila esta vacia");
  else
    puts("La pila no esta vacia");
  return 0;
}
