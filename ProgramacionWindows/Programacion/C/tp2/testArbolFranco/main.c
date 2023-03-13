#include <stdio.h>
#include <stdlib.h>
#include"../ArbolFranco/arbol.h"

int compararInt (const void* num1, const void* num2);
void mostrarInt ( void* num,void * stream);
//int insertarIntEnArbol(Arbol* pa, FILE *pf, size_t tamElem, Cmp cmp);
void generarArch(const char * name);

int main(int argc, char * argv[])
{

    Arbol t;
    crearArbol(&t);

    generarArch(argv[1]);

    FILE * fp = fopen(argv[1],"rb");

    if(!fp)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO EN LECTURA");
        return 1;
    }

    fseek(fp,0L,SEEK_END);
    int cantBytes = ftell(fp);
    int cantRegistros = cantBytes/sizeof(int);

    cargarEnArbolDeUnArchivoOrdenado(&t,0,cantRegistros-1,sizeof(int),fp,compararInt);

    fclose(fp);

    recorrerArbolIn(&t,mostrarInt,stdout);
    vaciarArbol(&t);

    return 0;
}


//int insertarIntEnArbol(Arbol* t, FILE *pf, size_t tamDato, Cmp cmp)
//{
//    int reg;
//    fread(&reg,tamDato,1,pf);
//    int res = insertarEnArbolRec(t,reg,tamDato,cmp);
//    return res;
//}

void generarArch(const char * name)
{
    FILE* pf = fopen(name,"wb");
    if(!pf)
    {
        fclose(pf);
        return;
    }

    int vec[] = {1,4,6,7,9,10,15,22,30,48};

    for(int i = 0; i < sizeof(vec)/sizeof(int) ; i++)
        fwrite(&vec[i],sizeof(int),1,pf);

    fclose(pf);
}

int compararInt (const void* num1, const void* num2)
{
    int* numero1 = (int*)num1;
    int* numero2 = (int*)num2;

    return (*numero1)-(*numero2);
}

void mostrarInt ( void* dato, void * output)
{
    int* numero = (int*)dato;

    fprintf(output,"%d ",*numero);
}
