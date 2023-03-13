/*****************************************************************************************************************
** Apellido/s, Nombre/s: Garcete, Franco Javier                                     													**
**
** DNI: 42875393                                                       													**
**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**
******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

/*****************************************************************************************************************
** Descomente SOLUCION_ALU y comente SOLUCION_DOC, para probar su código: 										**
**																												*/
//#define SOLUCION_DOC
#define SOLUCION_ALU
/*
*****************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include<string.h>


#include "../Cadena/Cadena.h"
#include "../Fecha/Fecha.h"
#include "../Solucion2doParcialCentroTele/Solucion2doParcialCentroTele.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define PATH_CLI 1
#define PATH_PAGOS 2
#define PATH_LISTADO 3

#define MIN(a,b) ((a)<(b)?(a):(b))

// FUNCIONES DE LISTA
NodoD * crearNodoD(const void * dato, unsigned tamDato);
void crearLista_ALU(Lista* l);
void vaciarLista_ALU(Lista *l);

booleano listaLlena_ALU(const Lista *l, size_t tamElem);
booleano listaVacia_ALU(const Lista *l);

int insertarEnListaAlFinal_ALU(Lista* l, const void* elem, size_t tamElem);
booleano eliminarDeListaPrimero_ALU(Lista* l, void* elem, size_t tamElem);
void ordenarLista_ALU(Lista* pl, Cmp cmp, int sentidoOrdenamiento);


typedef struct
{
    int nroCliente;
    int cantFactImpagasFueraTerm;
    char nombre[201];
} Deudores;

// FUNCIONES PUNTERO
void mostrarPagos_ALU(void *dato, void * datosAccion);
void mostrarIndice_ALU(void *dato, void * datosAccion);

int compararNumeroCliente_ALU(const void * d1, const void * d2);
int compararPagos_ALU(const void *d1, const void *d2);

int compararDeudores_ALU(const void *due1, const void * deu2);

void imprimirArbolIndice_ALU(const void * dato, void * dImprimir, int nivel);

// FUNCIONES GENERALES
void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado);

int cargarEnListaDePagosDeArchivo_ALU(const char * nombreArch, Lista *l);

// FUNCIONES DE ARBOl
booleano cargarArbolDeArchivoOrdenado_ALU(Arbol* pa, size_t tamElem, const char* nomArch);



int main(int argc, char* argv[])
{
    generarArchivoClientes(argv[PATH_CLI]);
    generarArchivoPagos(argv[PATH_PAGOS]);

    mostrarArchivoClientes(argv[PATH_CLI]);

    char nombreIdx[201];
    reemplazarSubcad(argv[PATH_CLI], ".dat", ".idx", nombreIdx, 201);
    mostrarArchivoClientesIdx(nombreIdx);

    mostrarArchivoPagos(argv[PATH_PAGOS]);

#ifdef SOLUCION_DOC
    procesarPagos(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#else
    procesarPagos_ALU(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#endif

    getchar();

    return 0;
}


void procesarPagos_ALU(const char* pathCli, const char* pathPagos, const char* pathListado)
{
    ///Inserte el código acá ...

    // CARGAMOS LA LISTA DE PAGOS
    Lista  listaPagos;
    crearLista(&listaPagos);
    puts("Lista de pagos");
    int res = cargarEnListaDePagosDeArchivo_ALU(pathPagos,&listaPagos);
    if ( res != TODO_OK)
    {
        return ;
    }
    recorrerLista(&listaPagos,mostrarPagos_ALU,NULL);
    puts("LIsta de pagos Ordenada");
    ordenarLista(&listaPagos,compararPagos_ALU,ASC);
    recorrerLista(&listaPagos,mostrarPagos_ALU,NULL);
    // CARGAMOS EL INDICE DE ARBOL
    Arbol arbolIndiceClientes;
    crearArbol(&arbolIndiceClientes);

    puts("Indice de Clientes");
    res =cargarArbolDeArchivoOrdenado(&arbolIndiceClientes,sizeof(IndCli),"clientes.idx");
//
//    recorrerArbolEnOrden(&arbolIndiceClientes,mostrarIndice_ALU,NULL);
//
//    imprimirArbol(&arbolIndiceClientes,imprimirArbolIndice_ALU,NULL);

    FILE * ftxt = fopen(pathListado,"wt");
    FILE * fp = fopen(pathCli, "rb");
    FILE * fd = fopen("Deudores.dat","wb");
    if(!ftxt|| !fp || !fd)
    {
        fprintf(stderr, "ERROR AL ABRIR LOS ARCHIVOS");
        return ;
    }
    IndCli ind;
    Cliente cli;
    Pago pago;
    FacturasImpagasFueraTerm fact;
    Deudores d;

    int cantImpagos=0;
    const Fecha fechaImpaga= {1,1,1900};

    // LEE EL PRIMERO PAGO
    eliminarDeListaPrimero(&listaPagos,&pago,sizeof(Pago));
    ind.nroCliente = pago.nroCliente;// INDICE IGUAL AL PRIMERO PAGO

    if(cmpFechas(&pago.fechaPago,&fechaImpaga)==0 || cmpFechas(&pago.fechaVencimiento,&pago.fechaPago)<0)
        cantImpagos++;



    while(!listaVacia_ALU(&listaPagos))
    {
        // LEE EL SIGUIENTE PAGO
        eliminarDeListaPrimero(&listaPagos,&pago,sizeof(Pago));
        // SI EL NUMERO DE CLIENTE DEL PRIMER PAGO QUE SE LEYO NO ES EL MISMO QUE EL DEL SIGUIENTE PAGO
        // ENTONCES TENGO QUE GRABAR EN EL ARCHIVO DE TEXTO EL NRO CLIENTE, NOMBRE Y CANT DE FACTURAS EN MORA;
        int comp = ind.nroCliente - pago.nroCliente;
        if(comp != 0)
        {
            if(buscarEnArbol(&arbolIndiceClientes,&ind,sizeof(IndCli),compararNumeroCliente_ALU))
            {
                fseek(fp,ind.nroReg*sizeof(Cliente),SEEK_SET);
                fread(&cli,sizeof(Cliente),1,fp);


                fact.nroCliente = ind.nroCliente;
                fact.cantFactImpagasFueraTerm = cantImpagos;

                fseek(fp,(long int)(-1L * sizeof(Cliente)),SEEK_CUR);

                d.cantFactImpagasFueraTerm =cantImpagos;
                strcpy(d.nombre,cli.nombre);
                d.nroCliente =fact.nroCliente;

                fwrite(&d,sizeof(Deudores),1,fd);
                cantImpagos =0;
                if(cmpFechas(&pago.fechaPago,&fechaImpaga)==0 || cmpFechas(&pago.fechaVencimiento,&pago.fechaPago)<0)
                    cantImpagos++;
            }
        }
        else
        {
            // SI EL SIGUIENTE Y EL INDICE SON IGUALES SE PRODUCE UNA ACUMULACION Y SE PROCEDE A INCREMENTAR EL CONTADOR
            if(cmpFechas(&pago.fechaPago,&fechaImpaga)==0 || cmpFechas(&pago.fechaVencimiento,&pago.fechaPago)<0)
                cantImpagos++;
        }
        ind.nroCliente = pago.nroCliente;

    }
//
//    int comp = ind.nroCliente - pago.nroCliente;
//    if(comp != 0)
//    {
//        if(buscarEnArbol(&arbolIndiceClientes,&ind,sizeof(IndCli),compararNumeroCliente_ALU))
//        {
//            fseek(fp,ind.nroReg*sizeof(Cliente),SEEK_SET);
//            fread(&cli,sizeof(Cliente),1,fp);
//            if(cmpFechas(&pago.fechaPago,&fechaImpaga)==0 || cmpFechas(&pago.fechaVencimiento,&pago.fechaPago)<0)
//                cantImpagos++;
//
//            fact.nroCliente = ind.nroCliente;
//            fact.cantFactImpagasFueraTerm= cantImpagos;
//
//            fseek(fp,(long int)(-1L * sizeof(Cliente)),SEEK_CUR);
//
//
//            fprintf(ftxt,"%0d\t%-16s\t%0d\n",fact.nroCliente,cli.nombre,fact.cantFactImpagasFueraTerm);
//
//        }
//    }

    fclose(ftxt);
    fclose(fp);
    fclose(fd);

    vaciarLista(&listaPagos);




    vaciarArbol(&arbolIndiceClientes);

    FILE * txt2 =fopen("listado-deudores.txt", "wt");
    FILE * fd2 = fopen("Deudores.dat","rb" );
    FILE * fd3 = fopen("Deudores2.dat","wb" );

    if(!txt2 || !fd2 || !fd3)
    {
        return ;
    }
    Lista lDeudores;
    crearLista_ALU(&lDeudores);
    Deudores d2;
    while(!feof(fd2) && !listaLlena_ALU(&lDeudores,sizeof(Deudores)))
    {
        fread(&d2,sizeof(Deudores),1,fd2);
        insertarEnListaAlFinal(&lDeudores,&d2,sizeof(Deudores));
    }
    ordenarLista(&lDeudores,compararDeudores_ALU,DESC);
// TERMINAMOS DE ORDENAR LOS ARCHIVOS

    char linea[256];
    strcpy(linea,"Nro Cliente     Nombre            Facturas en mora\n" );
    fputs(linea,txt2);

    fprintf(txt2,"%d\t%-16s\t%d\n",fact.nroCliente,cli.nombre,fact.cantFactImpagasFueraTerm);

    fprintf(stdout,"Nro Cliente     Nombre            Facturas en mora\n" );
    while(!listaVacia_ALU(&lDeudores) )
    {
        eliminarDeListaPrimero(&lDeudores,&d2,sizeof(Deudores));
        fprintf(stdout,"%0d\t%-16s\t%0d\n",d2.nroCliente,d2.nombre,d2.cantFactImpagasFueraTerm);
        fwrite(&d2,sizeof(Deudores),1,fd3);
        fprintf(ftxt,"%0d\t%-16s\t%0d\n",d2.nroCliente,d2.nombre,d2.cantFactImpagasFueraTerm);
    }

    vaciarLista_ALU(&lDeudores);
    fclose(txt2);
    fclose(fd2);
    fclose(fd3);
}

int cargarEnListaDePagosDeArchivo_ALU(const char * nombreArch, Lista *l)
{
    FILE * fp = fopen(nombreArch, "rb");
    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE PAGOS EN LECTURA");
        return ERR_ARCHIVO;

    }
    Pago pago;

    while(!listaLlena_ALU(l,sizeof(Pago)) && !feof(fp))
    {
        fread(&pago,sizeof(Pago),1,fp);
        insertarEnListaAlFinal(l,&pago,sizeof(Pago));
    }

    fclose(fp);

    return TODO_OK;
}

// FUNCIONES DE LISTA
NodoD * crearNodoD(const void * elem, unsigned tamDato)
{
    NodoD * nue =(NodoD*) malloc(sizeof(NodoD));
    if(!nue || !(nue->elem = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->elem,elem,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}
void crearLista_ALU(Lista* l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista *l)
{
    NodoD * act;
    NodoD * nae;

    if(!*l)
        return ;

    act = *l;

    while(act)
        act =act->ant;

    while(act)
    {
        nae = act;
        act = nae->sig;
        free(nae->elem);
        free(nae);

    }
    *l = NULL;

}

booleano listaLlena_ALU(const Lista *l, size_t tamElem)
{
    NodoD * nue =(NodoD*) malloc(sizeof(NodoD));
    void * dato = malloc(tamElem);
    free(nue);
    free(dato);

    return !nue || !dato;
}
booleano listaVacia_ALU(const Lista *l)
{

    return *l == NULL;
}


int insertarEnListaAlFinal_ALU(Lista* l, const void* elem, size_t tamElem)
{
    NodoD * nue = crearNodoD(elem,tamElem);
    if(!nue)
        return falso;

    NodoD * act = *l;
    while(act->sig)
        act =act->sig;

    nue->ant = act;
    if(act)
        act->sig = nue;

    *l =nue;

    return verdadero;
}

booleano eliminarDeListaPrimero_ALU(Lista* l, void* elem, size_t tamElem)
{
    NodoD * act;
    NodoD * nae;
    if(!*l)
        return falso;

    act =*l;
    if(act)
        while(act->ant)
            act =act->ant;

    act =*l;
    nae = act;
    act = nae->sig;

    if(nae == *l)
        *l = nae->sig;

    if(act)
        act->ant = NULL;

    return verdadero;

}
void ordenarLista_ALU(Lista* pl, Cmp cmp, int sentidoOrdenamiento)
{
    if(!*l)
        return;
    NodoD * act;
    int ordenado;
    act =*;
    do
    {
        ordenado =0;
        while (act->sig)
        {
        if(sentidoOrdenamiento = 1)
            cmp()
        }
    }
    while (ordenado);
}

// FUNCIONES PUNTERO
void mostrarPagos_ALU(void *dato, void * datosAccion)
{
    Pago * p = (Pago*)dato;
    printf("%d\t%-14s\tfv: %d/%d/%d\tfp: %d/%d/%d\t%lf\n",p->nroCliente,p->nroFactura,p->fechaVencimiento.dia,p->fechaVencimiento.mes, p->fechaVencimiento.anio, p->fechaPago.dia,p->fechaPago.mes,p->fechaPago.anio, p->importe);
}

void mostrarIndice_ALU(void *dato, void * datosAccion)
{
    IndCli*  i = (IndCli*)dato;

    printf("%d\t%d\n",i->nroCliente, i->nroReg);
}

void imprimirArbolIndice_ALU(const void * dato, void * dImprimir, int nivel)
{
    const IndCli*  i = (const IndCli*)dato;
    for (int j =0; j<nivel ; j++ )
    {
        printf("\t");
    }
    printf("%d\t%d\n",i->nroCliente, i->nroReg);
}

int compararNumeroCliente_ALU(const void * d1, const void * d2)
{
    const IndCli *i1 = (const IndCli *)d1;
    const IndCli *i2 = (const IndCli*)d2;
    return i1->nroCliente - i2->nroCliente;
}

int compararPagos_ALU(const void *d1, const void *d2)
{
    const Pago * c1 = (const Pago * )d1;
    const Pago * c2 = (const Pago *)d2;

    return  c1->nroCliente - c2->nroCliente;
}

int compararDeudores_ALU(const void *deu1, const void * deu2)
{
    const Deudores * d1 = (const Deudores *)deu1;
    const Deudores * d2 = (const Deudores *)deu2;

    return d1->cantFactImpagasFueraTerm - d2->cantFactImpagasFueraTerm;
}

// FUNCIONES DE ARBOl
