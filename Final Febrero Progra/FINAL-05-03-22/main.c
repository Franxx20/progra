#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_GENERAL -3

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;
} Nodo;

typedef struct
{
    int i;
    int j;
} Tupla;

typedef Nodo * Pila;

// FUNCIONES PILA
Nodo * crearNodo(const void* dato,size_t tamDato);
void crearPila(Pila * p);
int vaciarPila(Pila *p);

int pilaLlena(const Pila *p, size_t tamDato);
int pilaVacia(const Pila *p);

int insertarEnTope(Pila *p, const void * dato,size_t tamDato);
int sacarDeTope(Pila *p, void *dato,size_t tamDato);

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * filename);
int procesarPila(FILE * fp,Pila * vectorPilas,int cant);
int crearArchivosDeTexto(Pila *p,int cant);



int main()
{
    int res = crearLoteDePruebas("datos.txt");
    FILE * fp = fopen("datos.txt","rt");

    int cant;
    int i=0;
    char linea[50];
    Pila * vectorPilas;

    if(res != TODO_OK)
        return ERR_GENERAL;




    fgets(linea,50,fp);
    sscanf(linea,"%d",&cant);
    if(cant < 0 || cant > 500)
        return ERR_GENERAL;

    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }



    vectorPilas = (Pila*)calloc(cant,sizeof(Pila));
    if(!vectorPilas)
    {
        for (i =0; i<cant ; i++ )
        {
            free(vectorPilas[i]);
            return ERR_NODO;
        }
    }

    res = procesarPila(fp,vectorPilas,cant);
    if (res != TODO_OK)
        return ERR_GENERAL;

    res = crearArchivosDeTexto(vectorPilas,cant);
    if (res != TODO_OK)
        return ERR_GENERAL;


    for (i=0; i<cant ; i++ )
        vaciarPila(&vectorPilas[i]);

    fclose(fp);

    remove("datos.txt");
    return 0;
}

// FUNCIONES GENERALES
int crearLoteDePruebas(const char * filename)
{
    FILE * fp = fopen(filename,"wt");
    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    fprintf(fp,"%d\n",500);
    fprintf(fp,"(%d,%d)\n",410,340);
    fprintf(fp,"(%d,%d)\n",420,1200);
    fprintf(fp,"(%d,%d)\n",420,2200);
    fprintf(fp,"(%d,%d)\n",420,3200);
    fprintf(fp,"(%d,%d)\n",220,220);
    fprintf(fp,"(%d,%d)\n",100,400);
    fprintf(fp,"(%d,%d)\n",100,450);
    fprintf(fp,"(%d,%d)\n",2,290);
    fprintf(fp,"(%d,%d)\n",500,8000);
    fprintf(fp,"(%d,%d)\n",500,9000);
    fprintf(fp,"(%d,%d)\n",3,190);
    fprintf(fp,"(%d,%d)\n",410,380);
    fprintf(fp,"(%d,%d)\n",90,290);
    fprintf(fp,"(%d,%d)\n",8,190);
    fprintf(fp,"(%d,%d)\n",7,380);
    fprintf(fp,"(%d,%d)\n",500,11000);
    fprintf(fp,"(%d,%d)\n",-90,10);
    fprintf(fp,"(%d,%d)\n",90,1000);
    fprintf(fp,"(%d,%d)\n",-500,10);
    fprintf(fp,"(%d,%d)\n",-2,10);
    fprintf(fp,"(%d,%d)\n",-90,10);
    fprintf(fp,"(%d,%d)\n",-90,10);
    fprintf(fp,"(%d,%d)\n",8,1200);
    fprintf(fp,"(%d,%d)\n",7,1500);
    //fprintf(fp,"(%d,%d)\n",0,6969);
//    fprintf(fp,"3\n");
//    fprintf(fp,"(2,3)\n");
//    fprintf(fp,"(1,5)\n");
//    fprintf(fp,"(3,7)\n");
//    fprintf(fp,"(1,3)\n");
//    ///  fprintf(fp,"(0,-62)\n");
//    fprintf(fp,"(2,1)\n");
//    fprintf(fp,"(-2,7634)\n");
//    fprintf(fp,"(2,-3)\n");
//    fprintf(fp,"(1,2)\n");
//    fprintf(fp,"(3,6)\n");
//    fprintf(fp,"(3,-62)\n");

    fclose(fp);
    return TODO_OK;
}
int procesarPila(FILE * fp,Pila  *vectorPilas,int cant)
{


    Tupla tupla;
    int i;
    int num;

    char linea[50];

//    if(cant >= 1 && cant <=500)
//    {
    printf("%d",cant);

    while(fgets(linea,50,fp))
    {
        sscanf(linea,"(%d,%d)",&tupla.i,&tupla.j);

        if(tupla.i > 0 )
        {
            insertarEnTope(&vectorPilas[tupla.i-1],&tupla.j,sizeof(int));
        }
        else if(tupla.i>0 && tupla.j ==0 )
        {
            vaciarPila(&vectorPilas[tupla.i-1]);
        }
        else if(tupla.i<0)
        {
            sacarDeTope(&vectorPilas[(-1)*(tupla.i)-1],&num,sizeof(int));
        }
        else if(tupla.i ==0)
        {
            fprintf(stdout,"\nFIN ANORMAL");
            for (i=0; i<cant ; i++ )
            {
                vaciarPila(&vectorPilas[i]);
                free(vectorPilas[i]);
            }
            return ERR_GENERAL;
        }


    }

//
//    }


    fclose(fp);
    return TODO_OK;
}

int crearArchivosDeTexto(Pila *p,int cant)
{
    FILE * fp;
    int i= 0;
    char nombreArchivo[50];
    Pila pilaAux;
    int j;
    crearPila(&pilaAux);
    for (; i<cant ; i++ )
    {
        if(!pilaVacia(&p[i]))
        {
            sprintf(nombreArchivo,"pila%d.txt",i+1);
            fp = fopen(nombreArchivo,"wt");
            if(!fp)
            {
                fclose(fp);
                return ERR_ARCHIVO;
            }
            while(!pilaVacia(&p[i]))
            {
                sacarDeTope(&p[i],&j,sizeof(int));
                insertarEnTope(&pilaAux,&j,sizeof(int));
            }
            while(!pilaVacia(&pilaAux))
            {
                sacarDeTope(&pilaAux,&j,sizeof(int));
                fprintf(fp,"%d\n",j);
                insertarEnTope(&p[i],&j,sizeof(int));
            }
            fclose(fp);
        }




    }

    vaciarPila(&pilaAux);
    return TODO_OK;
}

// FUNCIONES PILA
Nodo * crearNodo(const void* dato,size_t tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;

    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato =tamDato;
    nue->sig = NULL;

    return nue;
}
void crearPila(Pila * p)
{
    *p =NULL;
}
int vaciarPila(Pila *p)
{
    Nodo * nae;
    int cne=0;

    while(*p)
    {
        nae = *p;
        *p =nae->sig;
        cne++;
        free(nae->dato);
        free(nae);
    }

    return cne;
}

int pilaLlena(const Pila *p, size_t tamDato)
{
    Nodo * nodo = (Nodo *)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo || !dato;
}
int pilaVacia(const Pila *p)
{
    return *p == NULL;
}

int insertarEnTope(Pila *p, const void * dato,size_t tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    nue->sig = *p;
    *p = nue;

    return TODO_OK;
}
int sacarDeTope(Pila *p, void *dato,size_t tamDato)
{
    Nodo * nae;
    if(!*p)
        return ERR_NODO;

    nae = *p;
    *p = nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);


    return TODO_OK;
}
