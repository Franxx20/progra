/* ------------------------------------------------------------------------- */
/*                           cola dinamica | cola.h                          */
/* ------------------------------------------------------------------------- */

#ifndef COLA_H_DINAMICA
#define COLA_H_DINAMICA

typedef struct sNodo
{
    void            *info;
    unsigned        tamInfo;
    struct sNodo    *sig;
}  tNodo;

typedef struct
{
    tNodo   *pri,
            *ult;
}  tCola;

void crearCola(tCola *p);
void vaciarCola(tCola *p);
int ponerEnCola(tCola *p, const void *d, unsigned cantBytes);
int sacarDeCola(tCola *p, void *d, unsigned cantBytes);
int colaLlena(const tCola *p, unsigned cantBytes);
int colaVacia(const tCola *p);
int verFrente(const tCola *p, void*d, unsigned cantBytes);

#endif

/* ------------------------------------------------------------------------- */
