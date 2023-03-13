#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct sNodo {
  void *dato;
  unsigned tamDato;
  struct sNodo *sig;
} Nodo;

typedef struct {
  Nodo *frente;
  Nodo *fondo;
} Cola;

void crearCola(Cola *c);
void vaciarCola(Cola *c);

bool colaLlena(const Cola *c, unsigned tamDato);
bool colaVacia(const Cola *c);

bool ponerEnCola(Cola *c, const void *dato, unsigned tamDato);
bool verPrimeroCola(const Cola *c, void *dato, unsigned tamDato);

bool sacarCola(Cola *c, void *dato, unsigned tamDato);

#endif // COLADINAMICA_H_INCLUDED
