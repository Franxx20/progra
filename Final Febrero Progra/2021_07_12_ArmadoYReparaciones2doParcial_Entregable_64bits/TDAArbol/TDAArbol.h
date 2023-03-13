#ifndef TDAARBOL_H
#define TDAARBOL_H

#include "../TDA/TDA.h"


void crearArbol(Arbol* pa);
int buscarEnArbol(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int insertarEnArbol(Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int insertarOActualizarEnArbol(Arbol* pa, void* dato, size_t tamElem, Cmp cmp, Actualizar actualizar);
int eliminarDeArbol(Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int alturaArbol(const Arbol* pa);
int cantElementosArbol(const Arbol* pa);
int grabarArbol(const Arbol* pa, const char* nomArch);
int cargarArbol(Arbol* pa, size_t tamElem, const char* nomArch);
void recorrerArbolPreOrden(Arbol* pa, Accion accion, void* datosAccion);
void recorrerArbolEnOrden(Arbol* pa, Accion accion, void* datosAccion);
void recorrerArbolPosOrden(Arbol* pa, Accion accion, void* datosAccion);
int arbolCompleto(const Arbol* pa);
int arbolBalanceado(const Arbol* pa);
int arbolAVL(const Arbol* pa);
int podarArbol(Arbol* pa, int nivel);
int eliminarNivelDeArbol(Arbol* pa, int nivel);
int vaciarArbol(Arbol* pa);


#endif // TDAARBOL_H
