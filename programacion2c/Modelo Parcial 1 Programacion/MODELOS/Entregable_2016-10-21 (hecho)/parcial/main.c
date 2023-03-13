#include <stdio.h>
#include <stdlib.h>
#include <banco.h>
#include <utilitarias.h>

int main()
{
    FILE* arch_ctas;
    crear_archivo_cuentas("../Archivos/cuentas.dat");
    crear_archivo_movimientos("../Archivos/movimientos.txt","clave");
    printf("\n\n*********CUENTAS***********\n");
    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS***********\n\n");
    printf("\n\n*********MOVIMIENTOS***********\n");
    mostrar_archivo_movimientos("../Archivos/movimientos.txt", "clave");
    printf("\n*********FIN MOVIMIENTOS***********\n\n");

    arch_ctas = fopen("../Archivos/cuentas.dat", "r+b");

    if (!arch_ctas)
    {
        exit(1);
    }
    /**
        Esta función debe realizar la actualización de cuentas
        a partir de los movimientos que deben ser desencriptados
        para usarlos
    */
//    actualizar_cuentas_res(arch_ctas,"../Archivos/movimientos.txt", "clave");
    actualizar_cuentas(arch_ctas,"../Archivos/movimientos.txt", "clave");

    fclose(arch_ctas);

    printf("\n\n*********CUENTAS ACT***********\n");
    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS ACT***********\n\n");

    return 0;
}
