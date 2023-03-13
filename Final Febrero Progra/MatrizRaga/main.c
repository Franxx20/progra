#include "Funciones.h"

int main()
{
    int max;
    tLista lista;
    CrearLista(&lista);
    int Matriz[FILA][COLUMNA]={
                                {0,0,0,6},
                                {0,2,0,0},
                                {1,0,8,0},
                                {0,0,0,7}
                              };
    max=PasarMatrizALista(&lista,Matriz,FILA,COLUMNA);
    printf("LA Dagonal Max %d\n",max);
    MostrarLista(&lista,VerNodoLista);

    return 0;
}
