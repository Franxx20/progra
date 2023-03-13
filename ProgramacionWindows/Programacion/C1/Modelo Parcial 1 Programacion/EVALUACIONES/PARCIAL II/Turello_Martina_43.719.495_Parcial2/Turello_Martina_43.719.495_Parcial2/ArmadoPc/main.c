#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

///
#include <memory.h>

#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../Matematica/Matematica.h"

#define ERR_ARCH 3 //error en apertura de archivo
#define ERR_EJ 4 //error de ejecucion

//Funciones Base
int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);
int obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx);
int cargarIndiceComponentes_alu(const char* pathComponentesIdx, Arbol* pa);

//Primitivas Arbol
void crearArbol_alu(Arbol* pa);
int cargarArbol_alu(Arbol* pa, size_t tam, const char* nombreArch);
int cargarArbolRec_alu(Arbol* pa, size_t tam, FILE* arch, int ri, int rd);
int buscarEnArbolNoOrd_alu(const Arbol* pa, void* dato, size_t tam, Cmp cmp);

//Primitivas Lista Doble
int listaVacia_alu(const Lista* pl);
void crearLista_alu(Lista* pl);
int ordenarLista_alu(Lista* pl, Cmp cmp);
int eliminarDuplicadosListaOrdAct_alu(Lista* pl, Cmp cmp, Actualizar actualizar);
int eliminarPrimeroLista_alu(Lista* pl, void* dato, size_t tam);

//Utilidades
int comparacionLista_alu(const void* e1, const void* e2);
int comparacionArbol_alu(const void* e1, const void* e2);
void actualizacionLista_alu(void* actualizado, const void* actualizador);

int strcmp_alu (char* text, char* text2);
///

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

//Funciones Base
int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
    char nombreIdx[20];
    sscanf(pathComponentes,"%[^.]s", nombreIdx);
    strcat(nombreIdx, ".idx");

    if(obtenerPathIdx_alu(pathComponentes, nombreIdx) != TODO_OK)
        return ERR_ARCH;

    Arbol AIndices;
    crearArbol_alu(&AIndices);

    if(cargarIndiceComponentes_alu(nombreIdx, &AIndices) != TODO_OK)
        return ERR_CARGA_IND;

    Lista LRepyAr;
    crearLista_alu(&LRepyAr);
    cargarArmadosYRepEnLista(pathArmadoYRep, &LRepyAr);
    ordenarLista_alu(&LRepyAr, comparacionLista_alu);
    eliminarDuplicadosListaOrdAct_alu(&LRepyAr, comparacionLista_alu, actualizacionLista_alu);

    FILE* pComponentes = fopen(pathComponentes, "r+b");
    if (!pComponentes)
        return ERR_ARCH;

    ArmadoYRep ayr;
    IndComponente ind;
    Componente compo;

    while(!listaVacia_alu(&LRepyAr))
    {
        eliminarPrimeroLista_alu(&LRepyAr,&ayr,sizeof(ArmadoYRep));
        strcpy(ind.codigo,ayr.codigo);
        if(buscarEnArbolNoOrd_alu(&AIndices,&ind,sizeof(IndComponente),comparacionArbol_alu) == VERDADERO)
        {
            fseek(pComponentes, ind.nroReg * sizeof(Componente), SEEK_SET);
            fread(&compo,sizeof(Componente),1,pComponentes);
            compo.stock -= ayr.cantidad;
            fseek(pComponentes,(long int)(-1L * sizeof(Componente)),SEEK_CUR);
            fwrite(&compo, sizeof(Componente),1,pComponentes);
            fseek(pComponentes,0L,SEEK_CUR);
        }
    }
    fclose(pComponentes);

    return TODO_OK;
}
int obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx)
{
    FILE* pComponentes = fopen(pathComponentes, "rb"),
        * pIndices = fopen(pathComponentesIdx, "wb");

    if (!pComponentes || !pIndices)
    {
        fclose(pComponentes);
        fclose(pIndices);
        return ERR_ARCH;
    }

    Componente compo;
    IndComponente ind;
    int reg = 0;

    fread(&compo,sizeof(Componente),1,pComponentes);
    while (!feof(pComponentes))
    {
        ind.nroReg = reg;
        strcpy(ind.codigo,compo.codigo);
        fwrite(&ind,sizeof(IndComponente),1,pIndices);
        reg++;
        fread(&compo,sizeof(Componente),1,pComponentes);
    }
    fclose(pComponentes);
    fclose(pIndices);

    return TODO_OK;
}
int cargarIndiceComponentes_alu(const char* pathComponentesIdx, Arbol* pa)
{
    return cargarArbol_alu(pa, sizeof(IndComponente),pathComponentesIdx) == TODO_OK ? TODO_OK : ERR_CARGA_IND;
}

//Primitivas Arbol
void crearArbol_alu(Arbol* pa)
{
    *pa = NULL;
}
int cargarArbol_alu(Arbol* pa, size_t tam, const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch)
        return ERR_ARCH;

    fseek(arch, 0L, SEEK_END);

    int rd = (ftell(arch) / tam) - 1;

    int ret = cargarArbolRec_alu(pa, tam, arch, 0, rd);

    fclose(arch);

    return ret;
}
int cargarArbolRec_alu(Arbol* pa, size_t tam, FILE* arch, int ri, int rd)
{
    if (ri > rd)
        return TODO_OK;

    NodoA* nue;
    if(!reservarMemoriaNodo(nue, sizeof(NodoA), tam))
        return SIN_MEM;

    int rm = (ri + rd) / 2;

    fseek(arch, rm * tam, SEEK_SET);
    fread(nue->dato, tam, 1, arch);

    nue->hIzq = nue->hDer = NULL;
    nue->tamElem = tam;

    *pa = nue;

    int ret = cargarArbolRec_alu(&(*pa)->hIzq, tam, arch, ri, rm-1);
    if(ret != TODO_OK)
        return ret;
    return cargarArbolRec_alu(&(*pa)->hDer, tam, arch, rm+1, rd);
}
int buscarEnArbolNoOrd_alu(const Arbol* pa, void* dato, size_t tam, Cmp cmp)
{
    if(!*pa)
        return FALSO;

    int comp = cmp(dato, (*pa)->dato);

    if(comp == 0)
    {
        memcpy(dato, (*pa)->dato, min(tam, (*pa)->tamElem));
        return VERDADERO;
    }

    int ret = buscarEnArbolNoOrd_alu(&(*pa)->hIzq, dato, tam, cmp);
    if(ret == VERDADERO)
        return VERDADERO;
    return buscarEnArbolNoOrd_alu(&(*pa)->hDer, dato, tam, cmp);
}

//Primitivas Lista Doble
int listaVacia_alu(const Lista* pl)
{
    return !*pl;
}
void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}
int ordenarLista_alu(Lista* pl, Cmp cmp)
{
    NodoD *act = *pl,* sup = NULL,* inf = NULL;
    int marca =  1;
    if(act == NULL)
        return ERR_EJ;

    while(act->ant)
        act = act ->ant;

    while(marca)
    {
        marca = 0;
        while(act->sig != sup)
        {
            if(cmp(act->dato, act->sig->dato) > 0)
            {
                void* inf = act->dato;
                size_t tam = act->tamElem;

                marca = 1;

                act->dato = act->sig->dato;
                act->sig->dato= inf;
                act->tamElem = act->sig->tamElem;
                act->sig->tamElem = tam;
            }
            act = act->sig;
        }

        sup = act;
        while(act->ant != inf)
        {
            if(cmp(act->dato, act->ant->dato) < 0)
            {
                void  *inf = act->dato;
                size_t tam = act->tamElem;

                marca = 1;

                act->dato = act->ant->dato;
                act->ant->dato = inf;
                act->tamElem = act->ant->tamElem;
                act->ant->tamElem = tam;
            }
            act = act->ant;
        }
        inf = act;
    }

    return TODO_OK;
}
int eliminarDuplicadosListaOrdAct_alu(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    int cantElim = 0;
    NodoD* n1 = *pl;

    if(!n1)
        return FALSO;

    while(n1->ant)
        n1 = n1->ant;

    NodoD* n2;
    NodoD* nae;

    while(n1)
    {
        n2 = n1->sig;

        while(n2 && cmp(n1->dato, n2->dato) == 0)
        {
            nae = n2;
            n2 = nae->sig;

            if(nae == *pl)
                *pl = nae->ant? nae->ant : nae->sig;

            if(nae->ant)
                nae->ant->sig = nae->sig;
            if(nae->sig)
                nae->sig->ant = nae->ant;

            actualizar(n1->dato, nae->dato);

            free(nae->dato);
            free(nae);

            cantElim++;
        }
        n1 = n1->sig;
    }

    return cantElim;
}
int eliminarPrimeroLista_alu(Lista* pl, void* dato, size_t tam)
{
    NodoD* nae = *pl;

    if(!nae)
        return TODO_OK;

    while(nae->ant)
        nae = nae->ant;

    if (nae->sig)
        nae->sig->ant = NULL;

    if(nae == *pl)
        *pl = nae->sig;

    memcpy(dato, nae->dato, min(tam, nae->tamElem));

    free(nae->dato);
    free(nae);

    return TODO_OK;
}

//Utilidades
int comparacionLista_alu(const void* e1, const void* e2)
{
    ArmadoYRep* dat1 = (ArmadoYRep*)e1;
    ArmadoYRep* dat2 = (ArmadoYRep*)e2;

    return strcmp_alu(dat1->codigo, dat2->codigo);
}
int comparacionArbol_alu(const void* e1, const void* e2)
{
    IndComponente* dat1 = (IndComponente*)e1;
    IndComponente* dat2 = (IndComponente*)e2;

    return strcmp_alu(dat1->codigo, dat2->codigo);
}
void actualizacionLista_alu(void* actualizado, const void* actualizador)
{
    ArmadoYRep* dat1 = (ArmadoYRep*)actualizado;
    ArmadoYRep* dat2 = (ArmadoYRep*)actualizador;

    dat1->cantidad += dat2->cantidad;
}
int strcmp_alu (char* text, char* text2)
{
    while (*text || *text2)
    {
        if (*text == *text2)
        {
            text++;
            text2++;
        }
        else
            return *text-*text2;
    }
    return 0;
}
