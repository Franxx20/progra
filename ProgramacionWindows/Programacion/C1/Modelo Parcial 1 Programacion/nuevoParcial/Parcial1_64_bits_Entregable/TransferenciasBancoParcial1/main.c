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
    //ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
    //                           NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
//
    /****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/
//
    ret = procesarTransferencias_alu(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
                                     NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
//

    /*if(ret != TODO_OK)
        return ret;

    puts("Despues de actualizar:\n");

    ret = mostrarCuentas(NOMBRE_CUENTAS);

    if(ret != TODO_OK)
        return ret;

    ret = mostrarTransferencias(NOMBRE_TRANSF);
    */
    return ret;
}


int procesarTransferencias_alu(const char* nombreTransf, const char* nombreTransfSentander, const char* nombreTransfYCBC, const char* nombreCuentas,
                               const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado)
{
    int resSan = convertirTxtABinario(nombreTransfSentander, "tranSantander.dat");
    int resY = convertirTxtABinario(nombreTransfYCBC,"tranYCBC.dat");

    if(resSan != TODO_OK )
    {
        fprintf(stderr,"ERROR EN LA CONVERSION TXT A BIN");
        return resSan;
    }
    if(resY != TODO_OK )
    {
        fprintf(stderr,"ERROR EN LA CONVERSION TXT A BIN");
        return resY;
    }
    // MERGEAMOS EL ARCHIVO BINARIO DE SANTANDER CON EL ARCHIVO BINARIO DE YCBC
    int cod = mergeTransfer_alu("tranSantander.dat","tranYCBC.dat","MergeTemp.dat");
    if(cod != TODO_OK)
        return cod;
    // MERGEAMOS EL ARCHIVO BINARIO TEMPORAL CON EL ARCHIBO BINARIO DE PATAGONIA
    cod = mergeTransfer_alu(nombreTransf, "MergeTemp.dat","MergeFinal.dat");
    if(cod != TODO_OK)
        return cod;


    printf("Transferencias Mergeadas\n");
    printf("Trasferencias Patagonia\n-----------------------------------------\n");
    FILE *archMerge = fopen("MergeFinal.dat","rb");
    if(!archMerge)
    {
        fprintf(stderr, "ERROR EN LA APERTURA DEL ARCHIVO MERGE FINAL EN LECTURA");
        return ERR_AP_ARCH;
    }

    Transferencia trans;
    fread(&trans,sizeof(Transferencia),1,archMerge);
    trans.aplicada = 'N';
    char formato[]= {"%2d-%2d-%2d\t%s\t%-10s\t%-25s\t%-10s\t%010.2lf     %c\n"};

    while(!feof(archMerge))
    {
        fprintf(stdout,formato,trans.fecha.dia,trans.fecha.mes, trans.fecha.anio, trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,trans.monto,trans.aplicada);
        fread(&trans,sizeof(Transferencia),1,archMerge);
        trans.aplicada = 'N';
    }



    fclose(archMerge);
    actualizarCuentasYTransferencias_alu("MergeFinal.dat",nombreCuentas,nombreTransfSantanderEstado,nombreTransfYCBCEstado,nombreTransf);







    return TODO_OK;
}


int convertirTxtABinario_alu(const char* nombreTransfTxt, const char* nombreTransfBin)
{
    FILE * archTxt = fopen(nombreTransfTxt,"rt");
    FILE * archBin = fopen(nombreTransfBin, "wb");
    if(!archTxt)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE TEXTO DE TRANSFERENCIAS EN LECTURA");
        return ERR_AP_ARCH;
    }
    if(!archBin)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO BINARIO DE TRANSFERENCIAS EN ESCRITURA");
        return ERR_AP_ARCH;
    }
    char linea[100];
    char * car;
    // TITULOS
    fgets(linea,100,archTxt);
    // DATOS
    int err = TODO_OK;
    while(fgets(linea,100,archTxt))
    {
        car = strchr(linea,'\n');


        if(!car)
        {
            fprintf(stderr,"No se encontro el caracter de fin de linea");
            err = ERR_LINEA_LARGA;
        }


        if(err == TODO_OK)
        {
            Transferencia trans;
            // BUSCAMOS EL MONTO
            *car = '\0';
            car = strrchr(linea,'|');
            sscanf(car+1,"%lf",&trans.monto);
            // BUSCAMOS EL  BANCO DESTINO
            *car = '\0';
            car = strrchr(linea,'|');
            strncpy(trans.bancoDest,car+1,sizeof(trans.bancoDest));
            // BUSCAMOS LA CUENTA DE DESTINO
            *car = '\0';
            car = strrchr(linea,'|');
            strncpy(trans.cuentaDest,car+1,sizeof(trans.cuentaDest));
            // BUSCAMOS EL BANCO DE ORIGEN
            *car = '\0';
            car = strrchr(linea,'|');
            strncpy(trans.bancoOrig,car+1,sizeof(trans.bancoOrig));
            // BUSCAMOS LA CUENTA DE ORIGEN
            *car = '\0';
            car = strrchr(linea,'|');
            strncpy(trans.cuentaOrig,car+1,sizeof(trans.cuentaOrig));
            // BUSCAMOS LA FECHA
            *car = '\0';
            sscanf(linea,"%d-%d-%d", &trans.fecha.dia, &trans.fecha.mes, &trans.fecha.anio);

            // UNA VEZ OBTENIDA LA LINEA LA ESCRIBIMOS EN EL ARCHIVO BINARIO
            fwrite(&trans,sizeof(Transferencia),1,archBin);
        }

    }


    fclose(archTxt);
    fclose(archBin);

    return TODO_OK;
}


int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge)
{

    FILE *arch1 = fopen(nombreTransf1, "rb");
    FILE *arch2 = fopen(nombreTransf2,"rb");
    FILE *archMerge = fopen(nombreTransfMerge, "wb");

    if(!arch1 || !arch2 || !archMerge )
    {
        fprintf(stderr,"ERROR EN LA APERTURA DE LOS ARCHIVOS PARA EL PROCESO DE MERGE");

        return ERR_AP_ARCH;
    }
    Transferencia t1;
    Transferencia t2;

    int comp;
    fread(&t1, sizeof(Transferencia),1,arch1);
    fread(&t2, sizeof(Transferencia),1,arch2);

    while(!feof(arch1) && !feof(arch2))
    {
        comp=cmpFechas(&t1.fecha,&t2.fecha);

        // si la fecha t1 es mayor a t2 entonces t2 se escribe
        if(comp >0)
        {
            fwrite(&t2,sizeof(Transferencia),1,archMerge);
            fread(&t2,sizeof(Transferencia),1,arch2);
        }
        if(comp<0)
        {
            fwrite(&t1,sizeof(Transferencia),1,archMerge);
            fread(&t1,sizeof(Transferencia),1,arch1);
        }
        if(comp == 0)
        {
            fwrite(&t2,sizeof(Transferencia),1,archMerge);
            fwrite(&t1,sizeof(Transferencia),1,archMerge);
            fread(&t2,sizeof(Transferencia),1,arch2);
            fread(&t1,sizeof(Transferencia),1,arch1);
        }


    }

    while(!feof(arch1))
    {
        fwrite(&t1,sizeof(Transferencia),1,archMerge);
        fread(&t1,sizeof(Transferencia),1,arch1);

    }
    while(!feof(arch2))
    {
        fwrite(&t2,sizeof(Transferencia),1,archMerge);
        fread(&t2,sizeof(Transferencia),1,arch2);
    }

    fclose(arch1);
    fclose(arch2);
    fclose(archMerge);
    return TODO_OK;

}


int actualizarCuentasYTransferencias_alu(
    const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
    const char* nombreTransf)
{
    FILE * fMerge = fopen(nombreTransfMerge, "rb");
    FILE * fSantEstado = fopen(nombreTransfSantanderEstado, "wt");
    FILE * fYCBCEstado = fopen(nombreTransfYCBCEstado, "wt");
    FILE * fCuentas = fopen(nombreCuentas,"rb");
    FILE * fPata = fopen(nombreTransf, "rb");

    if(!fMerge || !fSantEstado || !fYCBCEstado || !fCuentas || ! fPata)
    {
        fprintf(stderr, "ERROR EN LA APERTURA DE LOS ARCHIVOS PARA ACTUALIZAR");
        return ERR_AP_ARCH;

    }

    Transferencia trans, transFile;
    Lista listaFecha;
    Lista listaCuenta;
    crearLista(&listaCuenta);
    crearLista(&listaFecha);
    Cuenta cue;
    char formato[] = "%2d-%2d-%2d|%s|%s|%s|%s|%lf|%c\n";

    // CARGAMOS LAS CUENTAS EN LA LISTA DE CUENTAS
    fread(&cue,sizeof(Cuenta),1,fCuentas);
    while(!feof(fCuentas))
    {
        insertarEnListaAlFinal(&listaCuenta,&cue,sizeof(Cuenta));
        fread(&cue,sizeof(Cuenta),1,fCuentas);
    }
    fclose(fCuentas);
    printf("\nLista recien cargada del archivo cuentas\n");
    recorrerLista(&listaCuenta, printear2_alu, &cue);

    fread(&transFile, sizeof(Transferencia),1,fMerge);
    Fecha f;

    while(!feof(fMerge))
    {
        f = transFile.fecha;
        while(!feof(fMerge) && cmpFechas(&f, &transFile.fecha) == 0)
        {
            // INICIALIZO A TODOS EN S
            transFile.aplicada = 'S';
            // ACTUALIZO LOS MONTOS
            recorrerLista(&listaCuenta,accion1_alu, & transFile);
            insertarEnListaAlFinal(&listaFecha,&transFile, sizeof(Transferencia));
            fread(&transFile,sizeof(Transferencia),1,fMerge);
        }
        // se termina de cargar un lote con la misma fecha

        // RECORRO LA LISTA CUENTAS VIENDO LA LISTA FECHA Y ACTUALIZICO CON S O N
        recorrerLista(&listaCuenta,accion2_alu,&listaFecha);
        printf("\nLista Transferencias al terminar el lote %d-%d-%d\n", f.dia, f.mes, f.anio);
        recorrerLista(&listaFecha, printear_alu, &trans);

        while(!listaVacia(&listaFecha))
        {
            eliminarDeListaPrimero(&listaFecha, &trans, sizeof(Transferencia));


            if(strcmpi(trans.bancoDest, "YCBC") == 0 || strcmpi(trans.bancoOrig, "YCBC") == 0)
            {
                fprintf(fYCBCEstado, formato, trans.fecha.dia, trans.fecha.mes, trans.fecha.anio, trans.cuentaOrig, trans.bancoOrig,
                        trans.cuentaDest, trans.bancoDest, trans.monto, trans.aplicada);
            }
            else
            {
                fprintf(fSantEstado, formato, trans.fecha.dia, trans.fecha.mes, trans.fecha.anio, trans.cuentaOrig, trans.bancoOrig,
                        trans.cuentaDest, trans.bancoDest, trans.monto, trans.aplicada);
            }

            fwrite(&trans, sizeof(Transferencia), 1, fPata);

        }

        printf("\nLista Cuentas al terminar el lote %d-%d-%d\n", f.dia, f.mes, f.anio);
        recorrerLista(&listaCuenta, printear2_alu, &cue);
    }



    fclose(fMerge);
    fclose(fSantEstado);
    fclose(fYCBCEstado);
    fclose(fPata);
    return TODO_OK;
}


void accion1_alu(void* datoAct, void* datoRef/*referencia*/)
{
    Transferencia * tranRef =(Transferencia * ) datoRef;
    Cuenta * cuentaAct = (Cuenta *)datoAct;
    if(strcmpi(cuentaAct->cuenta,tranRef->cuentaOrig) == 0)
    {
        cuentaAct->saldo -= tranRef->monto;
    }
    if(strcmpi(cuentaAct->cuenta,tranRef->cuentaDest) == 0)
    {

        cuentaAct->saldo += tranRef->monto;

    }

}


void accion2_alu(void* datoAct, void* datoRef)
{
    Cuenta * cuentaAct = datoAct;
    Lista * lista = datoRef;

    if(cuentaAct->saldo<0)
    {

        recorrerLista(lista,accion3_alu,cuentaAct);
    }
}

void accion3_alu(void* datoAct, void* datoRef)
{
    Cuenta * cuenta = datoRef;
    Transferencia* tran = datoAct;

    if(strcmpi(tran->cuentaDest, cuenta->cuenta)== 0 || strcmpi(tran->cuentaOrig, cuenta->cuenta) == 0 )
    {

        tran->aplicada = 'N';
        // y revierto las transferencias hechas
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
    Cuenta * c = (Cuenta * )datoAct;
    fprintf(stdout,"%s\t%-10d\t%010.2lf\n", c->cuenta, c->dniTitular, c->saldo);
}
