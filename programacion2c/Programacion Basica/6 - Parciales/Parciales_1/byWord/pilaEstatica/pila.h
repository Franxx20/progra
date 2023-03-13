/* ------------------------------------------------------------------------- */
/*                           pila estatica | pila.h                          */
/* ------------------------------------------------------------------------- */

#ifndef PILA_H_ESTATICA
#define PILA_H_ESTATICA

#define TAM_PILA    (12 + sizeof(unsigned)) * 3

typedef struct
{
    char        pila[TAM_PILA];
    unsigned    tope;
} tPila;

void crearPila(tPila *p);
void vaciarPila(tPila *p);
int  ponerEnPila(tPila *p, const void *d, unsigned cantBytes);
int  sacarDePila(tPila *p, void *d, unsigned cantBytes);
int  pilaLlena(const tPila *p, unsigned cantBytes);
int  pilaVacia(const tPila *p);
int  verTope(const tPila *p, void *d, unsigned cantBytes);

#endif

/* ------------------------------------------------------------------------- */
