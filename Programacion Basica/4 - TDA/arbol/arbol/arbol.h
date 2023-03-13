/* ------------------------------------------------------------------------- */
/*                          arbol binario | arbol.h                          */
/* ------------------------------------------------------------------------- */

#ifndef ARBOL_BIN_H_INCLUDED
#define ARBOL_BIN_H_INCLUDED

#include <stdio.h>

typedef struct sNodoArbol
{
    void *data;
    unsigned tamInfo;
    struct sNodoArbol   *izq,
                        *der;
} tNodoArbol;

typedef tNodoArbol *tArbol;

typedef void (*accion) (const void* data, unsigned tam);
typedef int  (*comparar) (const void *, const void *);
typedef void (*save)(const void *data, unsigned tam, void *where);

void crearArbol(tArbol *tree);
void vaciarArbol(tArbol *tree);

int arbol_insertar(tArbol *tree, const void *data, unsigned tam, comparar cmp);
int arbol_insertarRecursivo(tArbol *tree, const void *data, unsigned tam, comparar cmp);

void arbol_recorrerOrden(const tArbol *tree, accion acc);
void arbol_recorrerOrdenInverso(const tArbol *tree, accion acc);
void arbol_recorrerPreOrden(tArbol *tree, accion acc);
void arbol_recorrerPosOrden(const tArbol *tree, accion acc);

int arbol_eliminarRaiz(tArbol *tree);
int arbol_eliminaNodo(tArbol *tree, void *data, unsigned tam, comparar cmp);

tArbol *arbol_buscar(const tArbol *tree, void *data, unsigned tam, comparar cmp);

size_t arbol_altura(const tArbol *tree);
size_t arbol_cantNodos(const tArbol *tree);
size_t arbol_cantNodosHastaNivel(const tArbol *tree, int nivel);

int arbol_mayorNodo(const tArbol *tree, void *data, unsigned tam);
int arbol_menorNodo(const tArbol *tree, void *data, unsigned tam);

int arbol_esCompleto(const tArbol *tree);
int arbol_esBalanceado(const tArbol *tree);
int arbol_esAVL(const tArbol *tree);

void arbol_level(const tArbol *tree, unsigned nivel, accion acc);
void arbol_levelOrder(const tArbol *tree, accion acc);

#endif 

/* ------------------------------------------------------------------------- */
