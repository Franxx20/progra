#include <stdio.h>
#include <stdlib.h>
#include <banco.h>
#include <utilitarias.h>

int main()
{
    FILE* arch_ctas;
    char clave[] = "clave";
    crear_archivo_cuentas_res("../Archivos/cuentas.dat");
    crear_archivo_movimientos_res("../Archivos/movimientos.txt",clave);
    printf("\n\n*********CUENTAS***********\n");
    mostrar_archivo_cuentas_res("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS***********\n\n");
    printf("\n\n*********MOVIMIENTOS***********\n");
    mostrar_archivo_movimientos_res("../Archivos/movimientos.txt", clave);
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
    actualizar_cuentas_res("../Archivos/cuentas.dat","../Archivos/movimientos.txt", clave);
    //actualizar_cuentas("../Archivos/cuentas.dat","../Archivos/movimientos.txt", clave);

    fclose(arch_ctas);

    printf("\n\n*********CUENTAS ACT***********\n");
    mostrar_archivo_cuentas_res("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS ACT***********\n\n");

    printf("\n\n*********MOVIMIENTOS DESCUBIERTO***********\n");
    mostrar_archivo_movimientos_descubierto_res("../Archivos/movimientos_descubierto.txt");
    printf("\n*********FIN MOVIMIENTOS DESCUBIERTO***********\n\n");

    return 0;
}
