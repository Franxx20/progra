#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../Nodo/NodoD.h"
#include "../Nodo/NodoA.h"
#include<stdbool.h>
#include"../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include"../TDALista/TDALista.h"
#include"../TDAArbol/TDAArbol.h"

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

#define MIN(a,b) ((a) < (b) ? (a) : (b))
int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep);
void actualizarStock_ALU(void * actualizado, const void * actualizador);


int compararCodigos_ALU(const void * dato1, const void * dato2);
int compararCodigosIndice_ALU(const void * dato1, const void * dato2);
int compararComponenteConIndice(const void * dato1, const void * dato2);

void mostrarArmadoYRep_ALU(void *dato, void *datosAccion);
void mostrarIndice(void * dato, void * datosAccion);

int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* pa,Cmp cmp);
void cargarArmadosYRepEnLista_alu(const char* pathArmYRep, Lista* pl);

void obtenerPathIdx_ALU(const char* pathComponentes, char* pathComponentesIdx);

bool actualizarArchivoComponentes_ALU(const char * pathComponentes,Arbol *t, Lista *l);

bool cargarEnArbolDeUnArchivoOrdenado_ALU(Arbol * t, int li, int ls, int tamDato, FILE * fp, Cmp cmp,Actualizar actualizar);

//LISTA DOBLE
NodoD * crearNodo_ALU(const void * dato, unsigned tamDato);
void crearLista_ALU(Lista* pl);
int listaVacia_ALU(const Lista* pl);
int listaLlena_ALU(const Lista* pl, size_t tamElem);
void vaciarLista_ALU(Lista *l);
void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion);
int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);
void ordenarLista_ALU(Lista *l,Cmp cmp);

int eliminarPrimeroDeLista_ALU(Lista *l, void * dato, unsigned tamDato);

////// ARBOL
NodoA * crearNodoA_ALU(const void * dato, unsigned tamDato);
int insertarEnArbol_ALU(Arbol* t, void* dato, unsigned tamDato, Cmp cmp);
int buscarEnArbol_ALU(Arbol *t, void * dato, unsigned tamDato, Cmp cmp);
void recorrerArbolEnOrden_ALU(const Arbol *t, Accion accion, void * dAccion);

void crearArbol_ALU(Arbol *t);
int vaciarArbol_ALU(Arbol *t);



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

    // int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///************************************************************************************
    ///******** Descomente esta línea y comente la de arriba para probar su código ********
    int resp = actualizarComponentes_ALU(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
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


int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.


    Lista armYrep;
    crearLista(&armYrep);

    cargarArmadosYRepEnLista(pathArmadoYRep,&armYrep);
    //recorrerLista_ALU(&armYrep,mostrarArmadoYRep_ALU,NULL);
    ordenarLista_ALU(&armYrep,compararCodigos_ALU);

    // puts( "LISTA ORDENADA");
    //  recorrerLista_ALU(&armYrep,mostrarArmadoYRep_ALU,NULL);
    eliminarDeListaOrdDuplicados_ALU(&armYrep,compararCodigos_ALU,actualizarStock_ALU);

    puts("LISTA SIN DUPLICADOS");
    recorrerLista_ALU(&armYrep,mostrarArmadoYRep_ALU,NULL);

    Arbol tIndice;
    crearArbol(&tIndice);


    //  cargarIndiceComponentes("Componentes2.idx",&tIndice);
    char pathComponentesIndice[16];
    obtenerPathIdx_ALU(pathComponentes,pathComponentesIndice);

    puts("INDICES EN EL ARBOl");
    cargarIndiceComponentes_ALU(pathComponentesIndice,&tIndice,compararCodigosIndice_ALU);

//    recorrerArbolEnOrden_ALU(&tIndice,mostrarIndice,NULL);


    puts("ABRIMOS PARA ACTUALIZAR");

    actualizarArchivoComponentes_ALU(pathComponentes,&tIndice,&armYrep);
    vaciarLista_ALU(&armYrep);
    vaciarArbol_ALU(&tIndice);
    return TODO_OK;
}

void actualizarStock_ALU(void * actualizado, const void * actualizador)
{
    ArmadoYRep * destino = (ArmadoYRep *)actualizado;
    const ArmadoYRep * origen = (const ArmadoYRep *) actualizador;
    destino->cantidad += origen->cantidad;
}

int compararCodigos_ALU(const void * dato1, const void * dato2)
{
    ArmadoYRep* elem1 = (ArmadoYRep*)dato1;
    ArmadoYRep* elem2 = (ArmadoYRep*)dato2;

    return strcmp(elem1->codigo, elem2->codigo);
}

int compararCodigosIndice_ALU(const void * dato1, const void * dato2)
{
    IndComponente * d1 = (IndComponente *)dato1;
    const IndComponente * d2 = (const IndComponente *) dato2;

    return d1->nroReg - d2->nroReg;
}

int compararComponenteConIndice(const void * dato1, const void * dato2)
{
    IndComponente * d1 = (IndComponente *)dato1;
    const IndComponente * d2 = (const IndComponente *) dato2;

    return strncmp(d1->codigo, d2->codigo,21);
}

void mostrarArmadoYRep_ALU(void *dato, void *datosAccion)
{
    ArmadoYRep * d = (ArmadoYRep *)dato;
    printf("\t%d\t%-20s\t%d\t%.02f\n",d->nroOp,d->codigo,d->cantidad,d->precioUnitario);
}

void mostrarIndice(void * dato, void * datosAccion)
{

    IndComponente * d  = (IndComponente*) dato;
    printf("%-20s\t%d\n", d->codigo,d->nroReg);
}

bool actualizarArchivoComponentes_ALU(const char *  pathComponentes,Arbol *t, Lista *l)
{
    FILE *fp = fopen(pathComponentes,"r+b");

    if(!fp)
    {
        return false;
    }

    Componente comp;
    IndComponente idx;
    ArmadoYRep arm;



    while(!listaVacia(l))
    {
        eliminarPrimeroDeLista_ALU(l,&arm,sizeof(ArmadoYRep));
        strncpy(idx.codigo,arm.codigo,21);


        if ( buscarEnArbol_ALU(t,&idx,sizeof(IndComponente),compararComponenteConIndice))
        {
            fseek(fp,idx.nroReg*sizeof(Componente),SEEK_SET);
            fread(&comp,sizeof(Componente),1,fp);

            comp.stock -= arm.cantidad;

          //  fseek(fp,-(long)sizeof(Componente),SEEK_CUR);
            fseek(fp,(long int)(-1L * sizeof(Componente)), SEEK_CUR);
            fwrite(&comp,sizeof(Componente),1,fp);
            fseek(fp,0L,SEEK_CUR);
        }


    }

    fclose(fp);

    return true;
}

// LISTA
NodoD * crearNodo_ALU(const void * dato, unsigned tamDato)
{
    NodoD * nue = (NodoD*)malloc(sizeof(NodoD));
    if(!nue|| !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->ant = NULL;
    nue->sig = NULL;

    return nue;
}
void crearLista_ALU(Lista* l)
{
    *l = NULL;
}

int listaVacia_ALU(const Lista* l)
{
    return *l == NULL;
}

int listaLlena_ALU(const Lista* l, size_t tamElem)
{
    NodoD * nue = (NodoD  * )malloc(sizeof(NodoD));
    void * dato = malloc(tamElem);
    free(nue);
    free(dato);

    return !nue || !dato;
}

void vaciarLista_ALU(Lista *l)
{
    NodoD * nae;
    NodoD * act = *l;
    if(act)
    {
        while(act->ant)
            act = act->ant;


        while(act)
        {
            nae = act;
            act = nae->sig;
            free(nae->dato);
            free(nae);
        }
        *l = NULL;
    }

}

void recorrerLista_ALU(Lista* pl, Accion accion, void* datosAccion)
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

int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
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

void ordenarLista_ALU(Lista *l,Cmp cmp)
{
    int ordenado;
    NodoD * act = *l;
    if(!act)
        return;

    do
    {
        while(act->ant)
            act = act->ant;

        ordenado = 0;

        while (act->sig)
        {
            if (cmp(act->dato,act->sig->dato)>0)
            {
                void * auxDato = act->dato;
                size_t auxTamDato = act->tamElem;

                act->dato = act->sig->dato;
                act->sig->dato = auxDato;

                act->tamElem = act->sig->tamElem;
                act->sig->tamElem = auxTamDato;

                ordenado = 1;
            }
            act = act->sig;
        }
    }
    while (ordenado);

}

int cargarIndiceComponentes_ALU(const char* pathComponentesIdx, Arbol* pa, Cmp cmp)
{
//    FILE * fp  = fopen(pathComponentesIdx,"rb");
//    if(!fp)
//    {
//        fprintf(stderr,"ERROR  AL ABRIR EL ARCHIVO DE INDICES");
//        return false;
//    }
//    // vamos hasta el final del archivo
//    fseek(fp,0L,SEEK_END);
//
//    // CONTAMOS LA CANTIDAD DE BYTES DESDE EL INICIO HASTA EL FIN DEL ARCHIVO
//    int cantBytes = ftell(fp);
//    int cantidadRegistros = cantBytes/sizeof(IndComponente);
//
//
//    cargarEnArbolDeUnArchivoOrdenado_ALU(pa,0,cantidadRegistros-1,sizeof(IndComponente),fp,cmp,NULL);
//
//    fclose(fp);
    // return true;
    return cargarArbol(pa, sizeof(IndComponente), pathComponentesIdx);
}



void obtenerPathIdx_ALU(const char* pathComponentes, char* pathComponentesIdx)
{

    strcpy(pathComponentesIdx,pathComponentes);
    char * aux = strrchr(pathComponentesIdx,'.');
    strcpy(aux+1,"IDX");

}

bool cargarEnArbolDeUnArchivoOrdenado_ALU(Arbol *t, int li,int ls, int tamDato,FILE * fp,Cmp cmp,Actualizar actualizar)
{
    // CASE BASE CUANDO EL LI ES MAYOR AL Ls
    if(li > ls)
        return false;

    int mitad = (li + ls)/2;
    fseek(fp,mitad*tamDato,SEEK_SET);
    void * registro  = malloc(tamDato);
    if(!registro)
    {

        return false;
    }
    fread(registro,tamDato,1,fp);
    insertarEnArbol_ALU(t,registro,tamDato,cmp);

    cargarEnArbolDeUnArchivoOrdenado_ALU(t,0,mitad-1,tamDato,fp,cmp,actualizar);
    cargarEnArbolDeUnArchivoOrdenado_ALU(t,mitad+1,ls,tamDato,fp,cmp,actualizar);
    return true;
}
int eliminarPrimeroDeLista_ALU(Lista *l, void * dato, unsigned tamDato)
{
    if(!*l)
        return false;

    NodoD * act = *l;
    NodoD * nae;
    while(act->ant)
        act = act->ant;

    nae = act;
    act = nae->sig;


    if(act)
        act->ant = NULL;

    if(nae == *l)
        *l = nae->sig;


    memcpy(dato,nae->dato,min(nae->tamElem,tamDato));
    free(nae->dato);
    free(nae);
    return true;


}

////// ARBOL

NodoA * crearNodoA_ALU(const void * dato, unsigned tamDato)
{
    NodoA * nue = (NodoA*)malloc(sizeof(NodoA));
    if(!nue|| !(nue->dato = malloc(tamDato)))
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

int insertarEnArbol_ALU(Arbol* t, void* dato, unsigned tamDato, Cmp cmp)
{

    if(!*t)
    {
        *t = crearNodoA_ALU(dato,tamDato);
        if(!*t)
            return false;

        return TODO_OK;
    }

    int res = cmp(dato,(*t)->dato);
    if(res == 0)
        return false;

    return insertarEnArbol_ALU(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}
int buscarEnArbol_ALU(Arbol *t, void * dato, unsigned tamDato, Cmp cmp)
{
    if(!*t)
        return false;

    int res = cmp(dato,(*t)->dato);

    if(res == 0){
        memcpy(dato,(*t)->dato,MIN((*t)->tamElem,tamDato));
        return 1;

    }

    return buscarEnArbol_ALU(res<0?&(*t)->hIzq:&(*t)->hDer,dato,tamDato,cmp);
}

void crearArbol_ALU(Arbol *t)
{
    *t = NULL;
}

int vaciarArbol_ALU(Arbol *t)
{
    if(!*t)
        return 0;

    int cne= 0;
    cne += vaciarArbol_ALU(&(*t)->hIzq);
    cne += vaciarArbol_ALU(&(*t)->hDer);

    free((*t)->dato);
    free((*t));

    *t = NULL;

    return cne +1;
}

void recorrerArbolEnOrden_ALU(const Arbol *t, Accion accion, void * dAccion)
{

    if(*t)
    {
        recorrerArbolEnOrden_ALU(&(*t)->hIzq,accion,dAccion);
        accion((*t)->dato,dAccion);
        recorrerArbolEnOrden_ALU(&(*t)->hDer,accion,dAccion);
    }

}
