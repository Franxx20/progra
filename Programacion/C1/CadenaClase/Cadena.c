#include "Cadena.h"
#include "Palabra.h"
void normalizar(const char *texto, char *textoNormalizado) {

  SecuenciaPalabras secuenciaLect;
  crearSecuenciaPalabras(&secuenciaLect, (char *)texto);

  SecuenciaPalabras secuenciaEscr;
  crearSecuenciaPalabras(&secuenciaEscr, textoNormalizado);

  Palabra palabra, palabraDest;
  while (leerPalabra(&secuenciaLect, &palabra)) {

    escribirPalabra(&secuenciaEscr, &palabra, &palabraDest);
    aTitulo(&palabraDest);
    escribirCaracter(&secuenciaEscr, ' ');
  }

  reposicionarCursor(&secuenciaEscr, -1);
  cerrarSecuenciaPalabras(&secuenciaEscr);
}
