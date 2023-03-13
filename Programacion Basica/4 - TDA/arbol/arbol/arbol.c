/* ------------------------------------------------------------------------- */
/*                          arbol binario | arbol.c                          */
/* ------------------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arbol.h"

#define MINIMO(X, Y)    ((X) < (Y)? (X) : (Y))

/* Funciones Privadas */
tArbol *_mayorNodo(const tArbol *tree);
tArbol *_menorNodo(const tArbol *tree);


void crearArbol(tArbol *tree)
{
    *tree = NULL;
}


void vaciarArbol(tArbol *tree)
{
    if(!(*tree)) {
        return;
    }

    vaciarArbol(&(*tree)->izq);
    vaciarArbol(&(*tree)->der);

    free((*tree)->data);
    free(*tree);

    *tree = NULL;
}


int arbol_insertar(tArbol *tree, const void *data, unsigned tam, comparar cmp)
{
    tNodoArbol *nuevo;
    int rc;

    while(*tree) {

        rc = cmp(data, (*tree)->data);
        if(rc < 0) {
            tree = &(*tree)->izq;
        }
        else if (rc > 0) {
            tree = &(*tree)->der;
        }
        else {
            return 0;
        }
    }

    nuevo = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if( !nuevo || !(nuevo->data = malloc(tam)) ) {
        free(nuevo);
        return 0;
    }

    nuevo->tamInfo = tam;
    memcpy(nuevo->data, data, tam);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    *tree = nuevo;

    return 1;
}


int arbol_insertarRecursivo(tArbol *tree, const void *data, unsigned tam, comparar cmp)
{
    tNodoArbol *nuevo;
    int rc;

    if(*tree)
    {
        rc = cmp(data, (*tree)->data);
        if(rc < 0) {
            return arbol_insertarRecursivo(&(*tree)->izq, data, tam, cmp);
        }
        if (rc > 0) {
            return arbol_insertarRecursivo(&(*tree)->der, data, tam, cmp);
        }
        return 0;
    }

    nuevo = (tNodoArbol *)malloc(sizeof(tNodoArbol));
    if( !nuevo || !(nuevo->data = malloc(tam)) ) {
        free(nuevo);
        return 0;
    }

    nuevo->tamInfo = tam;
    memcpy(nuevo->data, data, tam);
    nuevo->der = NULL;
    nuevo->izq = NULL;
    *tree = nuevo;

    return 1;
}


void arbol_recorrerOrden(const tArbol *tree, accion acc)
{
    if(*tree) {
        arbol_recorrerOrden(&(*tree)->izq, acc);
        acc((*tree)->data, (*tree)->tamInfo);
        arbol_recorrerOrden(&(*tree)->der, acc);
    }
}


void arbol_recorrerOrdenInverso(const tArbol *tree, accion acc)
{
    if(*tree) {
        arbol_recorrerOrdenInverso(&(*tree)->der, acc);
        acc((*tree)->data, (*tree)->tamInfo);
        arbol_recorrerOrdenInverso(&(*tree)->izq, acc);
    }
}


void arbol_recorrerPreOrden(tArbol *tree, accion acc)
{ 
    if(*tree) {
        acc((*tree)->data, (*tree)->tamInfo);
        arbol_recorrerPreOrden(&(*tree)->izq, acc);
        arbol_recorrerPreOrden(&(*tree)->der, acc);
    }
}


void arbol_recorrerPosOrden(const tArbol *tree, accion acc)
{
    if(*tree) {
        arbol_recorrerPosOrden(&(*tree)->izq, acc);
        arbol_recorrerPosOrden(&(*tree)->der, acc);
        acc((*tree)->data, (*tree)->tamInfo);
    }
}


int arbol_eliminarRaiz(tArbol *tree)
{
    tNodoArbol **remp,
                *elim;
    
    if(!(*tree)) {
        return 0;
    }

    free((*tree)->data);
    if (!(*tree)->izq && !(*tree)->der) {
        free(*tree);
        *tree = NULL;
        return 1;
    }

    remp = (arbol_altura(&(*tree)->izq) > arbol_altura(&(*tree)->der))?
        _mayorNodo(&(*tree)->izq) :
        _menorNodo(&(*tree)->der);

    elim = *remp;
    (*tree)->data = elim->data;
    (*tree)->tamInfo = elim->tamInfo;

    *remp = (elim->izq)? elim->izq : elim->der;
    free(elim);

    return 1;
}


int arbol_eliminaNodo(tArbol *tree, void *data, unsigned tam, comparar cmp)
{
    if(!(tree = arbol_buscar(tree, data, tam, cmp))) {
        return 0;
    }

    memcpy(data, (*tree)->data, MINIMO(tam, (*tree)->tamInfo));
    return arbol_eliminarRaiz(tree);
}


tArbol *arbol_buscar(const tArbol *tree, void *data, unsigned tam, comparar cmp)
{
    int rc = -1;
    tArbol *nodo = NULL;

    while(*tree && rc) {
        rc = cmp(data, (*tree)->data);

        if(rc < 0) {
            tree = &(*tree)->izq;
        }
        else if (rc > 0) {
            tree = &(*tree)->der;
        }
    }

    if(rc == 0) {
        nodo = (tArbol *)tree;
    }

    return nodo;
}


tArbol *_mayorNodo(const tArbol *tree)
{
    if(!(*tree)) {
        return NULL;
    }
    if(!(*tree)->der) {
        return (tArbol *)tree;
    }

    return _mayorNodo(&(*tree)->der);
}


tArbol *_menorNodo(const tArbol *tree)
{
    if(!(*tree)) {
        return NULL;
    }
    if(!(*tree)->izq) {
        return (tArbol *)tree;
    }
    return _menorNodo(&(*tree)->izq);
}


size_t arbol_altura(const tArbol * tree)
{
    int hi, hd;
    if(!(*tree)) {
        return 0;
    }

    hi = arbol_altura(&(*tree)->izq);
    hd = arbol_altura(&(*tree)->der);
    
    return (hi > hd? hi : hd) +1;
}


size_t arbol_cantNodos(const tArbol * tree)
{
    if(!(*tree)) {
        return 0;
    }
    return arbol_cantNodos(&(*tree)->izq) + arbol_cantNodos(&(*tree)->der) + 1;
}


int arbol_mayorNodo(const tArbol * tree, void * data, unsigned tam)
{
    if(!(tree = _mayorNodo(tree))) {
        return 0;
    }
    memcpy(data, (*tree)->data, MINIMO(tam, (*tree)->tamInfo));
    return 1;
}


int arbol_menorNodo(const tArbol * tree, void * data, unsigned tam)
{
    if(!(tree = _menorNodo(tree))) {
        return 0;
    }
    memcpy(data, (*tree)->data, MINIMO(tam, (*tree)->tamInfo));
    return 1;
}


size_t arbol_cantNodosHastaNivel(const tArbol *tree, int nivel)
{
    if(!(*tree)) {
        return 0;
    }

    if(!nivel) {
        return 1;
    }

    return arbol_cantNodosHastaNivel(&(*tree)->izq, nivel-1)
        + arbol_cantNodosHastaNivel(&(*tree)->der, nivel-1) + 1;
}


int arbol_esCompleto(const tArbol *tree)
{
    int h = arbol_altura(tree);
    return arbol_cantNodos(tree) == (pow(2,h) - 1);
}


int arbol_esBalanceado(const tArbol *tree)
{
    int h = arbol_altura(tree);
    return arbol_cantNodosHastaNivel(tree, h-2) == pow(2,h-1)-1;
}


int arbol_esAVL(const tArbol *tree)
{
    int hi, hd;
    if(!(*tree)) {
        return 1;
    }

    hi = arbol_altura(&(*tree)->izq);
    hd = arbol_altura(&(*tree)->der);

    if(abs(hi-hd) > 1) {
        return 0;
    }

    return arbol_esAVL(&(*tree)->izq) && arbol_esAVL(&(*tree)->der);
}


void arbol_level(const tArbol *tree, unsigned nivel, accion acc)
{
    if(!(*tree)) {
        return;
    }
    if(nivel == 1) {
        acc((*tree)->data, arbol_altura(tree));
    }
    else if(nivel > 1) {
        arbol_level(&(*tree)->izq, nivel-1, acc);
        arbol_level(&(*tree)->der, nivel-1, acc);
    }
}


void arbol_levelOrder(const tArbol *tree, accion acc)
{
    size_t i, h = arbol_altura(tree);
    
    for(i = 1; i <= h; i++) {
        arbol_level(tree, i, acc);
        puts("");
    }
}
