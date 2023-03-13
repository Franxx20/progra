#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista/lista.h"
#include "empleado/empleado.h"


int main()
{
	int rc;
	tLista list;
	tEmpleado new_emp;

	crearLista(&list);

	rc = leerEmpleados("nuevosEmpleados.txt", &list);
	if(!rc) {
		puts("[ERROR] - No se encontro el archivo");
	}
	else { 
		puts("[Mostramos lista al reves]");
		lista_mostrarInvertido(&list, mostrarEmpleado, stdout);
	}

	/*puts("[Filtramos empleados con un salario menor a $550.00]");
	lista_filtrar(&list, filtrarEmpleados);

	puts("[Agregamos un nuevo empleado, Shion Yorigami]");
	{
		strncpy(new_emp.apellido, "Yorigami", SIZE - 1);
		strncpy(new_emp.nombre, "Shion", SIZE - 1);
		new_emp.dni = 26457894;
		new_emp.salario = 4.00;
	}
	lista_insertarPosicion(&list, &new_emp, sizeof(tEmpleado), 8);

	lista_mostrar(&list, mostrarEmpleado, stdout);

	puts("[Despedimos al empleado, Kasen Ibaraki]");
	new_emp.dni = 45631879;
	rc = lista_buscar(&list, &new_emp, sizeof(tEmpleado), compararEmpleados);

	if(rc != -1) {
		puts("[Removemos sus duplicados, si es que hay]");
		lista_removerDuplicados(&list, &new_emp, sizeof(tEmpleado), compararEmpleados);
		puts("\n[Empleado a Remover]:");
		lista_removerPosicion(&list, &new_emp, sizeof(tEmpleado), rc); 
		mostrarEmpleado(&new_emp, stdout);
	}
	else {
		puts("[ERROR] - Empleado para remover no encontrado");
	}


	puts("[Bonus holyday!!]");
	lista_recorrer(&list, agregarBonus);
	lista_mostrar(&list, mostrarEmpleado, stdout);
	lista_mostrar(&list, mostrarEmpleado, stdout);

	puts("[Buscamos al empleado Reisen Udongein Inaba]");
	new_emp.dni = 12345687;
	rc = lista_buscar(&list, &new_emp, sizeof(tEmpleado), compararEmpleados);
	if(rc == -1) {
		printf("[ERROR] Empleado no encontrado entr %d emplados\n", lista_contar(&list));
	}
	else {
		lista_verPosicion(&list, &new_emp, sizeof(tEmpleado), rc);
		mostrarEmpleado(&new_emp, stdout);
	}*/

	/*puts("[Menor nodo]");
	{
		tLista *rc = lista_buscarMenor(&list, compararEmpleados);
		mostrarEmpleado((*rc)->data, stdout);
	}*/

	puts("[Ordenar lista]");
	lista_ordenarSeleccion(&list, compararEmpleados);
	lista_mostrar(&list, mostrarEmpleado, stdout);
	
	vaciarLista(&list);
	return 0;
}