#include <stdlib.h>
#include "../include/my_strings.h"

/*Funciones privadas*/
int es_separador(const char c, const char *sep);


int str_len(const char *str)
{
    int len = 0;

    while(*str) {
        str++;
        len++;
    }

    return len;
}


char *str_ntok(char *str, const char *sep)
{
    static char *data = NULL;
    char *new_str;
    int i = 0;

    if(str) {
        data = str;
    }

    if(!data) {
        return NULL;
    }

    new_str = malloc(str_len(data) + 1);

    while(*(data + i)) {

        if( !es_separador(*(data + i), sep) ) {
            *(new_str + i) = *(data + i);
        } else {
            *(new_str + i) = '\0';
            data = data + i + 1;
            return new_str;
        }
        i++;
    }

    *(new_str + i) = '\0';
    data = NULL;

    return new_str;
}

int es_separador(const char c, const char *sep)
{
    int i, len = str_len(sep);

    for(i = 0; i < len; i++) {
        if(c == *(sep + i)) {
            return 1;
        }
    }

    return 0;
}


int str_ncmp(const char *s1, const char *s2, size_t n)
{
    while(n && *s1 && *s2) {

        if(*s1 != *s2) {
            return *(char *)s1 - *(char *)s2;
        }

        s1++;
        s2++;
        n--;
    }

    return 0;
}


char *str_str(const char *pajar, const char *aguja)
{
    int aguja_len = str_len(aguja);

    if(!aguja_len) {
        goto resultado;
    }

    while(*pajar) {

        if(!str_ncmp(pajar, aguja, aguja_len)) {
            goto resultado;
        }

        pajar++;
    }

    return NULL;

resultado:
    return (char *)pajar;
}


size_t str_cspn(const char *str, const char *reject)
{
    size_t lenght = 0;
    const char *aux;

    while(*str) {

        for(aux = reject; *aux != '\0'; aux++) {
            if(*str == *aux) {
                return lenght;
            }
        }

        str++;
        lenght++;
    }

    return lenght;
}

void *mem_move(void *dest, const void* src, size_t n)
{
	char *temp = dest;
	const char *temp_s = src;

	if(dest <= src) {
        while(n--) {
            *(temp)++ = *(temp_s)++;
        }
	}
	else {
        temp += n;
        temp_s += n;

        while(n--) {
            *--(temp) = *--(temp_s);
        }
	}

	return dest;
}


char *str_chr(const char *str, char c)
{
    while(*str != c && *str) {
        str++;
    }

    return (*str)? (char *)str : NULL;
}

char *proxPalabra(char **str)
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
