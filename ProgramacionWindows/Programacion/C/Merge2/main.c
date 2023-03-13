#include "Merge.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  escribirArchivos(argv[1], argv[2]);
  puts("ANTES DE ACTUALIZAR");
  mostrarArchivo(argv[1]);
  printf("%s %s\n", argv[1], argv[2]);
  actualizarProductos(argv[1], argv[2]);
  puts("DESPUES DE ACTUALIZAR");
  mostrarArchivo(argv[1]);

  return 0;
}
