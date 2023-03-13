#ifndef CMP_H
#define CMP_H

#include <stddef.h>
#include <stdio.h>

typedef int (*Cmp)(const void *elem1, const void *elem2);
typedef void (*Mostrar)(const void *elem, FILE *);

void ordenarSel(void *vec, int ce, size_t tamElem, Cmp cmp);
void *buscarMenor(void *ini, void *fin, size_t tamElem, Cmp cmp);
void intercambiar(void *elem1, void *elem2, size_t tamElem);
void mostrarVec(const void *vec, int ce, size_t tamElem, Mostrar mostrar,
                FILE *stream);

// AL LOBBY CANDE Y MAR
// BESTIA GOD
// PEKE ES DE AGUSTIN

#endif // CMP_H
