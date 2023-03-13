#ifndef ESTADOALUMNOMATERIA_H
#define ESTADOALUMNOMATERIA_H


typedef enum
{ PR, CU, RE, AU } ///PR = Promocionó, CU = Cursó, RE = Reprobó, AU = Ausente
CondicionMateria;


typedef struct
{
	int dni;
	char apyn[51];
    char materia[31];
	int notaP1;
    int notaP2;
    int notaR1;
    int notaR2;
    CondicionMateria condicion;
    int notaFinal;
}
EstadoAlumnoMateria;


#endif /* ESTADOALUMNOMATERIA_H */
