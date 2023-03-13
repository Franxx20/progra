#include <stdio.h>
#include <stdlib.h>

#include "ejer2.h"
size_t mi_strlen(const char *cad)
{
    size_t i=0;
    while(*cad)
    {
        i++;
        cad++;
    }
    return i;
}


char mi_strstr(char*donde,const char *buscar)
{
    size_t longitud=mi_strlen(buscar);
    int i=0;
    while(*donde)
    {
        if(i=longitud)
        {
            return (donde-1);
        }
        if(*donde==*buscar)
        {
            i++;
            buscar++;
        }
        else
        {
            buscar-=i;
        }
        donde++;
    }
    return NULL;
}
