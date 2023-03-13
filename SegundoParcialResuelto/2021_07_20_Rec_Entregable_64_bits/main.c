/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: Aragón, Rodrigo Ezequiel
*
* DNI: 43.509.985
*
****************************************************************************************
********** Descomente el parcial que debe rendir. Si es el integrador, es P2: **********
***************************************************************************************/
#define P1
//#define P2
/***************************************************************************************
********************* Descomente la solución que quiere probar: ************************
***************************************************************************************/
//#define SOLUCION_DOC
#define SOLUCION_ALU
/**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

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


#define MIN(x,y) ((x) <= (y)? (x) : (y))
#define ERR_MEM -6

#include <memory.h>

int parseoPedidos_alu(char* cad, Pedido* reg);
int strlenHastaTab_alu(char* cad);
char* strcpyHastaTab_alu(char* dest, const char* origen);
int cadAInt_alu(char* cad);
int compararIndRec_alu(const void* dato1, const void* dato2);
int compararIndIng_alu(const void* dato1, const void* dato2);
int strcmp_alu(const char* cad1, const char* cad2);
char* strcpy_alu(char* dest, const char* origen);

///Declaracion de Funciones de Lista
void crearLista_alu(Lista* pl);
int insertarEnListaOrdCDup_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
booleano buscarEnListaOrd_alu(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);
void vaciarLista_alu(Lista* pl);

///Declaracion de Funciones de Cola
void crearCola_alu(Cola* pc);
bool encolar_alu(Cola* pc, const void* elem, size_t tamElem);
bool desencolar_alu(Cola* pc, void* elem, size_t tamElem);
bool colaVacia_alu(const Cola* pc);

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
    FILE *pfPedidos = fopen(nombreArchPedidos,"rt");
    FILE *pfRecetas = fopen(nombreArchRecetas,"rb");
    FILE *pfIngredientes = fopen(nombreArchIngredientes,"r+b");
    FILE *pfIngIdx = fopen("Ingredientes.idx","rb");
    FILE *pfRecIdx = fopen("Recetas.idx","rb");

    if(!pfIngIdx || !pfRecIdx ||!pfPedidos || !pfRecetas || !pfIngredientes)
    {
        fclose(pfPedidos);
        fclose(pfRecetas);
        fclose(pfIngredientes);
        fclose(pfIngIdx);
        fclose(pfRecIdx);
        return ERR_ARCHIVO;
    }

    Lista listaIdxIng;
    Lista listaIdxRec;

    crearLista_alu(&listaIdxIng);
    crearLista_alu(&listaIdxRec);

    IndReceta regIndRec;
    IndIngrediente regIndIng;

    fread(&regIndRec,sizeof(IndReceta),1,pfRecIdx);
    while(!feof(pfRecIdx))
    {
        insertarEnListaOrdCDup_alu(&listaIdxRec,&regIndRec,sizeof(IndReceta),compararIndRec_alu);
        fread(&regIndRec,sizeof(IndReceta),1,pfRecIdx);
    }

    fread(&regIndIng,sizeof(IndIngrediente),1,pfIngIdx);
    while(!feof(pfIngIdx))
    {
        insertarEnListaOrdCDup_alu(&listaIdxIng,&regIndIng,sizeof(IndIngrediente),compararIndRec_alu);
        fread(&regIndIng,sizeof(IndIngrediente),1,pfIngIdx);
    }

    char regPedCad[50];
    while(fgets(regPedCad,sizeof(regPedCad),pfPedidos))
    {
        Pedido regPed;
        parseoPedidos_alu(regPedCad,&regPed);

        Receta regReceta;

        Cola colaIngDeRec;
        crearCola_alu(&colaIngDeRec);

        strcpy_alu(regIndRec.codReceta,regPed.codReceta);

        buscarEnListaOrd_alu(&listaIdxRec,&regIndRec,sizeof(IndReceta),compararIndRec_alu);

        fseek(pfRecetas,regIndRec.nroReg*sizeof(Receta),SEEK_SET);
        fread(&regReceta,sizeof(Receta),1,pfRecetas);
        while(!feof(pfRecetas) && strcmp_alu(regReceta.codReceta,regPed.codReceta) == 0)
        {
            encolar_alu(&colaIngDeRec,&regReceta,sizeof(Receta));
            fread(&regReceta,sizeof(Receta),1,pfRecetas);
        }

        while(!colaVacia_alu(&colaIngDeRec))
        {
            Ingrediente regIng;

            desencolar_alu(&colaIngDeRec,&regReceta,sizeof(Receta));
            strcpy_alu(regIndIng.codIngr,regReceta.codIngr);
            buscarEnListaOrd_alu(&listaIdxIng,&regIndIng,sizeof(IndIngrediente),compararIndIng_alu);
            fseek(pfIngredientes,regIndIng.nroReg*sizeof(IndIngrediente),SEEK_SET);
            fread(&regIng,sizeof(Ingrediente),1,pfIngredientes);
            regIng.stock -= regPed.cantidad*regReceta.cantidad;
            fseek(pfIngredientes,-(long)sizeof(Ingrediente),SEEK_CUR);
            fwrite(&regIng,sizeof(Ingrediente),1,pfIngredientes);
        }

    }

    vaciarLista_alu(&listaIdxIng);
    vaciarLista_alu(&listaIdxRec);

    fclose(pfPedidos);
    fclose(pfRecetas);
    fclose(pfIngredientes);
    fclose(pfIngIdx);
    fclose(pfRecIdx);

    return TODO_OK;
}

int compararIndRec_alu(const void* dato1, const void* dato2)
{
    IndReceta* rec1 = (IndReceta*)dato1;
    IndReceta* rec2 = (IndReceta*)dato2;

    return strcmp_alu(rec1->codReceta,rec2->codReceta);
}

int compararIndIng_alu(const void* dato1, const void* dato2)
{
    IndIngrediente* ing1 = (IndIngrediente*)dato1;
    IndIngrediente* ing2 = (IndIngrediente*)dato2;

    return strcmp_alu(ing1->codIngr,ing2->codIngr);
}

char* strcpy_alu(char* dest, const char* origen)
{
    while(*origen)
    {
        *dest = *origen;
        dest++;
        origen++;
    }

    *dest = '\0';

    return dest;
}

int strcmp_alu(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2)
    {
        if(*cad1 != *cad2)
            return *cad1-*cad2;
        cad1++;
        cad2++;
    }

    if(*cad1)
        return *cad1-*cad2;

    if(*cad2)
        return *cad1-*cad2;

    return 0;
}

int parseoPedidos_alu(char* cad, Pedido* reg)
{
    char *aux = cad;

    reg->nroPedido = cadAInt_alu(aux);

    aux+=2;

    strcpyHastaTab_alu(reg->codReceta,aux);

    aux+=strlenHastaTab_alu(aux) + 1;

    reg->cantidad = cadAInt_alu(aux);

    return TODO_OK;
}

int cadAInt_alu(char* cad)
{
    int num = 0;
    int digitos = strlenHastaTab_alu(cad);

    while(*cad && *cad != '\t' && *cad != '\n')
    {
        int potencia = 1;
        for(int i = 1; i < digitos; i++)
            potencia*=10;
        num+= (*cad -'0') *potencia;

        cad++;
        digitos--;
    }

    return num;
}

int strlenHastaTab_alu(char* cad)
{
    int cont = 0;
    while(*cad && *cad != '\t' && *cad != '\n')
    {
        cont++;
        cad++;
    }

    return cont;
}

char* strcpyHastaTab_alu(char* dest, const char* origen)
{
    while(*origen && *origen != '\t')
    {
        *dest = *origen;
        dest++;
        origen++;
    }

    *dest = '\0';

    return dest;
}

///Funciones de Lista

void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}

int insertarEnListaOrdCDup_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    Nodo* nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return ERR_MEM;
    }
    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    while(*pl)
    {
        int comp = cmp(elem,(*pl)->elem);

        if(comp <= 0)
        {
            nue->sig = (*pl);
            (*pl) = nue;
            return TODO_OK;
        }
        pl = &(*pl)->sig;
    }

    if(!*pl)
    {
        nue->sig = NULL;
        *pl = nue;
    }

    return TODO_OK;
}

booleano buscarEnListaOrd_alu(const Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(*pl == NULL)
        return falso;

    while(*pl)
    {
        int comp = cmp(elem,(*pl)->elem);

        if(comp == 0)
        {
            memcpy(elem,(*pl)->elem,MIN(tamElem,(*pl)->tamElem));
            return verdadero;
        }
        if(comp < 0)
            return falso;
        pl = &(*pl)->sig;
    }

    return falso;
}

void vaciarLista_alu(Lista* pl)
{
    while(*pl)
    {
        Nodo* nae = *pl;

        *pl = nae->sig;

        free(nae->elem);
        free(nae);
    }
}

///Funciones de Cola

void crearCola_alu(Cola* pc)
{
    pc->fondo = NULL;
    pc->frente = NULL;
}

bool encolar_alu(Cola* pc, const void* elem, size_t tamElem)
{
    Nodo* nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return ERR_MEM;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!pc->frente)
    {
        nue->sig = NULL;
        pc->fondo = nue;
        pc->frente = nue;

        return TODO_OK;
    }

    nue->sig = pc->frente;
    pc->frente = nue;

    return TODO_OK;
}

bool desencolar_alu(Cola* pc, void* elem, size_t tamElem)
{
    if(!pc->frente)
        return false;

    Nodo* nae = pc->frente;
    pc->frente = nae->sig;

    memcpy(elem,nae->elem,MIN(nae->tamElem,tamElem));

    if(!pc->frente)
        pc->fondo = NULL;

    return TODO_OK;
}

bool colaVacia_alu(const Cola* pc)
{
    return pc->frente==NULL;
}
