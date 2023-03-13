#include <stdio.h>
#include <stdlib.h>

#include "../Comun/Comun.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES 1
#define ARG_MEDICIONES 2
#define ARG_FACTURAS 3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include<string.h>

int extraerMesesAFacturar(char *argv[], Mes *mesesAFacturar);
int generarFacturas_ALU(const char *nombreArchivoClientes, const char *nombreArchivoMediciones, const char *nombreArchivoFacturas, int proximoNroFactura, const Mes *mesesAFacturar, int cantMesesAFacturar);
int parsearLinea_ALU(const char * str, Medicion *med);
int cargarListaMediciones_ALU(Lista *l, const char * nombreArchivoMediciones);


void mostrarFactura_ALU(Factura* fac);
void mostrarMedicion_ALU(void* elem, void* datosAccion);

int compararMed_ALU(const void *med1, const void *med2);



int main(int argc, char *argv[])
{
    int ret = generarArchivos();

    if (ret != TODO_OK)
    {
        printf("Error al generar archivos\n");
        return ret;
    }

    printf("Archivos generados correctamente\n");

    puts("\nAntes de Actualizar:\n");

    mostrarClientes(argv[ARG_CLIENTES]);

    mostrarMediciones(argv[ARG_MEDICIONES]);

    Mes mesesAFacturar[MAX_MESES];

    int cantMesesAFacturar = extraerMesesAFacturar(argv, mesesAFacturar);

    //ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
    /// Descomente esta línea y comente la de arriba, para ejecutar su código
    ret = generarFacturas_ALU(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);

    if (ret != TODO_OK)
    {
        printf("Error al generar facturas\n");
        return ret;
    }

    puts("\nDespues de Actualizar:\n");

    mostrarFacturas(argv[ARG_FACTURAS]);

    mostrarClientes(argv[ARG_CLIENTES]);

    return ret;
}

int extraerMesesAFacturar(char *argv[], Mes *mesesAFacturar)
{
    int cantMesesAFacturar = atoi(argv[ARG_CANT_MESES_A_FACTURAR]);

    for (int i = 0; i < cantMesesAFacturar; i++)
        mesesAFacturar[i] = strToMes(argv[ARG_CANT_MESES_A_FACTURAR + 1 + i]);

    return cantMesesAFacturar;
}

int generarFacturas_ALU(const char *nombreArchivoClientes, const char *nombreArchivoMediciones, const char *nombreArchivoFacturas, int proximoNroFactura, const Mes *mesesAFacturar, int cantMesesAFacturar)
{
    /// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
    /// Coloque el sufijo _ALU a todas las funciones que desarrolle.
    /// No use otro archivo que no sea main.c. Será el que deberá entregar.
    FILE * fClientesAct = fopen("clientesActualizados.dat","wb");
    FILE * fClientes = fopen(nombreArchivoClientes, "rb");
    FILE * fFacturas = fopen(nombreArchivoFacturas,"wb" );


    if(!fClientes || !fClientesAct || !fFacturas )
    {
        fprintf(stdout, "ERROR AL ABRIR EL ARCHIVO\n");
        return ERR_ARCHIVO;
    }

    Lista lMediciones;
    crearLista(&lMediciones);
    printf("CANTIDAD DE MESES A FACTURARA %d", cantMesesAFacturar);

    cargarListaMediciones_ALU(&lMediciones,nombreArchivoMediciones);
    fprintf(stdout,"\nLISTA DE MEDICIONES \n");
    recorrerLista(&lMediciones,mostrarMedicion_ALU,NULL);

    int dd,dm;

    float cde,cm;

    Cliente cli;
    Factura f;
    Medicion med;
    Fecha ultF;
    int ultMed;


    int j = 0;
    fread(&cli,sizeof(Cliente),1,fClientes);
    while(!feof(fClientes))
    {
        ultF = cli.fechaUltMedicion;
        ultMed= cli.valorMedidor;
        f.nroCliente= cli.nroCliente;
        for (int i = 0; i<cantMesesAFacturar ; i++ )
        {

            eliminarDeListaPrimero(&lMediciones,&med,sizeof(Medicion));
            f.nroFactura= proximoNroFactura+j;
            j++;

            f.mesFacturado.mes = med.fechaMedicion.mes;
            f.mesFacturado.anio = med.fechaMedicion.anio;
            f.fechaUltMedicion = med.fechaMedicion;
            f.valorMedidor = med.valorMedidor;


            dm = f.valorMedidor - ultMed;
            dd = difEnDiasEntreFechas(&ultF,&med.fechaMedicion);
            cde =(float) dm/dd;
            cm = cde * cantDiasMes(med.fechaMedicion.mes,med.fechaMedicion.anio);

            f.consumoMes = cm;

            fprintf(stdout,"\n DM %d DD %d dme %.02f cm %.02f\n ",dm,dd,cde,cm);
            ultF = med.fechaMedicion;
            ultMed = med.valorMedidor;

            fwrite(&f,sizeof(Factura),1,fFacturas);
        }

        cli.fechaUltMedicion = ultF;
        cli.ultConsumoMes = f.consumoMes;
        cli.valorMedidor = f.valorMedidor;
        cli.ultMesFacturado.mes = ultF.mes;
        cli.ultMesFacturado.anio = ultF.anio;

        fwrite(&cli,sizeof(Cliente),1,fClientesAct);
        fread(&cli,sizeof(Cliente),1,fClientes);

    }

    fclose(fClientesAct);
    fclose(fClientes);
    fclose(fFacturas);

    remove(nombreArchivoClientes);
    rename("clientesActualizados.dat",nombreArchivoClientes);

    return TODO_OK;
}

int parsearLinea_ALU(const char * str, Medicion* med)
{

    char * aux = strchr(str,'\n');
    if(*aux != '\n')
        return ERR_LINEA;
    *aux = '\0';

    // buscamos el valorMedidor int
    aux = strrchr(str,'|');
    sscanf(aux+1,"%d",&med->valorMedidor);
    *aux = '\0';

    // Buscamos la fechaMedicion Fecha
    aux = strrchr(str, '|');
    sscanf(aux+1,"%02d/%02d/%04d",&med->fechaMedicion.dia,&med->fechaMedicion.mes,&med->fechaMedicion.anio);
    *aux = '\0';

    // Buscamos el nroCliente int
    sscanf(str, "%d", &med->nroCliente);


    return 0;
}



int cargarListaMediciones_ALU(Lista *l, const char * nombreArchivoMediciones)
{
    FILE * fMediciones = fopen(nombreArchivoMediciones, "rt");
    if(!fMediciones)
    {
        return ERR_ARCHIVO;
    }
    Medicion med;

    char linea[256];
    while(fgets(linea,256,fMediciones))
    {
        parsearLinea_ALU(linea,&med);
        insertarEnListaOrdCDup(l,&med,sizeof(Medicion),compararMed_ALU);
    }

    fclose(fMediciones);
    return 1;
}



void mostrarFactura_ALU(Factura* fac)
{
    printf("%d|%d|%d|%d|%lf\n", fac->nroFactura, fac->nroCliente, fac->fechaUltMedicion.mes, fac->valorMedidor, fac->consumoMes);
}


void mostrarMedicion_ALU(void* elem, void* datosAccion)
{
    Medicion* medicion = (Medicion*)elem;
    printf("%d|%d/%d/%d|%d\n", medicion->nroCliente, medicion->fechaMedicion.dia, medicion->fechaMedicion.mes, medicion->fechaMedicion.anio, medicion->valorMedidor);
}

int compararMed_ALU(const void *med1, const void *med2)
{
    Medicion *m1 = (Medicion *) med1;
    Medicion *m2 = (Medicion *) med2;

    return m1->nroCliente - m2->nroCliente;
}

