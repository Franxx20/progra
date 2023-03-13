#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <memory.h>

#define MIN(x,y) x<=y?x:y

typedef struct sNodo
{
    void* dato;
    struct sNodo* sig;
    size_t tamElem;
} Nodo;

typedef struct
{
    int fila;
    int columna;
    int num;
} NumeroEnMatriz;

typedef Nodo* Lista;

typedef int(*Cmp)(const void* elem1, const void* elem2);

void crearLista(Lista *pl);
int insertarEnListaAlPrincipio(Lista *pl, const void* dato, size_t tamElem);
int buscarElemMayorNoClave(Lista *pl, Cmp cmp, void* mayor, size_t tamElem);
int eliminarDeListaPrimero(Lista *pl, void* dato, size_t tamElem);
int buscarEnLista(const Lista *pl, void* dato, size_t tamElem, Cmp cmp);
void vaciarLista(Lista *pl);
int listaVacia(const Lista *pl);

void crearArchTxt();

int verificar_mat(const char* nomArch, int* filas, int *columnas);
Lista* cargar_mat_rala(const char* nomArch);
void imprimir_mat_rala(const Lista* pl, int filas, int columnas);
NumeroEnMatriz maxDP_mat_rala(Lista *pl, int filas);
void parseo(char* cad, NumeroEnMatriz* reg);
int compararNumDP(const void* elem1, const void* elem2);
int compararFilCol(const void* elem1, const void* elem2);

int main()
{
    crearArchTxt();

    int filas = 4;
    int columnas = 4;

    if(verificar_mat("mat1.txt", &filas, &columnas))
        puts("La matriz tiene un elemento no nulo en la diagonal principal");
    else
    {
        puts("La matriz no tiene un elemento no nulo en la diagonal principal, abortando programa...");
        return 1;
    }

    Lista *listaElemNoNulos = cargar_mat_rala("mat1.txt");

    NumeroEnMatriz nroMax = maxDP_mat_rala(listaElemNoNulos, filas);

    printf("El numero mas grande de la diagonal principal es %d en [%d][%d]\n",nroMax.num,nroMax.fila,nroMax.columna);

    imprimir_mat_rala(listaElemNoNulos,filas,columnas);

    for(int i = 0; i < filas; i++)
        vaciarLista(&listaElemNoNulos[i]);

    return 0;
}

void crearArchTxt()
{
    FILE *pf = fopen("mat1.txt","wt");
    if(!pf)
    {
        fclose(pf);
        return;
    }


    //    fprintf(pf,"[3][3]\n");
//    fprintf(pf,"[3][3]7\n");
//    fprintf(pf,"[2][2]3\n");
//    fprintf(pf,"[2][0]1\n");
//    fprintf(pf,"[0][3]6\n");
//    fprintf(pf,"[0][0]4\n");
    fprintf(pf,"[3][3]\n");
    fprintf(pf,"[3][3]7\n");
    fprintf(pf,"[2][2]9\n");
    fprintf(pf,"[2][1]1\n");
    fprintf(pf,"[1][3]9\n");
    fprintf(pf,"[1][1]4\n");
/*
    fprintf(pf,"[10][5]\n");
    fprintf(pf,"[1][1]7\n");
    fprintf(pf,"[3][2]3\n");
    fprintf(pf,"[8][5]1\n");
    fprintf(pf,"[8][2]10\n");
    fprintf(pf,"[10][4]6\n");
    fprintf(pf,"[5][5]15\n");


     fprintf(pf,"[500][250]\n");
     fprintf(pf,"[253][55]14\n");
     fprintf(pf,"[100][123]5\n");
     fprintf(pf,"[54][12]1\n");
     fprintf(pf,"[100][100]100\n");
     fprintf(pf,"[250][250]300\n");
     fprintf(pf,"[50][50]200\n");
     fprintf(pf,"[345][68]66\n");
     fprintf(pf,"[100][200]74\n");
     fprintf(pf,"[125][249]97\n");
    */
    fclose(pf);
}

int verificar_mat(const char* nomArch, int* filas, int *columnas)
{
    FILE *pf = fopen(nomArch,"rt");
    if(!pf)
    {
        fclose(pf);
        return 0;
    }

    char cad[256];
    NumeroEnMatriz reg;

    fgets(cad,sizeof(cad),pf);
    sscanf(cad,"[%d][%d]",filas,columnas);
//    (*filas)++;
//    (*columnas)++;

    if(*filas == 0 || *columnas == 0)
        return 0;

    while(fgets(cad,sizeof(cad),pf))
    {
        sscanf(cad,"[%d][%d]%d",&reg.fila,&reg.columna,&reg.num);

        if(reg.columna == reg.fila)
            return 1;
    }

    return 0;
}

Lista* cargar_mat_rala(const char* nomArch)
{
    FILE *pf = fopen(nomArch,"rt");
    if(!pf)
    {
        fclose(pf);
        return NULL;
    }

    char cad[256];
    int columnas;
    int filas;
    NumeroEnMatriz reg;

    fgets(cad,sizeof(cad),pf);
    sscanf(cad,"[%d][%d]",&filas,&columnas);

    Lista *Matriz = (Lista*)calloc(filas,sizeof(Lista));

    for(int i = 0; i < filas; i++)
    {
        crearLista(&Matriz[i]);
    }

    while(fgets(cad,sizeof(cad),pf))
    {
        parseo(cad,&reg);

        insertarEnListaAlPrincipio(&Matriz[reg.fila-1],&reg,sizeof(NumeroEnMatriz));
    }

    fclose(pf);
    return Matriz;
}

NumeroEnMatriz maxDP_mat_rala(Lista *pl, int filas)
{
    NumeroEnMatriz mayor = {0,0,0};

    for(int i = 0; i < filas; i++)
        buscarElemMayorNoClave(&pl[i],compararNumDP, &mayor, sizeof(NumeroEnMatriz));

    return mayor;
}

void imprimir_mat_rala(const Lista* pl, int filas, int columnas)
{
    NumeroEnMatriz reg;

    for(int i = 0; i < filas; i++)
    {
        reg.fila = i+1;
        for(int j = 0; j < columnas; j++)
        {
            reg.columna = j+1;
            if(buscarEnLista(&pl[i],&reg,sizeof(NumeroEnMatriz),compararFilCol))
                printf("%d\t",reg.num);
            else
                printf("0\t");
        }
        printf("\n");
    }
}

void parseo(char* cad, NumeroEnMatriz* reg)
{
    char* aux = strrchr(cad,'\n');
    *aux = '\0';

    aux = strrchr(cad,']');
    aux++;
    sscanf(aux,"%d",&reg->num);
    aux--;
    *aux = '\0';

    aux = strrchr(cad,'[');
    aux++;
    sscanf(aux,"%d",&reg->columna);
    aux--;
    *aux = '\0';

    aux = strrchr(cad,']');
    *aux = '\0';

    sscanf(cad+1,"%d",&reg->fila);
}

void crearLista(Lista *pl)
{
    *pl = NULL;
}
int insertarEnListaAlPrincipio(Lista *pl, const void* dato, size_t tamElem)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->dato = malloc(tamElem);

    if(!nue || !nue->dato)
    {
        free(nue->dato);
        free(nue);
        return 0;
    }

    memcpy(nue->dato,dato,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->sig = NULL;
        *pl = nue;
        return 1;
    }

    nue->sig = *pl;
    *pl = nue;

    return 1;
}
int eliminarDeListaPrimero(Lista *pl, void* dato, size_t tamElem)
{
    if(!*pl)
        return 0;

    Nodo* nae = *pl;

    memcpy(dato,nae->dato,MIN(tamElem,nae->tamElem));

    *pl = nae->sig;

    return 1;
}
int buscarEnLista(const Lista *pl, void* dato, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return 0;

    while(*pl)
    {
        if(cmp((*pl)->dato,dato) == 0)
        {
            memcpy(dato,(*pl)->dato,MIN(tamElem,(*pl)->tamElem));
            return 1;
        }
        pl = &(*pl)->sig;
    }

    return 0;
}
int buscarElemMayorNoClave(Lista *pl, Cmp cmp, void* mayor, size_t tamElem)
{
    if(!*pl)
        return 0;

    while(*pl)
    {
        if(cmp(mayor,(*pl)->dato) < 0)
            memcpy(mayor,(*pl)->dato,MIN(tamElem,(*pl)->tamElem));

        pl = &(*pl)->sig;
    }

    return 1;
}
void vaciarLista(Lista *pl)
{
    while(*pl)
    {
        Nodo *nae = *pl;
        *pl = nae->sig;

        free(nae->dato);
        free(nae);
    }
}

int compararNumDP(const void* elem1, const void* elem2)
{
    NumeroEnMatriz* num1 = (NumeroEnMatriz*)elem1;
    NumeroEnMatriz* num2 = (NumeroEnMatriz*)elem2;

    if(num2->columna == num2->fila)
        return num1->num-num2->num;
    else
        return 1;
}

int compararFilCol(const void* elem1, const void* elem2)
{
    NumeroEnMatriz* num1 = (NumeroEnMatriz*)elem1;
    NumeroEnMatriz* num2 = (NumeroEnMatriz*)elem2;

    if(num1->columna == num2->columna)
        return num1->fila-num2->fila;
    else
        return num1->columna-num2->columna;
}
