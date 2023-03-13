#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

#include "../TDAArbol/TDAArbol.h"
#include "../TDALista/TDALista.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);
int listaLlena_alu(Lista* pl, size_t tamDato);
void vaciarLista_alu(Lista* pl);
void mostrarArmYRep_alu(void* dato, void* datosAccion);
int compararArmYRep_alu(const void* dato1, const void* dato2);
void recorrerLista_alu(Lista* pl, Accion accion, void* datosAccion);
void actualizarArmYRep_alu(void* actualizado, const void* actualizador);
int eliminarDeListaOrdDuplicados_alu(Lista* pl, Cmp cmp, Actualizar actualizar);
void ordenarLista_alu(Lista* pl, Cmp cmp);
void obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx);
int cargarIndiceComponentes_alu(const char* pathComponentesIdx, Arbol* pa);
int cargarArbol_alu(Arbol* pa, size_t tamElem, const char* nomArch);
int esArbolVacio_alu(const Arbol* pa);
int comparacionArbol_alu(const void* dato1, const void* dato2);
void mostrarIndices_alu(void* dato, void* datosAccion);
int eliminarDeListaPrimero_alu(Lista* pl, void* dato, size_t tamElem);
void crearArbol_alu(Arbol* pa);
int vaciarArbol_alu(Arbol* pa);
void cargarArbolRec_alu(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls);
int buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp);


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


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.
    Lista armYRep;
    crearLista(&armYRep);

    cargarArmadosYRepEnLista(pathArmadoYRep, &armYRep);

    ordenarLista_alu(&armYRep, compararArmYRep_alu);

    eliminarDeListaOrdDuplicados_alu(&armYRep, compararArmYRep_alu, actualizarArmYRep_alu);

    printf("\n\nLISTA ARMYREP CARGADA Y ORDENADA SIN DUPLICADOS\n\n");
    recorrerLista_alu(&armYRep, mostrarArmYRep_alu, NULL);

    Arbol indices;
    crearArbol_alu(&indices);

    char pathIndice[20];

    obtenerPathIdx_alu(pathComponentes, pathIndice);

    cargarIndiceComponentes_alu(pathIndice, &indices);

    /*printf("\n\nINDICES ARBOL\n\n");*/
    recorrerArbolEnOrden(&indices, mostrarIndices_alu , NULL);

    FILE* archComp = fopen(pathComponentes, "r+b");

    if(!archComp)
        return -1;

    ArmadoYRep arm;
    IndComponente idx;
    Componente comp;

    while(!listaVacia(&armYRep))
    {
        eliminarDeListaPrimero_alu(&armYRep, &arm, sizeof(ArmadoYRep));
        strcpy(idx.codigo, arm.codigo);
        if(buscarEnArbol_alu(&indices, &idx, sizeof(IndComponente), comparacionArbol_alu))
        {
            fseek(archComp, idx.nroReg * sizeof(Componente), SEEK_SET);
            fread(&comp, sizeof(Componente), 1, archComp);
            comp.stock -= arm.cantidad;

            fseek(archComp,(long int)(-1L * sizeof(Componente)), SEEK_CUR);
            fwrite(&comp, sizeof(Componente), 1, archComp);
            //fseek(archComp, 0L, SEEK_CUR);
        }
    }

    fclose(archComp);

    vaciarLista_alu(&armYRep);
    vaciarArbol_alu(&indices);



    return TODO_OK;
}


int buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    if(*pa == NULL)
        return 0;

    int comp = cmp(dato, (*pa)->dato);

    if(comp == 0)
    {
        memcpy(dato, (*pa)->dato, MIN((*pa)->tamElem, tamElem));
        return 1;
    }

    return buscarEnArbol_alu(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, dato, tamElem, cmp);
}


int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    if(*pa == NULL)
    {
        NodoA* nue = (NodoA*)malloc(sizeof(NodoA));

        if(nue == NULL || (nue->dato = malloc(tamElem)) == NULL)
        {
            free(nue);
            return 0;
        }

        memcpy(nue->dato, dato, tamElem);
        nue->tamElem = tamElem;
        nue->hDer = NULL;
        nue->hIzq = NULL;
        *pa = nue;
    }

    int comp = cmp(dato, (*pa)->dato);

    if(comp == 0)
        return 0;

    return insertarEnArbol_alu(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, dato, tamElem, cmp);
}

int vaciarArbol_alu(Arbol* pa)
{
    int cne = 0;

    if(*pa == NULL)
        return 0;

    cne = vaciarArbol_alu(&(*pa)->hIzq);
    cne += vaciarArbol_alu(&(*pa)->hDer);

    free((*pa)->dato);
    free(*pa);
    *pa = NULL;
    return cne + 1;
}

void mostrarIndices_alu(void* dato, void* datosAccion)
{
    IndComponente* elem = (IndComponente*)dato;

    printf("%s %d\n",elem->codigo, elem->nroReg);
}


int cargarArbol_alu(Arbol* pa, size_t tamElem, const char* nomArch)
{
    FILE* arch = fopen(nomArch, "rb");

    if(!arch)
        return -1;

    fseek(arch, 0L, SEEK_END);

    int ls = (ftell(arch) / tamElem) - 1;

    cargarArbolRec_alu(arch, pa, tamElem, comparacionArbol_alu, 0, ls);

    fclose(arch);

    return TODO_OK;
}


void cargarArbolRec_alu(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls)
{
    if(li > ls)
        return;

    int m = (li + ls) / 2;

    fseek(arch, m * tamElem, SEEK_SET);

    void* elem = malloc(tamElem);

    if(!elem)
        return;

    fread(elem, tamElem, 1, arch);

    insertarEnArbol_alu(pa, elem, tamElem, cmp);

    free(elem);

    cargarArbolRec_alu(arch, pa, tamElem, cmp, li, m-1);
    cargarArbolRec_alu(arch, pa, tamElem, cmp, m + 1, ls);
}


int eliminarDeListaPrimero_alu(Lista* pl, void* dato, size_t tamElem)
{
    NodoD* nae = *pl;

    if(nae == NULL)
        return 0;

    while(nae->ant)
        nae = nae->ant;

    if(nae->sig)
        nae->sig->ant = NULL;

    if(nae == *pl)
        *pl = nae->sig;

    memcpy(dato, nae->dato, MIN(nae->tamElem, tamElem));
    free(nae->dato);
    free(nae);
    return 1;
}

int comparacionArbol_alu(const void* dato1, const void* dato2)
{
    IndComponente* elem1 = (IndComponente*)dato1;
    IndComponente* elem2 = (IndComponente*)dato2;

    return strcmp(elem1->codigo, elem2->codigo);
}

int esArbolVacio_alu(const Arbol* pa)
{
    return *pa == NULL;
}


int cargarIndiceComponentes_alu(const char* pathComponentesIdx, Arbol* pa)
{
    return cargarArbol(pa, sizeof(IndComponente), pathComponentesIdx);
}

void crearArbol_alu(Arbol* pa)
{
    *pa = NULL;
}


void obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx)
{
    strcpy(pathComponentesIdx, pathComponentes);

    char* aux = strrchr(pathComponentesIdx, '.');

    strcpy(aux + 1, "idx");
}


int eliminarDeListaOrdDuplicados_alu(Lista* pl, Cmp cmp, Actualizar actualizar)
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

void ordenarLista_alu(Lista* pl, Cmp cmp)
{
    int ordenado;
    NodoD* act = *pl;

    if(!act)
        return;

    do
    {
        while(act->ant)
            act = act->ant;

        ordenado = 0;

        while(act->sig)
        {
            if(cmp(act->dato, act->sig->dato) > 0)
            {
                void* aux = act->dato;
                size_t cantBytes = act->tamElem;

                act->dato = act->sig->dato;
                act->sig->dato = aux;
                act->tamElem = act->sig->tamElem;
                act->sig->tamElem = cantBytes;

                ordenado = 1;
            }
            act = act->sig;
        }
    }
    while(ordenado);
}

void actualizarArmYRep_alu(void* actualizado, const void* actualizador)
{
    ArmadoYRep* actualizado1 = (ArmadoYRep*)actualizado;
    ArmadoYRep* actualizador2 = (ArmadoYRep*)actualizador;

    actualizado1->cantidad += actualizador2->cantidad;
}


void recorrerLista_alu(Lista* pl, Accion accion, void* datosAccion)
{
    NodoD* act = *pl;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            accion(act->dato, datosAccion);
            act = act->sig;
        }
    }
}

void mostrarArmYRep_alu(void* dato, void* datosAccion)
{
    ArmadoYRep* elem = (ArmadoYRep*)dato;

    printf("%d\t%-21s\t%d\t%lf\n",elem->nroOp, elem->codigo, elem->cantidad, elem->precioUnitario);
}



int compararArmYRep_alu(const void* dato1, const void* dato2)
{
    ArmadoYRep* elem1 = (ArmadoYRep*)dato1;
    ArmadoYRep* elem2 = (ArmadoYRep*)dato2;

    return strcmp(elem1->codigo, elem2->codigo);
}

int listaLlena_alu(Lista* pl, size_t tamDato)
{
    NodoD* aux = (NodoD*)malloc(sizeof(NodoD));
    void* info = malloc(tamDato);

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
            NodoD* nae = act;
            act = nae->sig;
            free(nae->dato);
            free(nae);
        }
        *pl = NULL;
    }
}

