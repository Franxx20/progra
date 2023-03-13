#include <stdlib.h>
#include "../include/descifrar.h"
#include "../include/my_strings.h"

void descifrarLinea(char *str, int *maxLenght, tPila *pila)
{
    static const char ofs[] = "bcdfgaeiou";
    static const char org[] = "aeioubcdfg";

    char *p_chr, /* Puntero al caracter encontrado en ofs */
		 *ini,	 /* Puntero a la palabra separada de la linea */
		 *fin = str;

    int i,
		tam; /* Tamanio de la palabra separada */


    while(*fin) {

		ini = proxPalabra(&fin);
		tam = fin - ini;

		/* Descifrador */
        for(i = 0; i < tam ; i++) {
            p_chr = str_chr(ofs, *(ini+i));
            if(p_chr) {
                *(ini + i) = *(org + (p_chr - ofs));
            }
        }

        if(tam >= *maxLenght) {

			char palabra[51] = ""; /* Cadena auxiliar para guardar la palabra en la pila*/

			if(tam > *maxLenght) {
				*maxLenght = tam;
				vaciarPila(pila);
			}

			mem_move(palabra, ini, tam);
            ponerEnPila(pila, palabra, tam + 1);
        }
    }
}
