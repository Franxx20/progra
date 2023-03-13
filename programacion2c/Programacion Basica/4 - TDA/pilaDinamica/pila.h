/* ------------------------------------------------------------------------- */
/*                           pila dinamica | pila.h                          */
/* ------------------------------------------------------------------------- */

#ifndef PILA_H_DINAMICA
#define PILA_H_DINAMICA

typedef struct sNodo
{
    void            *info;
    unsigned        tamInfo;
    struct sNodo    *sig;
} tNodo;
typedef tNodo *tPila;

void crearPila(tPila *p);
void vaciarPila(tPila *p);
int ponerEnPila(tPila *p, const void *d, unsigned cantBytes);
int sacarDePila(tPila *p, void *d, unsigned cantBytes);
int pilaLlena(const tPila *p, unsigned cantBytes);
int pilaVacia(const tPila *p);
int verTope(const tPila *p, void *d, unsigned cantBytes);

#endif

/* ------------------------------------------------------------------------- */