#include <stdio.h>
#include <stdlib.h>
#include<string.h>

size_t strlen_ALU(const char * str);
int strcmpALU(const char * str1, const char * str2);
char * strcpy_ALU(char * cadDestino, const char * cadOrigen);
char * strcat_ALU(char* cadDestino,const char* cadOrigen);
char * strrchr_ALU( char * str,int caracter);
char * strchr_ALU( char * str,int caracter);

int main()
{




    return 0;
}

size_t strlen_ALU(const char * str)
{
    size_t i=0;
    while(*str!='\0')
        i++;

    return i;
}

int strcmpALU(const char * str1, const char * str2)
{
    while(*str1 && *str2)
    {
        if(*str1 - *str2 != 0)
            return *str1 - *str2;
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

char * strcpy_ALU(char * cadDestino, const char * cadOrigen)
{


    if(cadDestino == NULL)
        return NULL;

    char *aux = cadDestino;

    while(*cadOrigen)
    {
        *cadDestino = *cadOrigen;
        cadDestino++;
        cadOrigen++;
    }

    *cadDestino = '\0';

    return aux;
}
char * strcat_ALU(char* cadDestino,const char* cadOrigen)
{

    char *aux;
    if(cadDestino == NULL)
        return NULL;

    aux = cadDestino;

    while(*cadDestino!='\0')
        cadDestino++;

    while(*cadOrigen)
    {
        *cadDestino = *cadOrigen;
        cadDestino++;
        cadOrigen++;
    }
    *cadDestino = '\0';
    return aux;
}

char * strrchr_ALU( char * str,int caracter)
{
    int i=0;
    while(*str)
    {
        str++;
        i++;
    }
    for (; i>0 ; i-- )
    {
        if(*str == caracter)
            return str;
        str--;
    }

    return NULL;
}

char * strchr_ALU( char * str,int caracter)
{
    while(*str)
    {
        if(*str == caracter)
            return str;

        str++;
    }

    return NULL;
}
