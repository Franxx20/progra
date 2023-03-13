#ifndef TDACOLA_H
#define TDACOLA_H

#include <stddef.h>
#include <stdbool.h>


#ifdef TDA_COLA_IMPL_DINAMICA
    #include "../TDAColaImplDinamica/TDAColaImplDinamica.h"
#endif

#ifdef TDA_COLA_IMPL_DINAMICA_CIRCULAR
    #include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#endif


void crearCola(Cola* pc);
bool encolar(Cola* pc, const void* elem, size_t tamElem);
bool desencolar(Cola* pc, void* elem, size_t tamElem);
bool verFrenteDeCola(const Cola* pc, void* elem, size_t tamElem);
bool colaVacia(const Cola* pc);
bool colaLlena(const Cola* pc, size_t tamElem);
void vaciarCola(Cola* pc);


#endif // TDACOLA_H
