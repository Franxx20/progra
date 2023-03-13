#include <stdio.h>
#include <stdlib.h>
#include "Ejercicio 3.h"

int main()
{
    int mat[6][6]={{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25},{26,27,28,29,30},{31,32,33,34,35,36}};
    muestra_mat_cuadrada(mat,6);
    printf("\n\n");
    mat_transpuesta_insitu(mat,6);
    muestra_mat_cuadrada(mat,6);
    return 0;
}
