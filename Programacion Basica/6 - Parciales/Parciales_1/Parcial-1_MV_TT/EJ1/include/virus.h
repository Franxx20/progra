#ifndef VIRUS_H
#define VIRUS_H

#include "pila.h"

#define SIZE 1024

#define ESMAYUS(A)			(A >= 'A' && A <= 'Z')
#define ESMINUS(a)			(a >= 'a' && a <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

void separarPorBloques(char *str, char *separadores, tPila *tamBloques);
void daniarBloque(char *str, char *separadores, tPila *tamBloques);
char daniarCaracter(char c, int offset);

#endif
