#include <string.h>
#include "cadenas.h"

#define ES_MAYUS(A) ((A) >= 'A' && (A) <= 'Z')
#define ES_MINUS(a) ((a) >= 'a' && (a) <= 'z')

#define ES_LETRA(a) ((ES_MAYUS(a) || ES_MINUS(a)) ? (1) : (0))


bool esPalindromo(const char * cad)
{
    const char* izq=cad;

    const char* der=cad+strlen(cad)-1;

    while(izq < der)
    {
        while(ES_LETRA(*izq))
            izq++;

        while(ES_LETRA(*der))
            der--;

        if(miTolower(*izq) != miTolower (*der))
            return false;

        izq++;
        der--;
    }

    return izq>=der;
}

//////////////////////////////////////

char miTolower(char c)
{
if (c>='A' && c<='Z')
{
    return c+('a' - 'A');
}
return c;
}

///////////////////////////////////////

bool sonAnagramas(const char* cad1, const char* cad2)
{
    int strlen1 = miStrlen(cad1);
    int strlen2 = miStrlen(cad2);

    if(strlen1 != strlen2)
        return false;

    int vec1[26] = {0}, vec2[26] = {0};

    while(*cad1)
    {
        int aux1 = (int)miTolower(*cad1) - 97;
        vec1[aux1]++;
        cad1++;
    }

    while(*cad2)
    {
        int aux2 = (int)miTolower(*cad2) - 97;
        vec2[aux2]++;
        cad2++;
    }

    int i = 0;
    while(vec1[i] == vec2[i] && i < 26)
        i++;

    return i >= 26;
}


int miStrlen(const char* cad)
{
    const char* aux = cad;

    while(*aux)
        aux++;

    return aux - cad;
}


//Practicar hacer strlen strcmp strcpy y strncpy con fin de cad
