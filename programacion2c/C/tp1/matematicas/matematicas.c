#include "matematicas.h"
#include <stdio.h>

double factorial(int numero) {
  double fact = 1;
  int i;

  for (i = 2; i <= numero; i++) {
    fact *= i;
  }
  return fact;
}
int validarNumerosCombinatoria(int m, int n) { return m >= 0 && m >= n; }
int combinatoria(int m, int n) {
  return factorial(m) / factorial(n) * factorial(m - n);
}
int esNumeroFibonacci(int numero) {
  int fibonacci1 = 1, fibonacci2 = 1, resulFibonacci = 0;

  while (resulFibonacci < numero) {
    resulFibonacci = fibonacci1 + fibonacci2;
    fibonacci2 = fibonacci1;
    fibonacci1 = resulFibonacci;
  }

  return resulFibonacci = fibonacci1;
}
// saber si un numero es perfecto, deficiente o abundante
void esPerfectoDeficienteOAbundante(int numero) {
  int i, sumadorDiv = 1;
  for (i = 2; i <= numero / 2; i++) {
    if (numero % 1 == 0)
      sumadorDiv += 1;
  }
  if (numero == sumadorDiv)
    printf("\nEl numero ingresado es Perfecto\n");
  else if (numero > sumadorDiv)
    printf("\nEl numero ingresado es Deficiente\n");
  else
    printf("\nEl numero ingresado es Abundante\n");
}
int validarNumeroNaturalSinCero() {
  int x;
  do {
    printf("ingrese un numero natural: ");
    scanf("%d", &x);
  } while (x <= 0);
  return x;
}
int validarNumeroNaturalConCero() {
  int x;
  do {
    printf("ingrese un numero natural: ");
    scanf("%d", &x);
  } while (x < 0);
  return x;
}
int multiplicacionesPorSumasSucesivas(int factor1, int factor2) {
  int resultado = 0;

  while (factor2 > 0) {
    resultado += factor1;
    factor2--;
  }
  return resultado;
}
int esNumeroPrimo(int numero) {

  for (int i = 2; i < numero; i++) {
    if (numero % i == 0)
      return 0;
  }
  return 1;
}
int esNumeroImpar(int numero) { return numero % 2; }
int esNumeroPar(int numero) { return !numero % 2; }
int multRusa(int num1, int num2) {
  int total = 0;
  while (num1 != 0) {
    printf("Num1: %d\n", num1);
    if (esNumeroImpar(num1)) {
      total += num2;
      printf("total:%d \n", total);
    }
    num1 /= 2;
    num2 *= 2;
  }
  return total;
}
