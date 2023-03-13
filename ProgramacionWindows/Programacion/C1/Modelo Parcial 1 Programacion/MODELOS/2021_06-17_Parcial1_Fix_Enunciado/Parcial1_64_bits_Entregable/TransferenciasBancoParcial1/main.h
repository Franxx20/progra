#ifndef MAIN_H
#define MAIN_H

#include "../SolucionParcialBanco/Transferencia.h"

#define TODO_OK	        0
#define ERR_AP_ARCH		1
#define ERR_LINEA_LARGA	2
#define ERR_LISTA		3

#define NOMBRE_TRANSF					"Transferencias.dat"
#define	NOMBRE_TRANSF_SENTANDER_TXT		"Transferencias_Sentander.txt"
#define NOMBRE_TRANSF_YCBC_TXT			"Transferencias_YCBC.txt"
#define NOMBRE_CUENTAS					"Cuentas.dat"
#define NOMBRE_TRANSF_SENTANDER_ESTADO	"Transferencias_Sentander_Estado.txt"
#define NOMBRE_TRANSF_YCBC_ESTADO		"Transferencias_YCBC_Estado.txt"

///agregadas mias
int convertirLinea (const char* linea, Transferencia* trans);

#endif // MAIN_H
