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

int procesarTransferencias_ALU
(const char* nombreTransf, char* nombreTransfSentander,
 char* nombreTransfYCBC, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado);
void txtAbin(char* nombreArchivoTransferencias);

void printCuenta( const void *c )
{
    printf( "%s\t%08u\t%010.2f\n", ((Cuenta*)c)->cuenta, ((Cuenta*)c)->dniTitular, ((Cuenta*)c)->saldo );
}
void printTransf( const void *t )
{
    printf("%02d-%02d-%04d     %-33s%-17s%-33s%-17s%010.2lf%4c\n", ((Transferencia*)t)->fecha.dia, ((Transferencia*)t)->fecha.mes, ((Transferencia*)t)->fecha.anio,
           ((Transferencia*)t)->cuentaOrig, ((Transferencia*)t)->bancoOrig, ((Transferencia*)t)->cuentaDest,
           ((Transferencia*)t)->bancoDest, ((Transferencia*)t)->monto, ((Transferencia*)t)->aplicada );
}

void crearLista_alu(Lista *pl);
int insertarEnListaAlFinal_alu(Lista *pl, const void* dato, size_t tamElem);
int buscarEnListaOrd_alu(const Lista *pl, void* dato, size_t tamElem, Cmp cmp);
int insertarOActualizarEnListaOrd_alu(Lista *pl, void* dato, size_t tamElem, Cmp cmp, Actualizar actualizar);
int eliminarDeListaPrimero_alu(Lista *pl, void* dato, size_t tamElem);
void recorrerLista_alu(Lista *pl, Accion accion, void* datosAccion);
int listaVacia_alu(const Lista *pl);

int convertirTxtABinario_alu(const char* nomArchTransTxt, const char* nomArchTransBin);
int mergeTransfer_alu(const char* nomTrans1, const char* nomTrans2, const char* nomTransMerge);
int parseoTrans_alu(char *cad, Transferencia* reg);

int compararCuentas_alu(const void* elem1, const void* elem2);
int compararTrans_alu(const void* elem1, const void* elem2);
void actualizarCuentas_alu(void* actualizado, const void* actualizador);
void mostrarCuentasLista_alu(void* dato, void* datosAccion);
void mostrarTransLista_alu(void* dato, void* datosAccion);
int mostrarTransferencias_alu(const char* nomArchTrans);

int strcmp_alu(const char* cad1, const char* cad2);
char* strrchr_alu(char* cad, const char c);
char* strncpy_alu(char* dest, const char* origen, const size_t tamElem);

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


    //ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
    //                           NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);

    /****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/

    ret = procesarTransferencias_ALU(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
                                     NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);


    if(ret != TODO_OK)
        return ret;

    puts("\nDespues de actualizar:");

    ret = mostrarCuentas(NOMBRE_CUENTAS);

    if(ret != TODO_OK)
        return ret;

    ret = mostrarTransferencias(NOMBRE_TRANSF);
    //ret = mostrarTransferencias("transfMerge.dat");

    return ret;
}

int procesarTransferencias_ALU
(const char* nombreTransf, char* nombreTransfSentander,
 char* nombreTransfYCBC, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado)
{
    convertirTxtABinario_alu(nombreTransfSentander,"Transferencias_Sentander.dat");
    convertirTxtABinario_alu(nombreTransfYCBC,"Transferencias_YCBC.dat");

    mergeTransfer_alu("Transferencias_YCBC.dat","Transferencias_Sentander.dat","mergeYCBC_Sentender.dat");
    mergeTransfer_alu(nombreTransf,"mergeYCBC_Sentender.dat","merge.temp");
    remove(nombreTransf);
    rename("merge.temp",nombreTransf);
    mostrarTransferencias_alu(nombreTransf);

    FILE *pfCuentas = fopen(nombreCuentas,"r+b");
    FILE *pfTransferencias = fopen(nombreTransf,"rb");
    FILE *pfTransTemp = fopen("filetemp.dat","wb");
    FILE *pfCuentasTemp = fopen("cuentasTemp.dat","wb");
    FILE *pfYCBCTemp = fopen("YCBC.temp","wt");
    FILE *pfSentanderTemp = fopen("Sentander.temp","wt");
    if(!pfCuentas || !pfTransferencias ||
            !pfTransTemp||!pfCuentasTemp || !pfYCBCTemp || !pfSentanderTemp)
    {
        fclose(pfCuentas);
        fclose(pfTransTemp);
        fclose(pfCuentasTemp);
        fclose(pfTransferencias);
        fclose(pfYCBCTemp);
        fclose(pfSentanderTemp);
        return 0;
    }
    Cuenta regCuenta;
    Transferencia regTrans;
    Fecha fechaActual;
    Lista listaCuentas;
    Lista listaTransferecias;
    crearLista_alu(&listaCuentas);
    crearLista_alu(&listaTransferecias);

    fread(&regCuenta,sizeof(Cuenta),1,pfCuentas);
    while(!feof(pfCuentas))
    {
        insertarEnListaAlFinal_alu(&listaCuentas,&regCuenta,sizeof(Cuenta));
        fread(&regCuenta,sizeof(Cuenta),1,pfCuentas);
    }

    fread(&regTrans,sizeof(Transferencia),1,pfTransferencias);
    while(!feof(pfTransferencias))
    {
        fechaActual = regTrans.fecha;
        while(!feof(pfTransferencias) && (regTrans.fecha.dia == fechaActual.dia))
        {
            insertarEnListaAlFinal_alu(&listaTransferecias,&regTrans,sizeof(Transferencia));
            fread(&regTrans,sizeof(Transferencia),1,pfTransferencias);
        }
        Transferencia regTransAux;
        Cuenta regCuentaAux;
        Lista listaTransAux;
        Lista listaTransActual;
        crearLista_alu(&listaTransAux);
        crearLista_alu(&listaTransActual);


        recorrerLista_alu(&listaCuentas,mostrarCuentasLista_alu,NULL);
        puts("");

        recorrerLista_alu(&listaTransferecias,mostrarTransLista_alu,NULL);
        puts("");


        while(!listaVacia_alu(&listaTransferecias))
        {
            double montoTotal = 0;
            char cuenta[51];
            eliminarDeListaPrimero_alu(&listaTransferecias,&regTransAux,sizeof(Transferencia));

            if(strcmp_alu(regTransAux.bancoDest,"Patagania") == 0)
            {
                strncpy_alu(regCuentaAux.cuenta,regTransAux.cuentaDest,51);
                buscarEnListaOrd_alu(&listaCuentas,&regCuentaAux,sizeof(Cuenta),compararCuentas_alu);
                montoTotal = regCuentaAux.saldo;
                montoTotal += regTransAux.monto;
                strncpy_alu(cuenta,regTransAux.cuentaDest,51);
                insertarEnListaAlFinal_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
            }
            if(strcmp_alu(regTransAux.bancoOrig,"Patagania") == 0)
            {
                strncpy_alu(regCuentaAux.cuenta,regTransAux.cuentaOrig,51);
                buscarEnListaOrd_alu(&listaCuentas,&regCuentaAux,sizeof(Cuenta),compararCuentas_alu);
                montoTotal = regCuentaAux.saldo;
                montoTotal-=regTransAux.monto;
                strncpy_alu(cuenta,regTransAux.cuentaOrig,51);
                insertarEnListaAlFinal_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
            }

            while(!listaVacia_alu(&listaTransferecias))
            {
                eliminarDeListaPrimero_alu(&listaTransferecias,&regTransAux,sizeof(Transferencia));
                if(strcmp_alu(regTransAux.cuentaDest,cuenta) != 0 && strcmp_alu(regTransAux.cuentaOrig,cuenta) != 0)
                    insertarEnListaAlFinal_alu(&listaTransAux,&regTransAux,sizeof(Transferencia));

                else if(strcmp_alu(regTransAux.cuentaDest,cuenta) == 0)
                {
                    montoTotal+=regTransAux.monto;
                    insertarEnListaAlFinal_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
                }
                else if(strcmp_alu(regTransAux.cuentaOrig,cuenta) == 0)
                {
                    montoTotal-=regTransAux.monto;
                    insertarEnListaAlFinal_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
                }
            }

            if(montoTotal >= 0)
            {
                while(!listaVacia_alu(&listaTransActual))
                {
                    eliminarDeListaPrimero_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
                    regTransAux.aplicada = 'S';
                    fwrite(&regTransAux,sizeof(Transferencia),1,pfTransTemp);
                    if(strcmp_alu(regTransAux.bancoDest,"YCBC") == 0
                       || strcmp_alu(regTransAux.bancoOrig,"YCBC") == 0)
                    {
                        fprintf(pfYCBCTemp,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n",regTransAux.fecha.dia,
                                regTransAux.fecha.mes,regTransAux.fecha.anio,regTransAux.cuentaOrig,regTransAux.bancoOrig,
                                regTransAux.cuentaDest,regTransAux.bancoDest,regTransAux.monto,regTransAux.aplicada);
                    }
                    if(strcmp_alu(regTransAux.bancoDest,"Sentander") == 0
                            || strcmp_alu(regTransAux.bancoOrig,"Sentander") == 0)
                    {
                        fprintf(pfSentanderTemp,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n",regTransAux.fecha.dia,
                                regTransAux.fecha.mes,regTransAux.fecha.anio,regTransAux.cuentaOrig,regTransAux.bancoOrig,
                                regTransAux.cuentaDest,regTransAux.bancoDest,regTransAux.monto,regTransAux.aplicada);
                    }
                }

                while(!listaVacia_alu(&listaTransAux))
                {
                    eliminarDeListaPrimero_alu(&listaTransAux,&regTransAux,sizeof(Transferencia));
                    insertarEnListaAlFinal_alu(&listaTransferecias,&regTransAux,sizeof(Transferencia));
                }

                regCuentaAux.saldo = montoTotal;
                insertarOActualizarEnListaOrd_alu(&listaCuentas,&regCuentaAux,sizeof(Cuenta),
                                                  compararCuentas_alu,actualizarCuentas_alu);
            }
            else
            {
                while(!listaVacia_alu(&listaTransAux))
                {
                    eliminarDeListaPrimero_alu(&listaTransAux,&regTransAux,sizeof(Transferencia));
                    insertarEnListaAlFinal_alu(&listaTransferecias,&regTransAux,sizeof(Transferencia));
                }
            }

            while(!listaVacia_alu(&listaTransActual))
            {
                eliminarDeListaPrimero_alu(&listaTransActual,&regTransAux,sizeof(Transferencia));
                fwrite(&regTransAux,sizeof(Transferencia),1,pfTransTemp);
                if(strcmp_alu(regTransAux.bancoDest,"YCBC") == 0
                   || strcmp_alu(regTransAux.bancoOrig,"YCBC") == 0)
                {
                    fprintf(pfYCBCTemp,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n",regTransAux.fecha.dia,
                            regTransAux.fecha.mes,regTransAux.fecha.anio,regTransAux.cuentaOrig,regTransAux.bancoOrig,
                            regTransAux.cuentaDest,regTransAux.bancoDest,regTransAux.monto,regTransAux.aplicada);
                }
                if(strcmp_alu(regTransAux.bancoDest,"Sentander") == 0
                        || strcmp_alu(regTransAux.bancoOrig,"Sentander") == 0)
                {
                    fprintf(pfSentanderTemp,"%d-%d-%d|%s|%s|%s|%s|%.2f|%c\n",regTransAux.fecha.dia,
                            regTransAux.fecha.mes,regTransAux.fecha.anio,regTransAux.cuentaOrig,regTransAux.bancoOrig,
                            regTransAux.cuentaDest,regTransAux.bancoDest,regTransAux.monto,regTransAux.aplicada);
                }
            }
        }
    }

    while(!listaVacia_alu(&listaCuentas))
    {
        eliminarDeListaPrimero_alu(&listaCuentas,&regCuenta,sizeof(Cuenta));
        fwrite(&regCuenta,sizeof(Cuenta),1,pfCuentasTemp);
    }

    fclose(pfCuentas);
    fclose(pfTransTemp);
    fclose(pfCuentasTemp);
    fclose(pfTransferencias);
    fclose(pfYCBCTemp);
    fclose(pfSentanderTemp);

    remove(nombreTransf);
    rename("filetemp.dat",nombreTransf);

    remove(nombreCuentas);
    rename("cuentasTemp.dat",nombreCuentas);

    remove(nombreTransfSantanderEstado);
    remove(nombreTransfYCBCEstado);

    rename("Sentander.temp",nombreTransfSantanderEstado);
    rename("YCBC.temp",nombreTransfYCBCEstado);

    return TODO_OK;
}

int mostrarTransferencias_alu(const char* nomArchTrans)
{
    FILE *pf = fopen(nomArchTrans,"rb");
    if(!pf)
    {
        fclose(pf);
        return 0;
    }

    Transferencia regTrans;

    fread(&regTrans,sizeof(Transferencia),1,pf);
    puts("Transferencias Patagania");
    puts("==============================================");
    while(!feof(pf))
    {
        printf("%02d-%02d-%02d %-31s %-21s %-31s %-21s %.2f %1c\n",regTrans.fecha.dia,regTrans.fecha.mes,
               regTrans.fecha.anio,regTrans.cuentaOrig,regTrans.bancoOrig,regTrans.cuentaDest,
               regTrans.bancoDest,regTrans.monto,regTrans.aplicada);
        fread(&regTrans,sizeof(Transferencia),1,pf);
    }

    fclose(pf);
    return 1;
}

int convertirTxtABinario_alu(const char* nomArchTransTxt, const char* nomArchTransBin)
{
    FILE *pfTxt = fopen(nomArchTransTxt,"rt");
    FILE *pfBin = fopen(nomArchTransBin,"wb");
    if(!pfTxt || !pfBin)
    {
        fclose(pfTxt);
        fclose(pfBin);
        return 0;
    }

    char cad[512];
    Transferencia regTrans;

    while(fgets(cad,sizeof(cad),pfTxt))
    {
        if(*cad - '0' != 1)
            continue;

        parseoTrans_alu(cad,&regTrans);
        fwrite(&regTrans,sizeof(Transferencia),1,pfBin);
    }


    fclose(pfTxt);
    fclose(pfBin);

    return 1;
}

int parseoTrans_alu(char *cad, Transferencia* reg)
{
    char *aux = strrchr_alu(cad,'\n');
    aux++;

    *aux = '\0';

    aux = strrchr_alu(cad,'|');
    aux++;
    sscanf(aux,"%lf",&reg->monto);
    aux--;
    *aux = '\0';

    aux = strrchr_alu(cad,'|');
    aux++;
    strncpy_alu(reg->bancoDest,aux,51);
    aux--;
    *aux = '\0';

    aux = strrchr_alu(cad,'|');
    aux++;
    strncpy_alu(reg->cuentaDest,aux,51);
    aux--;
    *aux = '\0';

    aux = strrchr_alu(cad,'|');
    aux++;
    strncpy_alu(reg->bancoOrig,aux,51);
    aux--;
    *aux = '\0';

    aux = strrchr_alu(cad,'|');
    aux++;
    strncpy_alu(reg->cuentaOrig,aux,51);
    aux--;
    *aux = '\0';

    sscanf(cad,"%d-%d-%d",&reg->fecha.dia,&reg->fecha.mes,&reg->fecha.anio);

    reg->aplicada = 'N';

    return 1;
}

int mergeTransfer_alu(const char* nomTrans1, const char* nomTrans2, const char* nomTransMerge)
{
    FILE *pfArch1 = fopen(nomTrans1,"rb");
    FILE *pfArch2 = fopen(nomTrans2,"rb");
    FILE *pfArchMerge = fopen(nomTransMerge,"wb");
    if(!pfArch1 || !pfArch2 || !pfArchMerge)
    {
        fclose(pfArch1);
        fclose(pfArch2);
        fclose(pfArchMerge);
        return 0;
    }

    Transferencia regTrans1;
    Transferencia regTrans2;

    fread(&regTrans1,sizeof(Transferencia),1,pfArch1);
    fread(&regTrans2,sizeof(Transferencia),1,pfArch2);

    while(!feof(pfArch1) && !feof(pfArch2))
    {
        int comp = regTrans1.fecha.dia-regTrans2.fecha.dia;

        if(comp < 0)
        {
            fwrite(&regTrans1,sizeof(Transferencia),1,pfArchMerge);
            fread(&regTrans1,sizeof(Transferencia),1,pfArch1);
        }

        if(comp > 0)
        {
            fwrite(&regTrans2,sizeof(Transferencia),1,pfArchMerge);
            fread(&regTrans2,sizeof(Transferencia),1,pfArch2);
        }

        if(comp == 0)
        {
            fwrite(&regTrans1,sizeof(Transferencia),1,pfArchMerge);
            fwrite(&regTrans2,sizeof(Transferencia),1,pfArchMerge);
            fread(&regTrans1,sizeof(Transferencia),1,pfArch1);
            fread(&regTrans2,sizeof(Transferencia),1,pfArch2);
        }
    }

    while(!feof(pfArch1))
    {
        fwrite(&regTrans1,sizeof(Transferencia),1,pfArchMerge);
        fread(&regTrans1,sizeof(Transferencia),1,pfArch1);
    }

    while(!feof(pfArch2))
    {
        fwrite(&regTrans2,sizeof(Transferencia),1,pfArchMerge);
        fread(&regTrans2,sizeof(Transferencia),1,pfArch2);
    }

    fclose(pfArch1);
    fclose(pfArch2);
    fclose(pfArchMerge);

    return 1;
}

int compararCuentas_alu(const void* elem1, const void* elem2)
{
    Cuenta* cuenta1 = (Cuenta*)elem1;
    Cuenta* cuenta2 = (Cuenta*)elem2;

    return strcmp_alu(cuenta1->cuenta,cuenta2->cuenta);
}

int compararTrans_alu(const void* elem1, const void* elem2)
{
    Transferencia* trans1 = (Transferencia*)elem1;
    Transferencia* trans2 = (Transferencia*)elem2;

    return trans1->fecha.dia - trans2->fecha.dia;
}

void actualizarCuentas_alu(void* actualizado, const void* actualizador)
{
    Cuenta* cuentaActualizado = (Cuenta*)actualizado;
    Cuenta* cuentaActualizador = (Cuenta*)actualizador;

    cuentaActualizado->saldo=cuentaActualizador->saldo;
}

void mostrarCuentasLista_alu(void* dato, void* datosAccion)
{
    Cuenta* cuentaDato = (Cuenta*)dato;

    printf("%s %d %.2f\n",cuentaDato->cuenta,cuentaDato->dniTitular,cuentaDato->saldo);
}

void mostrarTransLista_alu(void* dato, void* datosAccion)
{
    Transferencia* transDato = (Transferencia*)dato;

    printf("%d/%d/%d %s %s   %s %s   %.2f   %c\n",transDato->fecha.dia,transDato->fecha.mes,transDato->fecha.anio,
           transDato->cuentaOrig,transDato->bancoOrig,transDato->cuentaDest,transDato->bancoDest,
           transDato->monto,transDato->aplicada);
}

void crearLista_alu(Lista *pl)
{
    *pl = NULL;
}
int insertarEnListaAlFinal_alu(Lista *pl, const void* dato, size_t tamElem)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->dato = malloc(tamElem);

    if(!nue || !nue->dato)
    {
        free(nue->dato);
        free(nue);
        return 1;
    }

    memcpy(nue->dato,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->sig = NULL;
        *pl = nue;
        return 1;
    }

    while(*pl)
        pl = &(*pl)->sig;

    nue->sig = NULL;
    *pl = nue;

    return 1;
}
int buscarEnListaOrd_alu(const Lista *pl, void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return 0;

    while(*pl)
    {
        int comp = cmp((*pl)->dato,dato);
        if(comp == 0)
        {
            memcpy(dato,(*pl)->dato,MIN(tamElem,(*pl)->tamElem));
            return 1;
        }

        pl = &(*pl)->sig;
    }

    return 0;
}
int insertarOActualizarEnListaOrd_alu(Lista *pl, void* dato, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->dato = malloc(tamElem);

    if(!nue || !nue->dato)
    {
        free(nue->dato);
        free(nue);
        return 1;
    }

    memcpy(nue->dato,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->sig = NULL;
        *pl = nue;
        return 1;
    }

    while(*pl)
    {
        int comp = cmp((*pl)->dato,dato);

        if(comp == 0)
        {
            actualizar((*pl)->dato,dato);
            return 1;
        }

        if(comp > 0)
        {
            nue->sig = *pl;
            return 1;
        }

        pl = &(*pl)->sig;
    }

    nue->sig = NULL;
    *pl = nue;

    return 1;
}
int eliminarDeListaPrimero_alu(Lista *pl, void* dato, size_t tamElem)
{
    if(!*pl)
        return 0;

    Nodo *nae = *pl;

    memcpy(dato,nae->dato,MIN(tamElem,nae->tamElem));

    *pl = nae->sig;

    free(nae->dato);
    free(nae);

    return 1;
}

void recorrerLista_alu(Lista *pl, Accion accion, void* datosAccion)
{
    while(*pl)
    {
        accion((*pl)->dato,datosAccion);
        pl = &(*pl)->sig;
    }
}

int listaVacia_alu(const Lista *pl)
{
    return *pl == NULL;
}

int strcmp_alu(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2)
    {
        if((*cad1 - *cad2) != 0)
            return *cad1-*cad2;
        cad1++;
        cad2++;
    }

    return *cad1-*cad2;
}
char* strrchr_alu(char* cad, const char c)
{
    int i = 0;

    while(*cad)
    {
        cad++;
        i++;
    }

    for(; i > 0 ; i--, cad--)
    {
        if((*cad) == c)
            return cad;
    }

    return NULL;
}

char* strncpy_alu(char* dest, const char* origen, const size_t tamElem)
{
    for(int i = 0; i < tamElem; i++)
    {
        *dest = *origen;
        dest++;
        origen++;
    }

    return dest;
}

