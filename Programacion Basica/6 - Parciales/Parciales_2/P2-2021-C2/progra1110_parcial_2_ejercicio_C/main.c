#include <stdio.h>
#include <stdlib.h>
#include "funres.h"

int main()
{
    if(!loteCuentas("cuentas.dat")) {
        puts("[ERROR] - No se pudo crear el archivo \"cuentas.dat\"");
    }

    if(!loteMovimientos("movimientos.txt")) {
        puts("[ERROR] - No se pudo crear el archivo \"movimientos.txt\"");
    }

    if(!resolucion("cuentas.dat", "movimientos.txt")) {
        puts("[ERROR] - No se pudo realizar la soulcion");
    }
    return 0;
}
