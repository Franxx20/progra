#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include<stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct sNodo {
void * dato;
unsigned tamDato;
struct sNodo * sig;
}Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void * d1,const void * d2);
typedef void (*Actualizar) (void *actualizado, const void * actualizador);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaAlPrincipio(Lista *l,const void * dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato);
bool insertarEnPosicionDeLista(Lista *l, const void * dato, unsigned tamDato,int pos);

bool eliminarDeListaAlPrincipio(Lista *l, void * dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato);
bool eliminarDePosicionDeLista(Lista *l, void * dato, unsigned tamDato, int pos);

int buscarEnListaOrd(const Lista *l, void * dato, unsigned tamDato,Cmp cmp);
int buscarEnListaDesOrd(const Lista *l, void * dato, unsigned tamDato, Cmp cmp);

bool verEnListaAlPrincipio(const Lista *l , void * dato, unsigned tamDato);
bool verEnListaAlFinal(const Lista *l , void * dato, unsigned tamDato);
bool verEnPosicionDeLista(const Lista *l , void * dato, int pos);

void ordenarListaInsercion(Lista *l, Cmp cmp);
Lista * buscarMenorDeLista(Lista *l, Cmp cmp);






#endif // LISTA_H_INCLUDED
