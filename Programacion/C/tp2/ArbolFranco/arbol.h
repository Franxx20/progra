#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include<stdio.h>
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (const void * c1, const void * c2);
typedef void (*Accion) (void *accion, void * dAccion);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);

typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo *hIzq, *hDer;
}Nodo;

typedef Nodo * Arbol;



void crearArbol(Arbol *t);
int vaciarArbol(Arbol *t);

int insertarEnArbol(Arbol * t, const void * dato, unsigned tamDato, Cmp cmp);
int insertarEnArbolRec(Arbol *t, const void* dato, unsigned tamDato, Cmp cmp);

void recorrerArbolPre(Arbol *t, Accion accion, void * dAccion);
void recorrerArbolIn(Arbol *t, Accion accion, void * dAccion);
void recorrerArbolPos(Arbol *t, Accion accion, void * dAccion);

int podarArbol(Arbol *t, int nivel);
int contarNodosArbol(const Arbol *t);

int cargarEnArbolDeUnArchivoOrdenado(Arbol *t, int li, int ls, int tamDato,FILE *fp,Cmp cmp);

int eliminarNodoArbol(Arbol *t, void *dato, unsigned tamDato,Cmp cmp);
int eliminarRaizArbol(Arbol *t, void *dato);

Arbol * buscarEnArbol(const Arbol *t, void *dato, unsigned tamDato, Cmp cmp);




#endif // ARBOL_H_INCLUDED
