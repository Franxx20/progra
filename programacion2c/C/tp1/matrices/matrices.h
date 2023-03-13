#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED
#define COL 5
#define TAM 10

void mostrarDP(int mat[][COL], int fil);
int matrisDiag(int mat[][COL], int fil, int col);
int mostrarDiag(int mat[][COL], int fil, int col);
void debajoDiagPri(int mat[][COL], int fil, int col);
void superiorDiagPri(int mat[][COL], int fil, int col);
int sumatoriaEncimaElementosDiag(int mat[][COL], int fil, int col);

void MostrarMatriz(int mat[][COL], int fil, int col);
#endif // MATRICES_H_INCLUDED
