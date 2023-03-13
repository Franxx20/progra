///Turello, Martina Gloria 43.719.495

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionParcialBanco/SolucionParcialBanco.h"
#include "main.h"

///agregadas
#include "../SolucionParcialBanco/Transferencia.h"
#include "../SolucionParcialBanco/Cuenta.h"
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include "../TDALista/TDALista.h"

int lineaTxtVariableABin_alu (const char* linea, Transferencia* trans);
void accion_alu(void* elem, void* datosAccion);
void accion2_alu(void* elem, void* datosAccion);
void accion3_alu(void* elem, void* datosAccion);
void printear_alu(void* elem, void* datosAccion);
int strcmpi_2 (char* text, char* text2);
///
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
/*
    ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
*/
	/****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/

    ret = procesarTransferencias_alu(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);


	if(ret != TODO_OK)
		return ret;

	puts("\n\nDespues de actualizar:\n");

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
    int err;

    ///paso a Binario
    err=convertirTxtABinario_alu(nombreTransfSentander,"TempSen.tmp");
    if(err != TODO_OK)
        return err;
    err=convertirTxtABinario_alu(nombreTransfYCBC,"TempYCBC.tmp");
    if(err != TODO_OK)
        return err;

    ///agrupo todo
    err=mergeTransfer_alu("TempSen.tmp","TempYCBC.tmp","TempMerge.tmp");
    if(err != TODO_OK)
        return err;
    err=mergeTransfer_alu(nombreTransf,"TempMerge.tmp","MergeFinal.tmp");
    if(err != TODO_OK)
        return err;

    ///muestro
    FILE* f=fopen("MergeFinal.tmp","rb");
    if(!f)
        return ERR_AP_ARCH;

    Transferencia t;

    printf("Transferencias Mergeadas:\nTransferencias Patagania\n");
    printf("======================================================================\n");
    fread(&t,sizeof(Transferencia),1,f);
    while(!feof(f))
    {
        printf("%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%7lf\t\n", t.fecha.dia,t.fecha.mes,t.fecha.anio,t.cuentaOrig,t.bancoOrig,t.cuentaDest,t.bancoDest,t.monto);
        fread(&t,sizeof(Transferencia),1,f);
    }
    rewind(f);
    fclose(f);

    f=fopen(nombreCuentas,"rb");
    if(!f)
        return ERR_AP_ARCH;

    Cuenta cu;

    printf("\n\nLista recien cargada del archivo cuentas:\n");
    fread(&cu,sizeof(Cuenta),1,f);
    while(!feof(f))
    {
        printf("%-30s\t%-15u\t%lf\n",cu.cuenta,cu.dniTitular,cu.saldo);
        fread(&cu,sizeof(Cuenta),1,f);
    }
    rewind(f);
    fclose(f);

    //actualizo
    err=actualizarCuentasYTransferencias_alu("MergeFinal.tmp",nombreCuentas,nombreTransfSantanderEstado,nombreTransfYCBCEstado,nombreTransf);
    if(err != TODO_OK)
        return err;

    return TODO_OK;
}


int convertirTxtABinario_alu(const char* nombreTransfTxt, const char* nombreTransfBin)
{
	FILE* fTxt=fopen(nombreTransfTxt,"rt"),
        * fBin=fopen(nombreTransfBin,"wb");
    if (!fTxt || !fBin)
    {
        fclose(fTxt);
        fclose(fBin);
        return ERR_AP_ARCH;
    }

    rewind(fTxt);

    char linea[sizeof(Transferencia)];
    Transferencia trans;

    fgets(linea,sizeof(Transferencia),fTxt); //titulos

    fgets(linea,sizeof(Transferencia),fTxt); //datos
    while (!feof(fTxt))
    {
        if(lineaTxtVariableABin_alu(linea,&trans) == 0)
            fwrite(&trans,sizeof(Transferencia),1,fBin);
        fgets(linea,sizeof(Transferencia),fTxt);
    }

    fclose(fBin);
    fclose(fTxt);

    return 0;
}
int lineaTxtVariableABin_alu (const char* linea, Transferencia* trans) //agregada
{
    char* pos=strchr(linea,'\n');
    if (!pos)
        return ERR_LINEA_LARGA;

    pos=strrchr(linea,'|');
    sscanf(pos+1,"%lf",&trans->monto);
    *pos='\0';

    pos=strrchr(linea,'|');
    strncpy (trans->bancoDest,pos+1,50);
    *pos='\0';

     pos=strrchr(linea,'|');
    strncpy (trans->cuentaDest,pos+1,50);
    *pos='\0';

     pos=strrchr(linea,'|');
    strncpy (trans->bancoOrig,pos+1,50);
    *pos='\0';

     pos=strrchr(linea,'|');
    strncpy (trans->cuentaOrig,pos+1,50);
    *pos='\0';

    pos=strrchr(linea,'-');
    sscanf(pos+1,"%d",&trans->fecha.anio);
    *pos='\0';

    pos=strrchr(linea,'-');
    sscanf(pos+1,"%d",&trans->fecha.mes);
    *pos='\0';

    sscanf(linea,"%d",&trans->fecha.dia);

    return 0;
}


int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge)
{
	FILE* fTransf1=fopen(nombreTransf1,"rb"),
        * fTransf2=fopen(nombreTransf2,"rb");

    if (!fTransf1 || !fTransf2)
    {
        fclose(fTransf1);
        fclose(fTransf2);

        return ERR_AP_ARCH;
    }

    rewind(fTransf1);
    rewind(fTransf2);

    Transferencia transf1, transf2;
    Lista listaMerge;
    crearLista(&listaMerge);

    fread(&transf1,sizeof(Transferencia),1,fTransf1);
    fread(&transf2,sizeof(Transferencia),1,fTransf2);
    while(!feof(fTransf1) && !feof(fTransf2))
    {
        while(cmpFechas(&transf1.fecha,&transf2.fecha)<=0 && !feof(fTransf1))
        {
            insertarEnListaAlFinal(&listaMerge,&transf1,sizeof(Transferencia));
            fread(&transf1,sizeof(Transferencia),1,fTransf1);
        }
        while(cmpFechas(&transf1.fecha,&transf2.fecha)>0 && !feof(fTransf2))
        {
            insertarEnListaAlFinal(&listaMerge,&transf2,sizeof(Transferencia));
            fread(&transf2,sizeof(Transferencia),1,fTransf2);
        }
    }
    while(!feof(fTransf1))
    {
        insertarEnListaAlFinal(&listaMerge,&transf1,sizeof(Transferencia));
        fread(&transf1,sizeof(Transferencia),1,fTransf1);
    }
    while(!feof(fTransf2))
    {
        insertarEnListaAlFinal(&listaMerge,&transf2,sizeof(Transferencia));
        fread(&transf2,sizeof(Transferencia),1,fTransf2);
    }
    fclose(fTransf1);
    fclose(fTransf2);

    FILE* fMerge=fopen(nombreTransfMerge,"wb");
    if (!fMerge)
        return ERR_AP_ARCH;

    while(!listaVacia(&listaMerge))
    {
        eliminarDeListaPrimero(&listaMerge,&transf1,sizeof(Transferencia));
        fwrite(&transf1,sizeof(Transferencia),1,fMerge);
    }
    fclose(fMerge);

    return TODO_OK;
}


int actualizarCuentasYTransferencias_alu(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf)
{
    FILE* fTranMerge=fopen(nombreTransfMerge,"rb"),
        * fCuentas=fopen(nombreCuentas,"rb"),
        * fTransPat=fopen(nombreTransf,"wb"),
        * fEstSan=fopen(nombreTransfSantanderEstado,"wt"),
        * fEstYCBC=fopen(nombreTransfYCBCEstado,"wt");

    if (!fTransPat || !fTranMerge || !fCuentas || !fEstSan || !fEstYCBC)
    {
        fclose(fTransPat);
        fclose(fTranMerge);
        fclose(fCuentas);
        fclose(fEstSan);
        fclose(fEstYCBC);

        return ERR_AP_ARCH;
    }

    Transferencia trans;
    Cuenta cu;

    rewind(fCuentas);
    rewind(fTranMerge);

    Lista cuentas,dia;
    crearLista(&dia);
    crearLista(&cuentas);

    fread(&cu,sizeof(Cuenta),1,fCuentas);
    while (!feof(fCuentas))
    {
        insertarEnListaAlFinal(&cuentas,&cu,sizeof(Cuenta));
        fread(&cu,sizeof(Cuenta),1,fCuentas);
    }
    fclose(fCuentas);

    fread(&trans,sizeof(Transferencia),1,fTranMerge);
    while (!feof(fTranMerge))
    {
        Fecha f=trans.fecha;

        while(!cmpFechas(&f,&trans.fecha) && !feof(fTranMerge))
        {
            recorrerLista(&cuentas,accion_alu,&trans);
            trans.aplicada='S';
            insertarEnListaAlFinal(&dia,&trans,sizeof(Transferencia));
            fread(&trans,sizeof(Transferencia),1,fTranMerge);
        }

        recorrerLista(&cuentas,accion2_alu,&dia);

        printf("\n\nLista Transferencias al terminar el lote %d/%d/%d\n", f.dia, f.mes, f.anio);
        while(!listaVacia(&dia))
        {
            eliminarDeListaPrimero(&dia,&trans,sizeof(Transferencia));
            printf("%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%lf\t%c\n",
                    trans.fecha.dia,trans.fecha.mes,trans.fecha.anio,
                        trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,
                            trans.monto,trans.aplicada);

            fwrite(&trans,sizeof(Transferencia),1,fTransPat);

            if (!strcmpi_2(trans.bancoOrig,"Sentander") || !strcmpi_2(trans.bancoDest,"Sentantander"))
            {fprintf(fEstSan,"%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%7lf\t%c\n",
                    trans.fecha.dia,trans.fecha.mes,trans.fecha.anio,
                        trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,
                            trans.monto,trans.aplicada);}
            if (!strcmpi_2(trans.bancoOrig,"YCBC") || !strcmpi_2(trans.bancoDest,"YCBC"))
                {fprintf(fEstYCBC,"%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%7lf\t%c\n",
                    trans.fecha.dia,trans.fecha.mes,trans.fecha.anio,
                        trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,
                            trans.monto,trans.aplicada);}
        }

        printf("\nLista Cuentas al terminar el lote %d/%d/%d\n", f.dia, f.mes, f.anio);
        recorrerLista(&cuentas,printear_alu,0);

        if (!feof(fTranMerge))
        {
            fseek(fTranMerge,(long int)(-1L * sizeof(Transferencia)),SEEK_CUR);
            fseek(fTranMerge,0L,SEEK_CUR);
        }
        fread(&trans,sizeof(Transferencia),1,fTranMerge);
    }
    fclose(fTransPat);
    fclose(fTranMerge);
    fclose(fEstSan);
    fclose(fEstYCBC);

    fCuentas = fopen(nombreCuentas,"wb");
    if (!fCuentas)
        return ERR_AP_ARCH;

    while(!listaVacia(&cuentas))
    {
        eliminarDeListaPrimero(&cuentas,&cu,sizeof(Cuenta));
        fwrite(&cu,sizeof(Cuenta),1,fCuentas);
    }

    fclose(fCuentas);

    return TODO_OK;
}
void accion_alu(void* elem, void* datosAccion) //agregada
{
    Cuenta* cu = (Cuenta*)elem;
    Transferencia* trans = (Transferencia*)datosAccion;

    if (!strcmpi_2(cu->cuenta,trans->cuentaOrig))
        cu->saldo -= trans->monto;
    if (!strcmpi_2(cu->cuenta,trans->cuentaDest))
        cu->saldo += trans->monto;
}
void accion2_alu(void* elem, void* datosAccion) //agregada
{
    Cuenta* cu = (Cuenta*)elem;
    Lista* pl = (Lista*)datosAccion;

    if(cu->saldo < 0)
    {
        recorrerLista(pl,accion3_alu,cu);
    }
}
void accion3_alu(void* elem, void* datosAccion) //agregada
{
    Transferencia* trans = (Transferencia*)elem;
    Cuenta* cu = (Cuenta*)datosAccion;

    if(!strcmpi_2(cu->cuenta,trans->cuentaOrig) || !strcmpi_2(cu->cuenta,trans->cuentaDest))
    {
        trans->aplicada = 'N';
        if(!strcmpi_2(cu->cuenta,trans->cuentaOrig))
            cu->saldo+=trans->monto;
        else if(!strcmpi_2(cu->cuenta,trans->cuentaDest))
            cu->saldo-=trans->monto;
    }

}
void printear_alu(void* elem, void* datosAccion) //agregada
{
    Cuenta* cu = (Cuenta*)elem;

    printf("%-30s\t%-15u\t%lf\n",cu->cuenta,cu->dniTitular,cu->saldo);
}
int strcmpi_2 (char* text, char* text2) //agregada
{
    while (*text || *text2)
    {
        if (*text == *text2)
        {
            text++;
            text2++;
        }
        else
            return *text-*text2;
    }
    return 0;
}
