/*Marco_Agustin_Marcelo_42572925*/

#include <stdio.h>
#include <stdlib.h>
#include "include/cuentas.h"

int main()
{
    if(!crearCuentas("cuentas.dat")) {
		puts("[ERROR] - No se a podido crear el archivo cuentas.dat.");
		return -1;
    }

    puts("Cuentas antes de los movimientos:");
    puts("---------------------------------");

    if(!mostrarCuentas("cuentas.dat")) {
		puts("[ERROR] - No se a podido mostrar el archivo cuentas.dat.");
		return -1;
    }

    if(!crearMovimientos("movimientos.txt")) {
		puts("[ERROR] - No se a podido crear el archivo movimientos.txt.");
		return -1;
    }

	if(!actualizarCuentas("cuentas.dat", "movimientos.txt", "error_nro_cta.txt")) {
		puts("[ERROR] - No se a podido actualizar el archivo movimientos.txt.");
		return -1;
	}

	puts("\n\nCuentas despues de los movimientos:");
    puts("---------------------------------------");

	if(!mostrarCuentas("cuentas.dat")) {
		puts("[ERROR] - No se a podido mostrar el archivo cuentas.dat.");
		return -1;
    }

    return 0;
}
