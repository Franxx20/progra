#include "../Lista5/Lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nombre[20];
  char apellido[20];
  int dni;
} Raritos;

int main(int argc, char *argv[]) {
  FILE *archTxt = fopen(argv[1], "rt");

  if (!archTxt) {
    fprintf(stderr, "ERROR ABRIENDO EL ARCHIVO DE TEXTO");
    return 0;
  }

  return 0;
}
