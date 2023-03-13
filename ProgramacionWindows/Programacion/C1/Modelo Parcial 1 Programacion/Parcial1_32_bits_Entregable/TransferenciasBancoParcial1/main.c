#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionParcialBanco/SolucionParcialBanco.h"
#include "main.h"


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

    ret = procesarTransferencias(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);

	/****** DESCOMENTE ESTE CÓDIGO Y COMENTE EL DE ARRIBA PARA PROBAR SU CÓDIGO **********/
/**    
    ret = procesarTransferencias_alu(NOMBRE_TRANSF, NOMBRE_TRANSF_SENTANDER_TXT, NOMBRE_TRANSF_YCBC_TXT, NOMBRE_CUENTAS,
		NOMBRE_TRANSF_SENTANDER_ESTADO, NOMBRE_TRANSF_YCBC_ESTADO);
*/		
	
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
	
}	


int convertirTxtABinario_alu(const char* nombreTransfTxt, const char* nombreTransfBin)
{
	
}


int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge)
{
	
}


int actualizarCuentasYTransferencias_alu(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf)
{
	
}
