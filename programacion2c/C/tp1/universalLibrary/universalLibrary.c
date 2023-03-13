#include "universalLibrary.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
booleano continuar(const char *mensaje) {
  puts(mensaje);
  fflush(stdin);
  char respuesta = scanf("%c", &respuesta);

  respuesta = tolower(respuesta);

  while (respuesta != 's' && respuesta != 'n') {
    puts("Respuesta invalida. Ingrese de nuevo.\n");
    puts("Debe ingresar s o n");
    while ((respuesta = fgetc(stdin)) == '\n') {
    }
    scanf("%c", &respuesta);
    respuesta = tolower(respuesta);
  }
  return respuesta == 's';
}
char menuSinError(const char *msj, const char *opc) {
  char opta;
  do {
    printf("%s", msj);
    while ((opta = fgetc(stdin)) == '\n') {
    }
  } while (strchr(opc, opta) == NULL);

  return opta;
}
char menuConError(const char *msj, const char *opc) {
  char opta;
  int priVez = 1;

  do {
    printf("%s%s", priVez ? priVez = 0, "" : "ERROR - Opcion no valida.\n",
           msj);
    while ((opta = fgetc(stdin)) == '\n') {
    }

  } while (strchr(opc, opta) == NULL);

  return opta;
}
