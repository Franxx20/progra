#ifndef TRANSFERENCIA_H
#define TRANSFERENCIA_H

#include "../Fecha/Fecha.h"


typedef struct
{
	Fecha fecha;
	char cuentaOrig[51];
	char bancoOrig[51];
	char cuentaDest[51];
	char bancoDest[51];
	double monto;
	char aplicada; /// S o N
}
Transferencia;


#endif // TRANSFERENCIA_H
