#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista/lista.h"

#define ESMAYUS(A)			(A >= 'A' && A <= 'Z')
#define ESMINUS(a)			(a >= 'a' && a <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

#define AMAYUS(a)			(ESMINUS(a)? ((a) - 32) : (a))
#define AMINUS(A)			(ESMAYUS(A)? ((A) + 32) : (A))

char *get_word(char **str);
int cmp_word(const void *data_1, const void *data_2);
void print_str(const void *data, FILE *stream);
int str_ncmpi(const char *s1, const char *s2, size_t n);

int main() 
{
	FILE *archivo = fopen("archivo.txt", "wt");
	char *str = "Es mas, es la hora de ir de paseo, cerca, a la playa.";
	char *fin = get_word(&str);
	tLista lista_simple;
	crear_lista(&lista_simple);
	while (*fin) {
		int word_size = str-fin;
		char *word = (char *)malloc(word_size+1);

		memcpy(word, fin, word_size);
		word[word_size] = '\0';

		lista_insertar_ordenado(&lista_simple, word, word_size+1, cmp_word, NULL);
		fin = get_word(&str);

		free(word);
	}
	lista_mostrarInvertido(&lista_simple, print_str, archivo);
	//vaciar_lista(&lista_simple);
	fclose(archivo);
	return 0;
}

char *get_word(char **str)
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

int cmp_word(const void *data_1, const void *data_2)
{
	char *str_1 = (char *)data_1;
	char *str_2 = (char *)data_2;
	size_t size_1 = strlen(str_1);
	size_t size_2 = strlen(str_2);

	if(size_1 - size_2 == 0) {
		return str_ncmpi(str_1, str_2, size_1);
	}

	return (size_2 - size_1);
}

void print_str(const void *data, FILE *stream)
{
	fprintf(stream, "%s\n", (char *)data);
}

int str_ncmpi(const char *s1, const char *s2, size_t n)
{
    while(n && *s1) {

        if(AMAYUS(*s1) != AMAYUS(*s2)) {
            return AMINUS(*s1) - AMINUS(*s2);
        }

        n--;
        s1++;
        s2++;
    }

    return 0;
}