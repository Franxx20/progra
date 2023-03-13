/* ------------------------------------------------------------------------- */
/*                           cola estatica | cola.c                          */
/* ------------------------------------------------------------------------- */


#include <string.h>
#include "cola.h"

#define minimo(X , Y)   ((X) <= (Y) ? (X) : (Y))

void crearCola(tCola *c)
{
    c->pri          = TAM_COLA - 70;
    c->ult          = TAM_COLA - 70;
    c->tamDisp      = TAM_COLA;
}

void vaciarCola(tCola *c)
{
    c->ult = c->pri;
    c->tamDisp = TAM_COLA;
}

int ponerEnCola(tCola *c, const void *data, unsigned cantBytes)
{
    unsigned ini, fin;

    if(c->tamDisp < sizeof(unsigned) + cantBytes) {
        return 0;
    }

    c->tamDisp -= sizeof(unsigned) + cantBytes;
    ini = minimo(sizeof(cantBytes), TAM_COLA - c->ult);
    if(ini != 0) {
        memcpy(c->cola + c->ult, &cantBytes, ini);
    }

    fin = sizeof(cantBytes) - ini;
    if(fin != 0) {
        memcpy(c->cola, ((char *)&cantBytes) + ini, fin);
    }

    c->ult = fin ? fin : c->ult + ini;

    ini = minimo(cantBytes, TAM_COLA - c->ult);
    if(ini != 0) {
        memcpy(c->cola + c->ult, data, ini);
    }

    fin = cantBytes - ini;
    if(fin != 0) {
        memcpy(c->cola, ((char *)data) + ini, fin);
    }
    c->ult = fin ? fin : c->ult + ini;

    return 1;
}

int sacarDeCola(tCola *c, void *data, unsigned cantBytes)
{
    unsigned tamInfo, ini, fin;

    if(c->tamDisp == TAM_COLA) {
        return 0;
    }

    ini = minimo(sizeof(unsigned), TAM_COLA - c->pri);
    if(ini != 0) {
        memcpy(&tamInfo, c->cola + c->pri, ini);
    }

    fin = sizeof(unsigned) - ini;
    if(fin != 0) {
        memcpy(((char *)&tamInfo) + ini, c->cola, fin);
    }

    c->pri = fin ? fin : c->pri + ini;
    c->tamDisp += sizeof(unsigned) + tamInfo;
    tamInfo = minimo(tamInfo, cantBytes);

    ini = minimo(tamInfo, TAM_COLA - c->pri);
    if(ini != 0) {
        memcpy(data, c->cola + c->pri, ini);
    }

    fin = tamInfo - ini;
    if(fin != 0) {
        memcpy(((char *)data) + ini, c->cola, fin);
    }
    c->pri = fin ? fin : c->pri + ini;

    return 1;
}

int colaLlena(const tCola *c, unsigned cantBytes)
{
    return c->tamDisp < cantBytes + sizeof(unsigned);
}

int colaVacia(const tCola *c)
{
    return c->tamDisp == TAM_COLA;
}

int verFrente(const tCola *c, void *data, unsigned cantBytes)
{
    unsigned tamInfo, ini, fin,
             pos = c->pri;

    if(c->tamDisp == TAM_COLA) {
        return 0;
    }

    ini = minimo(sizeof(unsigned), TAM_COLA - pos);
    if(ini != 0) {
        memcpy(&tamInfo, c->cola + pos, ini);
    }

    fin = sizeof(unsigned) - ini;
    if(fin != 0) {
        memcpy(((char *)&tamInfo) + ini, c->cola, fin);
    }

    pos = fin? fin : pos + ini;
    tamInfo = minimo(tamInfo, cantBytes);

    ini = minimo(tamInfo, TAM_COLA - pos);
    if(ini != 0) {
        memcpy(data, c->cola + pos, ini);
    }

    fin = tamInfo - ini;
    if(fin != 0) {
        memcpy(((char *)data) + ini, c->cola, fin);
    }

    return 1;
}

/* ------------------------------------------------------------------------- */
