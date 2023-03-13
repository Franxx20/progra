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
#define P1
//#define P2
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

bool leerLina_ALU(char* linea, Pedido* ped);
void cambioExtDeArch_ALU(const char* nomArch,char* nomArchInd);
int cmpIngInd_ALU(const void* e1, const void* e2);
int cmpRecInd_ALU(const void* e1, const void* e2);
int cmpPedRec_ALU(const void* e1, const void* e2);
void indiceALista_ALU(const char* archivo,Lista* pl,void* elem,unsigned tamElem,Cmp cmp);

///Primitivas Cola ///
void crearCola_ALU(Cola* pc);
bool encolar_ALU(Cola* pc, void* elem, unsigned tamElem);
bool desencolar_ALU(Cola* pc, void* elem, unsigned tamElem);

///Primitivas Lista///
void crearLista_ALU(Lista* pl);
bool insertarEnListaOrd_ALU(Lista* pl,const void* elem, unsigned tamElem, Cmp cmp, Actualizar actualizar);
bool buscarEnListaOrd_ALU(const Lista* pl, void* elem, unsigned tamElem, Cmp cmp);


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

	getchar();

	return 0;
}



///Procesa los pedidos del archivo Pedidos.txt, actualizando el archivo Ingredientes.dat, para que �ste refleje la cantidad que queda en stock luego de despachar los pedidos.
int satisfacerPedidos_ALU(const char* nombreArchPedidos, const char* nombreArchRecetas, const char* nombreArchIngredientes)
{
    char nomArchRecInd[strlen(nombreArchRecetas)+1];
    char nomArchIngInd[strlen(nombreArchIngredientes)+1];

    cambioExtDeArch_ALU(nombreArchRecetas,nomArchRecInd);
    cambioExtDeArch_ALU(nombreArchIngredientes,nomArchIngInd);

    FILE* archPed=fopen(nombreArchPedidos,"rt");

    if(archPed==NULL)
        return ERR_ARCHIVO;

    char linea[50];
    Pedido pedido;
    Lista listaPedidos;
    crearLista(&listaPedidos);
    fgets(linea,50,archPed);
    while(!feof(archPed))
    {
        bool ret = leerLina_ALU(linea,&pedido);
        if(ret == true)
            insertarEnListaOrd(&listaPedidos,&pedido,sizeof(Pedido),cmpPedRec_ALU,NULL);
        fgets(linea,50,archPed);
    }
    fclose(archPed);

    Cola colaRec;
    crearCola(&colaRec);
    Receta recCola;

    FILE* archRec = fopen(nombreArchRecetas,"rb");
    fread(&recCola,sizeof(Receta),1,archRec);
    while(!feof(archRec))
    {
        encolar_ALU(&colaRec,&recCola,sizeof(Receta));
        fread(&recCola,sizeof(Receta),1,archRec);
    }
    fclose(archRec);
    Lista listaRecIdx;
    Lista listaIngIdx;
    crearLista_ALU(&listaIngIdx);
    crearLista_ALU(&listaRecIdx);
    IndIngrediente indiceIng;
    IndReceta indiceRec;


    FILE* archRecInd = fopen(nomArchRecInd,"rb");
    FILE* archIngInd = fopen(nomArchIngInd,"rb");

    if(!archRecInd||!archIngInd)
        return ERR_ARCHIVO;
    fread(&indiceRec,sizeof(IndReceta),1,archRecInd);
    while(!feof(archRecInd))
    {
        insertarEnListaOrd(&listaRecIdx,&indiceRec,sizeof(IndReceta),cmpRecInd_ALU,NULL);
        fread(&indiceRec,sizeof(IndReceta),1,archRecInd);
    }
    fclose(archRecInd);

    fread(&indiceIng,sizeof(IndIngrediente),1,archIngInd);
    while(!feof(archIngInd))
    {
        insertarEnListaOrd(&listaIngIdx,&indiceIng,sizeof(IndIngrediente),cmpIngInd_ALU,NULL);
        fread(&indiceIng,sizeof(IndIngrediente),1,archIngInd);
    }
    recorrerLista(&listaIngIdx,mostrarIngrediente,&indiceIng);

    Receta recActual;
    IndIngrediente indIngre;
    Ingrediente ingActual;
    Pedido pedActual;

    FILE* archIng = fopen(nombreArchIngredientes,"wb");
    fseek(archIng,0L,SEEK_SET);
    while(!colaVacia(&colaRec))
    {

        desencolar(&colaRec,&recActual,sizeof(Receta));
        strcpy(indIngre.codIngr,recActual.codIngr);
        strcpy(pedActual.codReceta,recActual.codReceta);

        buscarEnListaOrd(&listaIngIdx,&indiceIng,sizeof(IndIngrediente),cmpIngInd_ALU);
        buscarEnListaOrd(&listaPedidos,&pedActual,sizeof(Pedido),cmpPedRec_ALU);

        fseek(archIng,indIngre.nroReg*sizeof(Ingrediente),SEEK_SET);
        fread(&ingActual,sizeof(Ingrediente),1,archIng);
        ingActual.stock-=recActual.cantidad*pedActual.cantidad;
        fseek(archIng,indIngre.nroReg*sizeof(Ingrediente),SEEK_SET);
        fwrite(&ingActual,sizeof(Ingrediente),1,archIng);
    }

    fclose(archIng);






	return TODO_OK;
}

void cambioExtDeArch_ALU(const char* nomArch,char* nomArchInd)
{
    strcpy(nomArchInd,nomArch);
    nomArchInd=strrchr(nomArchInd,'.');
    strcpy(nomArchInd,".idx");
}

bool leerLina_ALU(char* linea, Pedido* ped)
{
    char* c = strchr(linea,'\n');

    if(!c)
        return false;
    *c='\0';


    c=strrchr(linea,'\t');
    sscanf(c+1,"%d",&ped->cantidad);
    *c='\0';


    c=strrchr(linea,'\t');
    strcpy(ped->codReceta,c+1);
    *c='\0';

    sscanf(linea,"%d",&ped->nroPedido);
    return true;

}

int cmpRecInd_ALU(const void* e1, const void* e2)
{
    IndReceta* ind1 = (IndReceta*) e1;
    IndReceta* ind2 = (IndReceta*) e2;

    return strcmpi(ind1->codReceta,ind2->codReceta);
}

int cmpPedRec_ALU(const void* e1, const void* e2)
{
    Pedido* ped1 = (Pedido*) e1;
    Pedido* ped2 = (Pedido*) e2;

    return strcmp(ped1->codReceta,ped2->codReceta);
}

int cmpIngInd_ALU(const void* e1, const void* e2)
{
    IndIngrediente* ind1 = (IndIngrediente*) e1;
    IndIngrediente* ind2 = (IndIngrediente*) e2;

    return strcmp(ind1->codIngr,ind2->codIngr);
}
/*
void indiceALista_ALU(const char* archivo,Lista* pl,void* elem,unsigned tamElem,Cmp cmp)
{
    FILE* arch = fopen(archivo,"rb");
    if(!arch)
        return;
    fread(elem,tamElem,1,arch);
    while(!feof(arch))
    {
        insertarEnListaOrd_ALU(pl,elemento,tamElem,cmp,NULL);
        fread(&elem,tamElem,1,arch);
    }
}*/

/// Primitivas Cola ///

void crearCola_ALU(Cola* pc)
{
    pc->fondo = NULL;
    pc->frente = NULL;
}

bool encolar_ALU(Cola* pc, void* elem, unsigned tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);
    if(!nue||!elemNodo)
    {
        free(nue);
        free(elemNodo);
        return false;
    }
    memcpy(elemNodo,elem,tamElem);
    nue->elem = elemNodo;
    nue->tamElem = tamElem;
    nue->sig = NULL;
    if(!pc->frente)
        pc->frente=nue;
    else
        pc->fondo->sig = nue;
    pc->fondo = nue;
    return true;
}

bool desencolar_ALU(Cola* pc, void* elem, unsigned tamElem)
{
    Nodo* nae = pc->frente;
    if(!nae)
        return false;
    memcpy(elem,nae->elem,min(tamElem,nae->tamElem));
    free(nae->elem);
    free(nae);
    pc->frente = nae->sig;
    if(!nae->sig)
        pc->fondo = NULL;
    return true;
}

/// Primitivas de Lista ///
void crearLista_ALU(Lista* pl)
{
    *pl=NULL;
}

bool insertarEnListaOrd_ALU(Lista* pl,const void* elem, unsigned tamElem, Cmp cmp, Actualizar actualizar)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);
    if(!nue||!elemNodo)
    {
        free(nue);
        return false;
    }
    memcpy(elemNodo,elem,tamElem);
    nue->elem = elemNodo;
    nue->tamElem= tamElem;
    nue->sig = NULL;

    while(*pl&&cmp((*pl)->elem,elem)<0)
        pl= &(*pl)->sig;

    nue->sig = *pl;
    *pl = nue;
    return true;


}

bool buscarEnListaOrd_ALU(const Lista* pl, void* elem, unsigned tamElem, Cmp cmp)
{
    if(!*pl)
        return false;

    while(*pl&&cmp(&(*pl)->elem,elem)<0)
        pl= &(*pl)->sig;

    if(cmp(&(*pl)->elem,elem)!= 0)
        return false;

    memcpy(elem,&(*pl)->elem,min(tamElem,&(*pl)->tamElem));

    return true;

}
