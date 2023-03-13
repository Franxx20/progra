#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#define MIN(a,b) ((a)<(b)?(a):(b))

#define ERR_NODO -1
#define ERR_ARCHIVO -2
#define TODO_OK 0
#define ERR_GEN -3
#define ERR_SIN_MEM -4
#define ERR_DUPLICADO -5

typedef int (*Cmp) (const void * d1, const void *d2);
typedef void (*Mostrar) (const void * dato, int nivel);
typedef void (*Accion) (void * accion, void * datosAccion);


typedef struct sNodo{
void * dato;
unsigned tamDato;
struct sNodo * hIzq;
struct sNodo * hDer;

}Nodo;

typedef Nodo * Arbol;

Nodo * crearNodo(void * dato, unsigned tamDato);

void crearArbol(Arbol *t);
int vaciarArbol(Arbol *t);

int arbolLleno(const Arbol *t, unsigned tamDato);

int insertarEnArbol(Arbol *t, const void * dato, unsigned tamDato, Cmp cmp);
int buscarEnArbol(const Arbol *t, void * dato, unsigned tamDato, Cmp cmp);

int recorrerArbolEnOrden(const Arbol *t,Accion accion, void * datosAccion);
int mostrarArbolEnOrden(const Arbol *t, Mostrar mostrar);
int mostrarArbolEnOrdenRec(const Arbol *t, Mostrar mostrar, int nivel);


#endif
