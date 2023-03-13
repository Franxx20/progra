#include <stdio.h>
#include <stdlib.h>
#include"arbol.h"
#include<string.h>

typedef struct
{
    char codigo[11];
    int sector;
    int pos;
} Indice;

typedef struct
{
    char codigo[11];
    int sector;
    int estado;

} Producto;

int compararIndicesPos(const void *d1, const void * d2);
int compararIndicesCod(const void * d1, const void *d2);
void mostrarIndices(const void * dato, int nivel);

void buscarMayorIndicePos(void * siguiente, void * actual);


int crearLote(const char * filename);
int cargarArbol(const char * filename, Arbol *t, Cmp cmp);

int buscarMayorRegistro(const Arbol * t);


int main()
{


    Arbol arbolIndice;
    crearArbol(&arbolIndice);
    crearLote("productos.bin");

    cargarArbol("productos.bin",&arbolIndice,compararIndicesCod);
    mostrarArbolEnOrden(&arbolIndice,mostrarIndices);

    buscarMayorRegistro(&arbolIndice);

    vaciarArbol(&arbolIndice);
    return 0;
}



int compararIndicesPos(const void *d1, const void * d2)
{
    Indice * i1 = (Indice* )d1;
    Indice * i2 = (Indice* )d2;

    return i1->pos - i2->pos;
}

int compararIndicesCod(const void * d1, const void *d2)
{
    Indice * i1 = (Indice* )d1;
    Indice * i2 = (Indice* )d2;
    int res;
    res = strcmp(i1->codigo,i2->codigo);
    if(res ==0)
        return i1->sector - i2->sector;

    return res;
}



int crearLote(const char * filename)
{
    int i=0;
    Producto p[8]=
    {
        {
            "cuader",22,1
        },
        {
            "plasti",7,1
        },
        {
            "lap",1,1
        },
        {
            "cuader",23,0
        },

        {
            "goma",6,1
        },
        {
            "plasti",5,1,
        },
        {
            "goma",4,0
        },

        {
            "plasti",6,1
        }
    };
    FILE *fp = fopen(filename,"wb");
    if(!fp)
    {
        fprintf(stderr, "ERROR AL CREAR EL ARCHIVO BINARIO");
        return ERR_ARCHIVO;
    }

    for (; i<8; i++)
    {
        if(p[i].sector>0 && p[i].sector<24)
            fwrite(&p[i],sizeof(Producto),1,fp);
    }

    fclose(fp);




    return TODO_OK;

}


int cargarArbol(const char * filename, Arbol *t, Cmp cmp)
{
    FILE *fp = fopen(filename,"rb");
    Indice indice;
    int i =0;
    Producto p;
    if(!fp)
    {
        fprintf(stderr, "ERROR AL LEER EL ARCHIVO BINARIO");
        return ERR_ARCHIVO;
    }


    fread(&p,sizeof(Producto),1,fp);
    strncpy(indice.codigo,p.codigo,11);
    indice.pos =i;
    indice.sector  = p.sector;

    while(!feof(fp) && !arbolLleno(t, sizeof(Indice)))
    {
        if(p.estado == 1)
            insertarEnArbol(t,&indice,sizeof(Indice),cmp);

        i++;
        fread(&p,sizeof(Producto),1,fp);
        strncpy(indice.codigo,p.codigo,11);
        indice.pos =i;
        indice.sector  = p.sector;
    }


    fclose(fp);


    return TODO_OK;
}

int buscarMayorRegistro(const Arbol * t)
{
    Indice i= {"",0,0};
    recorrerArbolEnOrden(t,buscarMayorIndicePos,&i);

    printf("\n mayor registro es %s %d %d", i.codigo,i.sector,i.pos);
    return TODO_OK;
}



void buscarMayorIndicePos(void * arbol, void * datoInd)
{
    Indice * arbolInd = (Indice* )arbol;
    Indice * datoIndice = (Indice* )datoInd;



    if(arbolInd->pos > datoIndice->pos)
    {
        datoIndice->pos = arbolInd->pos;

        strncpy(datoIndice->codigo,arbolInd->codigo,11);
        datoIndice->sector = arbolInd->sector;
    }

}

void mostrarIndices(const void * dato, int nivel)
{
    int contador= 0;
    Indice * i = (Indice *)dato;
    for (; contador<nivel ; contador++ )
    {
        printf("\t");
    }
    printf("%s %d %d\n",i->codigo, i->sector, i->pos);


}
