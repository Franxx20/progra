#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SUmar 9947389 57267

char *sumar(const char *c1, const char *c2);
bool apilarCeros(Pila *p, int cantCeros);
bool apilarNumero(Pila *p, const char *num);
bool desapilarNumero(char *num, Pila *p);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Cantidad de parametros Incorrecta");
    return 1;
  }

  char *suma = sumar(argv[1], argv[2]);
  fprintf(stdout, "%s", suma);
  free(suma);
  return 0;
}

char *sumar(const char *c1, const char *c2) {
  Pila p1, p2, ps;

  crearPila(&p1);
  crearPila(&p2);
  crearPila(&ps);

  int tanNum1 = strlen(c1);
  int tanNum2 = strlen(c2);
  int tamSuma = tanNum1 > tanNum2 ? tanNum1 : tanNum2;

  int restaTam = tanNum1 - tanNum2;
  int cantCeros = abs(restaTam);

  bool pila1Menor = restaTam < 0;

  apilarCeros(pila1Menor ? &p1 : &p2, cantCeros);

  apilarNumero(&p1, c1);
  apilarNumero(&p2, c2);

  int digito1, digito2, digitoSuma, acarreo = 0;
  char dig1C, dig2C, digSumaC;
  while (!PilaVacia(&p1)) {
    sacarDePila(&p1, &dig1C, sizeof(char));
    sacarDePila(&p2, &dig2C, sizeof(char));

    digito1 = dig1C - '0';
    digito2 = dig2C - '0';
    digitoSuma = digito1 + digito2 + acarreo;
    acarreo = digitoSuma / 10;
    digitoSuma %= 10;
    digSumaC = digitoSuma + '0';

    ponerEnPila(&ps, &digSumaC, sizeof(char));
  }

  if (acarreo == 1) {
    digSumaC = '1';
    ponerEnPila(&ps, &digSumaC, sizeof(char));
    tamSuma++;
  }

  char *suma = malloc(tamSuma + 1);
  if (!suma) {
    fprintf(stderr, "No se pudo reserver memoria");
    return NULL;
  }

  desapilarNumero(suma, &ps);

  return suma;
}

bool apilarCeros(Pila *p, int cantCeros) {

  int cerosApilados = 0;
  char cero = '0';
  while (cerosApilados < cantCeros) {
    if (!ponerEnPila(p, &cero, sizeof(char)))
      return false;
    cerosApilados++;
  }
  return true;
}

bool apilarNumero(Pila *p, const char *num) {
  char *i = (char *)num;
  while (*i) {
    if (!ponerEnPila(p, i, sizeof(char)))
      return false;
    i++;
  }
  return true;
}

bool desapilarNumero(char *num, Pila *p) {
  char *i = num;
  char digitoC;
  while (!PilaVacia(p)) {
    sacarDePila(p, &digitoC, sizeof(char));
    *i = digitoC;
    i++;
  }
  *i = '\0';

  return true;
}
void testPrint() {
  printf("Hola");

  printf("Hola");
  printf("Hola");
  printf("Hola");
  printf("Hola");
  printf("Hola");
}
