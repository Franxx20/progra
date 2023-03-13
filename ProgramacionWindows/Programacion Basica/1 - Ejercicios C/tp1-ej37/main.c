/*Se dispone de una matriz cuadrada de enteros de orden N, donde cada elemen-to [i][j]
representa la cantidad de puntos que obtuvo el equipo i frente al equipo j al fin de un
torneo de futbol (partidos de ida y vuelta) en el que participaron N equipos.
El sistema de puntuacion es: 3 puntos para el ganador del partido y ninguno para el per-dedor;
1 punto para cada equipo en caso de empate. Desarrollar una funcion que determine si la matriz esta correctamente generada.
Desarrollar  una  funcion  que  genere  un  arreglo  de  N elementos  tal  que  cada elemento V[k]
contenga la cantidad de puntos obtenidos por el equipo k*/
#include "main.h"

int main()
{
    int partido;
    int m[N][N]={{0}};  //Inicializamos la matriz
    int v[N] = {0};     //Puntaje de los equipos

    for(partido = 1; partido <= 2; partido++)
    {
        carga(m, partido);
        inspeccionar(m);
        puntaje(m, v);
    }

    return 0;
}

void carga(int m[][N], int partido)
{
    int i, j;

    for(i = 0 ; i <= EQUIPOS ; i++)
    {
        for (j = 0 ; j <= EQUIPOS ; j++)
        {
            if (i != j)
            {
                printf("Partido %d/%d: [%d][%d]: ",partido ,TOTAL ,i+1 ,j+1);
                scanf("%d", &m[i][j]);
            }
        }
    }
}

void puntaje(int m[][N], int v[N])
{
    int i, j;

    for(i = 0; i <= EQUIPOS; i++)
    {
        for (j = 0; j <= EQUIPOS; j++)
        {
            if (i != j && (m[i][j] > m[j][i])) //Si equipo I le gano a equipo J
                v[i] += 3;
            else if (i != j && (m[i][j] == m[j][i])) //Si empataron
                v[i] += 1;
            //Si el equipo perdio no se suma nada porque ya se inicializo el vector
        }
    }

    for(i = 0; i <= EQUIPOS; i++)
        printf("Equipo %d: %d\n", i+1, v[i]);
}

void inspeccionar(int m[][N])
{
    int i, j;

    for(i = 0; i <= EQUIPOS; i++)
    {
        for (j = 0; j<= EQUIPOS; j++)
        {
            if (m[i][j] < 0)
            {
                printf("Error - No se puede ingresar numeros negativos.\n");
                m[i][j] = -m[i][j]; //Si m[i][j] = -8 -> -m[i][j]= -(-8) -> 8
            }
        }
    }
}
