/* ------------------------------------------------------------------------- */
/*                           lista simple | lista.h                          */
/* ------------------------------------------------------------------------- */
#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <stdio.h>

#define DUPLICADO 2

typedef struct sNodo
{
    void            *data;
    unsigned        cantBytes;
    struct sNodo    *sig;
} tNodo;
typedef tNodo *tLista;

typedef void (*accion) (const void* data, void *params);
typedef int  (*comparar) (const void *data_1, const void *data_2, void *params);
typedef void (*mostrar) (const void *data, FILE *stream);
typedef int  (*acumular) (void *, const void *);

void crearLista(tLista *list);
int  listaVacia(const tLista *list);
int  listaLlena(unsigned cantBytes);
int  vaciarLista(tLista *list);

int  lista_insertarInicio(tLista *list, const void *data, unsigned cantBytes);
int  lista_removerPrimero(tLista *list, void *data, unsigned cantBytes);
int  lista_verPrimero(const tLista *list, void *data, unsigned cantBytes);

int  lista_insertarFinal(tLista *list, const void *data, unsigned cantBytes);
int  lista_removerUltimo(tLista *list, void *data, unsigned cantBytes);
int  lista_verUltimo(const tLista *list, void *data, unsigned cantBytes);


/* Retorna 0 si no se encontro */
int  lista_insertarPosicion(tLista *list, const void *data, unsigned cantBytes,
                unsigned pos);
/* Retorna 0 si no se encontro */
int  lista_removerPosicion(tLista *list, void *data, unsigned cantBytes,
                unsigned pos);
/* Retorna 0 si no se encontro */
int  lista_verPosicion(const tLista *list, void *data, unsigned cantBytes,
                unsigned pos);


/* Ingresar un NULL como el argumento de acumular para permitir
 * añadir duplicados en la lista. En otro caso retorna DUPLICADOS = 2 */
int lista_insertar(tLista *list, const void *data, unsigned cantBytes,
				comparar comparar, acumular acumular);
/* Ingresar un NULL como el argumento de acumular para permitir
 * añadir duplicados en la lista. */
int  lista_insertarOrdenado(tLista *list, const void *data, unsigned cantBytes,
                comparar comparar, acumular acumular, void *params);
/* Mantiene una copia del dato original */
void lista_removerDuplicados(tLista *list, const void *data, comparar comparar);
size_t lista_contarDuplicados(const tLista *list, void *data,
				unsigned cantBytes, comparar comparar);


int  lista_mostrar(const tLista *list, mostrar mostrar, FILE *stream);
int  lista_mostrarInvertido(const tLista *list, mostrar mostrar, FILE *stream);


void lista_ordenar(tLista *list, comparar comparar);
void lista_filtrar(tLista *list, int (*filtro) (const void *));
void lista_recorrer(const tLista *list, accion accion, void *params);
void lista_recorrerInvertido(const tLista *list, accion accion, void *params);

/* Devuelve la posicion en la lista o -1 si no existe */
size_t  lista_buscar(const tLista *list, const void *data, comparar comparar);
size_t  lista_contar(const tLista *list);

tNodo **lista_buscarMenor(tLista *list, comparar comparar);
tNodo **lista_buscarMayor(tLista *list, comparar comparar);
void lista_ordenarSeleccion(tLista *list, comparar comparar);


#endif
/* ------------------------------------------------------------------------- */
