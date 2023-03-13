#include "Cadena.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ESLETRA(car) (tolower(car) >= 'a' && tolower(car) < 'z' ? (1) : (0))

int miStrlen(const char *cad) {
  int cant = 0;
  while (*cad) {
    cant++;
    cad++;
  }

  return cant;
}

bool esPalindromo(const char *cad) {
  const char *izq = cad;
  const char *der = cad + strlen(cad) - 1;
  while (izq < der) {
    while (!ESLETRA(*izq))
      izq++;
    while (!ESLETRA(*der))
      der--;
    if (ESLETRA(*izq) != ESLETRA(*der))
      return false;
    izq++;
    der--;
  }

  return izq >= der;
}

bool sonAnagramas(const char *cad1, const char *cad2) {
  int tam1 = miStrlen(cad1);
  int tam2 = miStrlen(cad2);
  printf("%d %d\n", tam1, tam2);
  int cantLetra1;
  int cantLetra2;

  const char *aux1 = cad1;
  const char *aux2 = cad2;

  for (int i = 0; i < tam1; i++) {
    printf("%c", *(aux1 + i));
  }
  puts("");
  for (int i = 0; i < tam1; i++) {
    printf("%c", *(aux2 + i));
  }
  puts("");

  if (tam1 != tam2)
    return false;

  for (int w = 0; w < tam1; w++) {

    cantLetra1 = 0;
    cantLetra2 = 0;

    for (int i = 0; i < tam1; i++) {
      printf("Letra %c %c\n", *aux1, *(aux1 + i));
      if (*aux1 == *(cad1 + i)) {
        cantLetra1++;
      }
    }
    printf("cad 1 %c %d\n", *aux1, cantLetra1);
    printf("\n");
    for (int j = 0; j < tam2; j++) {
      printf("Letra %c %c\n", *aux1, *(aux2 + j));
      if (*aux1 == *(cad2 + j)) {
        cantLetra2++;
      }
    }
    printf("cad 2 %c %d\n", *(aux1), cantLetra2);
    printf("\n");
    if (cantLetra1 != cantLetra2)
      return false;

    printf("\n");
    aux1++;
  }

  return true;
}
