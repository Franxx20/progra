#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Comun/Comun.h"
#include "../Nodo/Nodo.h"
#include "../TDALista/TDALista.h"
#include "../Fecha/Fecha.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES	1
#define ARG_MEDICIONES	2
#define ARG_FACTURAS	3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar);
int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar);
void cargarMediciones(const char* nombreArchivoMediciones, Lista* pl);
void mostrarMedicion(void* elem, void* datosAccion);
int cmpMediciones(const void* e1, const void* e2);
void mostrarFactura(Factura fac);

int main(int argc, char* argv[])
{
	int ret = generarArchivos();

	if(ret != TODO_OK)
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

	if(ret != TODO_OK)
	{
		printf("Error al generar facturas\n");
		return ret;
	}

	puts("\nDespues de Actualizar:\n");

	mostrarFacturas(argv[ARG_FACTURAS]);

	mostrarClientes(argv[ARG_CLIENTES]);

	return ret;
}


int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar)
{
	int cantMesesAFacturar = atoi(argv[ARG_CANT_MESES_A_FACTURAR]);

	for(int i = 0; i < cantMesesAFacturar; i++)
		mesesAFacturar[i] = strToMes(argv[ARG_CANT_MESES_A_FACTURAR + 1 + i]);

	return cantMesesAFacturar;
}


int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar)
{
    Lista listaMediciones;
    crearLista(&listaMediciones);

    cargarMediciones(nombreArchivoMediciones, &listaMediciones); //Funciona
    printf("\n\nLISTA\n");
    recorrerLista(&listaMediciones, mostrarMedicion, NULL);
    printf("\n\nFacturas\n");

    FILE* archCli = fopen(nombreArchivoClientes, "r+b");
    FILE* archFac = fopen(nombreArchivoFacturas, "wb");
    if(!archCli || !archFac)
    {
        fclose(archCli);
        fclose(archFac);
        return 2;
    }

    Cliente cliAct;
    Medicion medAct;
    Factura facAct;

    int i, dm, dd, ultMed;
    double cde, cm;
    Fecha ultFecha;

    fread(&cliAct, sizeof(Cliente), 1, archCli);
    while(!feof(archCli))
    {
        ultFecha = cliAct.fechaUltMedicion;
        ultMed = cliAct.valorMedidor;
        for(i=0; i<cantMesesAFacturar; i++)
        {
            eliminarDeListaPrimero(&listaMediciones, &medAct, sizeof(Medicion));

            dm = medAct.valorMedidor - ultMed;
            dd = difEnDiasEntreFechas(&ultFecha, &medAct.fechaMedicion);
            cde = (double)dm/dd;
            cm = cde*cantDiasMes(medAct.fechaMedicion.mes, medAct.fechaMedicion.anio);

            facAct.nroFactura = proximoNroFactura;
            proximoNroFactura++;
            facAct.nroCliente = cliAct.nroCliente;
            facAct.fechaUltMedicion = medAct.fechaMedicion;
            facAct.valorMedidor = medAct.valorMedidor;
            facAct.mesFacturado.mes = medAct.fechaMedicion.mes;
            facAct.mesFacturado.anio = medAct.fechaMedicion.anio;
            facAct.consumoMes = cm;
            ultFecha = medAct.fechaMedicion;
            ultMed = medAct.valorMedidor;
            mostrarFactura(facAct);
            fwrite(&facAct, sizeof(Factura), 1, archFac);
        }
        cliAct.fechaUltMedicion = facAct.fechaUltMedicion;
        cliAct.valorMedidor = facAct.valorMedidor;
        cliAct.ultMesFacturado = facAct.mesFacturado;
        cliAct.ultConsumoMes = facAct.consumoMes;

        fseek(archCli, (long int)-sizeof(Cliente), SEEK_CUR);
        fwrite(&cliAct, sizeof(Cliente), 1, archCli);
        fseek(archCli, 0, SEEK_CUR);
        fread(&cliAct, sizeof(Cliente), 1, archCli);
    }

    fclose(archCli);
    fclose(archFac);
    return 0;
}



void cargarMediciones(const char* nombreArchivoMediciones, Lista* pl)
{
    FILE* archMed = fopen(nombreArchivoMediciones, "rt");
    if(!archMed)
        return;

    char linea[256];
    char* act;

    Medicion medAct;

    while(fgets(linea, 256, archMed) != NULL)
    {
        act = strchr(linea, '\n');
        if(!act)
            return;

        act = strrchr(linea, '|');
        sscanf(act+1, "%d", &medAct.valorMedidor);
        *act = '\0';

        act = strrchr(linea, '|');
        sscanf(act+1, "%d/%d/%d", &medAct.fechaMedicion.dia, &medAct.fechaMedicion.mes, &medAct.fechaMedicion.anio);
        *act = '\0';

        sscanf(linea, "%d", &medAct.nroCliente);

        insertarEnListaOrdCDup(pl, &medAct, sizeof(Medicion), cmpMediciones);
    }
}

void mostrarMedicion(void* elem, void* datosAccion)
{
    Medicion* medicion = (Medicion*)elem;
    printf("%d|%d/%d/%d|%d\n", medicion->nroCliente, medicion->fechaMedicion.dia, medicion->fechaMedicion.mes, medicion->fechaMedicion.anio, medicion->valorMedidor);
}

int cmpMediciones(const void* e1, const void* e2)
{
    Medicion* m1 = (Medicion*)e1;
    Medicion* m2 = (Medicion*)e2;

    return m1->nroCliente-m2->nroCliente;
}

void mostrarFactura(Factura fac)
{
    printf("%d|%d|%d|%d|%lf\n", fac.nroFactura, fac.nroCliente, fac.fechaUltMedicion.mes, fac.valorMedidor, fac.consumoMes);
}
