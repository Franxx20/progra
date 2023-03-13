#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista/lista.h"
#include "empleado/empleado.h"


int main()
{
	int rc;
	size_t i;
	tLista list;
	tEmpleado emp;

	crearLista(&list);

	rc = leerEmpleados("listaEmpleados.txt", &list);
	if(!rc) {
		puts("[ERROR] - No se encontro el archivo");
		return -1;
	}


	puts("--- [Agregamos al nuevo empleado, Shion Yorigami. Al final de la lista] ---");
	{
		strncpy(emp.apellido, "Yorigami", SIZE - 1);
		strncpy(emp.nombre, "Shion", SIZE - 1);
		emp.dni = 68457894;
		emp.salario = 4.00;
	}
	lista_insertarPosicion(&list, &emp, sizeof(tEmpleado), lista_contar(&list));

	
	puts("--- [Agregamos aun empleado repetido, Reimu Hakurei. Al inicio de la lista] ---");
	{
		strncpy(emp.apellido, "Hakurei", SIZE - 1);
		strncpy(emp.nombre, "Reimu", SIZE - 1);
		emp.dni = 42789456;
		emp.salario = 489.56;
	}
	lista_insertarInicio(&list, &emp, sizeof(tEmpleado));


	puts("--- [Ordenamos la lista por orden ascendente del numero de DNI] ---");
	lista_ordenar(&list, compararEmpleados);


	puts("--- [Removemos todos los duplicados] ---");
	for(i = 0; i < lista_contar(&list); i++) {
		lista_verPosicion(&list, &emp, sizeof(tEmpleado), i);
		lista_removerDuplicados(&list, &emp, sizeof(tEmpleado), compararEmpleados);
	}


	puts("--- [Bonus navideño] ---");
	lista_recorrer(&list, agregarBonus);


	puts("--- [Escribimos la nueva lista en un archivo 'listaFinal.txt'] ---");
	{
		FILE *fp = fopen("listaFinal.txt", "wt");
		lista_mostrar(&list, mostrarEmpleado, fp);
		fclose(fp);
	}


	puts("--- [Comparamos el nuevo archivo con 'listaEsperada.txt'] ---");
	{
		int good = 1;
		char str_fin[200], str_esp[200];
		FILE *fin = fopen("listaFinal.txt", "rt"),
			 *esp  = fopen("listaEsperada.txt", "rt");

		if(esp && fin) {	
			while( fgets(str_fin, sizeof(str_fin), fin) && 
				fgets(str_esp, sizeof(str_esp), esp) ) 
			{
				if(strncmp(str_esp, str_fin, strlen(str_esp)) != 0) {
					good = 0;
					break;
				}
			}

			(good)? 
				puts("--- [Lista generada satisfactoriamente] ---") :
				puts("--- [ERROR lista incorrectamente generada] ---");
		}
		else {
			puts("--- [ERROR archivos no encontrados] ---");
		}

		if(fin) {
			fclose(fin);
		}
		if(esp) {
			fclose(esp);
		}
	}


	/*puts("--- [Buscar empleado] ---");
	{
		printf("> ");
		scanf("%lu", &emp.dni);

		rc = lista_buscar(&list, &emp, sizeof(tEmpleado), compararEmpleados);
		if(rc != -1) {
			lista_verPosicion(&list, &emp, sizeof(tEmpleado), rc);
			mostrarEmpleado(&emp, stdout);
		}
		else {
			puts("[ERROR] - Empleado no encontrado");
		}
	}*/

	vaciarLista(&list);
	return 0;
}