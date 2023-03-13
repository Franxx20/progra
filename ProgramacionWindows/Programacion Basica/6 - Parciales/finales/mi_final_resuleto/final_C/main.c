#include <stdio.h>
#include <stdlib.h>
#include "pila/pila.h"

#define FILE_ERROR -1
#define MEMORY_ERROR -2
#define PROGRAM_ERROR 1

int main()
{
    const char *datos_path = "datos.txt";

    char aux_str[80];
    int n_pilas;
    FILE *datos = fopen(datos_path, "rt");

    if(!datos) {
        return FILE_ERROR;
    }

    fgets(aux_str, sizeof(aux_str), datos);
    sscanf(aux_str, "%d", &n_pilas);

    if(n_pilas >= 1 && n_pilas <= 500) {
        int i, j;
        tPila *pilas = (tPila *)calloc(n_pilas, sizeof(tPila));

        if(!pilas) {
            fclose(datos);
            return MEMORY_ERROR;
        }

        for(i = 0; i < n_pilas; i++) {
            crear_pila(&pilas[i]);
        }

        while(fgets(aux_str, sizeof(aux_str), datos)) {
            sscanf(aux_str, "(%d,%d)", &i, &j);
            if(i == 0) {
                for(i = 0; i < n_pilas; i++) {
                    vaciar_pila((pilas+i));
                }
                free(pilas);
                fclose(datos);
                return PROGRAM_ERROR;
            }
            else if(i > 0 && j != 0) {
                pila_insertar(pilas+i-1, &j, sizeof(int));
            }
            else if(i > 0 && j == 0) {
                vaciar_pila(pilas+i-1);
            }
            else if(i < 0) {
               pila_eliminar(pilas+(i*-1)-1, &j, sizeof(int));
            }
        }

        for(i = 0; i < n_pilas; i++) {
            FILE *pila_datos;
            char pila_path[20];

            if(pila_vacia(&pilas[i])) {
                continue;
            }

            sprintf(pila_path, "pila_%d.txt", i+1);
            pila_datos = fopen(pila_path, "wt");
            if(!pila_datos) {
                for(i = 0; i < n_pilas; i++) {
                    vaciar_pila((pilas+i));
                }
                free(pilas);
                fclose(datos);
                return FILE_ERROR;
            }

            while(!pila_vacia(&pilas[i])) {
                pila_eliminar(&pilas[i], &j, sizeof(int));
                fprintf(pila_datos, "%d\n", j);
            }
            fclose(pila_datos);
        }

        free(pilas);
    }

    fclose(datos);
    //remove(datos_path);
    return 0;
}
