/* --------------------------------o---x---o--------------------------------
 *		    			cola.h     COLA DINÁMICA CIRCULAR3    
 *--------------------------------o---x---o-------------------------------- */
 
#ifndef COLA_H_DINAMICA_CIRCULAR
#define COLA_H_DINAMICA_CIRCULAR

#include <stdlib.h>
#include <string.h>
#define minimo(X , Y)   ((X) <= (Y) ? (X) : (Y))

typedef struct sNodo
{
    void            *info;
    unsigned        tamInfo;
    struct sNodo    *sig;
}  tNodo;

typedef tNodo *tCola;

void crearCola(tCola *p);
int colaLlena(const tCola *p, unsigned cantBytes);
int ponerEnCola(tCola *p, const void *d, unsigned cantBytes);
int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes);
void vaciarCola(tCola *p);
int colaVacia(const tCola *p);
int sacarDeCola(tCola *p, void *d, unsigned cantBytes);

#endif // COLA_H_DINAMICA_CIRCULAR

/* --------------------------------o---x---o-------------------------------- */