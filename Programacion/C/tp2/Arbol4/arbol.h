#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include<stdio.h>
#include<stdbool.h>
#define MIN(a,b) ((a)<(b)?(a):(b))

#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2

typedef int (*Cmp) (const void *dato1, const void *dato2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Accion) (void * accion, void * datosAccion);
typedef void (*Mostrar) (const void * dato, int nivel);

typedef struct sNodo{
    void * dato;
    unsigned tamDato;
    struct sNodo * hIzq;
    struct sNodo * hDer;

}Nodo;

typedef Nodo * Arbol;

void crearArbol(Arbol * t);
int vaciarArbol(Arbol *t);

bool arbolLleno(const Arbol *t, unsigned tamDato);
bool arbolVacio(const Arbol *t);

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar);
bool eliminarDeArbol(Arbol *t, void * dato, unsigned tamDato, Cmp cmp);

bool buscarEnArbol(const Arbol *t, void * dato, unsigned tamDato, Cmp cmp);

void recorrerArbolPre(Arbol *t,Accion accion, void * datosAccion); // R - I - D
void recorrerArbolEn(Arbol *t,Accion accion, void * datosAccion);  // I - R - D
void recorrerArbolPos(Arbol *t,Accion accion, void * datosAccion); // I - D - R

#endif // ARBOL_H_INCLUDED
