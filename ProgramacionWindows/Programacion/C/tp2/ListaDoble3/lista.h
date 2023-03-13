#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<stdbool.h>
#define MIN(a,b) ((a)<(b)?(a):(b))


typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo * sig;
    struct sNodo * ant;
} Nodo;

typedef Nodo *Lista;

typedef int (*Cmp) (const void * dato1, const void *dato2);
typedef void (*Actualizar) (void *actualizado, const void *actualizador);
typedef void (*Accion) (void *dato, void *datosAccion);


Nodo * crearNodo(const void *dato, unsigned tamDato);
void destruirNodo(Nodo * nae, void * dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);


bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos);

bool eliminarDeListaAlInicio(Lista *l, void * dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato);
bool eliminarDeListaPorPos(Lista *l, void * dato, unsigned tamDato, int pos);

bool verEnListaAlInicio(const Lista *l, void * dato, unsigned tamDato);
bool verEnlistaAlFinal(const Lista *l, void * dato, unsigned tamDato);
bool verEnListaPorPos(const Lista *l, void * dato, unsigned tamDato, int pos);

void listaOrdenar(Lista *l, Cmp cmp);
int listaBuscar(const Lista *l, void * dato, unsigned tamDato, Cmp cmp);

bool eliminarDuplicadosListaOrdenada(Lista *l,  Cmp cmp, Actualizar actualizar);
bool eliminarDuplicadosListaDesordenada(Lista *l, Cmp cmp, Actualizar actualizar);

void recorrerLista(const Lista *l, Accion accion,void * datosAccion);

#endif // LISTA_H_INCLUDED
