#include <stdio.h>
#include <stdlib.h>
#include "cmp.h"
#define TAM 5

typedef struct {
  int cod, stock;
  char desc[30];
} Producto;

int cmpProdCod(const void *elem1, const void *elem2);
void mostrarProd(const void *elem, FILE *stream);

int main() {
  int ceProd = TAM;
  Producto Vprod[TAM] = {{30, 40, "banana"},
                         {12, 10, "manzana"},
                         {15, 20, "pera"},
                         {13, 100, "kiwi"},
                         {25, 30, "mora"}};
  mostrarVec(Vprod, ceProd, sizeof(Producto), mostrarProd, stdout);
  puts("");
  ordenarSel(Vprod, ceProd, sizeof(Producto), cmpProdCod);
  mostrarVec(Vprod, ceProd, sizeof(Producto), mostrarProd, stdout);

  return 0;
}

int cmpProdCod(const void *elem1, const void *elem2) {
  const Producto *p1 = (Producto *)elem1;
  const Producto *p2 = (Producto *)elem2;

  return p1->cod - p2->cod;
}

void mostrarProd(const void *elem, FILE *stream) {
  const Producto *p = (Producto *)elem;
  fprintf(stream, "cod %d stock %d descripcion %s\n", p->cod, p->stock,
          p->desc);
}
