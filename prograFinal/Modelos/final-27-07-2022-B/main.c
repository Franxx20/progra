#include <stdio.h>
#include <stdlib.h>
#include"listaDoble.h"
#include"arbol.h"
#include<string.h>

typedef struct
{
    char cod[5];
    char tipo;
    int cant;
} Producto;

typedef struct
{
    char cod[5];
    char tipo;
    int pos;
} Indice;

int crearLoteDePrueba(const char * filename);
int crearIndice(const char * filename, Lista *l);
int cargarListaDeArchivo(const char * filename, Lista *l);

int cargarArbolDeUnArchivoOrdenado(const char * filename, Arbol *t, unsigned tamDato, Cmp cmp, Actualizar actualizar);
int cargarArbolDeUnArchivoOrdenadoRec(Arbol *t, int li, int ls,unsigned tamDato, Cmp cmp, Actualizar actualizar, FILE * fp);


int compararIndices(const void * d1, const void * d2);
int compararIndices2(const void * d1, const void * d2);
void mostrarIndice(const void * dato, int nivel);

int main()
{

    Lista listaProductos;
    Arbol arbolIndice;

    crearArbol(&arbolIndice);
    crearLista(&listaProductos);

    crearLoteDePrueba("productos.dat");
    cargarListaDeArchivo("productos.dat",&listaProductos);
    crearIndice("prodTC.idx",&listaProductos);

    cargarArbolDeUnArchivoOrdenado("prodTC.idx",&arbolIndice,sizeof(Indice),compararIndices,NULL);


    mostrarArbol(&arbolIndice,mostrarIndice);




    vaciarArbol(&arbolIndice);
    vaciarLista(&listaProductos);
    return 0;
}


int crearLoteDePrueba(const char * filename)
{

    int i =0;
    Producto p [6] =
    {
        {
            "lap",'a', 15
        },
        {
            "cua", 'b', 10
        },
        {
            "lap", 'e',25
        },
        {
            "cua", 'c', 30

        },
        {
            "cartu",'d', 50

        },
        {
            "Hoja", 'e', 1000
        }

    };
    FILE *fp = fopen(filename,"wb");
    if(!fp)
        return ERR_ARCHIVO;


    for (; i<6 ; i++ )
    {
        fwrite(&p[i],sizeof(Producto),1,fp);
    }
    fclose(fp);

    return TODO_OK;
}


int crearIndice(const char * filename, Lista *l)
{
    int i=0;
    Indice indice;
    Producto p;
    Lista listaIndices;

    FILE *fp = fopen(filename,"wb");
    crearLista(&listaIndices);
    if(!fp)
        return ERR_ARCHIVO;


    while(!listaVacia(l))
    {
        eliminarPrimeroDeLista(l,&p,sizeof(Producto));

        strcpy(indice.cod,p.cod);
        indice.tipo = p.tipo;
        indice.pos = i;
        insertarEnListaOrd(&listaIndices,&indice,sizeof(Indice),compararIndices,NULL);



        i++;
    }

    while (!listaVacia(&listaIndices))
    {
        eliminarPrimeroDeLista(&listaIndices,&indice,sizeof(Indice));
        fwrite(&indice,sizeof(Indice),1,fp);
    }

    fclose(fp);
    vaciarLista(&listaIndices);
    return TODO_OK;
}

int cargarListaDeArchivo(const char * filename, Lista *l)
{
    Producto p;
    FILE *fp = fopen(filename,"rb");
    if(!fp)
        return ERR_ARCHIVO;

    while(!feof(fp))
    {
        fread(&p,sizeof(Producto),1,fp);
        insertarEnListaAlFinal(l,&p,sizeof(Producto));
    }

    fclose(fp);
    return TODO_OK;
}

int cargarArbolDeUnArchivoOrdenado(const char * filename, Arbol *t, unsigned tamDato, Cmp cmp, Actualizar actualizar)
{
    FILE * fp = fopen(filename,"rb");
    int ls;
    if(!fp)
        return ERR_ARCHIVO;

    fseek(fp,0L,SEEK_END);
    ls = ((ftell(fp))/tamDato)-1;

    cargarArbolDeUnArchivoOrdenadoRec(t,0,ls,tamDato,cmp,actualizar,fp);

    fclose(fp);

    return TODO_OK;
}
int cargarArbolDeUnArchivoOrdenadoRec(Arbol *t, int li, int ls,unsigned tamDato, Cmp cmp, Actualizar actualizar, FILE * fp)
{
    int mitad;
    void * registro;

    if(li > ls)
        return ERR_LIMITES;

    mitad = (li + ls)/2;
    fseek(fp,mitad*tamDato,SEEK_SET);

    registro = malloc(tamDato);

    if(!registro)
        return SIN_MEM;

    fread(registro,tamDato,1,fp);
    insertarEnArbol(t,registro,tamDato,cmp,actualizar);

    cargarArbolDeUnArchivoOrdenadoRec(t,li,mitad-1,tamDato,cmp,actualizar,fp);
    cargarArbolDeUnArchivoOrdenadoRec(t,mitad+1,ls,tamDato,cmp,actualizar,fp);

    return TODO_OK;
}





int compararIndices(const void * d1, const void * d2)
{
    int res;
    Indice * p1 = (Indice *)d1;
    Indice * p2 = (Indice*)d2;

    res = strcmp(p1->cod,p2->cod);
    if(res ==0)
        return res = p1->tipo - p2->tipo;

    return res;
}

int compararIndices2(const void * d1, const void * d2){

    Indice * p1 = (Indice *)d1;
    Indice * p2 = (Indice*)d2;


    return p1->pos - p2->pos;
}

void mostrarIndice(const void * dato, int nivel)
{
    int i =0;
    Producto * p = (Producto*)dato;
    for (; i<nivel ; i++ )
    {
        printf("\t");
    }
    printf("%s %c %d\n",p->cod,p->tipo,p->cant);

}
