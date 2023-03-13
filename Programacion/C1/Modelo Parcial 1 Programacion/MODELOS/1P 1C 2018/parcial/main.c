#include <stdio.h>
#include <stdlib.h>
#include <banco.h>
#include <utilitarias.h>

int main()
{
    FILE* arch_ctas;
//    crear_archivo_cuentas("../Archivos/cuentas.dat");
//    crear_archivo_movimientos("../Archivos/movimientos.txt");
    printf("\n\n*********CUENTAS***********\n");
//    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS***********\n\n");
    printf("\n\n*********MOVIMIENTOS***********\n");
//    mostrar_archivo_movimientos("../Archivos/movimientos.txt");
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
//    actualizar_cuentas_res(arch_ctas,"../Archivos/movimientos.txt");
    ///actualizar_cuentas(arch_ctas,"../Archivos/movimientos.txt");

    t_cuenta_banco cue;

    fread(&cue, sizeof(t_cuenta_banco), 1, arch_ctas);
    while(!feof(arch_ctas))
    {
        printf("%-9s%ld\t%-40s\t%.2f\n", cue.cod_cta, cue.dni, cue.apyn, cue.saldo);
        fread(&cue, sizeof(t_cuenta_banco), 1, arch_ctas);
    }

    fclose(arch_ctas);

    printf("\n\n*********CUENTAS ACT***********\n");
//    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS ACT***********\n\n");

    return 0;
}
