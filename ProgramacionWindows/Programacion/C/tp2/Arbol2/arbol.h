#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include<stdio.h>
#include<stdbool.h>
#define MIN(a,b) ((a) < (b)?(a):(b))

#define SIN_MEM -1
#define TODO_OK 0
#define DUPLICADO -2

typedef int (*Cmp) (const void * dato1, const void * dato2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Accion) (void * dato, void * datosAccion);



typedef struct sNodo
{
    void * dato;
    unsigned tamDato;
    struct sNodo *hIzq;
    struct sNodo *hDer;

}Nodo;

typedef Nodo * Arbol;

Nodo* crearNodo(const void * dato, unsigned tamDato);

void crearArbol(Arbol *t);
int vaciarArbol(Arbol *t);

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato,Cmp cmp,Actualizar Actualizar );
bool eliminarDeArbol(Arbol *t, void * dato, unsigned tamDato, Cmp cmp, Actualizar actualizar);

bool buscarEnArbol(const Arbol *t, void * dato, unsigned tamDato, Cmp cmp);

void recorrerArbolPre( Arbol *t, Accion accion, void * dAccion);
void recorrerArbolIn( Arbol *t, Accion accion, void * dAccion);
void recorrerArbolPos( Arbol *t, Accion accion,void * dAccion);

bool cargarEnArbolDeUnArchivoOrdenado(Arbol *t, int li,int ls, int tamDato, FILE *fp, Cmp cmp,Actualizar actualizar);

int podarArbol(Arbol *t, int nivel);

int contarNodoArbol(const Arbol *t);






#endif // ARBOL_H_INCLUDED
