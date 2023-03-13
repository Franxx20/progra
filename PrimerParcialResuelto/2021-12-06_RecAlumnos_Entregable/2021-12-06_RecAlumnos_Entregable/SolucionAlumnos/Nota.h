#ifndef NOTA_H
#define NOTA_H

typedef enum
{ P1, P2, R1, R2 }  ///P1 = Parcial 1, P2 = Parcial 2, R1 = Recuperatorio P1, R2 = Recuperatorio P2
TipoParcial;


typedef struct
{
	int dni;
	char apyn[51];
	char materia[31];
	TipoParcial tipoParcial;
	int nota;
}
Nota;


#endif // NOTA_H
