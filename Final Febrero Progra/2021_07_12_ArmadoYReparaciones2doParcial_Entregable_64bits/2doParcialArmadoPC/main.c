#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDALista/TDALista.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

#define minimo(x,y) ((x) <= (y)? (x) : (y))

int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);

int compararCodigoArmYRep_ALU(const void* armYRep1, const void* armYRep2);
int compararIndice_ALU(const void* comp1, const void* comp2);
void actualizarArmYRep_ALU(void *actualizado, const void* actualizador);
int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* pa);
void cargarArmadosYRepEnLista_alu(const char* pathArmYRep, Lista* pl);
void mostrarArmadoYRep_alu(void* dato, void* datosAccion);

int insertarEnListaOrdCDup_alu(Lista* pl, const void* dato, size_t tamElem, Cmp cmp);
int eliminarDeListaOrdDuplicados_alu(Lista* pl, Cmp cmp, Actualizar actualizar);
void recorrerLista_alu(Lista* pl, Accion accion, void* datosAccion);

int cargarArbol_alu(Arbol* pa,FILE* pf, size_t tamElem,int li, int ls, Cmp cmp);
int buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
int vaciarArbol_alu(Arbol* pa);

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
    Lista listaArmYRep;
    crearLista(&listaArmYRep);

    Arbol arbolComp;
    crearArbol(&arbolComp);

    cargarArmadosYRepEnLista_alu(pathArmadoYRep,&listaArmYRep);
    eliminarDeListaOrdDuplicados_alu(&listaArmYRep,compararCodigoArmYRep_ALU,actualizarArmYRep_ALU);
    cargarIndiceComponentes_ALU("Componentes.idx",&arbolComp);

    FILE *pfComponentes = fopen(pathComponentes,"r+b");
    if(!pfComponentes)
    {
        fclose(pfComponentes);
        return -56;
    }

    ArmadoYRep regArm;
    IndComponente regInd;
    Componente regComp;

    while(!listaVacia(&listaArmYRep))
    {
        eliminarDeListaPrimero(&listaArmYRep,&regArm,sizeof(ArmadoYRep));
        strcpy(regInd.codigo,regArm.codigo);
        buscarEnArbol_alu(&arbolComp,&regInd,sizeof(IndComponente),compararIndice_ALU);
        fseek(pfComponentes,regInd.nroReg*sizeof(Componente),SEEK_SET);
        fread(&regComp,sizeof(Componente),1,pfComponentes);
        regComp.stock-=regArm.cantidad;
        fseek(pfComponentes,-(long)sizeof(Componente),SEEK_CUR);
        fwrite(&regComp,sizeof(Componente),1,pfComponentes);
    }

    vaciarArbol_alu(&arbolComp);

    fclose(pfComponentes);
    return TODO_OK;
}

void cargarArmadosYRepEnLista_alu(const char* pathArmYRep, Lista* pl)
{
    FILE *pf = fopen(pathArmYRep,"rb");
    if(!pf)
    {
        fclose(pf);
        return;
    }

    ArmadoYRep regArm;

    fread(&regArm,sizeof(ArmadoYRep),1,pf);
    while(!feof(pf))
    {
        insertarEnListaOrdCDup_alu(pl,&regArm,sizeof(ArmadoYRep),compararCodigoArmYRep_ALU);
        fread(&regArm,sizeof(ArmadoYRep),1,pf);
    }

    fclose(pf);
}

int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* pa)
{
    FILE *pf = fopen(pathComponentesIdx,"rb");
    if(!pf)
    {
        fclose(pf);
        return -35;
    }

    fseek(pf,0L,SEEK_END);
    int cBytes = ftell(pf);
    int cRegs = cBytes/sizeof(IndComponente);
    fseek(pf,0L,SEEK_SET);

    cargarArbol_alu(pa,pf,sizeof(IndComponente),0,cRegs-1,compararIndice_ALU);


    fclose(pf);
    return TODO_OK;
}

int vaciarArbol_alu(Arbol* pa)
{
    if(!*pa)
        return 0;

    int cne = 0;
    cne+=vaciarArbol_alu(&(*pa)->hDer);
    cne+=vaciarArbol_alu(&(*pa)->hIzq);
    free((*pa)->dato);
    free(*pa);
    *pa = NULL;
    return cne+1;
}

int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    NodoA* nue = malloc(sizeof(NodoA));
    nue->dato = malloc(tamElem);

    if(!nue || !nue->dato)
    {
        free(nue->dato);
        free(nue);
        return -4;
    }

    memcpy(nue->dato,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pa)
    {
        nue->hDer = NULL;
        nue->hIzq = NULL;

        *pa = nue;

        return TODO_OK;
    }

    int comp = cmp((*pa)->dato, dato);

    if(comp < 0)
        return insertarEnArbol_alu(&(*pa)->hDer,dato,tamElem,cmp);
    else
        return insertarEnArbol_alu(&(*pa)->hIzq,dato,tamElem,cmp);
}

int cargarArbol_alu(Arbol* pa,FILE* pf, size_t tamElem,int li, int ls, Cmp cmp)
{
    if(li > ls)
        return 0;

    int mitad = (li+ls)/2;
    fseek(pf,(long)mitad*tamElem,SEEK_SET);

    void* reg = malloc(tamElem);
    if(!reg)
    {
        free(reg);
        return -6;
    }

    fread(reg,tamElem,1,pf);
    insertarEnArbol_alu(pa,reg,tamElem,cmp);
    cargarArbol_alu(pa,pf,tamElem,mitad+1,ls,cmp);
    cargarArbol_alu(pa,pf,tamElem,li,mitad-1,cmp);

    return TODO_OK;
}

int buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return 0;

    int comp = cmp((*pa)->dato,dato);

    if(comp == 0)
    {
        memcpy(dato,(*pa)->dato,minimo(tamElem,(*pa)->tamElem));
        return 1;
    }

    if(comp < 0)
        return buscarEnArbol_alu(&(*pa)->hDer,dato,tamElem,cmp);
    else
        return buscarEnArbol_alu(&(*pa)->hIzq,dato,tamElem,cmp);
}

int eliminarDeListaOrdDuplicados_alu(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return -5;

    NodoD* act = *pl;

    while(act->ant)
        act = act->ant;

    while(act && act->sig)
    {
        int comp = cmp(act->dato, act->sig->dato);

        if(comp == 0)
        {
            actualizar(act->dato,act->sig->dato);
            NodoD* nae = act->sig;
            if(nae->sig)
                nae->sig->ant = act;
            act->sig = nae->sig;

            free(nae->dato);
            free(nae);
        }
        else
            act = act->sig;
    }

    *pl = act;

    return TODO_OK;
}

int insertarEnListaOrdCDup_alu(Lista* pl, const void* dato, size_t tamElem, Cmp cmp)
{
    NodoD* nue = malloc(sizeof(NodoD));
    nue->dato = malloc(tamElem);

    if(!nue || !nue->dato)
    {
        free(nue->dato);
        free(nue);
        return -1;
    }

    memcpy(nue->dato,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->ant = NULL;
        nue->sig = NULL;
        *pl = nue;
        return TODO_OK;
    }

    if(cmp((*pl)->dato,dato) < 0)
    {
        NodoD* act = *pl;

        while(act->sig && cmp(act->dato,dato) < 0)
            act = act->sig;

        if(cmp(act->dato,dato) < 0)
        {
            NodoD* ant = act;
            NodoD* sig = act->sig;

            ant->sig = nue;

            nue->ant = ant;
            nue->sig = sig;

            *pl = nue;

            return TODO_OK;
        }

        if(cmp(act->dato,dato) >= 0)
        {
            NodoD* ant = act->ant;
            NodoD* sig = act;

            ant->sig = nue;
            sig->ant = nue;

            nue->ant = ant;
            nue->sig = sig;

            *pl = nue;

            return TODO_OK;
        }
    }

    if(cmp((*pl)->dato, dato) > 0)
    {
        NodoD* act = *pl;

        while(act->ant && cmp(act->dato,dato) > 0)
            act = act->ant;

        if(cmp(act->dato,dato) > 0)
        {
            NodoD* ant = act->ant;
            NodoD* sig = act;

            sig->ant = nue;

            nue->ant = ant;
            nue->sig = sig;

            *pl = nue;

            return TODO_OK;
        }

        if(cmp(act->dato,dato) <= 0)
        {
            NodoD* ant = act;
            NodoD* sig = act->sig;

            ant->sig = nue;
            sig->ant = nue;

            nue->sig = sig;
            nue->ant = ant;

            *pl = nue;

            return TODO_OK;
        }
    }

    NodoD* ant = (*pl);
    NodoD* sig = (*pl)->sig;

    if(ant)
        ant->sig = nue;
    if(sig)
        sig->ant = nue;

    nue->ant = ant;
    nue->sig = sig;

    *pl = nue;

    return TODO_OK;
}

int compararIndice_ALU(const void* comp1, const void* comp2)
{
    IndComponente* ind1 = (IndComponente*)comp1;
    IndComponente* ind2 = (IndComponente*)comp2;

    return strcmp(ind1->codigo,ind2->codigo);
}

int compararCodigoArmYRep_ALU(const void* armYRep1, const void* armYRep2)
{
    ArmadoYRep* armado1 = (ArmadoYRep*)armYRep1;
    ArmadoYRep* armado2 = (ArmadoYRep*)armYRep2;

    return strcmp(armado1->codigo,armado2->codigo);
}

void actualizarArmYRep_ALU(void *actualizado, const void* actualizador)
{
    ArmadoYRep* rep1 = (ArmadoYRep*)actualizado;
    ArmadoYRep* rep2 = (ArmadoYRep*)actualizador;

    rep1->cantidad+=rep2->cantidad;
}

void mostrarArmadoYRep_alu(void* dato, void* datosAccion)
{
    ArmadoYRep* rep = (ArmadoYRep*)dato;

    printf("%d %s %d %f\n",rep->nroOp, rep->codigo,rep->cantidad,rep->precioUnitario);
}

void recorrerLista_alu(Lista* pl, Accion accion, void* datosAccion)
{
    if(!*pl)
        return;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        accion((*pl)->dato,datosAccion);
        pl = &(*pl)->sig;
    }
}
