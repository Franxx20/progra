#ifndef TDA_PILA_H_INCLUDED
#define TDA_PILA_H_INCLUDED

#ifdef PILA_EST
#include "../Pila_Estatica_Lib/Pila_Estatica_Lib.h"
#endif // PILA_EST

#ifdef PILA_DIN
#include "Pila_Dinamica.h"
#endif // PILA_DIN

void crearPila(Pila *pp);
bool apilar(Pila *pp, const void *elem, size_t tamElem);
bool desapilar(Pila *pp, void *elem, size_t tamElem);
bool topeDePila(const Pila *pp, void *elem, size_t tamElem);
bool pilaLlena(const Pila *pp, size_t tamElem);
bool pilaVacia(const Pila *pp);
void vaciarPila(Pila *pp);

#endif // TDA_PILA_H_INCLUDED
