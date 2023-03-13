#ifndef UTILITARIAS_H
#define UTILITARIAS_H

#include "../Comun/Comun.h"


typedef void (*CopiarIdx)(void* pvIdx, const void* pvReg, int nroReg);


void generarIndice(const char* pathBin, size_t tamElem, size_t tamIdx, CopiarIdx copiarIdx, Cmp cmpIdx);
void cargarIndiceEnLista(const char* pathIdx, size_t tamIdx, Lista* lista, Cmp cmpIdx);


#endif // UTILITARIAS_H
