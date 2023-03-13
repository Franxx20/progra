#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include<stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef int (*Cmp) (const void * dato1,const void *dato2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Accion) (void * accion, void * datosAccion);

typedef struct sNodo
{
    void * dato;
    unsigned tamDato;
    struct sNodo * sig;
    struct sNodo * ant;
} Nodo;

typedef Nodo * Lista;

void crearLista( Lista *l);
void vaciarLista( Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaAlFinal(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos);

bool verEnListaAlInicio(const Lista *l, void * dato, unsigned tamDato);
bool verEnListaAlFinal(const Lista *l, void * dato, unsigned tamDato);
bool verEnListaPorPos(const Lista *l, void * dato, unsigned tamDato, int pos);

bool eliminarDeListaAlInicio(Lista *l, void *dato, unsigned tamDato);
bool eliminarDeListaAlFinal(Lista *l, void * dato, unsigned tamDato);
bool eliminarDeListaPorPos(Lista *l, void * dato, unsigned tamDato, int pos);

void ordenarLista(Lista *l, Cmp cmp);

bool insertarEnListaOrdenada(Lista *l, void * dato, unsigned tamDato,Cmp cmp, Actualizar actualizar);
bool buscarEnListaOrdenada(const Lista *l, void * dato, unsigned tamDato, Cmp cmp);
bool buscarEnListaDesordenada(const Lista *l, void * dato, unsigned tamDato,Cmp cmp);

void recorrerLista(Lista *l, Accion accion,void *datosAccion);

int eliminarDuplicadosListaOrd(Lista *l, Cmp cmp,Actualizar actualizar);
int eliminarDuplicadosListaDes(Lista *L,Cmp cmp,Actualizar actualizar);


#endif // LISTA_H_INCLUDED
