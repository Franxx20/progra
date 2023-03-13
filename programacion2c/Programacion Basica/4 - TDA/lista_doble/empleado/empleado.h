#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <stdlib.h>
#include "../lista/lista.h"
#define SIZE 40

typedef enum {false, true} bool;

typedef struct emp
{
	size_t dni;
	double salario;
	char nombre[SIZE],
		 apellido[SIZE];
} tEmpleado;

int leerEmpleados(const char *filename, tLista *list);
void mostrarEmpleado(const void *emp, FILE *stream);
int filtrarEmpleados(const void *emp);
int compararEmpleados(const void *emp_1, const void *emp_2);
void agregarBonus(const void *emp);

#endif