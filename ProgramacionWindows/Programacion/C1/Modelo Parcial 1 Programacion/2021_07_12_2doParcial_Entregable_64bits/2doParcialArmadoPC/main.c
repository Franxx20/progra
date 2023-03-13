#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

typedef struct
{
    int nroOp;
    char codigo[21];
    int cantidad;
    double precioUnitario;
}
ArmadoYRep_alu;

void crearLista_alu(Lista* pl);
void vaciarLista_alu(Lista* pl);
int listaLlena_alu(Lista* pl, unsigned tam);
int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);


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

    ///int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
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


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.
    Lista listaArmadoYRep;
    crearLista_alu(&listaArmadoYRep);

    FILE* archArmadoYRep = fopen(pathArmadoYRep, "rb");

    if(!archArmadoYRep)
    {
        fprintf(stderr, "Error = no se pudo abrir el archivo de armado y reparaciones");
        return 0;
    }

    ArmadoYRep_alu armYRep;
    fread(&armYRep, sizeof(ArmadoYRep_alu), 1, archArmadoYRep);

    while(!feof(archArmadoYRep) && listaLlena_alu(&listaArmadoYRep, sizeof(ArmadoYRep_alu)))
    {

        fread(&armYRep, sizeof(ArmadoYRep_alu), 1, archArmadoYRep);
    }


    vaciarLista_alu(&listaArmadoYRep);
    fclose(archArmadoYRep);
    return 1;
}


void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}


int listaLlena_alu(Lista* pl, unsigned tam)
{
    NodoD* aux = (NodoD*)malloc(sizeof(NodoD));
    void* info = malloc(tam);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}


void vaciarLista_alu(Lista* pl)
{
    NodoD* act = *pl;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            NodoD* aux = act;
            act = aux->sig;
            free(aux->dato);
            free(aux);
        }
        *pl = NULL;
    }
}


int insertarEnListaOrd(Lista* pl, const void* dato, unsigned tam, Cmp cmp, Actualizar actualizar)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, *sig = NULL;

    if(act)
    {
        while(act->ant && cmp((*pl)->dato, dato) > 0)
            act = act->ant;

        while(act->sig && cmp((*pl)->dato, dato) < 0)
            act = act->sig;

        int comp = cmp((*pl)->dato, dato)

        if(comp == 0)
        {
            if(actualizar != NULL)
            {
                int rc = actualizar((*pl)->dato, dato);

                return rc;
            }
        }

        if(comp > 0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nue = (NodoD*)malloc(sizeof(NodoD));

    if(nue == NULL || (nue->dato = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy

    *pl = nue;
    return 1;
}



int acumularStock_alu()
