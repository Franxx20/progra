#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///*************************************************************************************
///********************** DESCOMENTAR EL QUE CORRESPONDA *******************************
#include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
//#include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
///*************************************************************************************

#include "../TDACola/TDACola.h"
#include "../SolucionParcialArchivoCola/SolucionParcialArchivoCola.h"

#define MIN(X,Y) X<Y? X:Y

int procesarArchProductos_alu(const char* nombreArchProd, const char* nombreArchProdMas1000, const char* nombreArchProdMenos1000);
typedef struct
{
    char COD_ART[7];
    char COD_MAT_PRI[7];
    int CANTIDAD;
    float COSTO_UNIT;
} Articulo;


// FUNCIONES DE COLA
void crearCola_ALU(Cola* pc);
int encolar_ALU(Cola* pc, const void* dato, size_t tamElem);
int desencolar_ALU(Cola* pc, void* dato, size_t tamElem);

int colaVacia_ALU(const Cola* pc);
int colaLlena_ALU(const Cola* pc, size_t tamElem);
void vaciarCola_ALU(Cola* pc);




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
    float costoTotal=0;
    char * codArt = calloc(7,sizeof(char));
    FILE * fpArt = fopen(nombreArchProd,"rb");
    FILE * fpMas = fopen(nombreArchProdMas1000,"wb");
    FILE * fpMenos = fopen(nombreArchProdMenos1000, "wb");


    Cola colaArticulos;

    Articulo articulo;
    Articulo primeroDelSiguiente;

    if(!fpArt || !fpMas || !fpMenos)
    {
        free(fpArt);
        free(fpMenos);
        free(fpMas);

        return ERR_ARCHIVO;
    }

    crearCola_ALU(&colaArticulos);

    costoTotal =0;
    fread(&articulo,sizeof(Articulo),1,fpArt);
    if(!feof(fpArt))
        while(!feof(fpArt))
        {
            costoTotal += articulo.CANTIDAD  * articulo.COSTO_UNIT;

            encolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));

            strcpy(codArt,articulo.COD_ART);

            fread(&articulo,sizeof(Articulo),1,fpArt);
            while(!feof(fpArt) && strcmp(codArt,articulo.COD_ART) == 0)
            {
                encolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));
                costoTotal += articulo.CANTIDAD  * articulo.COSTO_UNIT;
                fread(&articulo,sizeof(Articulo),1,fpArt);
            }

            primeroDelSiguiente = articulo;

            if(costoTotal > 1000)
            {

                while(!colaVacia_ALU(&colaArticulos))
                {
                    desencolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));

                    fwrite(&articulo,sizeof(Articulo),1,fpMas);
                }
            }
            else
            {
                while(!colaVacia_ALU(&colaArticulos))
                {
                    desencolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));

                    fwrite(&articulo,sizeof(Articulo),1,fpMenos);
                }
            }

            encolar_ALU(&colaArticulos,&primeroDelSiguiente,sizeof(Articulo));
            fread(&articulo,sizeof(Articulo),1,fpArt);
            costoTotal =0;
        }
    else
    {
        costoTotal += articulo.CANTIDAD  * articulo.COSTO_UNIT;

        if(costoTotal > 1000)
        {

            while(!colaVacia_ALU(&colaArticulos))
            {
                desencolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));

                fwrite(&articulo,sizeof(Articulo),1,fpMas);
            }
        }
        else
        {
            while(!colaVacia_ALU(&colaArticulos))
            {
                desencolar_ALU(&colaArticulos,&articulo,sizeof(Articulo));

                fwrite(&articulo,sizeof(Articulo),1,fpMenos);
            }
        }
    }







    vaciarCola_ALU(&colaArticulos);


    free(codArt);
    fclose(fpMas);
    fclose(fpMenos);
    fclose(fpArt);
    return TODO_OK;
}

// FUNCIONES DE COLA
void crearCola_ALU(Cola* c)
{
    *c =NULL;
}
int encolar_ALU(Cola* c, const void* dato, size_t tamDato)
{
    Nodo * nue = (Nodo * )calloc(1,sizeof(Nodo));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return -1;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;


    if(*c == NULL)
        nue->sig= nue;
    else
    {
        nue->sig = (*c)->sig;
        (*c)->sig = nue;
    }
    *c = nue;

    return TODO_OK;
}
int desencolar_ALU(Cola* c, void* dato, size_t tamDato)
{
    Nodo * nae;
    if(*c == NULL)
        return -1;

    nae = (*c)->sig;
    memcpy(dato,nae->dato,MIN(nae->tamElem,tamDato));
    if(nae == *c)
        *c = NULL;
    else
        (*c)->sig = nae->sig;


    free(nae->dato);
    free(nae);

    return TODO_OK;
}

int colaVacia_ALU(const Cola* c)
{
    return *c == NULL;
}
int colaLlena_ALU(const Cola* c, size_t tamDato)
{
    Nodo * nodo = (Nodo *)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo || !dato;
}
void vaciarCola_ALU(Cola* c)
{
    Nodo * aux;
    while(*c)
    {
        aux = (*c)->sig;
        if(*c == aux)
            *c = NULL;
        else
        {
            (*c)->sig = aux->sig;
        }
        free(aux->dato);
        free(aux);
    }
}
