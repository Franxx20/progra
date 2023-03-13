#include <stdio.h>
#include <stdlib.h>

#include "../Comun/Comun.h"
#include "../SolucionFacturacionElectro/SolucionFacturacionElectro.h"

#define ARG_CLIENTES	1
#define ARG_MEDICIONES	2
#define ARG_FACTURAS	3
#define ARG_PROXIMO_NRO_FACTURA 4
#define ARG_CANT_MESES_A_FACTURAR 5

#define MAX_MESES 10

int extraerMesesAFacturar(char* argv[], Mes* mesesAFacturar);
int generarFacturas_ALU(const char* nombreArchivoClientes, const char* nombreArchivoMediciones, const char* nombreArchivoFacturas, int proximoNroFactura, const Mes* mesesAFacturar, int cantMesesAFacturar);
int CmpMediciones_ALU(const void* e1, const void* e2);
int difEnDiasEntreFechas_ALU(Fecha f1, Fecha f2);

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

	ret = generarFacturas(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);
	/// Descomente esta línea y comente la de arriba, para ejecutar su código
    //ret = generarFacturas_ALU(argv[ARG_CLIENTES], argv[ARG_MEDICIONES], argv[ARG_FACTURAS], atoi(argv[ARG_PROXIMO_NRO_FACTURA]), mesesAFacturar, cantMesesAFacturar);

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
	/// Desarrolle esta función y todas las que invoque. Puede usar funciones de la biblioteca estándar.
	/// Coloque el sufijo _ALU a todas las funciones que desarrolle.
	/// No use otro archivo que no sea main.c. Será el que deberá entregar.

	int ret;

	Cliente cliAct;
    Medicion medAct;
    Factura facAct;
    Fecha ultFecha;
    int ultMed;

    Lista mediciones;
    crearLista(&mediciones);

    FILE* c = fopen(nombreArchivoClientes, "r+b");
    FILE* m = fopen(nombreArchivoMediciones, "r");
    FILE* f = fopen(nombreArchivoFacturas, "w+b");

    if(!c || !m || !f)
        return ERR_ARCHIVO;

////Inserta Mediciones.txt en una Lista Ordenada por NroCliente///////////////////////////////
    fscanf(m, "%d|%d/%d/%d|%d", &medAct.nroCliente,&medAct.fechaMedicion.dia,&medAct.fechaMedicion.mes,&medAct.fechaMedicion.anio,&medAct.valorMedidor);
    while(!feof(m))
    {
        //fscanf(m, "%d|%d/%d/%d|%d", &medAct.nroCliente,&medAct.fechaMedicion.dia,&medAct.fechaMedicion.mes,&medAct.fechaMedicion.anio,&medAct.valorMedidor);
        ret = insertarEnListaOrdCDup(&mediciones, &medAct, sizeof(Medicion), CmpMediciones_ALU);
        fscanf(m, "%d|%d/%d/%d|%d", &medAct.nroCliente,&medAct.fechaMedicion.dia,&medAct.fechaMedicion.mes,&medAct.fechaMedicion.anio,&medAct.valorMedidor);
    }

    fclose(m);

    if(ret != TODO_OK)
	{
		printf("Error al insertar en lista\n");
		return ret;
	}

/////////////////////////////////////////////////////////////////////////////////////////////

    fread(&cliAct, sizeof(Cliente), 1, c);
    while(!feof(c)) //recorre el archivo Clientes.dat
    {
        int dm, dd;
        float cm;

        int i;
        for(i=0; i<cantMesesAFacturar; i++) //carga las facturas del cliente actual
        {
            if(i==0) //asigna la ultima fecha de medicion y su valor
            {
                ultFecha = cliAct.fechaUltMedicion;
                ultMed = cliAct.valorMedidor;
            }
            else
            {
                ultFecha = medAct.fechaMedicion;
                ultMed = medAct.valorMedidor;
            }

            eliminarDeListaPrimero(&mediciones, &medAct, sizeof(Medicion));
            dm = medAct.valorMedidor - ultMed;
            dd = difEnDiasEntreFechas_ALU(medAct.fechaMedicion, ultFecha);
            if(dd)
                cm = ((float)dm/(float)dd)*cantDiasMes(medAct.fechaMedicion.mes, medAct.fechaMedicion.anio);
            else
                cm = (float)dm*cantDiasMes(medAct.fechaMedicion.mes, medAct.fechaMedicion.anio);

            facAct.nroFactura = proximoNroFactura;
            facAct.nroCliente = medAct.nroCliente;
            facAct.mesFacturado.mes = medAct.fechaMedicion.mes;
            facAct.mesFacturado.anio = medAct.fechaMedicion.anio;
            facAct.fechaUltMedicion = medAct.fechaMedicion;
            facAct.valorMedidor = medAct.valorMedidor;
            facAct.consumoMes = cm;

            fwrite(&facAct, sizeof(Factura), 1, f);
            proximoNroFactura++;
        }

        //Actualiza Clientes.dat
        cliAct.fechaUltMedicion = facAct.fechaUltMedicion;
        cliAct.valorMedidor = facAct.valorMedidor;
        cliAct.ultMesFacturado = facAct.mesFacturado;
        cliAct.ultConsumoMes = facAct.consumoMes;

        fseek(c,-sizeof(Cliente),SEEK_CUR);
        fwrite(&cliAct, sizeof(Cliente), 1, c);

        fseek(c,0,SEEK_CUR);
        fread(&cliAct, sizeof(Cliente), 1, c);
    }

    fclose(c);
    fclose(f);

	return TODO_OK;
}

int CmpMediciones_ALU(const void* e1, const void* e2) //compara dos mediciones por nro de cliente
{
    Medicion* m1 = (Medicion*)e1;
    Medicion* m2 = (Medicion*)e2;

    return m1->nroCliente - m2->nroCliente;
}

int difEnDiasEntreFechas_ALU(Fecha f1, Fecha f2)
{
    #define bisciesto(anio) (!anio%4 && (anio%100 || !anio%400))? 1:0
    #define abs(x) x<0? -x:x

    int diasAcum[13]={0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int f1Dias, f2Dias;

    f1Dias = (f1.anio-1)*147097/400;
    f2Dias = (f2.anio-1)*147097/400;

    f1Dias += diasAcum[f1.mes]+f1.dia;
    f2Dias += diasAcum[f2.mes]+f2.dia;

    if(f1.mes > 2)
        f1Dias += bisciesto(f1.anio);

    if(f2.mes > 2)
        f2Dias += bisciesto(f2.anio);

        return abs(f1Dias-f2Dias);
}
