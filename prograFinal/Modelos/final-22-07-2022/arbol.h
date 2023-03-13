#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2

typedef struct sNodo{
void * dato;
unsigned tamDato;
struct sNodo * hIzq;
struct sNodo * hDer;
}Nodo;

typedef Nodo * Arbol;

typedef void (*Mostrar) (const void * dato, int nivel);
typedef int (*Cmp) (const void * d1,const void * d2);
typedef void (*Actualizar) (void *actualizado, void * actualizador);

Nodo * crearNodo(const void * dato, unsigned tamDato);

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar);
void crearArbol(Arbol *t);
void mostrarArbolSegunNivel(const Arbol *t, Mostrar mostrar, int nivel);


int vaciarArbol(Arbol *t);

#endif
