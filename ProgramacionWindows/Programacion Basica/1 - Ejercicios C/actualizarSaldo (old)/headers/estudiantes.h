#include "base.h"

typedef struct estudiante
{
	unsigned dni;
		char apellido[SIZE],
			 nombre[SIZE];
	   float promedio;
} estudiante;


void cargar_est(estudiante *est, char *ap, char *nb)
{
	est->dni = rand() % (99999999 + 1 - 10000000) + 10000000;
	est->promedio = (float) (rand() % 20 + 1) / 2;
	strcpy(est->apellido, ap);
	strcpy(est->nombre, nb);
}


void escribirArchivo_est(char *filename)
{
	char cad[SIZE], 
		 *ap, *nb;
	estudiante est;

	FILE *file = fopen(filename, "wb"),
		 *names = fopen("est_names.txt", "rt");

	if(!file || !names)
	{
		printf("[Error] No se pudo escribir archivo %s", filename);
		return;
	}

	fgets(cad, sizeof(cad), names); /*Skips #Estudiantes:*/
	while (fgets(cad, sizeof(cad), names))
	{
		ap = strtok(cad, " ");
		nb = strtok(NULL, " ");
		nb[strcspn(nb, "\n")] = '\0';

		cargar_est(&est, ap, nb);
		fwrite(&est, sizeof(estudiante), 1, file);
	}
	fclose(file);
	fclose(names);
}


void mostrar_est(estudiante *est, int number)
{
	printf("Estudiante %d:\n", number);
	printf("[%s %s]\nDNI:%u\nPromedio:%.2f\n",
	est->apellido, est->nombre, est->dni, est->promedio);
	puts("--------------------");
}


void verArchivo_est(char *filename)
{
	int i = 0;
	estudiante est;
	FILE *file = fopen(filename, "rb");

	if(!file)
	{
		printf("[Error] No se pudo leer archivo %s", filename);
		return;
	}

	printf("Contenidos de %s:\n", filename);
	fread(&est, sizeof(estudiante), 1, file);
	while (!feof(file))
	{
		mostrar_est(&est, ++i);
		fread(&est, sizeof(estudiante), 1, file);
	}
	fclose(file);
}