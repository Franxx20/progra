#define TDA_PILA_IMPL_DINAMICA
#include "../TDAPila/TDAPila.h"
#include <stdlib.h>

void crearPila(Pila *p) {
  // inicialmente el puntero no direcciona a ningun nodo
  *p = NULL;
}
void vaciarPila(Pila *p) {
  // realiza accion mientras haya un nodo conectado
  while (*p) {
    Nodo *aux = *p;
    *p = aux->sig;
    free(aux->dato);
    free(aux);
  }
}

bool pilaLlena(const Pila *p, unsigned tamDato);
bool pilaVacia(const Pila *p) { return *p == NULL; }
bool verTope(const Pila *p, void *dato, unsigned tamDato);

bool PonerEnPila(Pila *p, const void *dato, unsigned tamDato);
bool sacarDePila(Pila *p, void *dato, unsigned tamDato);
