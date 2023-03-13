#include "Funciones.h"

void CrearLista(tLista *p)
{
    *p=NULL;
}
int InsertarEnLista(tLista *p,const void *d,unsigned cantbytes)
{
    tNodoLista *nue;
    while(*p)
        p=&(*p)->sig;
    if((nue=(tNodoLista *)malloc(sizeof(tNodoLista)))==NULL
            ||(nue->info=malloc(cantbytes))==NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,d,cantbytes);
    nue->taminfo=cantbytes;
    nue->sig=NULL;
    *p=nue;
    return 1;
}
int PasarMatrizALista(tLista *p,int Mat[][COLUMNA],int fila,int columna)
{
    int i,j;
    tMatriz mat;
    int max,band=0;
    for(i=0; i<fila; i++)
    {
        if(Mat[i][i])
        {
            if(band)
            {
                if(Mat[i][i]>max)
                    max=Mat[i][i];
                mat.fila=i;
                mat.columna=i;
                mat.valor=Mat[i][i];
                InsertarEnLista(p,&mat,sizeof(mat));
            }
            if(band==0)
            {
                max=Mat[i][i];
                mat.fila=i;
                mat.columna=i;
                mat.valor=Mat[i][i];
                InsertarEnLista(p,&mat,sizeof(mat));
                band=1;
            }

        }
        for(j=i+1; j<columna; j++)
        {
            if(Mat[i][j])
            {
                mat.fila=i;
                mat.columna=j;
                mat.valor=Mat[i][j];
                InsertarEnLista(p,&mat,sizeof(mat));
            }
            if(Mat[j][i])
            {
                mat.fila=j;
                mat.columna=i;
                mat.valor=Mat[j][i];
                InsertarEnLista(p,&mat,sizeof(mat));
            }
        }
    }
    return max;


}
void MostrarLista(tLista *p,void (*mostrar)(const void *))
{
    if(!*p)
        return;
    mostrar((*p)->info);
    MostrarLista(&(*p)->sig,mostrar);
}
void VerNodoLista(const void *a)
{
    tMatriz *pri=(tMatriz *)a;
    printf("FILA %d COLUMNA %d VALOR %d\n",pri->fila,pri->columna,pri->valor);
}
