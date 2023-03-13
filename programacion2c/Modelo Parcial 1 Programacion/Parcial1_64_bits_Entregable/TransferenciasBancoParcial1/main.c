#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionParcialBanco/SolucionParcialBanco.h"
#include "main.h"

#include "../SolucionParcialBanco/Transferencia.h"
#include "../SolucionParcialBanco/Cuenta.h"
#include "../TDALista/TDALista.h"

void accion1_alu(void* datoAct, void* datoRef);
void accion2_alu(void* datoAct, void* datoRef);
void accion3_alu(void* datoAct, void* datoRef);
void printear_alu(void* datoAct, void* dato);
void printear2_alu(void* datoAct, void* dato);

int main()
{
    generarArchivos();

	puts("Antes de actualizar:\n");

	int ret;

	ret = mostrarCuentas(NOMBRE_CUENTAS);

	if(ret != TODO_OK)
		return ret;

	ret = mostrarTransferencias(NOMBRE_TRANSF);

	if(ret != TODO_OK)
		return ret;
//
    ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
//
	/****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/
//
//    ret = procesarTransferencias_alu(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
//		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
//

	if(ret != TODO_OK)
		return ret;

	puts("Despues de actualizar:\n");

	ret = mostrarCuentas(NOMBRE_CUENTAS);

	if(ret != TODO_OK)
		return ret;

	ret = mostrarTransferencias(NOMBRE_TRANSF);

    return ret;
}


int procesarTransferencias_alu(
	const char* nombreTransf, const char* nombreTransfSentander, const char* nombreTransfYCBC, const char* nombreCuentas,
	const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado)
{
    int cod = convertirTxtABinario_alu(nombreTransfSentander, "TransSant.dat");
    if(cod != TODO_OK)
        return cod;

    cod = convertirTxtABinario_alu(nombreTransfYCBC, "TransYCBC.dat");
    if(cod != TODO_OK)
        return cod;

    cod = mergeTransfer_alu("TransSant.dat", "TransYCBC.dat", "mergeTMP.dat");
    if(cod != TODO_OK)
        return cod;

    cod = mergeTransfer_alu(nombreTransf, "mergeTMP.dat", "MergeFinal.dat");
    if(cod != TODO_OK)
        return cod;

    printf("Transferencias mergeadas:\n");
    printf("Transferencias Patagania\n========================================\n");

    FILE* pf = fopen("MergeFinal.dat", "rb");
    if(!pf)
    {
        fclose(pf);
        return ERR_AP_ARCH;
    }

    Transferencia tran;

    fread(&tran, sizeof(Transferencia), 1, pf);
    while(!feof(pf))
    {
        printf("%2d-%2d-%2d\t%s\t%10s\t%25s\t%10s\t%010.2lf\n", tran.fecha.dia, tran.fecha.mes, tran.fecha.anio, tran.cuentaOrig,
        tran.bancoOrig, tran.cuentaDest, tran.bancoDest, tran.monto);
        fread(&tran, sizeof(Transferencia), 1, pf);
    }

    fclose(pf);

    actualizarCuentasYTransferencias_alu("MergeFinal.dat", nombreCuentas, nombreTransfSantanderEstado, nombreTransfYCBCEstado, nombreTransf);

    return TODO_OK;
}


int convertirTxtABinario_alu(const char* nombreTransfTxt, const char* nombreTransfBin)
{
	FILE* pt = fopen(nombreTransfTxt, "rt");
	FILE* pb = fopen(nombreTransfBin, "wb");

	if(!pt || !pb)
    {
        fclose(pt);
        fclose(pb);
        return ERR_AP_ARCH;
    }

	Transferencia tra;

	int error = TODO_OK;

	char linea[200];
    char* pos;

	fgets(linea, 200, pt); //titulares.
	fgets(linea, 200, pt); //datos.
	while(!feof(pt))
    {
        pos = strchr(linea, '\n');

        if(!pos)
            error = ERR_LINEA_LARGA;

        if(error == TODO_OK)
        {

            *pos = '\0';

            ///monto

            pos = strrchr(linea, '|');
            sscanf(pos + 1, "%lf", &tra.monto);
            *pos = '\0';

            ///Banco destino

            pos = strrchr(linea, '|');
//            sscanf(pos + 1, "%s", tra.bancoDest);
            strcpy(tra.bancoDest, pos + 1);
            *pos = '\0';

            ///Cta destino

            pos = strrchr(linea, '|');
//            sscanf(pos + 1, "%s", tra.cuentaDest);
            strcpy(tra.cuentaDest, pos + 1);

            *pos = '\0';

            ///Banco origen

            pos = strrchr(linea, '|');
//            sscanf(pos + 1, "%s", tra.bancoOrig);
            strcpy(tra.bancoOrig, pos + 1);

            *pos = '\0';

            ///cuenta origen

            pos = strrchr(linea, '|');
//            sscanf(pos + 1, "%s", tra.cuentaOrig);
            strcpy(tra.cuentaOrig, pos + 1);

            *pos = '\0';

            ///Fecha

            sscanf(linea, "%d-%d-%d", &tra.fecha.dia, &tra.fecha.mes, &tra.fecha.anio);

            ///escribo en el binario:

            fwrite(&tra, sizeof(Transferencia), 1, pb);
        }

        fgets(linea, 200, pt);
        error = TODO_OK;
    }

    fclose(pb);
    fclose(pt);

    return TODO_OK;
}


int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge)
{
    FILE* pb1 = fopen(nombreTransf1, "rb");
    FILE* pb2 = fopen(nombreTransf2, "rb");
    FILE* pbt = fopen(nombreTransfMerge, "wb");

    if(!pb1 || !pb2 || !pbt)
    {
        fclose(pb1);
        fclose(pb2);
        fclose(pbt);
        return ERR_AP_ARCH;
    }

    Transferencia tra1, tra2;

    int comparar;

    fread(&tra1, sizeof(Transferencia), 1, pb1);
    fread(&tra2, sizeof(Transferencia), 1, pb2);


    while(!feof(pb1) && !feof(pb2))
    {
        comparar = cmpFechas(&tra1.fecha, &tra2.fecha);

        if(comparar > 0)
        {
            fwrite(&tra2, sizeof(Transferencia), 1, pbt);
            fread(&tra2, sizeof(Transferencia), 1, pb2);
        }

        if(comparar < 0)
        {
            fwrite(&tra1, sizeof(Transferencia), 1, pbt);
            fread(&tra1, sizeof(Transferencia), 1, pb1);
        }

        if(comparar == 0)
        {
            fwrite(&tra1, sizeof(Transferencia), 1, pbt);
            fwrite(&tra2, sizeof(Transferencia), 1, pbt);
            fread(&tra1, sizeof(Transferencia), 1, pb1);
            fread(&tra2, sizeof(Transferencia), 1, pb2);
        }
    }

    while(!feof(pb1))
    {
        fwrite(&tra1, sizeof(Transferencia), 1, pbt);
        fread(&tra1, sizeof(Transferencia), 1, pb1);
    }

    while(!feof(pb2))
    {
        fwrite(&tra2, sizeof(Transferencia), 1, pbt);
        fread(&tra2, sizeof(Transferencia), 1, pb2);
    }

    fclose(pb1);
    fclose(pb2);
    fclose(pbt);

    return TODO_OK;
}


int actualizarCuentasYTransferencias_alu(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf)
{
    FILE* transfeMerge = fopen(nombreTransfMerge, "rb");
    FILE* cuentas = fopen(nombreCuentas, "rb");
    FILE* traSant = fopen(nombreTransfSantanderEstado, "wt");
    FILE* traYCBC = fopen(nombreTransfYCBCEstado, "wt");
    FILE* traPata= fopen(nombreTransf, "wb");


    if(!transfeMerge || !cuentas || !traSant || !traYCBC || !traPata)
    {
        fclose(transfeMerge);
        fclose(cuentas);
        fclose(traSant);
        fclose(traYCBC);
        fclose(traPata);
        return ERR_AP_ARCH;
    }

    Lista listaFecha, listaCuentas;
    crearLista(&listaFecha);
    crearLista(&listaCuentas);
    Transferencia tran, tranFile;
    Cuenta cue;
    char formato[] = "%2d-%2d-%2d|%s|%s|%s|%s|%lf|%c\n";

    fread(&cue, sizeof(Cuenta), 1, cuentas);
    while(!feof(cuentas))
    {
        insertarEnListaAlFinal(&listaCuentas, &cue, sizeof(Cuenta));
        fread(&cue, sizeof(Cuenta), 1, cuentas);
    }

    fclose(cuentas); //termine de cargar las cuentas en una lista.

    printf("\nLista recien cargada del archivo cuentas\n");
    recorrerLista(&listaCuentas, printear2_alu, &cue);

    fread(&tranFile, sizeof(Transferencia), 1, transfeMerge);
    while(!feof(transfeMerge))
    {
        Fecha fAct = tranFile.fecha;
        while(!feof(transfeMerge) && cmpFechas(&fAct, &tranFile.fecha) == 0)
        {
            tranFile.aplicada = 'S'; //inicializo todas en S.
            recorrerLista(&listaCuentas, accion1_alu, &tranFile); //actualiza montos
            insertarEnListaAlFinal(&listaFecha, &tranFile, sizeof(Transferencia));
            fread(&tranFile, sizeof(Transferencia), 1, transfeMerge);
        }


        //termino de cargar un lote con la misma fecha.

        recorrerLista(&listaCuentas, accion2_alu, &listaFecha); //recorro la lista cuentas viendo la lista fecha y actualizo con S o N.

        printf("\nLista Transferencias al terminar el lote %d-%d-%d\n", fAct.dia, fAct.mes, fAct.anio);
        recorrerLista(&listaFecha, printear_alu, &tran);


        while(!listaVacia(&listaFecha))
        {
            eliminarDeListaPrimero(&listaFecha, &tran, sizeof(Transferencia));


            if(strcmpi(tran.bancoDest, "YCBC") == 0 || strcmpi(tran.bancoOrig, "YCBC") == 0)
            {
                fprintf(traYCBC, formato, tran.fecha.dia, tran.fecha.mes, tran.fecha.anio, tran.cuentaOrig, tran.bancoOrig,
                        tran.cuentaDest, tran.bancoDest, tran.monto, tran.aplicada);
            }
            else
            {
                fprintf(traSant, formato, tran.fecha.dia, tran.fecha.mes, tran.fecha.anio, tran.cuentaOrig, tran.bancoOrig,
                        tran.cuentaDest, tran.bancoDest, tran.monto, tran.aplicada);
            }

            fwrite(&tran, sizeof(Transferencia), 1, traPata);

        }

        printf("\nLista Cuentas al terminar el lote %d-%d-%d\n", fAct.dia, fAct.mes, fAct.anio);
        recorrerLista(&listaCuentas, printear2_alu, &cue);
    }

    fclose(transfeMerge);
    fclose(cuentas);
    fclose(traSant);
    fclose(traYCBC);
    fclose(traPata);

    return TODO_OK;
}


void accion1_alu(void* datoAct, void* datoRef/*referencia*/)
{
    Transferencia* tranRef = datoRef;
    Cuenta* cuentaAct = datoAct;

    if(strcmpi(cuentaAct->cuenta, tranRef->cuentaOrig) == 0)
    {
        cuentaAct->saldo -= tranRef->monto;
    }

    if(strcmpi(cuentaAct->cuenta, tranRef->cuentaDest) == 0)
    {
        cuentaAct->saldo += tranRef->monto;
    }
}


void accion2_alu(void* datoAct, void* datoRef)
{
    Cuenta* cuentaAct = datoAct;
    Lista* lista = datoRef;

    if(cuentaAct->saldo < 0)
    {
        recorrerLista(lista, accion3_alu, cuentaAct);
    }
}

void accion3_alu(void* datoAct, void* datoRef)
{
    Cuenta* cuenta = datoRef;
    Transferencia* tran = datoAct;

    if(strcmpi(tran->cuentaDest, cuenta->cuenta) == 0 || strcmpi(tran->cuentaOrig, cuenta->cuenta) == 0)
    {
        tran->aplicada = 'N';
        //y revierto las transferencias hechas:
        if(strcmpi(tran->cuentaDest, cuenta->cuenta) == 0)
            cuenta->saldo -= tran->monto;

        if(strcmpi(tran->cuentaOrig, cuenta->cuenta) == 0)
            cuenta->saldo += tran->monto;
    }
}

void printear_alu(void* datoAct, void* dato)
{
    Transferencia* t;
    t = datoAct;

    printf("%2d-%2d-%2d\t%s\t%10s\t%25s\t%10s\t%010.2lf  %c\n",t->fecha.dia, t->fecha.mes, t->fecha.anio, t->cuentaOrig, t->bancoOrig,
                        t->cuentaDest, t->bancoDest, t->monto, t->aplicada);

}

void printear2_alu(void* datoAct, void* dato)
{
    Cuenta* c = datoAct;

    printf("%s\t%-10d\t%010.2lf\n", c->cuenta, c->dniTitular, c->saldo);
}
