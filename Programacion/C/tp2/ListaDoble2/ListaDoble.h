#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include<stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct sNodo
{
    void * dato;
    unsigned tamDato;
    struct sNodo * sig;
    struct sNodo * ant;

} Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void *, const void *);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Accion) (void * Accion, void * datosAccion);


Nodo * crearNodo(const void * dato, unsigned tamDato);
void destruirNodo(Nodo * nae, void * dato, unsigned tamDato);

void crearLista(Lista *l);
void vaciarLista(Lista *l, unsigned tamDato);

bool listaVacia(const Lista *l);
bool listaLlena(const Lista *l, unsigned tamDato);

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

bool eliminarDuplicados(Lista *l, const void * dato, unsigned tamDato, Cmp cmp);

void recorrerLista(const Lista *l, Accion accion,void * datosAccion);
#endif // LISTADOBLE_H_INCLUDED
