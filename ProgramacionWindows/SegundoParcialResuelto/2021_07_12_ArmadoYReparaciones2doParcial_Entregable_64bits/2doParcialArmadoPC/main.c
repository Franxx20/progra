#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../TDALista/TDALista.h"
#include "../TDAArbol/TDAArbol.h"

typedef int (*Cmp)(const void*, const void*);
typedef void (*Actualizar)(void*, const void*);

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

#define MAX(X,Y) X>Y? X:Y

int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);
int cmpArmado_alu(const void* e1, const void* e2);
int cmpCodigo_alu(const void* e1, const void* e2);
void recorrerLista_alu(Lista* pl,Accion acc,void* dAcc);
void recorrerArbolEn_alu(Arbol* pa, Accion accion, void* datosAccion);


void actArmado_alu(void* actualizado, const void* actualizador);

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

	puts("Componentes antes de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");

    //int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	///******** Descomente esta línea y comente la de arriba para probar su código ********
    int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK)
	{
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}

void mostrarArmado_alu(void* elem, void* datos)
{
    ArmadoYRep* a = (ArmadoYRep*)elem;

    printf("%d|%s|%d|%f\n", a->nroOp, a->codigo, a->cantidad, a->precioUnitario);
}

void mostrarIndice_alu(void* elem, void* datos)
{
    IndComponente* a = (IndComponente*)elem;

    printf("%d|%s\n", a->nroReg,a->codigo);
}

int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
    char pathIndices[strlen(pathComponentes)+1];
    strcpy(pathIndices, pathComponentes);
    char* act = strrchr(pathIndices, '.');
    *act = '\0';
    strcat(pathIndices, ".idx");

    IndComponente indAct;
    ArmadoYRep armAct;
    Componente comAct;

    //FILE* archIndices = fopen(pathIndices, "rb");
    FILE* archComponentes = fopen(pathComponentes, "r+b");
    FILE* archArmados = fopen(pathArmadoYRep, "rb");
    if(!archComponentes || !archArmados)
    {
        fclose(archArmados);
        fclose(archComponentes);
        return -1;
    }

    Lista listaArmado;
    crearLista(&listaArmado);
    fread(&armAct, sizeof(ArmadoYRep), 1, archArmados);
    while(!feof(archArmados))
    {
        insertarOActualizarEnListaOrd(&listaArmado, &armAct, sizeof(ArmadoYRep), cmpArmado_alu, actArmado_alu);
        fread(&armAct, sizeof(ArmadoYRep), 1, archArmados);
    }
    fclose(archArmados);

    printf("\n\n///////////////Lista Armados/////////////////\n\n");
    recorrerLista_alu(&listaArmado, mostrarArmado_alu, NULL);

    Arbol arbolIndices;
    crearArbol(&arbolIndices);
    cargarArbol(&arbolIndices, sizeof(IndComponente), pathIndices);

    printf("\n\n///////////////Arbol Indices/////////////////\n\n");
    recorrerArbolEnOrden(&arbolIndices, mostrarIndice_alu, NULL);

    while(eliminarDeListaPrimero(&listaArmado, &armAct, sizeof(ArmadoYRep)))
    {
        strcpy(indAct.codigo, armAct.codigo);
        buscarEnArbol(&arbolIndices, &indAct, sizeof(IndComponente), cmpCodigo_alu);
        fseek(archComponentes, indAct.nroReg*sizeof(Componente), SEEK_SET);
        fread(&comAct, sizeof(Componente), 1, archComponentes);
        comAct.stock -= armAct.cantidad;
        fseek(archComponentes, (long int)-sizeof(Componente), SEEK_CUR);
        fwrite(&comAct, sizeof(Componente), 1, archComponentes);
    }

    fclose(archComponentes);
    return 0;
}

int cmpCodigo_alu(const void* e1, const void* e2)
{
    IndComponente* i1 = (IndComponente*)e1;
    IndComponente* i2 = (IndComponente*)e2;

    return strcmp(i1->codigo, i2->codigo);
}

int cmpArmado_alu(const void* e1, const void* e2)
{
    ArmadoYRep* i1 = (ArmadoYRep*)e1;
    ArmadoYRep* i2 = (ArmadoYRep*)e2;

    return strcmp(i1->codigo, i2->codigo);
}

void actArmado_alu(void* actualizado, const void* actualizador)
{
    ArmadoYRep* i1 = (ArmadoYRep*)actualizado;
    ArmadoYRep* i2 = (ArmadoYRep*)actualizador;

    i1->cantidad += i2->cantidad;
}

void recorrerLista_alu(Lista* pl,Accion acc,void* dAcc)
{
    if(!*pl)
        return;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        acc((*pl)->dato,dAcc);
        pl = &(*pl)->sig;
    }
}
