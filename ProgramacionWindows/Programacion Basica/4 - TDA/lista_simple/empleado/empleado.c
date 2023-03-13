#include <stdio.h>
#include <string.h>
#include "empleado.h"

void paresarCadena(char *str, tEmpleado *emp);
int acumularEmpleados(void *, unsigned, const void *, unsigned);

int leerEmpleados(const char *filename, tLista *list)
{
	tEmpleado emp;
	char str[100];

	FILE *file = fopen(filename, "rt");
	if(!file) {
		goto error;
	}

	while (fgets(str, sizeof(str), file))
	{
		paresarCadena(str, &emp);
		if(listaLlena(list, sizeof(tEmpleado)) == 0) {
			lista_insertarFinal(list, &emp, sizeof(tEmpleado));
		}
		else goto error;
	}

	fclose(file);
	return 1;

error:
	if(file) {
		fclose(file);
	}
	return 0;
}


void paresarCadena(char *str, tEmpleado *emp)
{
	char *aux = &str[strcspn(str, "\n")];
	*aux = '\0';

	/*Apellido*/
	aux = strrchr(str, '|');
	strncpy(emp->apellido, aux + 1, SIZE - 1);
	*aux = '\0';

	/*Nombre*/
	aux = strrchr(str, '|');
	strncpy(emp->nombre, aux + 1, SIZE - 1);
	*aux = '\0';

	/*Salario*/
	aux = strrchr(str, '|');
	sscanf(aux + 1, "%lf", &emp->salario);
	*aux = '\0';

	/*DNI*/
	sscanf(str, "%lu", &emp->dni);
}


void mostrarEmpleado(const void *emp, FILE *stream)
{
	fprintf(stream, "---------------------\n");
	fprintf(stream, "Nombre: %s\nApellido: %s\nDNI: %lu\nSalario: %f",
			((tEmpleado *)emp)->nombre, 
			((tEmpleado *)emp)->apellido, 
			((tEmpleado *)emp)->dni, 
			((tEmpleado *)emp)->salario);
	fprintf(stream, "\n---------------------\n");
}

void _mostrarEmpleado(const void *emp)
{
	mostrarEmpleado(emp, stdout);
}

int filtrarEmpleados(const void *emp)
{
	bool check = false;
	tEmpleado *aux_emp = (tEmpleado *)emp;

	if(aux_emp->salario > 550.00) {
		check = true;
	}

	return check;
}

int compararEmpleados(const void *emp_1, const void *emp_2)
{
	tEmpleado *e_1 = (tEmpleado *)emp_1,
			  *e_2 = (tEmpleado *)emp_2;
	return (e_1->dni - e_2->dni);
}

int acumularEmpleados(void *dest, unsigned dest_n, 
		const void *src, unsigned src_n)
{
	tEmpleado *emp_dest = (tEmpleado *)dest,
			  *emp_src  = (tEmpleado *)src;

	 emp_dest->salario += emp_src->salario;

	 return 1;
}

void agregarBonus(const void *emp)
{
	tEmpleado *_emp = (tEmpleado *)emp;
	_emp->salario += 1000.0;
}