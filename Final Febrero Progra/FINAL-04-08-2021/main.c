#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define TODO_OK 0
#define ERR_GENERAL -1
#define ERR_ARCHIVO -2
#define ERR_NODO -3

#define MIN(a,b) ((a)<(b)?(a):(b))

#define esMayus(a) ((a) >= 'A' && (a)<='Z')
#define esMinus(a) ((a) >= 'a' && (a)<='z')

#define esLetra(a) (esMayus((a)) || esMinus((a)))

typedef struct sNodo
{
    void * dato;
    size_t tamDato;
    struct sNodo * sig;

} Nodo;

typedef Nodo * Lista;

Nodo * crearNodo(const void *dato,size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaLlena(const Lista *l, size_t tamDato);
int listaVacia(const Lista *l);

int insertarAlInicio(Lista *l, const void * dato,size_t tamDato);
int eliminarPrimero(Lista *l,  void * dato,size_t tamDato);
int eliminarUltimo(Lista *, void * dato,size_t tamDato);

int verPrimero(const Lista *l, void * dato,size_t tamDato);


int cargarLote(const char * filename);
int desofuscarArchivo(const char * filename);

int esClave(const char * reg,Lista *l);
int cmpCar(char a,char b);
int vaciarListaEnCadena(char * cad,Lista *l);

int main()
{

    int res;

    res = cargarLote("claves.txt");

    res = desofuscarArchivo("claves.txt");

    if(res!=TODO_OK)
        return ERR_GENERAL;


    return 0;
}

Nodo * crearNodo(const void *dato,size_t tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if(!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;

    return nue;
}

void crearLista(Lista *l)
{
    *l = NULL;
}

int vaciarLista(Lista *l)
{
    Nodo * nae;
    int cne = 0;
    if(!*l)
        return cne;

    while(*l)
    {
        nae = *l;
        *l = nae->sig;
        cne++;
        free(nae->dato);
        free(nae);
    }

    return cne;
}

int listaLlena(const Lista *l, size_t tamDato)
{
    Nodo * nodo = (Nodo *)calloc(1,sizeof(Nodo));
    void * dato = calloc(1,tamDato);
    free(nodo);
    free(dato);

    return !nodo ||!dato;
}
int listaVacia(const Lista *l)
{
    return *l == NULL;
}

int insertarAlInicio(Lista *l, const void * dato,size_t tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    if(!nue)
        return ERR_NODO;

    nue->sig = *l;
    *l = nue;

    return TODO_OK;
}


int eliminarPrimero(Lista *l,  void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    nae = *l;
    *l = nae->sig;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);

    return TODO_OK;
}

int eliminarUltimo(Lista *l, void * dato,size_t tamDato)
{
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    while((*l)->sig)
        l = &(*l)->sig;

    nae = *l;
    *l  = NULL;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);



    return TODO_OK;
}

int verPrimero(const Lista *l, void * dato,size_t tamDato)
{
    if(!*l)
        return ERR_NODO;

    memcpy(dato,(*l)->dato,MIN(tamDato,(*l)->tamDato));

    return TODO_OK;
}

int cargarLote(const char * filename)
{
    FILE * fp = fopen(filename,"wt");
    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }
    char linea[56]= {"ccC++d-- aRRarRa"};
    char linea2[56] = {"+++___**+"};
    char linea3[56] ={"ab++ab--ab"};
    char linea4[56]={ "abab"};

    fprintf(fp,"%s\n",linea);
    fprintf(fp,"%s\n",linea2);
    fprintf(fp,"%s\n",linea3);
    fprintf(fp,"%s\n",linea4);



    fclose(fp);
    return TODO_OK;
}





int desofuscarArchivo(const char * filename)
{
    FILE *fp = fopen(filename,"rt");
    FILE * fpTemp = fopen("temp.txt","wt");
    char linea[57];
    Lista lista;
    crearLista(&lista);

    if (!fp  || !fpTemp)
    {
        fclose(fp);
        fclose(fpTemp);
        return ERR_ARCHIVO;
    }

    while(fgets(linea,57,fp))
    {
        if(esClave(linea,&lista) ==TODO_OK)
        {
            vaciarListaEnCadena(linea,&lista);
            fprintf(fpTemp,"%s\n",linea);
            fprintf(stdout,"%s\n",linea);
        }
    }


    vaciarLista(&lista);

    fclose(fp);
    fclose(fpTemp);

    remove(filename);
    rename("temp.txt",filename);

    return TODO_OK;
}


int esClave(const char * reg,Lista *l)
{
    char car;
    char aux;
    if(*reg)
    {
        insertarAlInicio(l,reg,sizeof(char));
        reg++;

        while(*reg)
        {
            if(verPrimero(l,&car,sizeof(char))== TODO_OK && tolower(car) == tolower(*reg))
            {
                eliminarPrimero(l,&aux,sizeof(char));
            }
            else
            {
                insertarAlInicio(l,reg,sizeof(char));
            }

            reg++;
        }
    }

    return listaVacia(l)?ERR_GENERAL:TODO_OK;
}

int cmpCar(char a,char b)
{

    return a == b;
}

int vaciarListaEnCadena(char * cad,Lista *l)
{

    char car;

    while(!listaVacia(l))
    {
        eliminarUltimo(l,&car,sizeof(char));
        if(isalpha(car) || car == ' ')
        {
            *cad = car;
            cad++;

        }
    }
    *cad = '\0';
    vaciarLista(l);


    return TODO_OK;
}
