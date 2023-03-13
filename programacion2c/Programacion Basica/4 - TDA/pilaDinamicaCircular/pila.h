/* ------------------------------------------------------------------------- */
/*                  pila dinamica circular | pila.h                          */
/* ------------------------------------------------------------------------- */

#ifndef PILA_H_DINAMICA_CIRCULAR
#define PILA_H_DINAMICA_CIRCULAR

typedef struct sNodo
{
    void            *info;
    unsigned        tamInfo;
    struct sNodo    *sig;
} tNodo;
typedef tNodo *tPila;

void crearPila(tPila *pila);
void vaciarPila(tPila *pila);
int pilaLlena(const tPila *pila, unsigned cantBytes);
int pilaVacia(const tPila *pila);
int ponerEnPila(tPila *pila, const void *data, unsigned cantBytes);
int sacarDePila(tPila *pila, void *data, unsigned cantBytes);
int verTope(const tPila *pila, void *data, unsigned cantBytes);

#endif

/* ------------------------------------------------------------------------- */