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


int parseTransf (char *read, Transferencia *transfRead);
int escribirArchLista_Bin(const char *nombre, Lista *lista, unsigned tamDato);

int cmpTransferencia(const void *first, const void *second)
{
    //Se hace comparacion segun la fecha
    Fecha stFirst  = ((Transferencia*)(first))->fecha ;
    Fecha ndSecond = ((Transferencia*)(second))->fecha;
    //int rdo = cmpFechas( &stFirst , &ndSecond );

    return cmpFechas( &stFirst, &ndSecond );
}
int cmpCuenta(const void *first, const void *second)
{
    return strcmp( ((Cuenta*)first)->cuenta, ((Cuenta*)(second))->cuenta);
}

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


int ordenarLista(Lista* pl, Cmp cmp)
{
    Lista lOrd = NULL;
    Lista *plOrd;
    Nodo *nodo;

    while(*pl)
    {
        nodo = *pl;
        *pl = nodo->sig;
        plOrd = &lOrd;

        while(*plOrd && cmp(nodo->dato, (*plOrd)->dato) > 0)
        {
            plOrd = &(*plOrd)->sig;
        }

        nodo->sig = *plOrd;
        *plOrd = nodo;
    }
    *pl= lOrd;

    return TODO_OK;
}
void recorrer(Lista *lista, void(*accion)(const void *))
{
    while(*lista)
    {
        accion((*lista)->dato);
        lista = &(*lista)->sig;
    }
}

int actualizarEstados( Cuenta *cuentaExito, Lista *listaActividad )
{
    Transferencia transfActual;

    if( !listaActividad )
    {
        return ERROR;
    }
    while(*listaActividad)
    {
        transfActual = *((Transferencia*)(*listaActividad)->dato);
        int cmpExtraccion = strcmp( cuentaExito->cuenta, transfActual.cuentaOrig );
        int cmpDeposito = strcmp( cuentaExito->cuenta, transfActual.cuentaDest );

        if( cmpExtraccion == 0 || cmpDeposito == 0 ) ///Si la cuenta se encontro en algun movimiento realizado
        {
            (*((Transferencia*)(*listaActividad)->dato)).aplicada = 'S';
            //Trabajo directamente en la lista de Actividades y seteo el succesfull
            //insertarEnListaOrd( transfFallidas, &transfActual, sizeof(Transferencia), cmpTransferencia);
        }
        listaActividad = &(*listaActividad)->sig;
    }

    return TODO_OK;
}
int reemplazoCuentaYstatus(Lista *toChange, Lista *backup, Lista *listaActividad)
{
    Cuenta accBackup;
    Cuenta accActual;
    int status = 0;
    if( !backup )
    {
        return ERROR;
    }
    while(*toChange)
    {
        accActual = *((Cuenta*)(*toChange)->dato);
        if( accActual.saldo < 0 )
        {
            strcpy( accBackup.cuenta, accActual.cuenta);
            buscarEnListaOrd( backup, &accBackup, sizeof(Cuenta), cmpCuenta); //Obtengo el dato de la lista original

            eliminarDeListaOrdPorValor( toChange, &accActual, sizeof(Cuenta), cmpCuenta);
            insertarEnListaOrd(toChange,&accBackup, sizeof(Cuenta), cmpCuenta);


            status--;
        }
        else
        {
            actualizarEstados( &accActual, listaActividad );
        }

        toChange = &(*toChange)->sig;
    }

    return status == 0? TODO_OK : status ;
}



void actCuentaMonto (void* actualizado, const void* actualizador)
{
///Primer datito es donde se van a alojar los cambios, debe ser la primera coincidencia y el segundo parametro es lo repetido (debe juntarse con lo primero)
    ((Cuenta*)actualizado)->saldo = ((Cuenta*)actualizador)->saldo;
}
int sinSaldosNegativos(const void* elem)
{
    return (((Cuenta*)elem)->saldo < 0) ;
}
void copiarLista(void* dato, void* listaDestino)
{
    insertarEnListaAlFinal((Lista *)listaDestino, dato, sizeof(Cuenta));
}

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

    /*
        ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
    		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
    */
    /****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/

    ret = procesarTransferencias_alu(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
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

int procesarTransferencias_alu
(const char* nombreTransf, const char* nombreTransfSentander,
 const char* nombreTransfYCBC, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado)
{
    printf("********************************Transferencias Mergeadas:********************************\n");

    convertirTxtABinario( nombreTransfSentander, "Transferencias_Sentander.dat" );
    convertirTxtABinario( nombreTransfYCBC, "Transferencias_YCBC.dat" );

    int statusRdo = mergeTransfer_alu( "Transferencias_Sentander.dat", "Transferencias_YCBC.dat", nombreTransf );

    remove("Transferencias_Sentander.dat");
    remove("Transferencias_YCBC.dat");

    if( statusRdo != TODO_OK )
    {
        return statusRdo;
    }

    printf("*****************************************************************************************\n");

    printf("\nLista recien cargada del archivo cuentas\n");

    Cuenta readCuenta;
    Transferencia movimiento;

    Lista listaCuentas;
    Lista listaCuentas_final; //utilizada para backup
    Lista listaActividad;

    crearLista(&listaCuentas);
    crearLista(&listaCuentas_final);

    /** COLOCO CUENTAS EN UNA LISTA A LA CUAL UPGRATEAR **/
    /*****************************************************/
    FILE *binCuentas = fopen(nombreCuentas, "rb");
    if(!binCuentas)
    {
        vaciarLista( &listaCuentas); //Libero el espacio solicitado de memoria
        vaciarLista( &listaCuentas_final);
        return ERR_AP_ARCH;
    }
    fread( &readCuenta, 1, sizeof(Cuenta), binCuentas );
    while( !feof(binCuentas) )
    {
        insertarEnListaAlFinal(&listaCuentas, &readCuenta, sizeof(Cuenta) );
        insertarEnListaAlFinal(&listaCuentas_final, &readCuenta, sizeof(Cuenta) );
        fread(&readCuenta, 1, sizeof(Cuenta),binCuentas );
    }
    fclose(binCuentas);
    recorrer(&listaCuentas, printCuenta); //Para comprobar que todo se ingreso correctamente
    /** FIN DE LISTACUENTAS **/


    /** INICIO DE TRABAJO EN BLOQUES **/
    FILE *binUpdate = fopen( "Transfer_Merge.dat", "rb"); //Abro el archivo mergeado
    if(!binUpdate)
    {
        vaciarLista( &listaCuentas); //Libero el espacio en memoria
        vaciarLista( &listaCuentas_final);
        return ERR_AP_ARCH;
    }
    FILE *estadosUpdate = fopen( "transfEstados.dat", "wb");
    if(!binUpdate)
    {
        vaciarLista( &listaCuentas); //Libero el espacio en memoria
        vaciarLista( &listaCuentas_final);
        fclose(binUpdate);
        return ERR_AP_ARCH;
    }

    puts("");
    crearLista(&listaActividad); //Solo si pude abrir el archivo solicito mas espacio a memoria
    fread( &movimiento, 1, sizeof(Transferencia), binUpdate );
    Fecha fechaAct;
    while( !feof(binUpdate) )
    {

        fechaAct = movimiento.fecha;
        while( !feof(binUpdate) && cmpFechas( &fechaAct, &movimiento.fecha ) == 0 )
        {
            ///Almaceno el primer valor de la fecha
            insertarEnListaAlFinal(&listaActividad, &movimiento, sizeof(Transferencia) );
            ///Analizo segun el movimiento
            if( strcmp( movimiento.bancoOrig, BCO_PATAGANIA )== 0 )  //Analizo si la transaccion se realizo DESDE cuentas Patagania --- EXTRACCIONES
            {
                strcpy( readCuenta.cuenta, movimiento.cuentaOrig );
                buscarEnListaOrd( &listaCuentas, &readCuenta, sizeof(Cuenta), cmpCuenta );  //Busco la cuenta por la que se realizo la extraccion
                readCuenta.saldo = readCuenta.saldo - movimiento.monto;
                insertarOActualizarEnListaOrd( &listaCuentas, &readCuenta, sizeof(Cuenta), cmpCuenta, actCuentaMonto );
            }
            else if( strcmp( movimiento.bancoDest, BCO_PATAGANIA )== 0 )  //DEPOSITOS
            {
                strcpy( readCuenta.cuenta, movimiento.cuentaDest );
                buscarEnListaOrd( &listaCuentas, &readCuenta, sizeof(Cuenta), cmpCuenta );
                readCuenta.saldo += movimiento.monto;
                insertarOActualizarEnListaOrd( &listaCuentas, &readCuenta, sizeof(Cuenta), cmpCuenta, actCuentaMonto );
            }
            fread(&movimiento, 1, sizeof(Transferencia),binUpdate );   //Leo el siguiente movimiento
        }
        printf("\nLista transferencias al terminar lote %02d-%02d-%04d\n", fechaAct.dia, fechaAct.mes, fechaAct.anio);
        recorrer( &listaActividad, printTransf);

        //printf("*****************************************************************************************\n");
        //recorrer( &listaCuentas , printCuenta );

        reemplazoCuentaYstatus( &listaCuentas, &listaCuentas_final, &listaActividad );
        //Descarto los valores que generaros saldo negativo y recupero el estado inicial >> actualizo status

        //printf("*****************************************************************************************\n");
        printf("\nLista cuentas al terminar lote %02d-%02d-%04d\n", fechaAct.dia, fechaAct.mes, fechaAct.anio);
        recorrer( &listaCuentas, printCuenta );
        //printf("*****************************************************************************************\n");
        vaciarLista( &listaCuentas_final );
        //        printf("\nDespues de borrar la lista\n");
        //        recorrer( &listaCuentas_final , printCuenta );
        //        printf("*****************************************************************************************\n");
        recorrerLista( &listaCuentas, copiarLista, &listaCuentas_final);
        //        printf("\nDespues de copiar\n");
        //        recorrer( &listaCuentas_final , printCuenta );
        //        printf("*****************************************************************************************\n");
        //listaCuentas_final = listaCuentas;

        /** ACA TERMINA DE ANALIZAR POR FECHA Y PASA A LA SIGUIENTE **/
        //        printf("*****************************************************************************************\n");
        //        printf("\nDespues de actualizar los estados de la lista\n");
        //        recorrer( &listaActividad , printTransf );
        //        printf("*****************************************************************************************\n");
        Transferencia tranfEstado_final;
        while ( listaActividad )
        {
            eliminarDeListaPrimero( &listaActividad, &tranfEstado_final, sizeof(Transferencia));
            fwrite( &tranfEstado_final, sizeof(Transferencia), 1, estadosUpdate);
        }
        vaciarLista(&listaActividad);
    }
    fclose(binUpdate);
    fclose(estadosUpdate);
    /** FIN TRABAJO EN BLOQUES **/

    escribirArchLista_Bin( "tmp_cuentasFinal.dat", &listaCuentas, sizeof(Cuenta) );
    //escribirArchLista_Bin( "tmp_estadosFinal.dat", &listaEstados, sizeof(Transferencia) );


    vaciarLista(&listaCuentas);
    vaciarLista(&listaCuentas_final);
    vaciarLista(&listaActividad);

    remove("Transfer_Merge.dat");
    rename("transfEstados.dat", "Transfer_Merge.dat");

    actualizarCuentasYTransferencias_alu("Transfer_Merge.dat", NOMBRE_CUENTAS, NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO, NOMBRE_TRANSF);


    return TODO_OK;
}

int escribirArchLista_Bin(const char *nombre, Lista *lista, unsigned tamDato)
{
    if( !lista )
    {
        return ERR_LISTA;
    }
    FILE *pf = fopen( nombre, "wb" );
    if( !pf )
    {
        return ERR_AP_ARCH;
    }

    while( (*lista)->sig )
    {
        fwrite( (*lista)->dato, tamDato, 1, pf);
        lista = &(*lista)->sig;
    }
    fwrite( (*lista)->dato, tamDato, 1, pf);  //Copio el ultimo dato de la lista
    fclose( pf );

    return TODO_OK;
}

int convertirTxtABinario_alu
(const char* nombreTransfTxt, const char* nombreTransfBin)
{
///Nombre original del archivo, nombre final del archivo

    Transferencia transfRead;
    char read[250];
    FILE *txtTrans = fopen(nombreTransfTxt, "rt");
    ///Abro y confirmo que el archivo puede abrirse, si no pudo realizarse no hay con que trabajar.
    if(!txtTrans)
    {
        return ERR_AP_ARCH;
    }
    FILE *binTrans = fopen(nombreTransfBin, "wb");
    if(!binTrans)
    {
        fclose(txtTrans);
        return ERR_AP_ARCH;
    }
    fgets( read, sizeof(Transferencia), txtTrans);
    while( fgets( read, sizeof(Transferencia), txtTrans) )
    {
        //Construccion del Cmp typedef int (*Cmp)(const void*,const void*);
        parseTransf(read,&transfRead);
        fwrite( &transfRead, sizeof(Transferencia), 1, binTrans);
    }

    fclose(txtTrans);
    fclose(binTrans);

    return TODO_OK;
}

int parseTransf (char *read, Transferencia *transfRead)
{
    char *ocurrencia;
    //Me posiciono en la ultima | >> al final de la cadena

    SIG_OCURR;
    if( ocurrencia && *(ocurrencia+1)!='\0' )
    {
        sscanf( ocurrencia+1, "%c", &(transfRead)->aplicada );
        *ocurrencia = '\0';
    }
    else return ERROR;

    SIG_OCURR;
    if( ocurrencia && *(ocurrencia+1)!='\0' )
    {
        sscanf( ocurrencia+1, "%lf", &(transfRead)->monto );
        *ocurrencia = '\0';
    }
    else return ERROR;

    SIG_OCURR;
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%s", (transfRead)->bancoDest );
        *ocurrencia = '\0';
    }
    else return ERROR;

    SIG_OCURR;
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%s", (transfRead)->cuentaDest);
        *ocurrencia = '\0';
    }
    else return ERROR;

    SIG_OCURR;
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%s", (transfRead)->bancoOrig);
        *ocurrencia = '\0';
    }
    else return ERROR;

    SIG_OCURR;
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%s", (transfRead)->cuentaOrig);
        *ocurrencia = '\0';
    }
    else return ERROR;

    //Parse de la fecha
    ocurrencia = strrchr(read,'-');
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%d", &((transfRead)->fecha).anio );
        *ocurrencia = '\0';
    }
    else return ERROR;

    ocurrencia = strrchr(read,'-');
    if(ocurrencia && *(ocurrencia+1)!='\0')
    {
        sscanf( ocurrencia+1, "%d", &(transfRead)->fecha.mes );
        *ocurrencia = '\0';
    }
    else return ERROR;

    if(*read)
    {
        sscanf( read, "%d", &(transfRead)->fecha.dia );
    }
    else return ERROR;

    return TODO_OK;
}

int mergeTransfer_alu
(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransf)
{
    ///Deberia hacer un merge con los tres archivos, ordenado segun fecha

    Transferencia transfRead;

    //Creo una lista donde colocare todos los archivos de forma ordenada
    Lista listaMerge;
    crearLista(&listaMerge);

    FILE *binTransf = fopen(nombreTransf1, "rb");
    ///Coloco el primer archivo BIN a la lista
    if(!binTransf)
    {
        vaciarLista( &listaMerge); //Libero el espacio en memoria
        return ERR_AP_ARCH;
    }
    fread( &transfRead, 1, sizeof(Transferencia), binTransf );
    while( !feof(binTransf) )
    {
        //insertarEnListaOrd( &listaMerge, &transfRead, sizeof(Transferencia), cmpTransferencia);
        insertarEnListaAlFinal(&listaMerge, &transfRead, sizeof(Transferencia) );
        fread(&transfRead, 1, sizeof(Transferencia),binTransf );
    }
    fclose(binTransf);

    binTransf = fopen(nombreTransf2, "rb");
    ///Coloco el segundo archivo BIN a la lista
    if(!binTransf)
    {
        vaciarLista( &listaMerge); //Libero el espacio en memoria
        return ERR_AP_ARCH;
    }
    fread( &transfRead, 1, sizeof(Transferencia), binTransf );
    while( !feof(binTransf) )
    {
        //insertarEnListaOrd( &listaMerge, &transfRead, sizeof(Transferencia), cmpTransferencia);
        insertarEnListaAlFinal(&listaMerge, &transfRead, sizeof(Transferencia) );
        fread(&transfRead, 1, sizeof(Transferencia),binTransf );
    }
    fclose(binTransf);

    binTransf = fopen(nombreTransf, "rb");
    ///Coloco el ultimo archivo BIN a la lista
    if(!binTransf)
    {
        vaciarLista(&listaMerge);
        return ERR_AP_ARCH;
    }
    fread( &transfRead, 1, sizeof(Transferencia),binTransf );
    while( !feof(binTransf) )
    {
        //insertarEnListaOrd( &listaMerge, &transfRead, sizeof(Transferencia), cmpTransferencia);
        insertarEnListaAlFinal(&listaMerge, &transfRead, sizeof(Transferencia) );
        fread(&transfRead, 1, sizeof(Transferencia),binTransf );
    }
    fclose(binTransf);

    ordenarLista( &listaMerge, cmpTransferencia );

    FILE *binMerge = fopen("Transfer_Merge.dat", "wb");
    if(!binMerge)
    {
        vaciarLista(&listaMerge);
        return ERR_AP_ARCH;
    }
    while( listaMerge )
    {
        eliminarDeListaPrimero( &listaMerge, &transfRead, sizeof(Transferencia));
        fwrite( &transfRead, sizeof(Transferencia), 1, binMerge);
    }
    fclose( binMerge );

    //remove( NOMBRE_TRANSF );
    //rename( "transfMerge.dat",NOMBRE_TRANSF );

    //mostrarTransferencias(NOMBRE_TRANSF);
    mostrarTransferencias("Transfer_Merge.dat");

    vaciarLista(&listaMerge);

    return TODO_OK;
}

int actualizarCuentasYTransferencias_alu
(const char* nombreTransfMerge, const char* nombreCuentas,
 const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
 const char* nombreTransf)
{

    /** ACTUALIZO ARCHIVO DE DATOS CUENTAS**/
    remove(NOMBRE_CUENTAS);
    rename("tmp_cuentasFinal.dat", NOMBRE_CUENTAS);

    /** ACTUALIZACION DE ESTADOS **/
    /* APERTURA DE ARCHIVOS */

    FILE *pfTransfMerge = fopen( nombreTransfMerge, "rb");  ///Archivo que contiene todas las transferencias con su estado actualizado
    if(!pfTransfMerge)
    {
        return ERR_AP_ARCH;
    }


    FILE *pfTranfPTG = fopen( nombreTransf, "wb" );  ///Archivo que conoce las transacciones realizadas DESDE **Patagania**
    if(!pfTranfPTG)
    {
        fclose(pfTransfMerge);
        return ERR_AP_ARCH;
    }

    FILE *pfTranfSTD = fopen( nombreTransfSantanderEstado, "wt" );  ///Archivo que conoce las transacciones realizadas DESDE **Santander**
    if(!pfTranfSTD)
    {
        fclose(pfTransfMerge);
        fclose(pfTranfPTG);
        return ERR_AP_ARCH;
    }

    FILE *pfTranfYCBC = fopen( nombreTransfYCBCEstado, "wt" );  ///Archivo que conoce las transacciones realizadas DESDE **YCBC**
    if(!pfTranfSTD)
    {
        fclose(pfTransfMerge);
        fclose(pfTranfPTG);
        fclose(pfTranfSTD);
        return ERR_AP_ARCH;
    }
    /* FIN DE APERTURA DE ARCHIVOS */

    /* INICIO DE LA LOGICA DE ACTUALIZACION */
    Transferencia transfRead;
    fread(&transfRead, sizeof(Transferencia),1, pfTransfMerge);
    while( !feof(pfTransfMerge) )
    {
        if( strcmp( transfRead.bancoOrig, "Patagania") == 0)  //Archivo binario
        {
            fwrite( &transfRead, sizeof(Transferencia), 1, pfTranfPTG);
        }
        else if( strcmp( transfRead.bancoOrig, "Sentander") == 0)    //Archivo txt
        {
            fprintf( pfTranfSTD, "%d-%d-%d|%s|%s|%s|%s|%lf|%c\n", transfRead.fecha.dia, transfRead.fecha.mes, transfRead.fecha.anio,  //Fecha
                     transfRead.cuentaOrig,                                              //char[51]
                     transfRead.bancoOrig,                                               //char[51]
                     transfRead.cuentaDest,                                              //char[51]
                     transfRead.bancoDest,                                               //char[51]
                     transfRead.monto,                                                   //double
                     transfRead.aplicada);                                               //char
        }
        else if( strcmp( transfRead.bancoOrig, "YCBC") == 0)    //Archivo txt
        {
            fprintf( pfTranfYCBC, "%d-%d-%d|%s|%s|%s|%s|%lf|%c\n", transfRead.fecha.dia, transfRead.fecha.mes, transfRead.fecha.anio, //Fecha
                     transfRead.cuentaOrig,                                                          //char[51]
                     transfRead.bancoOrig,                                                           //char[51]
                     transfRead.cuentaDest,                                                          //char[51]
                     transfRead.bancoDest,                                                           //char[51]
                     transfRead.monto,                                                               //double
                     transfRead.aplicada);                                                           //char
        }
        fread(&transfRead, sizeof(Transferencia),1,pfTransfMerge);
    }
    /* FIN DE LA LOGICA DE ACTUALIZACION */
    fclose(pfTransfMerge);
    fclose(pfTranfPTG);
    fclose(pfTranfSTD);
    fclose(pfTranfYCBC);

    remove( nombreTransf );
    //printf("DESPUES DE REMOVE %d\n", status);
    rename( nombreTransfMerge, nombreTransf );
    //printf("DESPUES DE RENAME %d\n", status);

    return TODO_OK;
}
