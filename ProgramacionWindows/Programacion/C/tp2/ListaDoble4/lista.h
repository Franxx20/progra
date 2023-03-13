#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include<stdbool.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct sNodo
{

    void * dato;
    unsigned tamDato;
    struct sNodo * sig;
    struct sNodo *ant;
}
Nodo;

typedef Nodo * Lista;

typedef int (*Cmp) (const void * dato1, const void * dato2);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Accion) (void *accion, void * datosAccion);


void crearLista(Lista *l);
void vaciarLista(Lista *l);

bool listaLlena(const Lista *l, unsigned tamDato);
bool listaVacia(const Lista *l);

bool insertarEnListaAlInicio(Lista *l, const void * dato, unsigned tamDato);
bool insertarEnListaALFinal(Lista *l, const void * dato,  unsigned tamDato);
bool insertarEnListaPorPos(Lista *l, const void * dato, unsigned tamDato, int pos);

bool verPrimeroDeLista(const Lista *l, void * dato, unsigned tamDato);
bool verUltimoDelista(const Lista *l, void * dato, unsigned tamDato);
bool verPosicionLista(const Lista *l, void * dato, unsigned tamDato);

bool eliminarDeListaAlInicio(Lista *l, const void * dato, unsigned tamDato);
bool eliminarDelistaAlFinal(Lista *l, const void * dato, unsigned tamDato);
bool eliminarDeListaPorPos(Lista *l, const void * dato, unsigned tamDato);




#endif // LISTA_H_INCLUDED
