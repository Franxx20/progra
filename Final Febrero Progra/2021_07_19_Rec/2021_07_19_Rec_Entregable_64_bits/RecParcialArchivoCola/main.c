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

///Funciones cola
void crearCola_alu(Cola* pc);
int encolar_alu(Cola* pc, const void* dato, size_t tamElem);
int desencolar_alu(Cola* pc, void* dato, size_t tamElem);
int colaVacia_alu(const Cola* pc);
void copiarDatoEnCola_alu(Cola *c, const void* dato, size_t tamDato);
void copiarDatoDeCola_alu(Cola *c, void* dato, size_t tamDato);

///Funciones string
int strcmp_alu(const char* cad1, const char* cad2);
char* strcpy_alu(char* dest, const char* origen);

typedef struct
{
    char COD_ART[7];
    char COD_MAT_PRI[7];
    int CANTIDAD;
    float COSTO_UNIT;
} Articulo;

int main()
{
    generarArchivoProductos();

    puts("Archivo de Productos");
    mostrarArchivoProd("productos.dat");

    //int ret = procesarArchProductos_alu("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");
   int ret = procesarArchProductos("productos.dat", "ProductosMas1000.dat", "ProductosMenos1000.dat");

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
    FILE *pfArchProd = fopen(nombreArchProd,"rb");
    FILE *pfProdMas1000 = fopen(nombreArchProdMas1000,"wb");
    FILE *pfProdMenos1000 = fopen(nombreArchProdMenos1000,"wb");

    if(!pfArchProd || !pfProdMas1000 || !pfProdMenos1000)
    {
        fclose(pfArchProd);
        fclose(pfProdMas1000);
        fclose(pfProdMenos1000);
        return -3;
    }

    Cola colaProd;
    crearCola_alu(&colaProd);

    char codArt[7];
    Articulo regProd;
    fread(&regProd,sizeof(Articulo),1,pfArchProd);
    while(!feof(pfArchProd))
    {
        float costo = 0;
        strcpy_alu(codArt,regProd.COD_ART);
        while(!feof(pfArchProd) && strcmp_alu(codArt,regProd.COD_ART) == 0)
        {
            encolar_alu(&colaProd,&regProd,sizeof(Articulo));
            costo+=(regProd.CANTIDAD*regProd.COSTO_UNIT);
            fread(&regProd,sizeof(Articulo),1,pfArchProd);
        }

        if(costo > 1000)
        {
            Articulo regAux;
            while(!colaVacia_alu(&colaProd))
            {
                desencolar_alu(&colaProd,&regAux,sizeof(Articulo));
                fwrite(&regAux,sizeof(Articulo),1,pfProdMas1000);
            }
        }
        else
        {
            Articulo regAux;
            while(!colaVacia_alu(&colaProd))
            {
                desencolar_alu(&colaProd,&regAux,sizeof(Articulo));
                fwrite(&regAux,sizeof(Articulo),1,pfProdMenos1000);
            }
        }

    }


    fclose(pfArchProd);
    fclose(pfProdMas1000);
    fclose(pfProdMenos1000);

    return TODO_OK;
}

int strcmp_alu(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2)
    {
        if(*cad1 != *cad2)
            return *cad1-*cad2;
        cad1++;
        cad2++;
    }

    return 0;
}

char* strcpy_alu(char* dest, const char* origen)
{
    while(*origen)
    {
        *dest = *origen;
        dest++;
        origen++;
    }

    *dest = '\0';

    return dest;
}

void crearCola_alu(Cola* pc)
{
    pc->fondo = TAM_COLA - 1500;
    pc->frente = TAM_COLA -1500;
    pc->tamDisponible = TAM_COLA;
}

int encolar_alu(Cola* pc, const void* dato, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > pc->tamDisponible)
        return 0;

    copiarDatoEnCola_alu(pc,&tamElem,sizeof(size_t));
    pc->fondo = (pc->fondo + sizeof(size_t))%TAM_COLA;
    copiarDatoEnCola_alu(pc,dato,tamElem);
    pc->fondo = (pc->fondo + sizeof(size_t))%TAM_COLA;
    pc->tamDisponible -= tamElem + sizeof(size_t);

    return 1;
}

int desencolar_alu(Cola* pc, void* dato, size_t tamElem)
{
    if(pc->tamDisponible==TAM_COLA)
        return 0;
    size_t tamElemEncolado;

    copiarDatoDeCola_alu(pc,&tamElemEncolado,sizeof(size_t));
    pc->frente = (pc->frente + sizeof(size_t))%TAM_COLA;
    copiarDatoDeCola_alu(pc,dato,MIN(tamElem,tamElemEncolado));
    pc->tamDisponible += tamElemEncolado + sizeof(size_t);

    return 1;
}

int colaVacia_alu(const Cola* pc)
{
    return pc->tamDisponible == TAM_COLA;
}

void copiarDatoEnCola_alu(Cola *c, const void* dato, size_t tamDato)
{
    int cantACopiar = tamDato;
    int cantContigua = c->fondo >= c->frente ? TAM_COLA - c->fondo : c->frente - c->fondo;

    memcpy(c->vCola + c->fondo, dato, cantContigua);
    cantACopiar -= cantContigua;

    if(cantACopiar > 0)
        memcpy(c->vCola, dato + cantContigua, cantACopiar);
}

void copiarDatoDeCola_alu(Cola *c, void* dato, size_t tamDato)
{
    int cantACopiar = tamDato;
    int cantContigua = c->frente >= c->fondo ? MIN(TAM_COLA - c->frente,tamDato) : tamDato;

    memcpy(dato, c->vCola + c->frente, cantContigua);
    cantACopiar -= cantContigua;

    if(cantACopiar > 0)
        memcpy(dato + cantContigua, c->vCola, cantACopiar);
}
