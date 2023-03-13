#include <stdio.h>
#include <stdlib.h>
#include"merge.h"
int main(int argc, char *argv[])
{
    escribirArchivos(argv[1],argv[2]);
    puts("ANTES DE ACTUALIZAR");
    mostrarArchivo(argv[1]);
    printf("%s %s\n",argv[1],argv[2]);
    actualizarProds(argv[1],argv[2]);
    puts("DESPUES DE ACTUALIZAR");
    mostrarArchivo(argv[1]);

    return 0;
}
