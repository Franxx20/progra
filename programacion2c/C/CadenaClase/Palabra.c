#include "Palabra.h"
#include <ctype.h>
#include <stdio.h>
#define esLetra(a) (((a) >= 'a' && (a) <= 'z') || ((a) >= 'A' && (a) <= 'Z'))

void crearSecuenciaPalabras(SecuenciaPalabras *secuencia, char *cadena) {
  secuencia->cursor = cadena;
  secuencia->finSecuencia = false;
}

bool leerPalabra(SecuenciaPalabras *secuencia, Palabra *palabra) {
  char *cursor = secuencia->cursor;

  while (*cursor && !esLetra(*cursor))
    cursor++;

  if (!*cursor) {
    secuencia->finSecuencia = true;
    secuencia->cursor = cursor;
    return false;
  }
  palabra->ini = cursor;

  while (*cursor && esLetra(*cursor))
    cursor++;

  palabra->fin = cursor - 1;
  secuencia->cursor = cursor;

  return true;
}

bool finSecuencia(const SecuenciaPalabras *secuencia) {
  return secuencia->finSecuencia;
}

void imprimirPalabra(const Palabra *palabra) {
  for (char *c = palabra->ini; c <= palabra->fin; c++)
    putchar(*c);
}

void escribirPalabra(SecuenciaPalabras *secuencia, const Palabra *palabra,
                     Palabra *palabraDest) {

  palabraDest->ini = secuencia->cursor;
  char *actO;
  char *actD;

  for (actO = palabra->ini, actD = secuencia->cursor; actO <= palabra->fin;
       actO++, actD++)
    *actD = *actO;

  palabraDest->fin = actD - 1;

  secuencia->cursor = actD;
}

// Primera letra en mayuscula, el resto en minuscula
void aTitulo(Palabra *palabra) {

  *palabra->ini = toupper(*palabra->ini);
  for (char *c = palabra->ini + 1; c <= palabra->fin; c++) {
    *c = tolower(*c);
  }
}

void escribirCaracter(SecuenciaPalabras *secuencia, char caracter) {

  *secuencia->cursor = caracter;
  secuencia->cursor++;
}

void reposicionarCursor(SecuenciaPalabras *secuencia, int desplazamiento) {
  secuencia->cursor += desplazamiento;
}

void cerrarSecuenciaPalabras(SecuenciaPalabras *secuencia) {
  *secuencia->cursor = '\0';
}
