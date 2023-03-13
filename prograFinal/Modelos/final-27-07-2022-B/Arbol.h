#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include"comun.h"

typedef struct sNodoA{
void * dato;
unsigned tamDato;
struct sNodoA * hIzq;
struct sNodoA * hDer;
}NodoA;

typedef NodoA * Arbol;





int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar);



void crearArbol(Arbol *t);
int vaciarArbol(Arbol*t);

void mostrarArbol(const Arbol *t, Mostrar mostrar);



#endif
