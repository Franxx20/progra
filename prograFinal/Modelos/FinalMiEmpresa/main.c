#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define minimo(x,y) ((x) <= (y)? (x) : (y))

typedef struct
{
    int nroPedido;
    char codPro[11];
    int cantPedida;
    char codSector;
    char oficina[21];
}Pedido;

typedef struct
{
    char codPro[11];
    int cantPedida;
}Compra;

typedef struct
{
    char codSector;
    int cantPedida;
    char codPro[11];
    char oficina[21];
}Sector;

typedef struct sNodo
{
    void* elem;
    size_t tamElem;
    struct sNodo* ant;
    struct sNodo* sig;
}Nodo;

typedef Nodo* Lista;

typedef int (*Cmp)(const void* elem1,const void* elem2);
typedef void (*Actualizar)(void* actualizado, const void* actualizador);
typedef void (*Mostrar) (const void* elem);

void crearLista(Lista *pl);
int insertarOActualizarEnLista(Lista *pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int eliminarPrimeroLista(Lista *pl, void* elem, size_t tamElem);
int eliminarUltimosNdeLaLista(Lista *pl, int n);
int cantidadDeNodosEnLista(const Lista *pl);
void recorrerLista(Lista* pl, Mostrar mostrar);
void vaciarLista(Lista* pl);
int listaVacia(const Lista *pl);


void generarArch();
int cargarEnListaComprasYSectores(const char *nombreArch, Lista *plCompras, Lista *plSectores);
void cadAPedido(char* cad, Pedido* reg);
int cadAInt(char* cad);

int compararCompra(const void* elem1, const void* elem2);
void actualizarSectores(void* actualizado, const void* actualizador);
void actualizarCompra(void* actualizado, const void* actualizador);
int compararSectores(const void* elem1, const void* elem2);
void actualizarSectores(void* actualizado, const void* actualizador);
void mostrarPedidoCompras(const void* elem);
void mostrarPedidoSectores(const void* elem);

int strlen_mio(const char* cad);
int strcmp_mio(const char* cad1, const char* cad2);
char* strncpy_mio(char* dest, const char* origen, size_t tamMax);
char* strrchr_mio( char* cad, char carac);
char* strchr_mio( char* cad, char carac);

int main()
{
    generarArch();

    FILE *pfBin = fopen("resultadoCompras.bin","wb");
    if(!pfBin)
    {
        fclose(pfBin);
        return -1;
    }

    Lista listaSectores;
    Lista listaCompras;

    crearLista(&listaCompras);
    crearLista(&listaSectores);

    cargarEnListaComprasYSectores("pedidos.txt",&listaCompras,&listaSectores);

    puts("Listas antes del eliminarUltimosNdeLaLista");
    recorrerLista(&listaCompras,mostrarPedidoCompras);
    puts("");
    recorrerLista(&listaSectores,mostrarPedidoSectores);
    puts("");

    eliminarUltimosNdeLaLista(&listaCompras,3);
    eliminarUltimosNdeLaLista(&listaSectores,6);

    puts("Listas despues del eliminarUltimosNdeLaLista");
    recorrerLista(&listaCompras,mostrarPedidoCompras);
    puts("");
    recorrerLista(&listaSectores,mostrarPedidoSectores);
    puts("");


    while(!listaVacia(&listaCompras))
    {
        Compra regCom;

        eliminarPrimeroLista(&listaCompras,&regCom,sizeof(Compra));
        fwrite(&regCom,sizeof(Compra),1,pfBin);
    }

    vaciarLista(&listaSectores);

    fclose(pfBin);

    return 0;
}

int cargarEnListaComprasYSectores(const char *nombreArch, Lista *plCompras, Lista *plSectores)
{
    FILE *pf = fopen(nombreArch,"rt");
    if(!pf)
    {
        fclose(pf);
        return -1;
    }

    char cadAux[256];
    Pedido regPed;
    Compra regCom;
    Sector regSec;
    while(fgets(cadAux, sizeof(cadAux),pf))
    {
        cadAPedido(cadAux,&regPed);

        regCom.cantPedida = regPed.cantPedida;
        strncpy_mio(regCom.codPro,regPed.codPro,sizeof(regCom.codPro));

        regSec.cantPedida = regPed.cantPedida;
        strncpy_mio(regSec.codPro,regPed.codPro,sizeof(regSec.codPro));
        regSec.codSector = regPed.codSector;
        strncpy_mio(regSec.oficina,regPed.oficina,sizeof(regSec.oficina));

        insertarOActualizarEnLista(plCompras,&regCom,sizeof(Compra),compararCompra,actualizarCompra);
        insertarOActualizarEnLista(plSectores,&regSec,sizeof(Sector),compararSectores,actualizarSectores);
    }

    return 1;
}

void cadAPedido(char* cad, Pedido* reg)
{
    char *aux = strchr_mio(cad,'\n');
    *aux = '\0';

    aux = strrchr_mio(cad,'|');
    aux++;
    strncpy_mio(reg->oficina,aux,sizeof(reg->oficina));
    aux--;
    *aux = '\0';

    aux = strrchr_mio(cad,'|');
    aux++;
    reg->codSector = *aux;
    aux--;
    *aux = '\0';

    aux = strrchr_mio(cad,'|');
    aux++;
    reg->cantPedida = cadAInt(aux);
    aux--;
    *aux = '\0';

    aux = strrchr_mio(cad,'|');
    aux++;
    strncpy_mio(reg->codPro,aux,sizeof(reg->codPro));
    aux--;
    *aux = '\0';

    reg->nroPedido = cadAInt(cad);
}

int cadAInt(char* cad)
{
    int digitos = strlen_mio(cad);
    int num = 0;

    while(*cad)
    {
        float potencia = 1;

        for(int i = 1; i < digitos ; i++)
            potencia *= 10;

        num+=(potencia*(*cad-'0'));

        digitos--;
        cad++;
    }

    return num;
}

void generarArch()
{
    FILE *pf = fopen("pedidos.txt","wt");


    fprintf(pf,"1|MANAOS|10|F|Factory\n");
    fprintf(pf,"10|COCA|12|T|Trayectory\n");
    fprintf(pf,"9|COCA|5|F|Factory\n");
    fprintf(pf,"5|MANAOS|7|A|Abiline\n");
    fprintf(pf,"3|MALBORO|20|L|Larry\n");
    fprintf(pf,"2|MALBORO|10|C|Carry\n");
    fprintf(pf,"6|REXONA|4|B|Billy\n");
    fprintf(pf,"8|DOVE|10|A|Abiline\n");
    fprintf(pf,"4|DOVE|5|L|Larry\n");
    fprintf(pf,"7|ARROZ|10|B|Billy\n");
    fprintf(pf,"11|MALBORO|2|C|Carry\n");

    fclose(pf);
}

int compararCompra(const void* elem1, const void* elem2)
{
    Compra* ped1 = (Compra*)elem1;
    Compra* ped2 = (Compra*)elem2;

    return strcmp_mio(ped1->codPro,ped2->codPro);
}

void actualizarCompra(void* actualizado, const void* actualizador)
{
    Compra* pedActualizado = (Compra*)actualizado;
    Compra* pedActualizador = (Compra*)actualizador;

    pedActualizado->cantPedida += pedActualizador->cantPedida;
}

void actualizarSectores(void* actualizado, const void* actualizador)
{
    Sector* pedActualizado = (Sector*)actualizado;
    Sector* pedActualizador = (Sector*)actualizador;

    pedActualizado->cantPedida+=pedActualizador->cantPedida;
}

int compararSectores(const void* elem1, const void* elem2)
{
    Sector* ped1 = (Sector*)elem1;
    Sector* ped2 = (Sector*)elem2;

    if(ped1->codSector-ped2->codSector == 0)
        return strcmp_mio(ped1->codPro,ped2->codPro);
    else
        return ped1->codSector-ped2->codSector;
}

void mostrarPedidoCompras(const void* elem)
{
    Compra* ped = (Compra*)elem;

    printf("%s %d\n",ped->codPro,ped->cantPedida);
}

void mostrarPedidoSectores(const void* elem)
{
    Sector* ped = (Sector*)elem;

    printf("%c %s %d %s\n",ped->codSector,ped->codPro,ped->cantPedida,ped->oficina);
}


void crearLista(Lista *pl)
{
    *pl = NULL;
}

int insertarOActualizarEnLista(Lista *pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    Nodo* nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue || !nue->elem)
    {
        free(nue->elem);
        free(nue);
        return -3;
    }

    memcpy(nue->elem,elem,tamElem);
    nue->tamElem = tamElem;

    if(!*pl)
    {
        nue->ant = NULL;
        nue->sig = NULL;
        *pl = nue;

        return 1;
    }

    if(cmp((*pl)->elem,elem) < 0)
    {
        Nodo* act = *pl;

        while(act->sig && cmp(act->elem,elem) < 0)
            act = act->sig;

        int comp = cmp(act->elem,elem);

        if(comp < 0)
        {
            Nodo* ant = act;
            Nodo* sig = act->sig;

            ant->sig = nue;

            nue->ant = ant;
            nue->sig = sig;

            return 1;
        }

        if(comp > 0)
        {
            Nodo* ant = act->ant;
            Nodo* sig = act;

            ant->sig = nue;
            sig->ant = nue;

            nue->ant = ant;
            nue->sig = sig;

            return 1;
        }

        if(comp == 0)
        {
            actualizar(act->elem,elem);

            return 1;
        }
    }

    if(cmp((*pl)->elem,elem) > 0)
    {
        Nodo* act = *pl;

        while(act->ant && cmp(act->elem,elem) > 0)
            act = act->ant;

        int comp = cmp(act->elem,elem);

        if(comp > 0)
        {
            Nodo* ant = act->ant;
            Nodo* sig = act;

            sig->ant = nue;

            nue->ant = ant;
            nue->sig = sig;

            return 1;
        }

        if(comp < 0)
        {
            Nodo* ant = act;
            Nodo* sig = act->sig;

            ant->sig = nue;
            sig->ant = nue;

            nue->ant = ant;
            nue->sig = sig;

            return 1;
        }

        if(comp == 0)
        {
            actualizar(act->elem,elem);

            return 1;
        }
    }

    actualizar((*pl)->elem,elem);

    return 1;
}

void recorrerLista(Lista* pl, Mostrar mostrar)
{
    if(!*pl)
        return;

    Nodo* act = *pl;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        mostrar(act->elem);
        act = act->sig;
    }
}

int eliminarUltimosNdeLaLista(Lista *pl, int n)
{
    if(!*pl)
        return 0;

    if(cantidadDeNodosEnLista(pl) < n)
        return 0;


    Nodo *act = *pl;

    while(act->sig)
        act = act->sig;

    int i = 1;

    while(act && i <= n)
    {
        Nodo* nae = act;

        act = nae->ant;

        if(act)
            act->sig = NULL;

        free(nae->elem);
        free(nae);

        i++;
    }

    *pl = act;

    return 1;
}

int cantidadDeNodosEnLista(const Lista *pl)
{
    Nodo* act = *pl;
    int acum = 0;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        acum++;
        act = act->sig;
    }

    return acum;
}

int eliminarPrimeroLista(Lista *pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return 0;

    Nodo *act = *pl;

    while(act->ant)
        act = act->ant;

    Nodo* nae = act;

    act = act->sig;

    if(act)
        (act)->ant = NULL;

    memcpy(elem,nae->elem,minimo(tamElem,nae->tamElem));

    free(nae->elem);
    free(nae);

    *pl = act;

    return 1;
}

int listaVacia(const Lista *pl)
{
    return *pl == NULL;
}

void vaciarLista(Lista* pl)
{
    while((*pl)->ant)
        pl = &(*pl)->ant;

    Nodo *act = *pl;

    while(act)
    {
        Nodo* nae = act;

        act = act->sig;

        if(act)
            act->ant = NULL;

        free(nae->elem);
        free(nae);
    }

    *pl = act;
}

int strlen_mio(const char* cad)
{
    int cant = 0;

    while(*cad)
    {
        cant++;
        cad++;
    }

    return cant;
}

int strcmp_mio(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2)
    {
        if(*cad1 != *cad2)
            return *cad1-*cad2;
        cad1++;
        cad2++;
    }

    if(!*cad1 && *cad2)
        return *cad1-*cad2;

    if(*cad1 && !*cad2)
        return *cad1-*cad2;

    return 0;
}

char* strncpy_mio(char* dest, const char* origen, size_t tamMax)
{
    int i = 0;
    while(*origen && i <tamMax)
    {
        *dest = *origen;
        i++;
        dest++;
        origen++;
    }

    *dest = '\0';

    return dest;
}

char* strrchr_mio(char* cad, char carac)
{
    int i = 0;

    while(*cad)
    {
        i++;
        cad++;
    }

    for( ; i>0 ; i--)
    {
        if(*cad == carac)
            return cad;
        cad--;
    }

    return NULL;
}

char* strchr_mio(char* cad, char carac)
{
    while(*cad)
    {
        if(*cad == carac)
            return cad;
        cad++;
    }

    return NULL;
}

