#include <stdio.h>
#include <stdlib.h>
#include <banco.h>
#include <utilitarias.h>

int main()
{
    FILE* arch_ctas, * arch_movs, * arch_err;
    t_lista lista;
    crear_archivo_cuentas("../Archivos/cuentas.dat");
    crear_archivo_movimientos("../Archivos/movimientos.txt");
    printf("\n\n*********CUENTAS***********\n");
    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS***********\n\n");
    printf("\n\n*********MOVIMIENTOS***********\n");
    mostrar_archivo_movimientos("../Archivos/movimientos.txt");
    printf("\n*********FIN MOVIMIENTOS***********\n\n");

    arch_ctas = fopen("../Archivos/cuentas.dat", "r+b");
    arch_movs = fopen("../Archivos/movimientos.txt", "rt");
    arch_err = fopen("../Archivos/error_nro_cta.txt", "wb");

    if (!arch_ctas || !arch_err || !arch_movs)
    {
        exit(1);
    }
    crear_lista_res(&lista);
    /**
        Esta función debe realizar la actualización de cuentas,
        al mismo tiempo que calcula las 5 cuentas con mayor descubierto
        y valida los numeros de cuenta.
        Escribir las funciones:
            actualizar_cuentas
            texto_a_movimiento (genera una estructura movimiento a partir de una cadena)
            instertar_prim5_lista (inserta un registro en la lista - ordenado, cuidando que no haya mas de 5 regs)
            validar_nro_cuenta (Valida el numero de cuenta)
            Cualquier otra función necesaria para resolver el ejercicio
    */
    actualizar_cuentas_res(arch_ctas,arch_movs, arch_err, &lista);

    printf("\n\n*********LISTA***********\n");
    imprimir_lista_res(&lista);
    printf("\n*********FIN LISTA***********\n\n");
    vaciar_lista_res(&lista);

    fclose(arch_ctas);
    fclose(arch_movs);
    fclose(arch_err);

    printf("\n\n*********CUENTAS ACT***********\n");
    mostrar_archivo_cuentas("../Archivos/cuentas.dat");
    printf("\n*********FIN CUENTAS ACT***********\n\n");

    printf("\n\n*********ERROR***********\n");
    mostrar_archivo_errores("../Archivos/error_nro_cta.txt");
    printf("\n*********FIN ERROR***********\n\n");


    return 0;
}
