#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionParcialBanco/SolucionParcialBanco.h"
#include "main.h"

#include "../Fecha/Fecha.h"
#include "../Nodo/Nodo.h"
#include "../SolucionParcialBanco/Cuenta.h"
#include "../SolucionParcialBanco/Transferencia.h"
#include "../TDALista/TDALista.h"
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"

#define SIG_OCURR  ocurrencia = strrchr(read ,'|')
#define ERROR 9
#define BCO_PATAGANIA "Patagania"

#define MIN(x,y) x<=y?x:y

// FUNCIONES GENERALES

int procesarTransferencias_ALU
(const char* nombreTransf, char* nombreTransfSentander,
 char* nombreTransfYCBC, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado);

int convertirTxtABinario_ALU(const char * nombreTransTxt, const char * nombreTransBinario);
int parsearTransferencia_ALU(char *linea,Transferencia * transferencia);
int mergeTransfer_alu(const char * nombreTrans1, const char * nombreTrans2,const char * nombreMerge);


// FUNCIONES PUNTERO
int cmpCuentas_ALU(const void *d1, const void *d2);
void actualizarCuentas_ALU(void * actualizado, const void * actualizador);

// FUNCIONES LISTA
Nodo * crearNodo(const void * dato, size_t tamDato);
void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista *l);

int listaLlena_ALU(const Lista *l, size_t tamDato);
int listaVacia_ALU(const Lista *l);

int insertarEnListaAlFinal_ALU(Lista *l, const void *dato, size_t tamDato);
int eliminarDeListaPrimero_ALU(Lista *l, void *dato, size_t tamDato);

int buscarEnListaDesord_ALU(const Lista *l,void *dato,size_t tamDato, Cmp cmp);
int insertarOActualizarEnListaOrd_ALU(Lista *l, void *dato,size_t tamDato,Cmp cmp,Actualizar actualizar);

int main()
{
    generarArchivos();

    puts("Antes de actualizar:\nCUENTA			TITULAR		MONTO");

    int ret;

    ret = mostrarCuentas(NOMBRE_CUENTAS);

    if(ret != TODO_OK)
        return ret;

    ret = mostrarTransferencias(NOMBRE_TRANSF);

    if(ret != TODO_OK)
        return ret;


//    ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
//                                 NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);

//    ***** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO ********/
//
    ret = procesarTransferencias_ALU(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
                                     NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);


    if(ret != TODO_OK)
        return ret;

    puts("\nDespues de actualizar:");

    ret = mostrarCuentas(NOMBRE_CUENTAS);

    if(ret != TODO_OK)
        return ret;

    ret = mostrarTransferencias(NOMBRE_TRANSF);

    //puts("transferencias mergeadas");
    // ret = mostrarTransferencias("transfMerge.dat");

    return ret;
}

// FUNCIONES GENERALES

int procesarTransferencias_ALU
(const char* nombreTransf, char* nombreTransfSentander,
 char* nombreTransfYCBC, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado)
{
    FILE * fpCuentas = fopen(nombreCuentas,"r+b");
    FILE * fpSantanderEstado = fopen(nombreTransfSantanderEstado,"wt");
    FILE * fpYcbcEstado = fopen(nombreTransfYCBCEstado,"wt");
    FILE * fpMerge = fopen("transfMerge.dat","rb");
    FILE * fpTemp = fopen("transfTemp.dat","wb");
    FILE * fpCuentasTemp = fopen("cuentasTemp.dat","wb");


    Lista listaCuentas;
    Lista listaTransferencias;
    Lista listaTransferenciasAux;
    Lista listaTransferenciasActual;

    crearLista_ALU(&listaCuentas);
    crearLista_ALU(&listaTransferencias);


    Cuenta cuenta;
    Transferencia transferencia;
    Transferencia transferenciaAux;
    Cuenta cuentaAux;
    Fecha fechaActual;

    double montoTotal =0;
    char nombreCuenta[51];

    if(!fpCuentas || !fpSantanderEstado || !fpYcbcEstado ||!fpMerge || !fpTemp || !fpCuentasTemp)
    {
        fclose(fpCuentas);
        fclose(fpSantanderEstado);
        fclose(fpYcbcEstado);
        fclose(fpMerge);
        fclose(fpTemp);
        fclose(fpCuentasTemp);
        return ERR_AP_ARCH;
    }

    convertirTxtABinario_ALU(nombreTransfSentander,"Transferencias_Sentander.dat");
    convertirTxtABinario_ALU(nombreTransfYCBC,"Transferencias_YCBC.dat");

    mergeTransfer_alu("Transferencias_Sentander.dat","Transferencias_YCBC.dat","transfMerge1.dat");
    mergeTransfer_alu("transfMerge1.dat",nombreTransf,"transfMerge.dat");


    fread(&cuenta,sizeof(Cuenta),1,fpCuentas);
    while(!feof(fpCuentas))
    {
        insertarEnListaAlFinal_ALU(&listaCuentas,&cuenta,sizeof(Cuenta));
        fread(&cuenta,sizeof(Cuenta),1,fpCuentas);
    }


    fread(&transferencia,sizeof(Transferencia),1,fpMerge);
    while(!feof(fpMerge))
    {
        fechaActual = transferencia.fecha;
        while(!feof(fpMerge) && cmpFechas(&fechaActual,&transferencia.fecha) == 0)
        {
            insertarEnListaAlFinal_ALU(&listaTransferencias,&transferencia,sizeof(Transferencia));
            fread(&transferencia,sizeof(transferencia),1,fpMerge);
        }

        crearLista_ALU(&listaTransferenciasAux);
        crearLista_ALU(&listaTransferenciasActual);

        while(!listaVacia_ALU(&listaTransferencias))
        {
            eliminarDeListaPrimero_ALU(&listaTransferencias,&transferenciaAux,sizeof(Transferencia));
            montoTotal =0;
            if(strcmp(transferenciaAux.bancoDest,"Patagania")==0)

            {
                strncpy(cuentaAux.cuenta,transferenciaAux.cuentaDest,51);
                buscarEnListaDesord_ALU(&listaCuentas,&cuentaAux,sizeof(Cuenta),cmpCuentas_ALU);
                montoTotal=cuentaAux.saldo;
                montoTotal+=transferenciaAux.monto;
                strncpy(nombreCuenta,cuentaAux.cuenta,51);
                insertarEnListaAlFinal_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));

            }
            else if(strcmp(transferenciaAux.bancoOrig,"Patagania") ==0 )
            {
                strncpy(cuentaAux.cuenta,transferenciaAux.cuentaOrig,51);
                buscarEnListaDesord(&listaCuentas,&cuentaAux,sizeof(Cuenta),cmpCuentas_ALU);
                montoTotal=cuentaAux.saldo;
                montoTotal-=transferenciaAux.monto;
                strncpy(nombreCuenta,cuentaAux.cuenta,51);
                insertarEnListaAlFinal_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));

            }
            while(!listaVacia_ALU(&listaTransferencias))
            {
                eliminarDeListaPrimero_ALU(&listaTransferencias,&transferenciaAux,sizeof(transferencia));
                if(strcmp(nombreCuenta,transferenciaAux.cuentaDest) != 0 && strcmp(nombreCuenta,transferenciaAux.cuentaOrig) != 0)
                    insertarEnListaAlFinal_ALU(&listaTransferenciasAux,&transferenciaAux,sizeof(Transferencia));
                else if(strcmp(nombreCuenta,transferenciaAux.cuentaDest) == 0)
                {
                    montoTotal+=transferenciaAux.monto;
                    insertarEnListaAlFinal_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));
                }
                else if(strcmp(nombreCuenta,transferenciaAux.cuentaOrig) ==0)
                {
                    montoTotal-=transferenciaAux.monto;
                    insertarEnListaAlFinal_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));

                }

            }

            if(montoTotal>=0)
            {
                while(!listaVacia_ALU(&listaTransferenciasActual))
                {
                    eliminarDeListaPrimero_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));
                    transferenciaAux.aplicada = 'S';
                    fwrite(&transferenciaAux,sizeof(Transferencia),1,fpTemp);
                    if(strcmp(transferenciaAux.bancoDest,"YCBC")==0 || strcmp(transferenciaAux.bancoOrig,"YCBC")==0)
                    {
                        fprintf(fpYcbcEstado,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n", transferenciaAux.fecha.dia,transferenciaAux.fecha.mes,transferenciaAux.fecha.anio,transferenciaAux.cuentaOrig,transferenciaAux.bancoOrig,transferenciaAux.cuentaDest,transferenciaAux.bancoDest,transferenciaAux.monto,transferenciaAux.aplicada);

                    }
                    if(strcmp(transferenciaAux.bancoDest,"Sentander" )==0 || strcmp(transferenciaAux.bancoOrig,"Sentander")==0)
                    {
                        fprintf(fpSantanderEstado,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n", transferenciaAux.fecha.dia,transferenciaAux.fecha.mes,transferenciaAux.fecha.anio,transferenciaAux.cuentaOrig,transferenciaAux.bancoOrig,transferenciaAux.cuentaDest,transferenciaAux.bancoDest,transferenciaAux.monto,transferenciaAux.aplicada);
                    }

                }

                while(!listaVacia_ALU(&listaTransferenciasAux))
                {
                    eliminarDeListaPrimero_ALU(&listaTransferenciasAux,&transferenciaAux,sizeof(transferencia));
                    insertarEnListaAlFinal_ALU(&listaTransferencias,&transferenciaAux,sizeof(Transferencia));

                }

                cuentaAux.saldo = montoTotal;
                insertarOActualizarEnListaOrd_ALU(&listaCuentas,&cuentaAux,sizeof(Cuenta),cmpCuentas_ALU,actualizarCuentas_ALU);

            }
            else
            {
                while (!listaVacia(&listaTransferenciasAux))
                {
                    eliminarDeListaPrimero_ALU(&listaTransferenciasAux,&transferenciaAux,sizeof(Transferencia));
                    insertarEnListaAlFinal_ALU(&listaTransferencias,&transferenciaAux,sizeof(Transferencia));
                }
                while(!listaVacia(&listaTransferenciasActual))
                {
                    eliminarDeListaPrimero_ALU(&listaTransferenciasActual,&transferenciaAux,sizeof(Transferencia));
                    fwrite(&transferenciaAux,sizeof(Transferencia),1,fpTemp);
                    if(strcmp(transferenciaAux.bancoDest,"YCBC")==0 || strcmp(transferenciaAux.bancoOrig,"YCBC")==0)
                    {
                        fprintf(fpYcbcEstado,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n", transferenciaAux.fecha.dia,transferenciaAux.fecha.mes,transferenciaAux.fecha.anio,transferenciaAux.cuentaOrig,transferenciaAux.bancoOrig,transferenciaAux.cuentaDest,transferenciaAux.bancoDest,transferenciaAux.monto,transferenciaAux.aplicada);

                    }
                    if(strcmp(transferenciaAux.bancoDest,"Sentander" )==0 || strcmp(transferenciaAux.bancoOrig,"Sentander")==0)
                    {
                        fprintf(fpSantanderEstado,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n", transferenciaAux.fecha.dia,transferenciaAux.fecha.mes,transferenciaAux.fecha.anio,transferenciaAux.cuentaOrig,transferenciaAux.bancoOrig,transferenciaAux.cuentaDest,transferenciaAux.bancoDest,transferenciaAux.monto,transferenciaAux.aplicada);
                    }
                }

            }


        }

    }

    while(!listaVacia_ALU(&listaCuentas))
    {
        eliminarDeListaPrimero_ALU(&listaCuentas,&cuenta,sizeof(Cuenta));
        fwrite(&cuenta,sizeof(Cuenta),1,fpCuentasTemp);
    }

    vaciarLista_ALU(&listaCuentas);
    vaciarLista_ALU(&listaTransferencias);
    vaciarLista_ALU(&listaTransferenciasAux);



    fclose(fpCuentas);
    fclose(fpSantanderEstado);
    fclose(fpTemp);
    fclose(fpYcbcEstado);
    fclose(fpMerge);
    fclose(fpCuentasTemp);

    remove(nombreTransf);
    rename("transfTemp.dat",nombreTransf);

    remove(nombreCuentas);
    rename("cuentasTemp.dat",nombreCuentas);


    return TODO_OK;
}

int convertirTxtABinario_ALU(const char * nombreTransTxt, const char * nombreTransBinario)
{
    FILE * fpTxt = fopen(nombreTransTxt,"rt");
    FILE * fpBin = fopen(nombreTransBinario,"wb");
    Transferencia transferencia;
    char linea[300];

    if(!fpTxt || !fpBin)
    {
        fclose(fpBin);
        fclose(fpTxt);

        return ERR_AP_ARCH;
    }
    // para leer la linea con los titulos
    fgets(linea,300,fpTxt);
    while(fgets(linea,300,fpTxt))
    {
        parsearTransferencia_ALU(linea,&transferencia);
        fwrite(&transferencia,sizeof(Transferencia),1,fpBin);
    }

    fclose(fpTxt);
    fclose(fpBin);
    return TODO_OK;
}

int parsearTransferencia_ALU(char *linea,Transferencia * transferencia)
{
    char * aux = strchr(linea,'\n');
    if(!aux)
    {
        return ERR_LINEA_LARGA;
    }

    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%lf",&transferencia->monto);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strncpy(transferencia->bancoDest,aux+1,51);


    *aux = '\0';
    aux =strrchr(linea,'|');
    strncpy(transferencia->cuentaDest,aux+1,51);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strncpy(transferencia->bancoOrig,aux+1,51);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strncpy(transferencia->cuentaOrig,aux+1,51);

    *aux = '\0';
    sscanf(linea,"%d-%d-%d",&transferencia->fecha.dia,&transferencia->fecha.mes,&transferencia->fecha.anio);
    transferencia->aplicada = 'N';

    return TODO_OK;
}

int mergeTransfer_alu(const char * nombreTrans1, const char * nombreTrans2,const char * nombreMerge)
{
    FILE * fp1 = fopen(nombreTrans1,"rb");
    FILE * fp2 = fopen(nombreTrans2,"rb");
    FILE * fp3 = fopen(nombreMerge,"wb");
    int cmp ;

    Transferencia transferencia1;

    Transferencia transferencia2;

    if(!fp1 || !fp2|| !fp3)
    {
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        return ERR_AP_ARCH;
    }

    fread(&transferencia1,sizeof(Transferencia),1,fp1);
    fread(&transferencia2,sizeof(Transferencia),1,fp2);

    while(!feof(fp1) && !feof(fp2))
    {
        cmp = cmpFechas(&transferencia1.fecha,&transferencia2.fecha);

        // si la fecha de la transferencia 1 no tiene transferencias en la 2
        if(cmp < 0)
        {
            fwrite(&transferencia1,sizeof(Transferencia),1,fp3);
            fread(&transferencia1,sizeof(Transferencia),1,fp1);
        }

        // si la fecha de la transferencia 2 es nueva
        if(cmp >0)
        {
            fwrite(&transferencia2,sizeof(Transferencia),1,fp3);
            fread(&transferencia2,sizeof(Transferencia),1,fp2);
        }

        // las fechas de t1 y t2 son iguales
        if(cmp ==0 )
        {
            fwrite(&transferencia1,sizeof(Transferencia),1,fp3);
            fwrite(&transferencia2,sizeof(Transferencia),1,fp3);
            fread(&transferencia1,sizeof(Transferencia),1,fp1);
            fread(&transferencia2,sizeof(Transferencia),1,fp2);
        }
    }

    while(!feof(fp1))
    {
        fwrite(&transferencia1,sizeof(Transferencia),1,fp3);
        fread(&transferencia1,sizeof(Transferencia),1,fp1);
    }
    while(!feof(fp2))
    {
        fwrite(&transferencia2,sizeof(Transferencia),1,fp3);
        fread(&transferencia2,sizeof(Transferencia),1,fp2);

    }


    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return TODO_OK;
}


// FUNCIONES PUNTERO
int cmpCuentas_ALU(const void *d1, const void *d2)
{
    const Cuenta * c1 = (const Cuenta *)d1;
    const Cuenta * c2 = (const Cuenta * )d2;

    return strcmp(c1->cuenta,c2->cuenta);
}
void actualizarCuentas_ALU(void * actualizado, const void * actualizador)
{

    Cuenta * c1 = (Cuenta* )actualizado;
    const Cuenta * c2 = (const Cuenta *)actualizador;

    c1->saldo = c2->saldo;
}

// FUNCIONES LISTA
Nodo * crearNodo(const void * dato, size_t tamDato)
{
    Nodo * nue =(Nodo *)calloc(1,sizeof(Nodo));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;
    return nue;

}
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista *l)
{
    Nodo * nae ;
    Nodo * act =*l;

    while(act)
    {
        nae =act;
        act =nae->sig;
        free(nae->dato);
        free(nae);


    }


}

int listaLlena_ALU(const Lista *l, size_t tamDato)
{
    Nodo * nue = (Nodo*)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nue);
    free(dato);
    return !nue || !dato;

}
int listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaAlFinal_ALU(Lista *l, const void *dato, size_t tamDato)
{

    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_LISTA;

    while((*l))
        l = &(*l)->sig;

    nue->sig = *l;
    *l = nue;

    return TODO_OK;
}
int eliminarDeListaPrimero_ALU(Lista *l, void *dato, size_t tamDato)
{
    if(!*l)
        return 0;
    Nodo * act = *l;
    Nodo *nae = *l;


    memcpy(dato,nae->dato,MIN(tamDato,nae->tamElem));

    // *l = nae->sig;

    act =nae->sig;
    *l =act;
    free(nae->dato);
    free(nae);



    return TODO_OK;
}

int buscarEnListaDesord_ALU(const Lista *l,void *dato,size_t tamDato, Cmp cmp)
{
    int resultado;
    const Lista * act = l;

    while(*act)
    {
        resultado = cmp(dato,(*act)->dato);

        if(resultado ==0)
        {
            memcpy(dato,(*act)->dato,MIN(tamDato,(*act)->tamElem));
            return 1;
        }
        (act) =&(*act)->sig;
    }

    return 0;

}
int insertarOActualizarEnListaOrd_ALU(Lista *l, void *dato,size_t tamDato,Cmp cmp,Actualizar actualizar)
{
    int resultado;
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_LISTA;

    while(*l && cmp(dato,(*l)->dato)>0)
        l =&(*l)->sig;

    resultado  = cmp(dato,(*l)->dato);
    if(resultado == 0 && *l)
        if(actualizar)
        {
            actualizar((*l)->dato,dato);
            free(nue->dato);
            free(nue);
            return 1;
        }

    nue->sig =*l;
    *l = nue;

    return TODO_OK;
}
