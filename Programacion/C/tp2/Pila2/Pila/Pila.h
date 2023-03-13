#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifdef PILA_ESTATICA
#include "../PilaEstatica/PilaEstatica.h"
#else
#include "../PilaDinamica/PilaDinamica.h"
#endif

#include <stdbool.h>
#include <stddef.h>

void crearPila(Pila *p);
void vaciarPila(Pila *p);

bool pilaLlena(const Pila *p, unsigned tamDato);
bool pilaVacia(const Pila *p);

bool apilar(Pila *p, const void *dato, unsigned tamDato);
bool desapilar(Pila *p, void *dato, unsigned tamDato);

bool verTope(const Pila *p, void *dato, unsigned tamDato);

#endif // PILA_H_INCLUDED
