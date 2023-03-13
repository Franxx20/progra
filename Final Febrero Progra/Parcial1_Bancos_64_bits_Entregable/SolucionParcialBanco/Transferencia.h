#ifndef TRANSFERENCIA_H
#define TRANSFERENCIA_H

#include "../Fecha/Fecha.h"


typedef struct
{
	Fecha fecha;
	char cuentaOrig[51];    //Alias CBU
	char bancoOrig[51];     //
	char cuentaDest[51];    //Alias CBU
	char bancoDest[51];
	double monto;
	char aplicada;          /// S o N /*Corresponde a marca de exito o no, agregada
}
Transferencia;


#endif // TRANSFERENCIA_H
