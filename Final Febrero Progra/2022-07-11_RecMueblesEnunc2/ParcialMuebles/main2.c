#include <stdio.h>
#include <stdlib.h>

/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
* DNI: 44789809
****************************************************************************************
************* Descomente el parcial que debe rendir. Si son los 2, es PI: **************
***************************************************************************************/
///#define P1
#define P2
///#define PI
/**************************************************************************************/

#ifdef P1
#define TDA_LISTA_IMPL_DINAMICA
#endif

#if defined(P2) || defined(PI)
#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
#endif

#include "../TDALista/TDALista.h"

#include "../SolucionMuebles/MueblesComun.h"
#include "../SolucionMuebles/SolucionMuebles.h"


#define MINIMO(x,y) ((x)<=(y)? (x):(y))

#include <string.h> ///despues borrar


int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos);
void desencriptarTransferencias_alu(const char* nombreArchivo);
int cargarArchTransferenciaEnLista_alu(const char* archTransferencias, Lista *pl);

void mostrarListaTrans_alu(void* elem, void* datosAccion);
void desencriptar1raSubcadena_alu(char* cad);
void desencriptar2daSubcadena_alu(char* cad);
void parseo_alu(char* cad, Transferencia *reg);
int cadAInt_alu(char *cad);
int compararTrans_alu(const void* trans1, const void* trans2);
int compararInd_alu(const void* inx1, const void* inx2);
void mostrarIndice_alu(const void *elem, void* datosImprimir, int nivel);

/// Funciones de arboles
void crearArbol_alu(Arbol* pa);
int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
booleano buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp);
booleano cargarArbolDeArchivoOrdenado_alu(Arbol* pa, size_t tamElem, const char* nomArch);
int cargarEnArbol_alu(Arbol *pa, FILE *pf, size_t tamElem, int li, int ls, Cmp cmp);
int vaciarArbol_alu(Arbol* pa);
booleano arbolVacio_alu(const Arbol *pa);
void imprimirArbol_alu(const Arbol* pa, ImprimirElemArbol imprimir, int nivel);

/// Funciones de listas
void crearLista_alu(Lista* pl);
int insertarEnListaAlInicio_alu(Lista* pl, const void* elem, size_t tamElem);
int insertarEnListaOrdCDup_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
booleano buscarEnListaOrd_alu(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeListaPrimero_alu(Lista* pl, void* elem, size_t tamElem);
booleano listaVacia_alu(const Lista* pl);

////////////////////////


int main()
{
#if defined(P1) || defined(PI)
    generarArchivos(verdadero, verdadero);
#else
    generarArchivos(falso, verdadero);
#endif

    mostrarArchivoTransferencias("Transferencias.txt");

    puts("");
    puts("Depositos antes de actualizar:");
    mostrarArchivoDepositos("Depositos.dat");

    //actualizarDepositos("Transferencias.txt", "Depositos.dat");
    actualizarDepositos_ALU("Transferencias.txt", "Depositos.dat");

    puts("");
    puts("Depositos despues de actualizar:");
    mostrarArchivoDepositos("Depositos.dat");

    return 0;
}


int actualizarDepositos_ALU(const char* nombreArchTransferencias, const char* nombreArchDepositos)
{
    /*
    desencriptarTransferencias_alu(nombreArchTransferencias);

    puts("");
    puts("Transferencias despues de desencriptar:");


    mostrarArchivoTransferencias(nombreArchTransferencias);

    FILE *pfTrans = fopen(nombreArchTransferencias,"rt");
    FILE *pfDep = fopen(nombreArchDepositos,"r+b");
    FILE *pfDepInd = fopen("Depositos.idx","rb");

    if(!pfTrans || !pfDep || !pfDepInd)
    {
        fclose(pfTrans);
        fclose(pfDep);
        fclose(pfDepInd);
        return -1;
    }

    Lista listaTrans;
    Lista listaIndice;
    crearLista(&listaTrans);
    crearLista(&listaIndice);

    char aux[256];
    Transferencia regTrans;

    while(fgets(aux,sizeof(aux),pfTrans))
    {
        parseo_alu(aux,&regTrans);
        insertarEnListaOrdCDup_alu(&listaTrans,&regTrans,sizeof(regTrans),compararTrans_alu);
    }

    Indice regInd;
    fread(&regInd,sizeof(Indice),1,pfDepInd);
    while(!feof(pfDepInd))
    {
        insertarEnListaOrdCDup_alu(&listaIndice,&regInd,sizeof(Indice),compararInd_alu);
        fread(&regInd,sizeof(Indice),1,pfDepInd);
    }

    while(!listaVacia_alu(&listaTrans))
    {
        Deposito regDep;
        eliminarDeListaPrimero_alu(&listaTrans,&regTrans,sizeof(Transferencia));
        strcpy(regInd.codProd,regTrans.codProd);
        regInd.nroDep = regTrans.depOrigen;
        buscarEnListaOrd_alu(&listaIndice,&regInd,sizeof(Indice),compararInd_alu);

        fseek(pfDep,regInd.nroReg*sizeof(Deposito),SEEK_SET);
        fread(&regDep,sizeof(Deposito),1,pfDep);

        regDep.stock-=regTrans.cantidad;
        fseek(pfDep,-(long)sizeof(Deposito),SEEK_CUR);
        fwrite(&regDep,sizeof(Deposito),1,pfDep);

        regInd.nroDep = regTrans.depDestino;
        buscarEnListaOrd_alu(&listaIndice,&regInd,sizeof(Indice),compararInd_alu);

        fseek(pfDep,regInd.nroReg*sizeof(Deposito),SEEK_SET);
        fread(&regDep,sizeof(Deposito),1,pfDep);

        regDep.stock+=regTrans.cantidad;
        fseek(pfDep,-(long)sizeof(Deposito),SEEK_CUR);
        fwrite(&regDep,sizeof(Deposito),1,pfDep);

    }


    fclose(pfTrans);
    fclose(pfDep);
    fclose(pfDepInd);
    */

    Lista listaTrans;
    crearLista_alu(&listaTrans);

    cargarArchTransferenciaEnLista_alu(nombreArchTransferencias,&listaTrans);


    Arbol arbolInd;
    crearArbol_alu(&arbolInd);

    cargarArbolDeArchivoOrdenado_alu(&arbolInd,sizeof(Indice),"Depositos.idx");

    FILE *pfDepositos = fopen(nombreArchDepositos,"r+b");
    if(!pfDepositos)
    {
        fclose(pfDepositos);
        return -55;
    }

    Transferencia regTrans;
    Deposito regDeposito;
    Indice regIndice;

    while(!listaVacia_alu(&listaTrans))
    {
        eliminarDeListaPrimero_alu(&listaTrans,&regTrans,sizeof(Transferencia));
        strcpy(regIndice.codProd,regTrans.codProd);

        regIndice.nroDep = regTrans.depOrigen;
        buscarEnArbol_alu(&arbolInd,&regIndice,sizeof(Indice),compararInd_alu);
        fseek(pfDepositos,sizeof(Deposito)*regIndice.nroReg,SEEK_SET);
        fread(&regDeposito,sizeof(Deposito),1,pfDepositos);
        regDeposito.stock-=regTrans.cantidad;
        fseek(pfDepositos,-(long)sizeof(Deposito),SEEK_CUR);
        fwrite(&regDeposito,sizeof(Deposito),1,pfDepositos);

        regIndice.nroDep = regTrans.depDestino;
        buscarEnArbol_alu(&arbolInd,&regIndice,sizeof(Indice),compararInd_alu);
        fseek(pfDepositos,sizeof(Deposito)*regIndice.nroReg,SEEK_SET);
        fread(&regDeposito,sizeof(Deposito),1,pfDepositos);
        regDeposito.stock += regTrans.cantidad;
        fseek(pfDepositos,-(long)sizeof(Deposito),SEEK_CUR);
        fwrite(&regDeposito,sizeof(Deposito),1,pfDepositos);
    }

    imprimirArbol_alu(&arbolInd,mostrarIndice_alu,0);

    vaciarArbol_alu(&arbolInd);

    fclose(pfDepositos);
    return TODO_OK;
}

void desencriptarTransferencias_alu(const char* nombreArchivo)
{
    FILE *pf = fopen(nombreArchivo,"rt");
    FILE *pfTemp = fopen("archivoTemp.temp","wt");
    if(!pf || !pfTemp)
    {
        fclose(pf);
        fclose(pfTemp);
    }

    char aux[256];

    while(fgets(aux,sizeof(aux),pf))
    {
        desencriptar1raSubcadena_alu(aux);
        fprintf(pfTemp,"%s",aux);
    }

    fclose(pfTemp);
    fclose(pf);

    remove(nombreArchivo);
    rename("archivoTemp.temp",nombreArchivo);

}

void desencriptar1raSubcadena_alu(char* cad)
{
    int cantCarac = *cad-'0';

    char* act = cad;

    char *ult = (cad+1);

    for(int i = 1; i < cantCarac; i++)
        ult++;

    act = (cad+1);

    for(int i = 1; i <=cantCarac/2; i++)
    {
        char aux = *act;

        *act = *ult;
        *ult = aux;

        act++;
        ult--;
    }


    while(*act != '\n')
        act++;
    act--;

    cantCarac = *act -'0';
    act--;

    char *ini = act;

    for(int i = 1; i <cantCarac; i++)
    {
        ini--;
    }

    for(int i = 1; i <= cantCarac/2; i++)
    {
        char aux = *act;

        *act = *ini;
        *ini = aux;

        act--;
        ini++;
    }

}

int cargarArchTransferenciaEnLista_alu(const char* archTransferencias, Lista *pl)
{

    FILE *pf = fopen(archTransferencias,"rt");

    if(!pf)
    {
        fclose(pf);
        return -33;
    }

    Transferencia regTrans;
    char cadTrans[256];

    while(fgets(cadTrans,sizeof(cadTrans),pf))
    {
        parseo_alu(cadTrans,&regTrans);
        insertarEnListaAlInicio_alu(pl,&regTrans,sizeof(Transferencia));
    }

    fclose(pf);
    return TODO_OK;
}

void parseo_alu(char* cad, Transferencia *reg)
{
    char* aux = strrchr(cad,'\n');
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;
    reg->cantidad = cadAInt_alu(aux);
    aux--;
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;
    strcpy(reg->codProd,aux);
    aux--;
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;
    reg->depDestino = cadAInt_alu(aux);
    aux--;
    *aux = '\0';

    reg->depOrigen = cadAInt_alu(cad);
}

int cadAInt_alu(char *cad)
{
    int num = 0;
    int digitos = strlen(cad);

    while(*cad)
    {
        int potencia = 1;
        for(int i = 1; i < digitos; i++)
            potencia*=10;
        num+=(*cad-'0')*potencia;
        digitos--;
        cad++;
    }

    return num;
}

int compararTrans_alu(const void* trans1, const void* trans2)
{
    Transferencia* transferencia1 = (Transferencia*)trans1;
    Transferencia* transferencia2 = (Transferencia*)trans2;

    if((transferencia1->depOrigen-transferencia2->depOrigen) == 0)
        return strcmp(transferencia1->codProd,transferencia2->codProd);
    return transferencia1->depOrigen-transferencia2->depOrigen;
}

int compararInd_alu(const void* inx1, const void* inx2)
{
    Indice *ind1 = (Indice*)inx1;
    Indice *ind2 = (Indice*)inx2;

    if(ind1->nroDep-ind2->nroDep == 0)
        return strcmp(ind1->codProd,ind2->codProd);
    else
        return ind1->nroDep-ind2->nroDep;
}

void mostrarIndice_alu(const void *elem, void* datosImprimir, int nivel)
{
    Indice* indx = (Indice*)elem;

    for(int i = 0; i < nivel; i++)
        printf("        ");

    printf("%d|%s\n",indx->nroDep,indx->codProd);
}

///Funciones lista simple
/*
void crearLista_alu(Lista* pl)
{
    (*pl) = NULL;
}

int insertarEnListaOrdCDup_alu(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return -4;
    }

    nue->tamElem = tamElem;
    memcpy(nue->elem,elem,tamElem);

    while(*pl && cmp(elem,(*pl)->elem) > 0)
        pl = &(*pl)->sig;

    nue->sig = *pl;
    (*pl) = nue;

    return TODO_OK;
}


booleano eliminarDeListaPrimero_alu(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return falso;

    Nodo *nae = (*pl);

    memcpy(elem,nae->elem,MINIMO(nae->tamElem,tamElem));

    (*pl) = nae->sig;

    free(nae->elem);
    free(nae);

    return TODO_OK;
}

booleano listaVacia_alu(const Lista* pl)
{
    return (*pl) == NULL;
}

booleano buscarEnListaOrd_alu(const Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return falso;

    while(*pl)
    {
        if(cmp((*pl)->elem,elem) < 0)
            pl = &(*pl)->sig;
        else if(cmp((*pl)->elem,elem) == 0)
        {
            memcpy(elem,(*pl)->elem,MINIMO((*pl)->tamElem,tamElem));
            return TODO_OK;
        }
        else
            return falso;
    }

    return falso;
}


void mostrarListaTrans_alu(void* elem, void* datosAccion)
{
    Transferencia* elemento = (Transferencia*)elem;

    printf("DepOrg = %d DepDes = %d codProd = %s cantidad= %d\n",elemento->depOrigen,elemento->depDestino,
           elemento->codProd,elemento->cantidad);
}
*/

/// Funciones de Lista

void crearLista_alu(Lista* pl)
{
    *pl = NULL;
}

int insertarEnListaAlInicio_alu(Lista* pl, const void* elem, size_t tamElem)
{
    NodoD* nue = malloc(sizeof(NodoD));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return -4;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->ant = NULL;
        nue->sig = NULL;

        *pl = nue;

        return TODO_OK;
    }

    while((*pl)->ant)
        pl = &(*pl)->ant;


    nue->sig = *pl;
    (*pl)->ant = nue;
    nue->ant = NULL;

    *pl = nue;

    return TODO_OK;
}

booleano eliminarDeListaPrimero_alu(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return falso;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    NodoD* nae = *pl;
    (*pl) = (*pl)->sig;

    if(*pl)
        nae->sig->ant = NULL;

    memcpy(elem,nae->elem,MINIMO(nae->tamElem,tamElem));

    free(nae->elem);
    free(nae);

    return TODO_OK;
}

booleano listaVacia_alu(const Lista* pl)
{
    return *pl == NULL;
}

/// Funciones de Arbol

void crearArbol_alu(Arbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol_alu(Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    NodoA* nue = malloc(sizeof(NodoA));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return -455;
    }

    memcpy(nue->elem,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pa)
    {
        nue->hDer = NULL;
        nue->hIzq = NULL;

        *pa = nue;

        return TODO_OK;
    }

    int comp = cmp((*pa)->elem,dato);

    if(comp < 0)
        return insertarEnArbol_alu(&(*pa)->hDer,dato,tamElem,cmp);
    else
        return insertarEnArbol_alu(&(*pa)->hIzq,dato,tamElem,cmp);

}

booleano buscarEnArbol_alu(const Arbol* pa, void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return falso;

    int comp = cmp((*pa)->elem,dato);

    if(comp == 0)
    {
        memcpy(dato,(*pa)->elem,MINIMO((*pa)->tamElem,tamElem));
        return verdadero;
    }

    if(comp < 0)
        return buscarEnArbol_alu(&(*pa)->hDer,dato,tamElem,cmp);
    else
        return buscarEnArbol_alu(&(*pa)->hIzq,dato,tamElem,cmp);
}

booleano cargarArbolDeArchivoOrdenado_alu(Arbol* pa, size_t tamElem, const char* nomArch)
{
    FILE *pf = fopen(nomArch,"rb");
    if(!pf)
    {
        fclose(pf);
        return -5;
    }

    fseek(pf,0L,SEEK_END);
    int cBytes = ftell(pf);
    int cReg = cBytes/tamElem;

    fseek(pf,0L,SEEK_SET);

    cargarEnArbol_alu(pa,pf,tamElem,0,cReg-1,compararInd_alu);

    fclose(pf);
    return TODO_OK;
}

int cargarEnArbol_alu(Arbol *pa, FILE *pf, size_t tamElem, int li, int ls, Cmp cmp)
{
    if(li > ls)
        return 0;

    int mitad = (li+ls)/2;
    fseek(pf,(long)mitad*tamElem,SEEK_SET);

    void *reg = malloc(tamElem);
    if(!reg)
    {
        free(reg);
        return -54;
    }

    fread(reg,tamElem,1,pf);
    insertarEnArbol_alu(pa,reg,tamElem,cmp);
    cargarEnArbol_alu(pa,pf,tamElem,li,mitad-1,cmp);
    cargarEnArbol_alu(pa,pf,tamElem,mitad+1,ls,cmp);

    return TODO_OK;
}

int vaciarArbol_alu(Arbol* pa)
{
    if(!*pa)
        return 0;

    int cne = 0;
    cne+=vaciarArbol(&(*pa)->hDer);
    cne+=vaciarArbol(&(*pa)->hIzq);
    free((*pa)->elem);
    free((*pa));
    *pa = NULL;
    return cne+1;
}

booleano arbolVacio_alu(const Arbol *pa)
{
    return *pa == NULL;
}

void imprimirArbol_alu(const Arbol* pa, ImprimirElemArbol imprimir, int nivel)
{
    if(!*pa)
        return;

    imprimirArbol_alu(&(*pa)->hDer,imprimir,nivel+1);
    imprimir((*pa)->elem,imprimirIndice,nivel);
    imprimirArbol_alu(&(*pa)->hIzq,imprimir,nivel+1);
}
