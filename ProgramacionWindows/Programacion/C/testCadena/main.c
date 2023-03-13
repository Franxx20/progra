#include "../CadenaClase/Cadena.h"
#include "../CadenaClase/Palabra.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  char texto[] = "\t hola, \t /.,¿/.¿Como*&*(&⁽*&^estas??././/¿.que tal?)";
  char textoNormalizado[201];

  SecuenciaPalabras secuencia;
  crearSecuenciaPalabras(&secuencia, texto);

  puts(texto);

  normalizar(texto, textoNormalizado);
  puts(textoNormalizado);
  return 0;
}
