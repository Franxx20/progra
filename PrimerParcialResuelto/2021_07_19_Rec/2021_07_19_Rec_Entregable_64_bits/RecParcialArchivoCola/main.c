#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///*************************************************************************************
///********************** DESCOMENTAR EL QUE CORRESPONDA *******************************
//#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
///*************************************************************************************

#include "../TDACola/TDACola.h"
#include "../SolucionParcialArchivoCola/SolucionParcialArchivoCola.h"

#define MIN(X,Y) X<Y? X:Y

int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000);
void encolarProd(Cola* pc, const char* nombreArchProd);

typedef struct
{
    char COD_ART[7];
    char COD_MAT_PRI[7];
    int CANTIDAD;
    float COSTO_UNIT;
}Articulo;

int main()
{
	generarArchivoProductos();

 	puts("Archivo de Productos");
	mostrarArchivoProd("productos.dat");

    int ret = procesarArchProductos_alu("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");
    //int ret = procesarArchProductos("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");

    if(ret != TODO_OK)
    {
        puts("Hubo un error en el proceso.");
        return ret;
    }

    puts("\nArchivo de productos de costo mayor a $1000");
	mostrarArchivoProd("ProductosMas1000.dat");

    puts("\nArchivo de productos de costo menor a $1000");
    mostrarArchivoProd("ProductosMenos1000.dat");

    return 0;
}


int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000)
{
    float costo;

    Cola colaProd;
    crearCola(&colaProd);
    encolarProd(&colaProd, nombreArchProd);

    FILE* archProd = fopen(nombreArchProd, "rb");
    FILE* mas1000 = fopen(nombreArchProdMas1000, "wb");
    FILE* menos1000 = fopen(nombreArchProdMenos1000, "wb");
    if(!archProd || !mas1000 || !menos1000)
    {
        fclose(archProd);
        fclose(mas1000);
        fclose(menos1000);
        return 1;
    }

    Articulo artAct;
    char* artAnt = malloc(sizeof(artAct.COD_ART));

    fread(&artAct, sizeof(Articulo), 1, archProd);
    while(!colaVacia(&colaProd))
    {
        desencolar(&colaProd, &costo, sizeof(float));
        strcpy(artAnt, artAct.COD_ART);
        while(!strcmp(artAct.COD_ART, artAnt) && !feof(archProd))
        {
            if(costo>=1000)
                fwrite(&artAct, sizeof(Articulo), 1, mas1000);
            else
                fwrite(&artAct, sizeof(Articulo), 1, menos1000);
            fread(&artAct, sizeof(artAct), 1, archProd);
        }
    }
    fclose(archProd);
    fclose(mas1000);
    fclose(menos1000);
    return 0;
}

void encolarProd(Cola* pc, const char* nombreArchProd)
{
    FILE* archProd = fopen(nombreArchProd, "rb");
    if(!archProd)
    {
        fclose(archProd);
        return;
    }

    Articulo artAct;
    float costo;
    char* artAnt = malloc(sizeof(artAct.COD_ART));
    fread(&artAct, sizeof(Articulo), 1, archProd);
    while(!feof(archProd))
    {
        costo = 0;
        strcpy(artAnt, artAct.COD_ART);
        while(!strcmp(artAct.COD_ART, artAnt) && !feof(archProd))
        {
            costo += artAct.CANTIDAD * artAct.COSTO_UNIT;
            fread(&artAct, sizeof(artAct), 1, archProd);
        }
        encolar(pc, &costo, sizeof(float));
    }
    fclose(archProd);
}
