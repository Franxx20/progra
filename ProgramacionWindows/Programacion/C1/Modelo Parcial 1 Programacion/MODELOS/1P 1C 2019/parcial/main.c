#include <stdio.h>
#include <stdlib.h>
#include <biblioteca.h>
#include <utilitarias.h>

int main()
{
    FILE* arch_libros, * arch_stock, * arch_err;
    ///-----------------------------EJERCICIO 1-----------------------------///
    printf("\n-----------------------------EJERCICIO 1-----------------------------\n\n");
    crear_archivo_libros();
    crear_archivo_stock();
    printf("\n\n*********LIBROS***********\n");
    mostrar_archivo_libros();
    printf("\n*********FIN LIBROS***********\n\n");
    printf("\n\n*********MOVIMIENTOS STOCK***********\n");
    mostrar_archivo_stock();
    printf("\n*********FIN MOVIMIENTOS STOCK***********\n\n");

    arch_libros = fopen("../Archivos/libros.dat", "r+b");
    arch_stock = fopen("../Archivos/nuevo_stock.txt", "rt");
    arch_err = fopen("../Archivos/errores.txt", "wb");

    if (!arch_libros || !arch_err || !arch_stock)
    {
        exit(1);
    }

    //actualizar_stock_res(arch_libros,arch_stock, arch_err);
    actualizar_stock(arch_libros,arch_stock, arch_err);

    fclose(arch_libros);
    fclose(arch_stock);
    fclose(arch_err);

    printf("\n\n*********LIBROS ACT***********\n");
    mostrar_archivo_libros();
    printf("\n*********FIN LIBROS ACT***********\n\n");

    printf("\n\n*********ERROR***********\n");
    mostrar_archivo_errores();
    printf("\n*********FIN ERROR***********\n\n");
    return 0;
}
