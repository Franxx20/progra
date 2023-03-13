#ifndef CUENTA_H
#define CUENTA_H

#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"


typedef struct
{
	char cuenta[51];
	unsigned dniTitular;
	double saldo;
}
Cuenta;


#endif // CUENTA_H
