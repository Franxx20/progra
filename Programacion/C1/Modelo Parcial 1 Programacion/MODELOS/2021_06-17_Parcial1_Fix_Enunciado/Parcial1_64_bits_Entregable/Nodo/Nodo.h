#ifndef NODO_H
#define NODO_H

//#include <stddef.h>

typedef struct sNodo
{
    void* dato;
    size_t tam;
    struct sNodo* sig;
} Nodo;


#endif // NODO_H
