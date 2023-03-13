#include <stdio.h>
#include <stdlib.h>
#include "funres.h"

int main()
{
	int option,
		 order;

	puts("Creando lote de prueba...");
	lotePrueba("alumnos.txt");

	do {
		printf("Desa ordenar el lote por cant.Materias - Carrera o\n"
				"Carrera - cant.Materias? (1/2): ");
		scanf("%d", &option);
	} while(option != 1 && option != 2);

	do {
		printf("Desa ordenar el lote en orden ascendente\n"
				"o descendente? (1/2): ");
		scanf("%d", &order);
	} while(order != 1 && order != 2);

	puts("");

	(order == 2)? (order = -1) : (order = 1);
	(option == 2)? resolucion("alumnos.txt", cmp_carrerasMaterias, order) :
		resolucion("alumnos.txt", cmp_materiasCarreras, order);

	return 0;
}
