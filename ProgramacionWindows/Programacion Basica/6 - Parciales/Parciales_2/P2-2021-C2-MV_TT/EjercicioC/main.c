#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "funres.h"

#define NOM_ARCH_LPRUEBA "loteprueba.txt"
#define NOM_ARCH_SALIDA "informe.txt"


int main()
{
    /*Sectores y muelles*/
    const tSector secs[] = {{'A', 3},{'B', 2},{'C',4},{'D',5}};

    if (!crearLotePrueba_alumn(NOM_ARCH_LPRUEBA)){
        puts("Error al crear lote de prueba\n");
        return 1;
    }

    if(!generarInforme_alumn(NOM_ARCH_LPRUEBA, NOM_ARCH_SALIDA, secs)){
        puts("No se pudo abrir el archivo de entradas y salidas\n");
        return 1;
    }

    printf("Fin de ejecucion\n");
    return 0;
}
