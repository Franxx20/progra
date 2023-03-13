#include "../Lista4/Lista.h"
#include <stdio.h>
#include <stdlib.h>

int compararNumeros(const void *n1, const void *n2);
void mostrarNumeros(void *num, void *datos);
int main() {
  Lista l;
  int numeros[18] = {1, 4,4, 2, 3, 6, 87, 5, 4, 2, 1,4, 4,65,4, 9, 9, 99};
  crearLista(&l);

  for (int i = 0; i < 18; i++) {
    insertarEnListaAlFinal(&l, &numeros[i], sizeof(int));
  }

  recorrerLista(&l, mostrarNumeros, NULL);

  ordenarLista(&l, compararNumeros);
  puts("Lista ordenada");
  recorrerLista(&l, mostrarNumeros, NULL);

  puts("Borrando duplicados");
  eliminarDuplicadosLista(&l, sizeof(int), compararNumeros);
  recorrerLista(&l, mostrarNumeros, NULL);

  vaciarLista(&l);
  return 0;
}

int compararNumeros(const void *n1, const void *n2) {
  return *(int *)n1 - *(int *)n2;
}

void mostrarNumeros(void *num, void *datos) {
  printf("El numero es: %d\n", *(int *)num);
}
