/* ------------------------------------------------------------------------- */
/*                           pila estatica | pila.c                          */
/* ------------------------------------------------------------------------- */

#include <string.h>
#include "pila.h"

#define minimo(X , Y)   ((X) <= (Y) ? (X) : (Y))

void crearPila(tPila *p)
{
    p->tope = TAM_PILA;
}

void vaciarPila(tPila *p)
{
    p->tope = TAM_PILA;
}

int ponerEnPila(tPila *p, const void *data, unsigned cantBytes)
{
    if(p->tope < cantBytes + sizeof(unsigned)) {
        return 0;
    }

    p->tope -= cantBytes;
    memcpy(p->pila + p->tope, data, cantBytes);
    p->tope -= sizeof(unsigned);
    memcpy(p->pila + p->tope, &cantBytes, sizeof(unsigned));

    return 1;
}

int sacarDePila(tPila *p, void *data, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA) {
        return 0;
    }

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
    p->tope += sizeof(unsigned);
    memcpy(data, p->pila + p->tope, minimo(cantBytes, tamInfo));
    p->tope += tamInfo;

    return 1;
}

int  pilaLlena(const tPila *p, unsigned cantBytes)
{
    return p->tope < cantBytes + sizeof(unsigned);
}

int pilaVacia(const tPila *p)
{
    return p->tope == TAM_PILA;
}

int verTope(const tPila *p, void *data, unsigned cantBytes)
{
    unsigned tamInfo;

    if(p->tope == TAM_PILA) {
        return 0;
    }

    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
    memcpy(data, p->pila + p->tope + sizeof(unsigned), minimo(cantBytes, tamInfo));

    return 1;
}

/* ------------------------------------------------------------------------- */