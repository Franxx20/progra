#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include "../TDALista/TDALista.h"
#include "main.h"
#include "../SolucionParcialBanco/SolucionParcialBanco.h"
#include "../SolucionParcialBanco/Transferencia.h"
#include "../SolucionParcialBanco/Cuenta.h"
#include "../Fecha/Fecha.h"

void accion(void* elem, void* datosAccion);
void accion2(void* elem, void* datosAccion);
void accion3(void* elem, void* datosAccion);
int strcmpi_2 (char* text, char* text2);

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
    int err;

    err=convertirTxtABinario_alu(nombreTransfSentander,"TempSen.tmp");
    if(err)
        return err;
    err=convertirTxtABinario_alu(nombreTransfYCBC,"TempYCBC.tmp");
    if(err)
        return err;


    err=mergeTransfer_alu("TempSen.tmp","TempYCBC.tmp",nombreTransf,"Merge.tmp");
    if(err)
        return err;

    FILE* f=fopen("Merge.tmp","rb");
    Transferencia t;

    printf("Merge:\n\n");
    fread(&t,sizeof(Transferencia),1,f);
    while(!feof(f))
    {
        printf("%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%lf\t\n", t.fecha.dia,t.fecha.mes,t.fecha.anio,t.cuentaOrig,t.bancoOrig,t.cuentaDest,t.bancoDest,t.monto);
        fread(&t,sizeof(Transferencia),1,f);
    }
    rewind(f);
    fclose(f);

    f=fopen(nombreCuentas,"rb");
    Cuenta cu;

    printf("\nCuenta:\n\n");
    fread(&cu,sizeof(Cuenta),1,f);
    while(!feof(f))
    {
        printf("%-30s\t%-15u\t%lf\n",cu.cuenta,cu.dniTitular,cu.saldo);
        fread(&cu,sizeof(Cuenta),1,f);
    }
    rewind(f);
    fclose(f);

    err=actualizarCuentasYTransferencias_alu("Merge.tmp",nombreCuentas,nombreTransfSantanderEstado,nombreTransfYCBCEstado,nombreTransf);
    if(err)
        return err;

    return TODO_OK;
}

/*
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

    char linea[sizeof(Transferencia)];
    Transferencia trans;

    fgets(linea,sizeof(Transferencia),fTxt);

    fgets(linea,sizeof(Transferencia),fTxt);
    while (!feof(fTxt))
    {
        if(convertirLinea(linea,&trans) == 0)
            fwrite(&trans,sizeof(Transferencia),1,fBin);
        fgets(linea,sizeof(Transferencia),fTxt);
    }

    fclose(fBin);
    fclose(fTxt);

    return 0;
}
int convertirLinea (const char* linea, Transferencia* trans)
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

int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransf3, const char* nombreTransfMerge)
{
    FILE* fTransPat=fopen(nombreTransf3,"rb"),
        * fTransSen=fopen(nombreTransf1,"rb"),
        * fTransYCBC=fopen(nombreTransf2,"rb");

    if (!fTransPat || !fTransSen || !fTransYCBC)
    {
        fclose(fTransPat);
        fclose(fTransSen);
        fclose(fTransYCBC);

        return ERR_AP_ARCH;
    }

    Transferencia transfMerge, transf1, transf2;
    Lista listaTransPat;
    crear(&listaTransPat);

    fread(&transfMerge,sizeof(Transferencia),1,fTransPat);
    fread(&transf1,sizeof(Transferencia),1,fTransSen);
    fread(&transf2,sizeof(Transferencia),1,fTransYCBC);
    while(!feof(fTransPat) && !feof(fTransSen) && !feof(fTransYCBC))
    {
        while(cmpFechas(&transfMerge.fecha,&transf1.fecha)<=0 && cmpFechas(&transfMerge.fecha,&transf2.fecha)<=0 && !feof(fTransPat))
        {
            insertarListaAlFinal(&listaTransPat,&transfMerge,sizeof(Transferencia));
            fread(&transfMerge,sizeof(Transferencia),1,fTransPat);
        }
        while(cmpFechas(&transf1.fecha,&transfMerge.fecha)<=0 && cmpFechas(&transf1.fecha,&transf2.fecha)<=0 && !feof(fTransSen))
        {
            insertarListaAlFinal(&listaTransPat,&transf1,sizeof(Transferencia));
            fread(&transf1,sizeof(Transferencia),1,fTransSen);
        }
        while(cmpFechas(&transf2.fecha,&transf1.fecha)<=0 && cmpFechas(&transf2.fecha,&transfMerge.fecha)<=0 && !feof(fTransYCBC))
        {
           insertarListaAlFinal(&listaTransPat,&transf2,sizeof(Transferencia));
            fread(&transf2,sizeof(Transferencia),1,fTransYCBC);
        }
    }
    while(!feof(fTransPat))
    {
        insertarListaAlFinal(&listaTransPat,&transfMerge,sizeof(Transferencia));
        fread(&transfMerge,sizeof(Transferencia),1,fTransPat);
    }
    while(!feof(fTransSen))
    {
        insertarListaAlFinal(&listaTransPat,&transf1,sizeof(Transferencia));
        fread(&transf1,sizeof(Transferencia),1,fTransSen);
    }
    while(!feof(fTransYCBC))
    {
        insertarListaAlFinal(&listaTransPat,&transf2,sizeof(Transferencia));
        fread(&transf2,sizeof(Transferencia),1,fTransYCBC);
    }
    fclose(fTransPat);
    fclose(fTransSen);
    fclose(fTransYCBC);

    FILE* fTrans=fopen(nombreTransfMerge,"wb");
    if (!fTrans)
        return ERR_AP_ARCH;

    while(!vacia(&listaTransPat))
    {
        eliminarPrimero(&listaTransPat,&transfMerge,sizeof(Transferencia));
        fwrite(&transfMerge,sizeof(Transferencia),1,fTrans);
    }
    fclose(fTrans);

    return TODO_OK;
}
int cmpFechas(const Fecha* f1, const Fecha* f2)
{
    if(f1->anio == f2->anio)
    {
        if(f1->mes == f2->mes)
        {
            if (f1->dia == f2->dia)
                return 0;
            return f1->dia - f2->dia;
        }
        return f1->mes - f2->mes;
    }
    return f1->anio - f2->anio;
}

int actualizarCuentasYTransferencias_alu(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf)
{
    FILE* fTransPat=fopen(nombreTransf,"wb"),
        * fTranMerge=fopen(nombreTransfMerge,"rb"),
        * fCuentas=fopen(nombreCuentas,"rb"),
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
    crear(&dia);
    crear(&cuentas);
    fread(&cu,sizeof(Cuenta),1,fCuentas);
    while (!feof(fCuentas))
    {
        insertarListaAlFinal(&cuentas,&cu,sizeof(Cuenta));
        fread(&cu,sizeof(Cuenta),1,fCuentas);
    }
    fclose(fCuentas);

    fread(&trans,sizeof(Transferencia),1,fTranMerge);
    while (!feof(fTranMerge))
    {
        Fecha f=trans.fecha;
        while(!cmpFechas(&f,&trans.fecha) && !feof(fTranMerge))
        {
            recorrer(&cuentas,accion,&trans);
            trans.aplicada='S';
            insertarListaAlFinal(&dia,&trans,sizeof(Transferencia));
            fread(&trans,sizeof(Transferencia),1,fTranMerge);
        }
        recorrer(&cuentas,accion2,&dia);

        while(!vacia(&dia))
        {
            eliminarPrimero(&dia,&trans,sizeof(Transferencia));
            fwrite(&trans,sizeof(Transferencia),1,fTransPat);

            if (!strcmpi_2(trans.bancoOrig,"Sentander") || !strcmpi_2(trans.bancoDest,"Sentantander"))
            {fprintf(fEstSan,"%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%lf\t%c\n",
                    trans.fecha.dia,trans.fecha.mes,trans.fecha.anio,
                        trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,
                            trans.monto,trans.aplicada);}
            if (!strcmpi_2(trans.bancoOrig,"YCBC") || !strcmpi_2(trans.bancoDest,"YCBC"))
                {fprintf(fEstYCBC,"%d-%d-%d\t%-30s\t%-10s\t%-30s%-10s\t%lf\t%c\n",
                    trans.fecha.dia,trans.fecha.mes,trans.fecha.anio,
                        trans.cuentaOrig,trans.bancoOrig,trans.cuentaDest,trans.bancoDest,
                            trans.monto,trans.aplicada);}
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

    while(!vacia(&cuentas))
    {
        eliminarPrimero(&cuentas,&cu,sizeof(Cuenta));
        fwrite(&cu,sizeof(Cuenta),1,fCuentas);
    }

    fclose(fCuentas);

    return TODO_OK;
}
void accion(void* elem, void* datosAccion)
{
    Cuenta* cu = (Cuenta*)elem;
    Transferencia* trans = (Transferencia*)datosAccion;

    if (!strcmpi_2(cu->cuenta,trans->cuentaOrig))
        cu->saldo -= trans->monto;
    if (!strcmpi_2(cu->cuenta,trans->cuentaDest))
        cu->saldo += trans->monto;
}
void accion2(void* elem, void* datosAccion)
{
    Cuenta* cu = (Cuenta*)elem;
    Lista* pl = (Lista*)datosAccion;

    if(cu->saldo < 0)
    {
        recorrer(pl,accion3,cu);
    }
}
void accion3(void* elem, void* datosAccion)
{
    Transferencia* trans = (Transferencia*)elem;
    Cuenta* cu = (Cuenta*)datosAccion;

    if(!strcmpi_2(cu->cuenta,trans->cuentaOrig) || !strcmpi_2(cu->cuenta,trans->cuentaDest))
        trans->aplicada = 'N';
}
int strcmpi_2 (char* text, char* text2)
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
*/
