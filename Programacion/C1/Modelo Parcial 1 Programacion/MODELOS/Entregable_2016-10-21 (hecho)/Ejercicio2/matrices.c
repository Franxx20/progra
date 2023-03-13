#include"matrices.h"

int sumaElemPorDebajoDiagPrincSecu(int m[][COL],int fil,int col)
{
    int i,
        j,
        suma = 0;
//    for(i = 1; i < fil; i++){
//        printf("%*c", fil - i, ' ');
//        for(j = fil - i; j < col; j++){
//            printf("%1d",m[i][j]);
//            suma += m[i][j];
//        }
//        printf("\n");
//    }

    for(i = 1 + fil / 2; i < fil; i++){
        for(j = fil - i; j < i ; j++){
            printf("%3d",m[i][j]);
            suma += m[i][j];
        }
        printf("\n");
    }
    return suma;
}
