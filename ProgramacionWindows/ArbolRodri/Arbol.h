#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED


#include <stdio.h>


typedef struct sNodo
{
    void* elem;
    unsigned tamElem;
    struct sNodo* hIzq;
    struct sNodo* hDer;
}tNodo;

typedef tNodo* Arbol;

typedef int(*Cmp)(const void*, const void*);
typedef void(*Accion)(void*,void*);
typedef int(*Insertar)(Arbol*,FILE*, size_t ,Cmp);


void crearArbol(Arbol *pa);
int insertarArbol(Arbol *pa, void* elem, size_t tamElem, Cmp cmp);
int podarArbol(Arbol* pa, int nivel);
int vaciarArbol(Arbol *pa);
void recorrerArbolPre(Arbol *pa, Accion accion, void* dAcc);
void recorrerArbolPos(Arbol *pa, Accion accion, void* dAcc);
void recorrerArbolEn(Arbol *pa, Accion accion, void* dAcc);
void cargarArbolDeArchivoOrd(Arbol *pa, FILE *pf, size_t tamElem, int li, int ls, Cmp cmp, Insertar insertar);

#endif // ARBOL_H_INCLUDED
