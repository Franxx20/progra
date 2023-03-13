#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#include <stdbool.h>

typedef struct {
  char *cursor;
  bool finSecuencia;
} SecuenciaPalabras;

typedef struct {
  char *ini;
  char *fin;
} Palabra;

void crearSecuenciaPalabras(SecuenciaPalabras *secuencia, char *cadena);
bool leerPalabra(SecuenciaPalabras *secuencia, Palabra *palabra);
bool finSecuencia(const SecuenciaPalabras *secuencia);
void imprimirPalabra(const Palabra *palabra);
void escribirPalabra(SecuenciaPalabras *secuencia, const Palabra *palabra,
                     Palabra *palabraDest);

void aTitulo(Palabra *palabra);
void escribirCaracter(SecuenciaPalabras *secuencia, char caracter);
void reposicionarCursor(SecuenciaPalabras *secuencia, int desplazamiento);
void cerrarSecuenciaPalabras(SecuenciaPalabras *secuencia);

#endif // PALABRA_H_INCLUDED
