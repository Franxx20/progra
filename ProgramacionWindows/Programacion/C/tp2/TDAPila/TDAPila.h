#ifndef TDAPILA_H_INCLUDED
#define TDAPILA_H_INCLUDED

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifdef TDA_PILA_IMPL_ESTATICA
#include "../TDAPilaEstatica/PilaEstatica.h"
#else
#include "../TDAPilaDinamica/PilaDinamica.h"
#endif

#include <stdbool.h>
#include <stddef.h>

void crearPila(Pila *p);
void vaciarPila(Pila *p);

bool pilaLlena(const Pila *p, unsigned tamDato);
bool pilaVacia(const Pila *p);
bool verTope(const Pila *p, void *dato, unsigned tamDato);

bool PonerEnPila(Pila *p, const void *dato, unsigned tamDato);
bool sacarDePila(Pila *p, void *dato, unsigned tamDato);

#endif // TDAPILA_H_INCLUDED
