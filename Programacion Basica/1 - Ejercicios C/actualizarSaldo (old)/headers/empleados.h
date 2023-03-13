#include "base.h"

typedef struct empleado
{
	unsigned dni;
		char apellido[SIZE],
			 nombre[SIZE];
	  double sueldo;
} empleado;


void cargar_emp(empleado *emp, char *ap, char *nb)
{
	emp->dni = rand() % (99999999 + 1 - 10000000) + 10000000;
	emp->sueldo = (double) (rand() % (99999 + 1 - 1000) + 1000)/ 12.5;
	strcpy(emp->apellido, ap);
	strcpy(emp->nombre, nb);
}


void escribirArchivo_emp(char *filename)
{
	char cad[SIZE], 
		 *ap, *nb;
	empleado emp;

	FILE *file = fopen(filename, "wb"),
		 *names = fopen("emp_names.txt", "rt");

	if(!file || !names)
	{
		printf("[Error] No se pudo escribir archivo %s", filename);
		return;
	}

	fgets(cad, sizeof(cad), names); /*Skips #Empleados:*/
	while (fgets(cad, sizeof(cad), names))
	{
		ap = strtok(cad, " ");
		nb = strtok(NULL, " ");
		nb[strcspn(nb, "\n")] = '\0';

		cargar_emp(&emp, ap, nb);
		fwrite(&emp, sizeof(empleado), 1, file);
	}
	fclose(file);
	fclose(names);
}


void mostrar_emp(empleado *emp, int number)
{
	printf("Empleado %d:\n",number);
	printf("[%s %s]\nDNI:%u\nSueldo:%.2f\n",
	emp->apellido, emp->nombre, emp->dni, emp->sueldo);
	puts("--------------------");
}


void verArchivo_emp(char *filename)
{
	int i = 0;
	empleado emp;
	FILE *file = fopen(filename, "rb");

	if(!file)
	{
		printf("[Error] No se pudo leer archivo %s", filename);
		return;
	}

	printf("Contenidos de %s:\n", filename);
	fread(&emp, sizeof(empleado), 1, file);
	while (!feof(file))
	{
		mostrar_emp(&emp, ++i);
		fread(&emp, sizeof(empleado), 1, file);
	}
	fclose(file);
}