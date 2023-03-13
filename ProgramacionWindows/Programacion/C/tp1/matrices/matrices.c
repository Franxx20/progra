#include "matrices.h"
#include <stdio.h>

/*
void MuestraVec(int *vec,int ce)
{
    int i;
    for(i=0;i<ce;i++)
    {
    printf("pos:%d  %d",i,vec[i]);
    vec[i]++;
    }
}
 void MostrarMatriz(int mat[][COL],int FIL,int COL)
 {
     int i;
     for(i=0;i<FIL;i++)
     {
         MuestraVec(mat[i],COL);
     }
 }
int MatrizDiagSec(int mat[][COL],int fil,int col)
{
    int i,j;
    for(j=0;j<col;j++)
    {
     for(i=0;i<fil;i++)
     {
        if(mat[i]==mat[j])
        printf("%*c |%d|\n",i*5,' ',mat[i][j]);
     }
    }
return 0;
}
*/

void MostrarDP(int mat[][COL], int fil) {
  int i;
  for (i = 0; i < fil; i++) {
    printf("%*c|%d|\n", i * 5, ' ', mat[i][i]);
  }
}

int MatriDiagg(int mat[][COL], int fil, int col) /// Mostrandolo con for
{
  int i, j;
  for (i = 0; i < fil; i++) {
    for (j = 0; j < col; j++) {
      if (mat[i] == mat[j])
        printf("\n %*c |%d|\n", i * 5, ' ', mat[i][j]);
    }
  }
  return 0;
}

void MostrarMatri(int mat[][COL], int fil, int col) {
  int i, j;
  printf("\n\n La matriz es: \n \n");
  for (i = 0; i < fil; i++) {

    printf("%*s", 2 * i, "\n");
    for (j = 0; j < col; j++) {
      printf("%3d", mat[i][j]);
    }
  }
}

void DebajoDiagPri(int mat[][COL], int fil, int col)

{
  int i, j;
  printf("\n \nDebajoDiagonalPrincpial: \n");
  for (i = 1; i < fil; i++) {
    for (j = 0; j < i; j++) {
      printf("%3d", mat[i][j]);
    }
    printf("\n");
  }
}

void SuperiorDiagPri(int mat[][COL], int fil, int col) {
  int i, j, inij;
  printf("\n DiagonalPrincipal Elementos superiores:\n");
  for (i = 0; i < fil - 1; i++) {
    printf("%*s", 2 * i, ""); ///* indica que la cantidad que ocupa se lo indico
                              /// como un parametro mas
    for (j = 1; j < col; j++) {

      if (i < j)
        printf("%2d", mat[i][j]);
    }

    printf("\n");
  }
}

int SumatoriaencimaElementosDiag(int mat[][TAM], int fil, int col) {
  int i, j, sumatoria = 0;
  for (i = 0; i < fil - 1; i++) {
    if (i < j)
      for (j = 1; j < col; j++) {
        sumatoria += mat[i][j];
      }
  }
  // printf("La suma es: %d",sumatoria);

  return sumatoria;
}
