#include "Ejercicio 3.h"
#include <stdio.h>

void mat_transpuesta_insitu(int cuad[][6],int tam){
    int aux;
    for(int i=0;i<tam;i++)
        for(int j=i;j<tam;j++){
            aux = cuad[i][j];
            cuad[i][j] = cuad[j][i];
            cuad[j][i] = aux;
        }
}

void muestra_mat_cuadrada(int mat[][6],int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++)
            printf("%d\t",mat[i][j]);
        printf("\n");
    }
}
