#include <stdio.h>
#include <stdlib.h>
#include"../Arbol3/arbol.h"

int compararInt (const void* num1, const void* num2);
void mostrarInt ( void* num,void * stream);
//int insertarIntEnArbol(Arbol* pa, FILE *pf, size_t tamElem, Cmp cmp);
void generarArch(const char * name);
void actualizarInt(void * actualizado, const void * actualizador);
void mostrarArbol(const void * dato, int nivel);

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

    cargarEnArbolDeUnArchivoOrdenado(&t,0,cantRegistros-1,sizeof(int),fp,compararInt,actualizarInt);

    fclose(fp);

    recorrerArbolIn(&t,mostrarInt,stdout);
    puts("");
    graficarArbol(&t,mostrarArbol);

    if(esArbolBalanceado(&t))
    {
        printf("\n ES ARBOL BALANCEADO\n");
    }
    else
    {
        printf("\nNO ES ARBOL BALANCEADO\n");
    }

    vaciarArbol(&t);

    int completo[15]= { 10,5,20,2,7,15,30,1,3,6,8,12,18,25,50};

    Arbol ac;
    crearArbol(&ac);

    for (int i = 0; i<15 ; i++ )
        insertarEnArbol(&ac,&completo[i],sizeof(int),compararInt,actualizarInt);

    graficarArbol(&ac,mostrarArbol);

    if(esArbolCompleto(&ac))
    {
        printf("\n ES ARBOL COMPLETO\n");
    }
    else
    {
        printf("\nNO ES ARBOL COMPLETO\n");
    }

    vaciarArbol(&ac);

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
return *(int *)num1 - *(int *)num2;
}

void mostrarInt ( void* dato, void * output)
{
    int* numero = (int*)dato;

    fprintf(output,"%d ",*numero);
}

void actualizarInt(void * actualizado,const  void * actualizador)
{
return;
}

void mostrarArbol(const void * dato, int nivel)
{
    for (int i = 0; i < nivel; i++ )
        printf("   ");

    printf("%d\n", *(int*)dato);
}
