#ifndef TDACOLA_H
#define TDACOLA_H

#include <stddef.h>


void crearCola(Cola* pc);
int encolar(Cola* pc, const void* dato, size_t tamElem);
int desencolar(Cola* pc, void* dato, size_t tamElem);
int verFrenteDeCola(const Cola* pc, void* dato, size_t tamElem);
int colaVacia(const Cola* pc);
int colaLlena(const Cola* pc, size_t tamElem);
void vaciarCola(Cola* pc);


#endif // TDACOLA_H
