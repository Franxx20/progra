#include "../Cadena/Cadena.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char cad[] = {"Anita lava latina"};
  char cad1[] = {"rro3ew!1q2masdoar"};
  char cad2[] = {"roqw2!er1ar3masdo"};

  printf("cad tiene %d miStrlen %d\n", (int)strlen(cad), miStrlen(cad));

  bool resultado = esPalindromo(cad);
  printf("%s %s!\n", resultado ? "true" : "false", cad);

  bool resultado2 = sonAnagramas(cad1, cad2);
  printf("%s %s %s!\n", cad1, cad2, resultado2 ? "true" : "false");

  return 0;
}
