#include <stdio.h>
#include <stdlib.h>
#include"C:\Users\franq\Desktop\ArbolRodri/Arbol.h"
int compararInt (const void* num1, const void* num2);
void mostrarInt (const void* num);
int insertarIntEnArbol(Arbol* pa, FILE *pf, size_t tamElem, Cmp cmp);
void generarArch();

int main()
{
    Arbol ar1;

    crearArbol(&ar1);

    /*    insertarArbol(&ar1,&num1,sizeof(int),compararInt);
        insertarArbol(&ar1,&num2,sizeof(int),compararInt);
        insertarArbol(&ar1,&num3,sizeof(int),compararInt);*/

    /*    recorrerArbolEn(&ar1,mostrarInt,NULL);
        puts("");
        recorrerArbolPos(&ar1,mostrarInt,NULL);
        puts("");
        recorrerArbolPre(&ar1,mostrarInt,NULL);
    */
//   generarArch();

    FILE *pf = fopen("Numeros.dat","rb");
    if(!pf)
    {
        fclose(pf);
        return -1;
    }

    fseek(pf,0L,SEEK_END);
    int cBytes = ftell(pf);
    int cR = cBytes/sizeof(int);

    cargarArbolDeArchivoOrd(&ar1,pf,sizeof(int),0,cR-1,compararInt,insertarIntEnArbol);

    fclose(pf);

    recorrerArbolEn(&ar1,mostrarInt,NULL);

    return 0;
}

int insertarIntEnArbol(Arbol* pa, FILE *pf, size_t tamElem, Cmp cmp)
{
    int reg;
    fread(&reg,tamElem,1,pf);
    int res = insertarArbol(pa,&reg,tamElem,cmp);
    return res;
}

void generarArch()
{
    FILE* pf = fopen("Numeros.dat","wb");
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

void mostrarInt (const void* num)
{
    int* numero = (int*)num;

    printf("%d ",*numero);
}
