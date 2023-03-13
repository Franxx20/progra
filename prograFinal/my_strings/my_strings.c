#include"my_strings.h"
#include<stdlib.h>

void  myMemcpy(void * destino, const void * origen, size_t num)
{
    char * d = (char  *)destino;
    char * o = (char * )origen;

    for (int i =0 ; i<num ; i++ )
    {
        d[i] = o[i];
    }

}


void myMemMove(void * destino, void * origen, size_t n)
{
    char * d = (char * )destino;
    char * o = (char * )origen;
    char * temp = malloc(n);

    for (int i =0; i<n ; i++)
    {
        temp[i] = o[i];
    }

    for (int i =0; i<n ; i++ )
    {
        d[i] = temp[i];
    }

    free(temp);
}


size_t myStrlen(const char * s)
{
    size_t i=0;
    for (; *s != '\0' ; s++ )
    {
        i++;
    }

    return i;
}

char * myStrcpy(char * d, const char * o)
{
//    char * a = d;
//for (;*o != '\0'  ;o++,d++ )
//{
//    *d = *o;
//}
//*d = '\0';

    char * temp1 = ( char * )o;
    char * temp2 = d;
    while(*temp1 != '\0')
    {
        *temp2 = *temp1;
        temp1++;
        temp2++;
    }
    *temp2 = '\0';

    return d;
}

char * myStrncpy(char * d, const char * o, size_t n)
{
    int i;
    char * a = d;
    for ( i= 0; i<n ; i++,d++,o++ )
    {
        *d = *o;
    }

    while(i<n)
        d[i] = '\0';

    return a;
}

char *myStrcat(char *d, const char *o)
{
    char * a = d;

    for (; *d != '\0' ; d++ )
    {
    }

    for (; *o!='\0' ; d++,o++ )
    {
        *d = *o;
    }
    *d = '\0';
    return a;
}


char * myStrrchr(char * s, int c){
int tam = myStrlen(s);
char * a = s + tam;

while(a >= s)
{
    if(*a == c)
        return a;

    a--;

}

return (void* )0;


}

char * myStrchr(char * s, int c){
while (*s)
{
    if(*s == c)
        return (char*)s;

    s++;
}
return ( void*)0;

}

int myStrcmp(const char * s1, const char * s2){
for (;*s1 && *s1 == *s2 ; s1++,s2++ )
{

}

return  * (unsigned char * ) (s1) - * (unsigned char * )(s2);
}
