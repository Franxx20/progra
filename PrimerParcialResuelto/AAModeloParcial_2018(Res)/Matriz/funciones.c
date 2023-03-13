#include "matriz.h"

int sumaTriDerecho(int mat[FILA][COLUMNA],int f,int c)
{
    int i,j,s;
    s=0;
    for (j=c-1;j>(c/2);j--)
    {
        for(i=f-j;i<j;i++)
        {
            s+=mat[i][j];

        }
    }return s;
}
