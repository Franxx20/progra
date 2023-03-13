#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


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
	
    int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	///******** Descomente esta línea y comente la de arriba para probar su código ********
	/// int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
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


void actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.
}
