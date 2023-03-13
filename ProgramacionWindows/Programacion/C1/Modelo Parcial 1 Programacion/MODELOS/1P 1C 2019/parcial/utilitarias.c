#include <stdio.h>
#include <string.h>
#include <utilitarias.h>
#include <biblioteca.h>

void texto_a_stock(const char * cad,t_libro_stock * pstock)
{
    char* pos = strrchr(cad,'\n');
        *pos='\0';

    pos = strrchr(cad,'|');
    sscanf(pos+1,"%d",&pstock->stock);
    *pos = '\0';

    sscanf(cad,"%s",pstock->isbn);
}
