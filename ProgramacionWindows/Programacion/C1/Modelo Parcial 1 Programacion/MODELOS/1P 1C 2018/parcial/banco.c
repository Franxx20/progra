#include<banco.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>

void actualizar_cuentas(FILE * arch_ctas, const char * path_movs)
{
    t_cuenta_banco cuenta;
    t_lista listaCuentas;
    t_movimiento_banco movi;
    crear_lista_res(&listaCuentas);
    fread(&cuenta, sizeof(t_cuenta_banco), 1, arch_ctas);
    while(!feof(arch_ctas))
    {
        insertarEnLista(&listaCuentas, &cuenta);
        fread(&cuenta, sizeof(t_cuenta_banco), 1, arch_ctas);
    }

    FILE* fmov = fopen(path_movs, "rt");
    if(!fmov)
    {
        fclose(fmov);
        return;
    }

    char cadena[100];
    fgets(cadena, 100, fmov);
    while(!feof(fmov))
    {
        texto_a_movimiento(cadena, &movi);
        recorrerLista(&listaCuentas, &movi, accion_1);
        fgets(cadena, 100, fmov);
    }

    fseek(arch_ctas, 0, SEEK_SET);

    while(!listaVacia(&listaCuentas))
    {
        sacar_primero_lista(&listaCuentas, &cuenta);
        fwrite(&cuenta, sizeof(t_cuenta_banco), 1, arch_ctas);
    }
}

//compararCuentas()
