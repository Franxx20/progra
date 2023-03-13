#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

#define TODO_OK 0
#define ERR_ARCHIVO -1
#define ERR_NODO -2
#define ERR_GENERAL -3
#define ERR_LETRA -4
#define MIN(a,b) ((a)<(b)?(a):(b))



#define esMin(a) ((a)>='a' && (a)<='z')
#define esMayus(a) ((a)>='A' && (a)<='Z')

#define esLetra(a) (esMin((a)) || esMayus((a)))
#define esNumero(num) ((num)>=1 && (num)<=9)
#define esSigno(a) ((a) == '.' || (a) == ',' || (a) == ';' || (a) == '¿' || (a) == '?' || (a) == '!' || (a) == '¡' || (a) == ' ')

#define esCaracterValido(a) (esLetra((a)) || esNumero((a)) || esSigno((a)))

typedef struct sNodo
{
    void *dato;
    size_t tamDato;
    struct sNodo * sig;
    struct sNodo * ant;
} Nodo;

typedef int (*Cmp) (const void *d1,const void *d2);

typedef Nodo * Lista;
int cargarArchivo(const char * nombreArchivo);
int normalizar(const char * nombreArchivo);
int cargarEnLista(Lista *l, char * linea);
int eliminarEspacios(Lista *l, Cmp cmp);
int eliminarBasura(Lista *l);

int cmpCaracteres(const void  * d1, const void *d2);

void mayus(void *d1);



Nodo * crearNodo(const void * dato,size_t tamDato);
void crearLista(Lista *l);
int vaciarLista(Lista *l);

int listaVacia(const Lista *l);

int insertarEnListaAlFinal(Lista *l, const void * dato,size_t tamDato);
int eliminarDeListaAlInicio(Lista *l, void * dato,size_t tamDato);
int verFrente(const Lista *l,  void * dato,size_t tamDato);
int verFondo(const Lista *l,  void * dato,size_t tamDato);

int main()
{
    int res;
    res = cargarArchivo("normalizacion.txt");
    if(res != TODO_OK)
        return ERR_GENERAL;

    res = normalizar("normalizacion.txt");
    return 0;
}

int cargarArchivo(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo,"wt");
    if (!fp)
    {
        fclose(fp);
        return ERR_ARCHIVO;
    }

    fprintf(fp,"       lA Locura aaaaacierta a     Veces cuaNdo el = juicio y la cordura no dan fruto.     no LE prestes leng/ua al pensamiento, Ni lo po-ngas por obra si es impropio.");
    fprintf(fp,"\nHola, Como estas?");

    fclose(fp);
    return TODO_OK;
}

int normalizar(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo,"rt");
    FILE *fpTemp = fopen("temp.txt","wt");

    Lista lista;
    crearLista(&lista);

    char *act;
    char car;
    char linea[256];
    if(!fp ||!fpTemp)
    {
        fclose(fp);
        fclose(fpTemp);
        return ERR_ARCHIVO;
    }

    while(fgets(linea,256,fp))
    {
        fputs("Original\n",stdout);
        fprintf(stdout,linea);

        cargarEnLista(&lista,linea);
        act = linea;

        puts("\n\nnormalizado");
        while(!listaVacia(&lista))
        {
            eliminarDeListaAlInicio(&lista,&car,sizeof(char));
            *act = car;
            act++;
        }
        *act = '\0';
        fprintf(stdout,"%s",linea);
        fprintf(fpTemp,"%s",linea);
        puts("");



    }


    fclose(fp);
    fclose(fpTemp);

    remove(nombreArchivo);
    rename("temp.txt",nombreArchivo);

    vaciarLista(&lista);
    return TODO_OK;
}

int cargarEnLista(Lista *lista, char * linea)
{
    char  car;
    char * aux;
    int mayus =0;

    aux  =linea;

    while(*aux == ' ' && *aux != '\0')
        aux++;


    car =toupper(*aux);
    insertarEnListaAlFinal(lista,&car,sizeof(char));
    aux++;
    while(*aux)
    {
        car =tolower(*aux);

        if(car == '.')
            mayus =1;
        if(mayus ==1  && esLetra(car))
        {
            car = toupper(car);
            if(esCaracterValido(car))
                insertarEnListaAlFinal(lista,&car,sizeof(char));
            mayus =0;
        }
        else
        {
            if(esCaracterValido(car))
                insertarEnListaAlFinal(lista,&car,sizeof(char));
        }
        aux++;
    }

    eliminarEspacios(lista,cmpCaracteres);


    return TODO_OK;
}

int eliminarEspacios(Lista *l,Cmp cmp)
{
    Nodo *act;
    Nodo * sig=NULL;
//    Nodo * ant = NULL;
    Nodo * nae;
    if(!*l)
        return ERR_NODO;

    act =*l;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        sig = act->sig;
        while(sig)
        {

            if(cmp(act->dato,sig->dato)==1)
            {
                nae =sig;
                sig =nae->sig;
                if(nae == *l)
                    *l =nae->ant?nae->ant:nae->sig;
                if(nae->ant)
                    nae->ant->sig = nae->sig;

                if(nae->sig)
                    nae->sig->ant = nae->ant;


                free(nae->dato);
                free(nae);
            }
            else
            {
                act =act->sig;
                sig = sig->sig;
            }
        }
        act =act->sig;
    }

    return TODO_OK;
}


int cmpCaracteres(const void *d1,const void *d2)
{
    char *c1 = (char *)d1;
    char *c2 = (char *)d2;


    return *c1 == ' ' && *c2 == ' ';
}



Nodo * crearNodo(const void * dato,size_t tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if (!nue || !(nue->dato = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }

    memcpy(nue->dato,dato,tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    nue->ant = NULL;

    return nue;
}

void crearLista(Lista *l)
{
    *l = NULL;
}
int vaciarLista(Lista *l)
{
    Nodo * act  = *l;
    Nodo * nae;
    int cne=0;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        while(act)
        {
            nae = act;
            act = nae->sig;
            cne++;
            free(nae->dato);
            free(nae);
        }
        *l = NULL;
    }


    return cne;
}


int listaVacia(const Lista *l)
{
    return *l == NULL;
}

int insertarEnListaAlFinal(Lista *l, const void * dato,size_t tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);
    Nodo * act = *l;
    if(!nue)
        return ERR_NODO;

    if(act)
        while(act->sig)
            act =act->sig;


    nue->ant =act;

    if(act)
        act->sig = nue;



    *l =nue;


    return TODO_OK;
}

int eliminarDeListaAlInicio(Lista *l, void * dato,size_t tamDato)
{
    Nodo * act =*l;
    Nodo * nae;
    if(!act)
        return ERR_NODO;



    while(act->ant)
        act =act->ant;

    nae = act;
    act = nae->sig;

    if(nae == *l)
        *l =nae->sig;

    if(act)
        act->ant = NULL;

    memcpy(dato,nae->dato,MIN(tamDato,nae->tamDato));
    free(nae->dato);
    free(nae);


    return TODO_OK;
}

int verFrente(const Lista *l,  void * dato,size_t tamDato)
{
    Nodo * act =*l;

    if (!act)
        return ERR_NODO;

    while(act->ant)
        act = act->ant;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));


    return TODO_OK;
}

int verFondo(const Lista *l,  void * dato,size_t tamDato)
{
    Nodo *act =*l;
    if(!act)
        return ERR_NODO;

    while(act->sig)
        act =act->sig;

    memcpy(dato,act->dato,MIN(tamDato,act->tamDato));


    return TODO_OK;
}
