#include "Pila_Estatica_Lib.h"
#include <string.h>

void crearPila(Pila *pp)
{
    pp->tope = 0;
}
bool apilar(Pila *pp, const void *elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > TAM_PILA - pp->tope)
        return false;
    memcpy(pp->vPila + pp->tope, elem, tamElem);
    pp->tope += tamElem;
    *(size_t*)(pp->vPila + pp->tope) = tamElem;
    pp->tope += sizeof(size_t);
    return true;
}
bool desapilar(Pila *pp, void *elem, size_t tamElem)
{
    if(pp->tope == 0)
        return false;
    pp->tope -= sizeof(size_t);
    size_t tamElemApilada = *(size_t*)(pp->vPila + pp->tope);
    pp->tope -= tamElemApilada;
    memcpy(elem,pp->vPila + pp->tope, min(tamElem,tamElemApilada));
    return true;
}
bool topeDePila(const Pila *pp, void *elem, size_t tamElem)
{
    if(pp->tope == 0)
        return false;
    unsigned tope = pp->tope;
    tope -= sizeof(size_t);
    size_t tamElemApilada = *(size_t*)(pp->vPila + tope);
    tope -= tamElemApilada;
    memcpy(elem,pp->vPila + tope, min(tamElem,tamElemApilada));
    return true;
}
bool pilaLlena(const Pila *pp, size_t tamElem)
{
    return tamElem + sizeof(size_t) > TAM_PILA - pp->tope;
}
bool pilaVacia(const Pila *pp)
{
    return pp->tope == 0;
}
void vaciarPila(Pila *pp)
{
    pp->tope = 0;
}
