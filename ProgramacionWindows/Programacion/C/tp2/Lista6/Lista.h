#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdbool.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct sNodo{
void * dato;
unsigned tamDato;
struct sNodo * sig;

}Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void *d1, const void *d2);
typedef void (*Actualizar) (void *actualizado, const void * actualizador);
typedef void (*Accion) (void * accion, void * datosAccion);

Nodo * crearNodo(const void * dato, unsigned tamDato);
void destruirNodo(Nodo * nae, void * dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaAlInicio(Lista *l , const void * dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaPorPos(Lista *l,const void * dato, unsigned tamDato, int pos);

bool eliminarDeListaAlPrincipio(Lista *l ,void * dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato);
bool eliminarDeListaPorPos(Lista *l, void * dato, unsigned tamDato, int pos);

bool verEnListaAlPrincipio(Lista *l, void * dato, unsigned tamDato);
bool verEnListaAlFinal(Lista *l, void * dato, unsigned tamDato);
bool verEnListaPorPor(Lista *l, void * dato, unsigned tamDato,int pos);

int buscarEnListaOrd(Lista *l, void * dato, unsigned tamDato, Cmp cmp);
int buscarEnListaDes(Lista *l, void * dato, unsigned tamDato, Cmp cmp);

void ordenarLista(Lista *l, Cmp cmp);
void ordenarListaInsersion(Lista *l, Cmp cmp);
Lista *buscarMenorDeLista(Lista *l, Cmp cmp);

void recorrerLista(Lista *l, Accion accion, void *datosAccion);

bool eliminarDuplicadosListaOrdConAcum(Lista *l, Cmp cmp, Actualizar actualizar);
bool eliminarDuplicadosListaDesConAcum(Lista *l, Cmp cmp, Actualizar actualizar);

bool insertarEnListaOrdConAcum(Lista *l, const void * dato, unsigned tamDato,Cmp cmp,Actualizar actualizar);
bool insertarEnListaDesConAcum(Lista *l, const void * dato, unsigned tamDato, Cmp cmp, Actualizar Actualizar);
#endif // LISTA_H_INCLUDED
