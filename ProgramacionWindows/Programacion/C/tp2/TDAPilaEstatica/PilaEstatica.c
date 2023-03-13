#define TDA_PILA_IMPL_ESTATICA
#include "../TDAPila/TDAPila.h"
#include <string.h>

void crearPila(Pila *p) {

  // cantidad maxima de datos a consumir
  p->tope = TAM_PILA;
}

void vaciarPila(Pila *p) { p->tope = TAM_PILA; }

bool pilaLlena(const Pila *p, unsigned tamDato) {
  // si tope es menor significa que ya no tengo mas espacio para guardar un dato
  // y su tamanio
  return p->tope < tamDato + sizeof(tamDato);
}

bool pilaVacia(const Pila *p) {
  // si es verdero significa que no se consimio nada de memoria
  return p->tope == TAM_PILA;
}

bool verTope(const Pila *p, void *dato, unsigned tamDato) {

  unsigned cantBytes;

  if (p->tope == TAM_PILA)
    return false;

  // primero se recupera el tamanio del dato a ver
  memcpy(&cantBytes, p->pila + p->tope, sizeof(unsigned));
  // se recupera el dato. Tamanio en donde se guarda y el dato guardado puede
  // diferir
  memcpy(dato, p->pila + p->tope + sizeof(unsigned), MIN(cantBytes, tamDato));

  return true;
}

bool PonerEnPila(Pila *p, const void *dato, unsigned tamDato) {
  if (p->tope < tamDato + sizeof(unsigned))
    return false;

  p->tope -= tamDato;
  memcpy(p->pila + p->tope, dato, tamDato);
  p->tope -= sizeof(unsigned);
  memcpy(p->pila + p->tope, &tamDato, sizeof(unsigned));

  return true;
}

bool sacarDePila(Pila *p, void *dato, unsigned tamDato) {
  // lo mismo que ver tope solo que se incrementa el tope
  if (p->tope == TAM_PILA)
    return false;

  unsigned cantBytes;
  memcpy(&cantBytes, p->pila + p->tope, sizeof(unsigned));
  p->tope += sizeof(unsigned);
  memcpy(dato, p->pila + p->tope, MIN(tamDato, cantBytes));
  p->tope += cantBytes;

  return true;
}
