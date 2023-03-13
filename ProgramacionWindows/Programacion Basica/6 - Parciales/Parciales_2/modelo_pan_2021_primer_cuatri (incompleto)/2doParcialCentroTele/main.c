#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Solucion2doParcialCentroTele.h>


#define PATH_CLI 1
#define PATH_PAGOS 2
#define PATH_LISTADO 3

int vencimiento(t_pago pago);
int cmpInd(const void* dato1, const void* dato2);
int cmpFactImp(const void* d1, const void* d2);
int cmpCantFactImp(const void* dato1, const void* dato2);


int main(int argc, char* argv[])
{
    //generarArchivoClientes(argv[PATH_CLI]);
    //generarArchivoPagos(argv[PATH_PAGOS]);

    procesarPagos(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
///	procesarPagos_res(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);

    return 0;
}


void procesarPagos(const char* pathCli, const char* pathPagos, const char* pathListado)
{
    t_arbol pArb;
    t_lista pListaD;
    t_pago pago;
    t_indice indx;
    t_cliente cli;
    t_facturasImpagasFueraTerm venc;
    char pathIndex[200];

    venc.cantFactImpagasFueraTerm = 1;

    FILE* fClientes = fopen(pathCli,"rb");
    FILE* fPagos = fopen(pathPagos,"rb");
    FILE* fListado = fopen(pathListado,"wt");

    if(!fClientes || !fPagos || !fListado)
        return;
    crear_arbol(&pArb);
    ///Cargo el indice al arbol
    generarPathIndex(pathCli,pathIndex);
    cargar_arbol_de_archivo_ordenado(&pArb, pathIndex);

    crear_lista(&pListaD);

    fread(&pago,sizeof(t_pago),1,fPagos);
    while(!feof(fPagos))
    {
        ///inserto en la lista
        if(vencimiento(pago))
        {
            venc.nroCliente = pago.nroCliente;
            lista_actualizar_insertar(&pListaD,&venc,cmpFactImp,actualizar);
        }
        fread(&pago,sizeof(t_pago),1,fPagos);
    }
    fclose(fPagos);
    ordenar_lista_2(&pListaD,cmpCantFactImp);

    ///ahora debo acceder con el indice al archivo de clientes
    printf("Nro Cliente    Nombre del cliente       Facturas Impagas\n");
    fputs("Nro Cliente    Nombre del cliente       Facturas Impagas\n",fListado);
    while(!lista_vacia(&pListaD))
    {
        lista_sacar_primero(&pListaD, &venc);
        indx.nroCliente=venc.nroCliente;
        buscar_en_arbol_bin_busq(&pArb,&indx,cmpInd);
        fseek(fClientes,indx.nroReg*sizeof(t_cliente),SEEK_SET);
        fread(&cli,sizeof(t_cliente),1,fClientes);
        printf("%-15d %-30s %-10d\n", venc.nroCliente, cli.nombre ,venc.cantFactImpagasFueraTerm);
        fprintf(fListado,"%-15d %-30s %-10d\n",venc.nroCliente, cli.nombre, venc.cantFactImpagasFueraTerm);
    }

    fclose(fClientes);
    fclose(fListado);

}

void generarPathIndex(const char* pathCli, char* pathIndex)
{
    strcpy(pathIndex,pathCli);
    pathIndex = strchr(pathIndex,'.');
    strcpy(pathIndex,".idx");
}

void crear_arbol(t_arbol* pa)
{
    *pa=NULL;
}

void crear_lista(t_lista* pl)
{
    *pl=NULL;
}

int cmpFactImp(const void* dato1, const void* dato2)
{
    t_facturasImpagasFueraTerm* d1 = (t_facturasImpagasFueraTerm*) dato1;
    t_facturasImpagasFueraTerm* d2 = (t_facturasImpagasFueraTerm*) dato2;
    return d1->nroCliente - d2->nroCliente;
}

int cmpCantFactImp(const void* dato1, const void* dato2)
{
    t_facturasImpagasFueraTerm* d1 = (t_facturasImpagasFueraTerm*) dato1;
    t_facturasImpagasFueraTerm* d2 = (t_facturasImpagasFueraTerm*) dato2;
    return d1->cantFactImpagasFueraTerm - d2->cantFactImpagasFueraTerm;
}

int cmpInd(const void* dato1, const void* dato2)
{
    t_indice* d1 = (t_indice*) dato1;
    t_indice* d2 = (t_indice*) dato2;
    return d1->nroCliente - d2->nroCliente;
}

int vencimiento(t_pago pago)
{
    t_fecha fecha;
    fecha.d=1;
    fecha.m=1;
    fecha.a=1900;
    return (!cmpFechas_res(&fecha,&pago.fechaPago) || cmpFechas_res(&pago.fechaVencimiento,&pago.fechaPago)<0);
}

void mostrarClave(const void* dato)
{
    t_dato_arbol* info = (t_dato_arbol*)dato;
    printf("%d %d\n",info->nroCliente, info->nroReg);
}
