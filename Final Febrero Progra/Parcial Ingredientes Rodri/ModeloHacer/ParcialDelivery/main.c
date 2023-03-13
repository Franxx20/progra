/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: ANGEL, FACUNDO NICOLAS
*
* DNI: 40640923
*
****************************************************************************************
********** Descomente el parcial que debe rendir. Si es el integrador, es P2: **********
***************************************************************************************/
//#define P1
#define P2
/***************************************************************************************
********************* Descomente la solución que quiere probar: ************************
***************************************************************************************/
///#define SOLUCION_DOC
#define SOLUCION_ALU
/**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef P1
#define TDA_COLA_IMPL_DINAMICA
#define TDA_LISTA_IMPL_DINAMICA
#endif

#ifdef P2
#define TDA_COLA_IMPL_DINAMICA_CIRCULAR
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#endif

#include "../TDACola/TDACola.h"
#include "../TDALista/TDALista.h"
#include "../SolucionDelivery/TiposDelivery.h"
#include "../SolucionDelivery/SolucionDelivery.h"
#include "../Utilitarias/Utilitarias.h"


#define TAM_LINEA 100
#define min(x,y) (x>y)?(y):(x)

void cargarIndiceEnLista_alu(const char* nomArch, size_t tamElem, Lista *pl, Cmp cmp);
void parseo_alu(char *cad, Pedido *reg);
int compararIndIngr_alu(const void* elem1, const void* elem2);
int compararIndRec_alu(const void* elem1, const void* elem2);

///Funciones de Cola Circular
void crearCola_alu(Cola *pc);
int encolar_alu(Cola *pc, const void* elem, size_t tamElem);
int desencolar_alu(Cola *pc, void* elem, size_t tamElem);
int colaVacia_alu(const Cola *pc);

///Funciones de Lista Doble
void crearLista_alu(Lista *pl);
int insertarEnListaAlFinal_alu(Lista *pl, const void* elem, size_t tamElem);
int buscarEnListaOrd_alu(const Lista *pl, void* elem, size_t tamElem, Cmp cmp);
void vaciarLista_alu(Lista *pl);

///Funciones string
int strcmp_alu(const char* cad1, const char* cad2);
char* strrchr_alu(char* cad, int caracter);
char* strncpy_alu(char* dest, const char* origen, size_t tamCad);

int main()
{
    generarArchivoPedidos();
    generarArchivoRecetas();
    generarArchivoIngredientes();

    mostrarArchivoPedidos("Pedidos.txt");
    mostrarArchivoRecetas("Recetas.dat");

    puts("Ingredientes antes de la actualizacion");
    mostrarArchivoIngredientes("Ingredientes.dat");

    int resp;

#ifdef SOLUCION_DOC
    resp = satisfacerPedidos("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#else
    resp = satisfacerPedidos_ALU("Pedidos.txt", "Recetas.dat", "Ingredientes.dat");
#endif

    if(resp != TODO_OK)
    {
        puts("Error actualizando los pedidos.");
        return resp;
    }

    puts("Ingredientes despues de la actualizacion");
    mostrarArchivoIngredientes("Ingredientes.dat");

    return 0;
}

///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que �ste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_ALU(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{
    FILE *pfPedidos = fopen(nombreArchPedidos,"rt");
    FILE *pfRecetas = fopen(nombreArchRecetas,"rb");
    FILE *pfIngredientes = fopen(nombreArchIngredientes,"r+b");
    if(!pfPedidos || !pfIngredientes || !pfRecetas)
    {
        fclose(pfPedidos);
        fclose(pfRecetas);
        fclose(pfIngredientes);
        return 0;
    }

    Lista listaIdxIngr;
    Lista listaIdxRec;
    Cola colaIngr;
    char cadPedido[256];
    Pedido regPedido;
    Ingrediente regIngr;
    IndIngrediente regIdxIngr;
    Receta regReceta;
    IndReceta regIdxReceta;


    crearLista_alu(&listaIdxIngr);
    crearLista_alu(&listaIdxRec);
    crearCola_alu(&colaIngr);

    cargarIndiceEnLista_alu("Ingredientes.idx",sizeof(IndIngrediente),&listaIdxIngr,compararIndIngr_alu);
    cargarIndiceEnLista_alu("Recetas.idx",sizeof(IndReceta),&listaIdxRec,compararIndRec_alu);

    while(fgets(cadPedido,sizeof(cadPedido),pfPedidos))
    {
        parseo_alu(cadPedido,&regPedido);

        strncpy_alu(regIdxReceta.codReceta,regPedido.codReceta,11);

        buscarEnListaOrd_alu(&listaIdxRec,&regIdxReceta,sizeof(IndReceta),compararIndRec_alu);
        fseek(pfRecetas,regIdxReceta.nroReg*sizeof(Receta),SEEK_SET);
        fread(&regReceta,sizeof(Receta),1,pfRecetas);
        while(!feof(pfRecetas) && strcmp_alu(regIdxReceta.codReceta,regReceta.codReceta) == 0)
        {
            encolar_alu(&colaIngr,&regReceta,sizeof(Receta));
            fread(&regReceta,sizeof(Receta),1,pfRecetas);
        }

        while(!colaVacia_alu(&colaIngr))
        {
            desencolar_alu(&colaIngr,&regReceta,sizeof(Receta));
            strncpy_alu(regIdxIngr.codIngr,regReceta.codIngr,11);

            buscarEnListaOrd_alu(&listaIdxIngr,&regIdxIngr,sizeof(IndIngrediente),compararIndIngr_alu);
            fseek(pfIngredientes,regIdxIngr.nroReg*sizeof(Ingrediente),SEEK_SET);
            fread(&regIngr,sizeof(Ingrediente),1,pfIngredientes);
            regIngr.stock -= regReceta.cantidad*regPedido.cantidad;
            fseek(pfIngredientes,-(long)sizeof(Ingrediente),SEEK_CUR);
            fwrite(&regIngr,sizeof(Ingrediente),1,pfIngredientes);
        }

    }

    vaciarLista_alu(&listaIdxIngr);
    vaciarLista_alu(&listaIdxRec);

    fclose(pfPedidos);
    fclose(pfRecetas);
    fclose(pfIngredientes);
    return TODO_OK;
}

void cargarIndiceEnLista_alu(const char* nomArch, size_t tamElem, Lista *pl, Cmp cmp)
{
    FILE *pfIdx = fopen(nomArch,"rb");
    if(!pfIdx)
    {
        fclose(pfIdx);
        return;
    }

    void *reg = malloc(tamElem);
    if(!reg)
    {
        free(reg);
        return;
    }

    fread(reg,tamElem,1,pfIdx);
    while(!feof(pfIdx))
    {
        insertarEnListaAlFinal_alu(pl,reg,tamElem);
        fread(reg,tamElem,1,pfIdx);
    }

    free(reg);
    fclose(pfIdx);
}

void parseo_alu(char *cad, Pedido *reg)
{
    char *aux = strrchr_alu(cad,'\n');
    *aux = '\0';

    aux = strrchr_alu(cad,'\t');
    aux++;
    sscanf(aux,"%d",&reg->cantidad);
    aux--;
    *aux = '\0';

    aux = strrchr_alu(cad,'\t');
    aux++;
    strncpy_alu(reg->codReceta,aux,11);
    aux--;
    *aux = '\0';

    sscanf(cad,"%d",&reg->nroPedido);
}

void crearLista_alu(Lista *pl)
{
    *pl = NULL;
}
int insertarEnListaAlFinal_alu(Lista *pl, const void* elem, size_t tamElem)
{
    NodoD *nue = malloc(sizeof(NodoD));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return 0;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->sig = NULL;
        nue->ant = NULL;
        *pl = nue;
        return 0;
    }

    while(*pl && (*pl)->sig)
        pl = &(*pl)->sig;

    (*pl)->sig = nue;
    nue->ant = (*pl);
    nue->sig = NULL;
    *pl = nue;

    return 1;
}
int buscarEnListaOrd_alu(const Lista *pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return 0;
/*
    int comp = cmp((*pl)->elem,elem);

    if(comp == 0)
    {
        memcpy(elem,(*pl)->elem,min(tamElem,(*pl)->tamElem));
        return 1;
    }

    if(comp < 0)
        return buscarEnListaOrd_alu(&(*pl)->sig,elem,tamElem,cmp);
    else
        return buscarEnListaOrd_alu(&(*pl)->ant,elem,tamElem,cmp);

        return buscarEnListaOrd_alu(comp <0? &(*pl)->sig : &(*pl)->ant,...)

*/
    while(*pl && cmp((*pl)->elem,elem) < 0)
        pl = &(*pl)->sig;

    while(*pl && cmp((*pl)->elem,elem) > 0)
        pl =&(*pl)->ant;

    if(*pl && cmp((*pl)->elem,elem) == 0)
    {
        memcpy(elem,(*pl)->elem,min(tamElem,(*pl)->tamElem));
        return 1;
    }

    return 0;
}
void vaciarLista_alu(Lista *pl)
{
    while(*pl && (*pl)->ant)
        pl = &(*pl)->ant;
    while(*pl)
    {
        NodoD *nae = *pl;

        *pl = nae->sig;

        free(nae->elem);
        free(nae);
    }
}

void crearCola_alu(Cola *pc)
{
    *pc = NULL;
}
int encolar_alu(Cola *pc, const void* elem, size_t tamElem)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return 0;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pc)
    {
        nue->sig = nue;
        *pc = nue;
        return 1;
    }

    nue->sig = (*pc)->sig;
    (*pc)->sig = nue;
    *pc = nue;
    return 1;
}
int desencolar_alu(Cola *pc, void* elem, size_t tamElem)
{
    if(!*pc)
        return 0;

    Nodo *nae = (*pc)->sig;

    memcpy(elem,nae->elem,min(tamElem,nae->tamElem));

    if(*pc == (*pc)->sig)
    {
        *pc = NULL;
        return 1;
    }

    (*pc)->sig = nae->sig;
    return 1;
}
int colaVacia_alu(const Cola *pc)
{
    return *pc == NULL;
}

int compararIndIngr_alu(const void* elem1, const void* elem2)
{
    IndIngrediente* ingr1 = (IndIngrediente*)elem1;
    IndIngrediente* ingr2 = (IndIngrediente*)elem2;

    return strcmp_alu(ingr1->codIngr,ingr2->codIngr);
}

int compararIndRec_alu(const void* elem1, const void* elem2)
{
    IndReceta* rec1 = (IndReceta*)elem1;
    IndReceta* rec2 = (IndReceta*)elem2;

    return strcmp_alu(rec1->codReceta,rec2->codReceta);
}

int strcmp_alu(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2)
    {
        if(*cad1-*cad2 != 0)
            return *cad1-*cad2;
        cad1++;
        cad2++;
    }

    return *cad1-*cad2;
}

char* strrchr_alu(char* cad, int caracter)
{
    int i = 0;

    while(*cad)
    {
        cad++;
        i++;
    }

    for( ; i > 0; i--)
    {
        if(*cad == caracter)
            return cad;
        cad--;
    }

    return NULL;
}
char* strncpy_alu(char* dest, const char* origen, size_t tamCad)
{
    for(int i = 0; i < tamCad; i++, dest++, origen++)
    {
        *dest = *origen;
 /*       dest++;
        origen++;
   */ }

    return dest;
}
