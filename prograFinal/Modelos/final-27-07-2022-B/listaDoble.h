#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include"comun.h"

typedef struct sNodo{
void * dato;
unsigned tamDato;
struct sNodo * sig;
struct sNodo * ant;
}Nodo;

typedef Nodo * Lista;





void crearLista(Lista *l);
void vaciarLista(Lista *l);

int insertarEnListaAlFinal(Lista *l, const void *dato, unsigned tamDato);
int insertarEnListaOrd(Lista *l, const void * dato, unsigned tamDato, Cmp cmp,Actualizar actualizar);
int eliminarPrimeroDeLista(Lista *l, void * dato,  unsigned tamDato);

int listaLlena(const Lista *l, unsigned tamDato);
int listaVacia(const Lista *l);




#endif
