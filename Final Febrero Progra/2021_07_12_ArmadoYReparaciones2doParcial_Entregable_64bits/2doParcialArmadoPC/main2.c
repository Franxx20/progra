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

#define ERR_ARCHIVO -1
#define ERR_MEM -2
#define ERR_NODO -3
#define ERR_SALTO_DE_LINEA -4
#define ERR_LIMITES -5
#define REPETIDO -6

// FUNCIONES GENERALES
int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* pa);
int cargarArmadosYRepEnLista_ALU(const char * nombreArchivo, Lista *l);
int obtenerPathIdx_ALU(const char * pathComponentes,char * pathIndice);


// FUNCIONES PUNTERO
int cmpIndice_ALU(const void * d1, const void * d2);
int cmpArmYRep_ALU(const void * d1, const void * d2);
void actualizarAyR_ALU(void * actualizado, const void * actualizador);


// FUNCIONES LISTA
NodoD * crearNodoD(void * dato, size_t tamDato);

void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

int listaLlena_ALU(const Lista *l,size_t tamDato);
int listaVacia_ALU(const Lista *l);

int insertarOActualizarEnListaOrd_ALU(Lista *l,const void * dato,size_t tamDato, Cmp cmp, Actualizar actualizar);
int eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato);

int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp,Actualizar actualizar);



// FUNCIONES ARBOL
NodoA* crearNodoA(const void * dato, size_t tamDato);
void crearArbol_ALU(Arbol*t);
int vaciarArbol_ALU(Arbol *t);

int insertarEnArbol_ALU(Arbol *t, void *dato, size_t tamDato, Cmp cmp);
int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato,Cmp cmp);


int cargarEnUnArbolDesdeUnArchivoOrdenado_ALU(Arbol * a, int li, int ls, FILE * fp, size_t tamDato, Cmp cmp);

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

    //int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///************************************************************************************
    ///******** Descomente esta línea y comente la de arriba para probar su código ********
    //
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
    FILE * fpComponentes = fopen(pathComponentes,"r+b");


    Arbol arbolIndice;
    Lista listaArmadosYrep;

    ArmadoYRep ayr;
    IndComponente indice;
    Componente componente;

    char * pathIndice = calloc(50,sizeof(char));

    if(!fpComponentes)
    {
        fclose(fpComponentes);
        fprintf(stderr,"ERROR ABRIENDO EL ARCHIVO DE COMPONENTES");
        return ERR_ARCHIVO;
    }


    crearArbol(&arbolIndice);
    crearLista_ALU(&listaArmadosYrep);

    cargarArmadosYRepEnLista_ALU(pathArmadoYRep,&listaArmadosYrep);
    //  eliminarDeListaOrdDuplicados(&listaArmadosYrep,cmpArmYRep_ALU,actualizarAyR_ALU);

    obtenerPathIdx_ALU(pathComponentes,pathIndice);
    cargarIndiceComponentes_ALU(pathIndice,&arbolIndice);
// cargarIndiceComponentes_ALU("Componentes.idx",&arbolIndice);

    while(!listaVacia_ALU(&listaArmadosYrep))
    {
        eliminarDeListaPrimero_ALU(&listaArmadosYrep,&ayr,sizeof(ArmadoYRep));
        strcpy(indice.codigo,ayr.codigo);
        buscarEnArbol_ALU(&arbolIndice,&indice,sizeof(IndComponente),cmpIndice_ALU);

        fseek(fpComponentes,(long)indice.nroReg * sizeof(Componente),SEEK_SET);
        fread(&componente,sizeof(Componente),1,fpComponentes);
        componente.stock-=ayr.cantidad;

        fseek(fpComponentes,-(long) sizeof(Componente),SEEK_CUR);
        fwrite(&componente,sizeof(Componente),1,fpComponentes);
    }




    vaciarArbol_ALU(&arbolIndice);
    vaciarLista_ALU(&listaArmadosYrep);
    free(pathIndice);
    return TODO_OK;
}

// FUNCIONES PUNTERO
int cmpIndice_ALU(const void * d1, const void * d2)
{
    IndComponente * i1 = (IndComponente * )d1;
    IndComponente * i2 = (IndComponente *)d2;

    return strcmp(i1->codigo, i2->codigo);
}

int cmpArmYRep_ALU(const void * d1, const void * d2)
{
    ArmadoYRep * ayr1 =(ArmadoYRep * )d1;
    ArmadoYRep * ayr2 = (ArmadoYRep*)d2;

    return strcmp(ayr1->codigo, ayr2->codigo);
}

void actualizarAyR_ALU(void * actualizado, const void * actualizador)
{
    ArmadoYRep * ayr1 =(ArmadoYRep * )actualizado;
    ArmadoYRep * ayr2 = (ArmadoYRep*)actualizador;

    ayr1 ->cantidad +=ayr2->cantidad;
}

// FUNCIONES LISTA
NodoD * crearNodoD(void * dato, size_t tamDato)
{
    NodoD* nue = (NodoD* )calloc(1,sizeof(NodoD));
    if(!nue ||!(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}
void vaciarLista_ALU(Lista *l)
{
    NodoD * aux;
    NodoD * act;
    if(!*l)
        return;

    act  = *l;
    while(act->ant)
        act = act->ant;

    while(act->sig)
    {
        aux = act;
        act = aux->sig;

        free(aux->dato);
        free(aux);
    }
    *l = NULL;

}
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}

int listaLlena_ALU(const Lista *l,size_t tamDato)
{
    NodoD * nodoAux = (NodoD*)calloc(1,sizeof(NodoD));
    void *datoAux = calloc(1,tamDato);
    free(nodoAux);
    free(datoAux);
    return !nodoAux || !datoAux;
}

int listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}

int insertarOActualizarEnListaOrd_ALU(Lista *l,const void * dato,size_t tamDato, Cmp cmp, Actualizar actualizar)
{
    NodoD * nue = crearNodoD((void *)dato,tamDato);
    NodoD * act;
    NodoD * sig = NULL;
    NodoD * ant = NULL;
    int resultado ;
    if(!nue)
    {
        return ERR_NODO;
    }

    act =*l;

    if(act)
        while(act->ant)
            act =act->ant;

    if(act)
    {
        while(act->ant && cmp(act->dato,nue->dato)<0)
        {
            act =act->ant;
        }
        while(act->sig && cmp(act->dato,nue->dato)>0)
            act =act->sig;

        resultado = cmp(act->dato,nue->dato);

        // si el dato a insertar es igual al dato actual
        if(resultado == 0)
            if(actualizar)
            {
                actualizar(act->dato,nue->dato);
                return REPETIDO;
            }

        // si el dato a insertar es mas chico que el dato actual
        if(resultado < 0)
        {
            sig = act;
            ant = act->ant;
        } // si el dato a insertar es mas grande que el dato actual
        else
        {
            sig =act->sig;
            ant = act;
        }
    }

    nue->sig = sig;
    nue->ant = ant;

    if(ant)
        ant->sig = nue;

    if(sig)
        sig->ant = nue;

    *l = nue;




    return TODO_OK;
}

int eliminarDeListaPrimero_ALU(Lista *l, void * dato, size_t tamDato)
{
    NodoD * act;
    NodoD* nae;
    if(!*l)
        return ERR_NODO;

    act =*l;

    while(act->ant )
        act = act->ant;

    nae = act;
    act = nae->sig;

    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l = nae->sig;


    memcpy(dato,nae->dato,minimo(tamDato,nae->tamElem));

    free(nae->dato);
    free(nae);


    return TODO_OK;
}

int eliminarDeListaOrdDuplicados_ALU(Lista *l, Cmp cmp,Actualizar actualizar)
{
    NodoD * act;
    NodoD * sig;
    NodoD * nae;
    int cne=0;

    if(!*l)
        return ERR_NODO;
    act  = *l;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        sig = act->sig;
        while(sig && cmp(act->dato, sig->dato) ==0)
        {
            nae = sig;
            sig = nae->sig;

            if(nae == *l)
                *l =nae->sig?nae->sig:nae->ant;

            if(nae->ant)
                nae->ant->sig = nae->sig;
            if(nae->sig)
                nae->sig->ant = nae->ant;

            if(actualizar)
                actualizar(act->dato,nae->dato);

            free(nae->dato);
            free(nae);
            nae++;
        }
        act = act->sig;
    }

    return cne;
}



// FUNCIONES ARBOL
NodoA* crearNodoA(const void * dato, size_t tamDato)
{
    NodoA * nue = (NodoA* )calloc(1,sizeof(NodoA));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->hIzq = NULL;
    nue->hDer = NULL;


    return nue;
}
void crearArbol_ALU(Arbol*t)
{
    *t = NULL;
}

int vaciarArbol_ALU(Arbol *t)
{
    int cne =0;
    if(!*t)
        return cne;

    cne+= vaciarArbol_ALU(&(*t)->hIzq);
    cne+= vaciarArbol_ALU(&(*t)->hDer);

    free((*t)->dato);
    free((*t));

    return cne+1;
}

int insertarEnArbol_ALU(Arbol *t, void *dato, size_t tamDato, Cmp cmp)
{
    int resultado;
    if(!*t)
    {
        *t = crearNodoA(dato,tamDato);
        if(!*t)
            return ERR_NODO;

        return TODO_OK;

    }
    resultado = cmp((*t)->dato, dato);

    if(resultado ==0)
        return DUPLICADO;


    return insertarEnArbol_ALU(resultado >0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

int buscarEnArbol_ALU(const Arbol *t, void * dato, size_t tamDato,Cmp cmp)
{
    int resultado;

    if(!*t)
        return 0;

    resultado = cmp((*t)->dato,dato);

    if(resultado ==0)
    {

        memcpy(dato,(*t)->dato,tamDato);
        return TODO_OK;
    }



    return buscarEnArbol_ALU(resultado>0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

// FUNCIONES GENERALES
int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* a)
{
    FILE * fp = fopen(pathComponentesIdx,"rb");
    if(!fp)
    {
        fprintf(stderr,"ERROR EN ABRIR EL ARCHIVO PARA CARGAR EN EL ARBOl");
        fclose(fp);
        return ERR_ARCHIVO;
    }
    fseek(fp,0L,SEEK_END);
    int cantBytes = ftell(fp);
    int cantReg = cantBytes / sizeof(IndComponente);
    //fseek(fp,0L,SEEK_SET);

    cargarEnUnArbolDesdeUnArchivoOrdenado_ALU(a,0,cantReg-1,fp,sizeof(IndComponente),cmpIndice_ALU);


    fclose(fp);



    return TODO_OK;

}

int cargarArmadosYRepEnLista_ALU(const char * nombreArchivo, Lista *l)
{
    FILE * fp = fopen(nombreArchivo,"rb");
    ArmadoYRep ayr;
    if(!fp)
    {
        fclose(fp);
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE ARMADOS Y REPETIDOS");
        return ERR_ARCHIVO;
    }

    fread(&ayr,sizeof(ArmadoYRep),1,fp);
    while(!feof(fp))
    {
        insertarOActualizarEnListaOrd_ALU(l,&ayr,sizeof(ArmadoYRep),cmpArmYRep_ALU,actualizarAyR_ALU);
        fread(&ayr,sizeof(ArmadoYRep),1,fp);
    }

    return TODO_OK;
}

int obtenerPathIdx_ALU(const char * pathComponentes,char * pathIndice)
{

    char * aux;
    strcpy(pathIndice,pathComponentes);
    aux = strrchr(pathIndice,'.');
    strcpy(aux+1,"idx");
    return TODO_OK;

}
// FUNCIONES ARBOL
int cargarEnUnArbolDesdeUnArchivoOrdenado_ALU(Arbol * a, int li, int ls, FILE * fp, size_t tamDato, Cmp cmp)
{
    if(li > ls)
        return ERR_LIMITES;


    void *dato = calloc(1,tamDato);
    if(!dato)
    {
        free(dato);
        return ERR_MEM;
    }

    int mitad = (li + ls )/2;

    fseek(fp,(long)mitad * tamDato,SEEK_SET);
    fread(dato,tamDato,1,fp);
    insertarEnArbol_ALU(a,dato,tamDato,cmp);





    cargarEnUnArbolDesdeUnArchivoOrdenado_ALU(a,li,mitad-1,fp,tamDato,cmp);
    cargarEnUnArbolDesdeUnArchivoOrdenado_ALU(a,mitad+1,ls,fp,tamDato,cmp);

    free(dato);

    return TODO_OK;
}

