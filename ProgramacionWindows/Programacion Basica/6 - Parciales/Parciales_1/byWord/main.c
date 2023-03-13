#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilaEstatica/pila.h"

#define ESMAYUS(A)			(A >= 'A' && A <= 'Z')
#define ESMINUS(a)			(a >= 'a' && a <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

char *nextWord(char **str);

int main()
{
    char str[] = " ;.,;w;.  wet,, and,o reako sabat reak geako zabat;;! e";
    char *ini, *fin = str;
    unsigned aux_s, max = 0;
    tPila cola;

    crearPila(&cola);

    while(*fin) {
		char aux[100] = "";

		ini = nextWord(&fin);
		memcpy(aux, ini, fin - ini);
		/*puts(aux);*/

		aux_s = strlen(aux) + 1;

		if(aux_s >= max) {
			if(aux_s > max) {
				max = aux_s;
				vaciarPila(&cola);
			}

			if(!pilaLlena(&cola, aux_s)) {
				ponerEnPila(&cola, &aux, aux_s);
			}
		}
	}

	while(!pilaVacia(&cola)) {
		char aux[100];
		sacarDePila(&cola, &aux, sizeof(aux));
		puts(aux);
	}

    return 0;
}

char *nextWord(char **str)
{
	char *ini;

	/*Mientras no estemos sobre una palabra*/
	while(**str && !ESLETRA(**str)) {
		(*str)++;
	}

	ini = *str;  /*Donde empieza la palabra*/

	while(**str && ESLETRA(**str)) {
		(*str)++;
	}

	return ini;
}
