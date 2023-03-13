#include"matrices.h"


int main()
{
    int mat[FIL][COL]={
        {1,2,3,4,5,6},
        {4,5,6,2,7,8},
        {7,8,9,1,9,1},
        {1,2,3,4,2,3},
        {4,5,6,7,8,9},
        {1,2,3,4,5,6}};
    int resul;
    resul=sumaElemPorDebajoDiagPrincSecu(mat,FIL,COL);
    printf("El resultado de la suma de los elementos que estan por debajo de la diagonal principal y secundaria es: %d",resul);
    return 0;
}
