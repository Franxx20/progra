/* ------------------------------------------------------------------------- */
/*                           cola estatica | cola.h                          */
/* ------------------------------------------------------------------------- */

#ifndef COLA_C_ESTATICA
#define COLA_C_ESTATICA

#define TAM_COLA    400

typedef struct
{
    char        cola[TAM_COLA];
    unsigned    pri,
                ult,
                tamDisp;
}  tCola;

void crearCola(tCola *c);
void vaciarCola(tCola *c);
int ponerEnCola(tCola *c, const void *data, unsigned cantBytes);
int sacarDeCola(tCola *c, void *data, unsigned cantBytes);
int colaLlena(const tCola *c, unsigned cantBytes);
int colaVacia(const tCola *c);
int verFrente(const tCola *c, void *data, unsigned cantBytes);

#endif

/* ------------------------------------------------------------------------- */
