/*
 * Dado un array de char que contiene un texto compuesto por palabras que termina
 * en '.' (o en su defecto en carácter nulo '\0'), escriba un programa que
 * determine e informe:
 *      a- cuál es la primera palabra y cuántas veces se repite en el texto
 *		b- cuántas palabras tiene el texto
 *		c- longitud de la palabra más larga
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

char *firstWord(char *word)
{
	size_t size = 0;
	char *p_aux = word;
	char *first = calloc(SIZE, 1);

	while(*p_aux)
	{
		if(*p_aux == '.' || *p_aux == '\0') break;

		size++;
		p_aux++;
	}
	strncpy(first, word, size);

	return first;
}


int wordIterations(char *word, char *find)
{
	size_t times = 0;
	char *p_aux;

	while(*word)
	{
		p_aux = strstr(word, find);
		if(p_aux)
		{
			word = p_aux + strlen(find);
			times++;
		}
		else break;
	}

	return times;
}

int textLong(char *word)
{
	size_t 	size = 0,
			being = 0;

	while(*word)
	{
		if(*word == '.' || *word == '\0')
		{
			if(being) size++;
			being = 0;
		}
		else being = 1;

		word++;
	}
	if(being) size++;

	return size;
}

int longestWord(char *word)
{
	size_t 	size = 0,
			longest = 0;

	while(*word)
	{
		if(*word == '.' || *word == '\0')
		{
			if(size > longest) longest = size;
			size = 0;
		}
		else size++;

		word++;
	}

	return longest;
}

int main()
{
    char str[] = {"word.by.word.like.ants.around.the.road"};
    char *w = firstWord(str);
	int n = wordIterations(str, w);
	int l = textLong(str);
	int m = longestWord(str);
	printf("First word is: %s and it repeats %d times\n", w, n);
	printf("The text is %d long\n", l);
	printf("The longitud of the longest word is: %d\n", m);

    return 0;
}
