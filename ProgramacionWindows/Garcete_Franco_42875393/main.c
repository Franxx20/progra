/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
** DNI:                                                       													**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**                      																					   	**
******************************************************************************************************************
** Nota:																									   	**
*****************************************************************************************************************/

#include <stdio.h>
#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include "../Comun/Comun.h"
#include "../Cadena/Cadena.h"
#include "../Archivo/Archivo.h"
#include<string.h>
#include<stdlib.h>
#include "../Solucion1erParcialFabricasComputadoras/Solucion1erParcialFabricasComputadoras.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"

#define ERR_NOSALTOLINEA 5

//#define SOLUCION_DOC
#define SOLUCION_ALU

#define MIN_ALU(a,b) ((a)<(b)?(a):(b))

int procesarArchivos_ALU(const char * nombreProdCod, const char * nombreProdChu,const char *nombreCliCor,const char * nombreCliChu, const char * nombreProdFus, const char * nombreCliFus);
int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp);
int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp);
int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar);
int eliminarDeListaPrimero_ALU(Lista*l, void * dato, size_t tamDato);


int compararProductos_ALU(const void * prod1, const void * prod2);
int compararClientes_ALU(const void * cli1, const void* cli2);

int parsearChubutTxt_ALU(char * linea,Producto* prod);

int productosTxtABin_ALU(const void * nombreArchTxt,const void * nombreArchivoBin);

void actualizarClientes_ALU(void * actualizado, const void * actualizador);
void actualizarProductos_ALU(void * actualizado, const void * actualizador);

void mostrarArchivoClientes_ALU(const char * nombreArchivo);
void mostrarArchivoProductosBin_ALU(const char * nombreArchivo);
void mostrarArchivoProductosTxt_ALU(const char* nombreArchivo); // NO HACIA FALTA



//////// FUNCIONES DE LISTA
void crearLista_ALU(Lista *l);
void vaciarLista_ALU(Lista*l);

booleano listaVacia_ALU(const Lista *l);
booleano listaLlena_ALU(const Lista *l, size_t tamDato);

int insertarEnListaAlFinal_ALU(Lista *l,void * dato,size_t tamDato);
void ordenarLista_ALU(Lista *l, Cmp cmp);

int main()
{
    int resp = generarArchivos();

    if(resp != TODO_OK)
    {
        printf("Error al generar los archivos");
        return resp;
    }

    puts("Archivos Pre Fusion:\n");

    puts(PROD_COR);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_COR);



    puts("\n");

    puts(PROD_CHU_TXT);
    puts("=========================================");
    mostrarArchivoProductosTxt(PROD_CHU_TXT);

    puts("\n");

    puts(CLI_COR);
    puts("=========================================");
    mostrarArchivoClientes(CLI_COR);

    puts("\n");

    puts(CLI_CHU);
    puts("=========================================");
    mostrarArchivoClientes(CLI_CHU);


#ifdef SOLUCION_DOC
    resp = procesarArchivos(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
#else
    resp = procesarArchivos_ALU(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
#endif

    if(resp != TODO_OK)
    {
        printf("Error al procesar los archivos");
        return resp;
    }

    puts("\n\nArchivos Post Fusion:\n");

    puts(PROD_FUS);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_FUS);

    puts("\n");

    puts(CLI_FUS);
    puts("=========================================");
    mostrarArchivoClientes(CLI_FUS);
//
//        puts("Archivo productos bin");
//    mostrarArchivoProductosBin(CLI_CHU);

    return 0;
}

int procesarArchivos_ALU(const char * nombreProdCor, const char * nombreProdChu,const char *nombreCliCor,const char * nombreCliChu, const char * nombreProdFus, const char * nombreCliFus)
{

    Lista lChubut;
    crearLista_ALU(&lChubut);
    productosTxtABin_ALU(nombreProdChu,"Productos-chu2.dat");



//    printf("\n\n\n PRODUCTOS CHUBUT BINARIO2\n\n\n");

    ordenarArchivo("Productos-chu2.dat",sizeof(Producto),compararProductos_ALU);
//    mostrarArchivoProductosBin_ALU("Productos-chu2.dat");


//    printf("\n\n\n PRODUCTOS CHUBUT BINARIO\n\n\n");
//    mostrarArchivoProductosBin_ALU("Productos-chu.dat");

//
//    printf("\n\n\n PRODUCTOS CORDOBA BINARIO\n\n\n");
//    mostrarArchivoProductosBin_ALU(nombreProdCor);

//    printf("\n\n\n PRODUCTOS CORDOBA BINARIO ORDENADO\n\n\n");
    ordenarArchivo(nombreProdCor,sizeof(Producto),compararProductos_ALU);
//    mostrarArchivoProductosBin_ALU(nombreProdCor);


    //fusionarArchivos(nombreProdCor,"Productos-chu2.dat",nombreProdFus,sizeof(Producto),compararProductos_ALU);
    fusionarArchivos_ALU(nombreProdCor,"Productos-chu2.dat",nombreProdFus,sizeof(Producto),compararProductos_ALU);
//
//    printf("\n\n\n PRODUCTOS FUSIONADOS BINARIO SIN DUPES \n\n\n");
//    mostrarArchivoProductosBin_ALU(nombreProdFus);


//    printf("\n\n\n PRODUCTOS FUSIONADOS BINARIO CON DUPES \n\n\n");
    eliminarDuplicadosArchivoOrd(nombreProdFus,sizeof(Producto),compararProductos_ALU,actualizarProductos);
//    mostrarArchivoProductosBin_ALU(nombreProdFus);

    vaciarLista_ALU(&lChubut);

    /// EMPEZAMOS CON CLIENTES

//    printf("\n\n\n CLIENTES CHUBUT BINARIO\n\n\n");
//    mostrarArchivoClientes_ALU(nombreCliChu);

//    printf("\n\n\n CLIENTES CORDOBA BINARIO\n\n\n");
//    mostrarArchivoClientes_ALU(nombreCliCor);

//    printf("\n\n\n CLIENTES CHUBUT BINARIO ORDENADO\n\n\n");
ordenarArchivo(nombreCliChu,sizeof(Cliente),compararClientes_ALU);
    //    ordenarArchivo_ALU(nombreCliChu,sizeof(Cliente),compararClientes_ALU);

//    mostrarArchivoClientes_ALU(nombreCliChu);
//
//    printf("\n\n\n CLIENTES CORDOBA BINARIO ORDENADO\n\n\n");
    ordenarArchivo(nombreCliCor,sizeof(Cliente),compararClientes_ALU);
       // ordenarArchivo_ALU(nombreCliCor,sizeof(Cliente),compararClientes_ALU);

//    mostrarArchivoClientes_ALU(nombreCliCor);

    fusionarArchivos(nombreCliCor,nombreCliChu,nombreCliFus,sizeof(Cliente),compararClientes_ALU);

//    printf("\n\n\n CLIENTES FUSIONADOS BINARIO CON DUPLICADOS \n\n\n");
//    mostrarArchivoClientes_ALU(nombreCliFus);


//    printf("\n\n\n CLIENTES FUSIONADOS BINARIO SIN DUPLICADOS \n\n\n");
    eliminarDuplicadosArchivoOrd(nombreCliFus,sizeof(Cliente),compararClientes_ALU,actualizarClientes_ALU);


//    mostrarArchivoClientes_ALU(nombreCliFus);
    remove(nombreProdChu);
    rename("Productos-chu2.dat",nombreProdChu);
    return 0;
}



int parsearChubutTxt_ALU(char * linea,Producto* prod)
{
    char * aux = strchr(linea,'\n');
    if(!aux)
        return ERR_NOSALTOLINEA;

    *aux = '\0';
    // buscamos el stock
    aux = strrchr(linea,'|');
    sscanf( aux + 1, "%d", &prod->stock);

    // BUSCAMOS el precio
    * aux = '\0';
    aux = strrchr(linea, '|');

    sscanf(aux +1, "%f", &prod->precio);

    // BUSCAMOS LA DESCRIPCION
    *aux = '\0';
    aux = strrchr(linea, '|');
    strncpy(prod->descripcion,aux+1,50);


    // BUSCAMOS EL CODIGO DE PRODUCTO
    *aux = '\0';
    strncpy(prod->codigo, linea,20);

    return 0;
}


int compararProductos_ALU(const void * prod1, const void * prod2)
{
    Producto * p1 = (Producto *)prod1;
    Producto * p2 = (Producto *)prod2;

    int res = strcmp(p1->codigo, p2->codigo);
    return res;
}
int compararClientes_ALU(const void * cli1, const void* cli2)
{
    Cliente * c1 = (Cliente *)cli1;
    Cliente * c2 = (Cliente *)cli2;

    return c1->codigo - c2->codigo;
}

int productosTxtABin_ALU(const void * nombreArchTxt,const void * nombreArchivoBin)
{
    FILE * fArchTxt = fopen(nombreArchTxt,"rt");
    FILE * fArchBin = fopen(nombreArchivoBin, "wb");

    if(!fArchTxt)
    {
        fprintf(stdout,"ERROR AL ABRIR EL ARCHIVO DE TEXTO EN LECTURA");
    }
    if(!fArchBin)
    {
        fprintf(stdout,"ERROR AL ABRIR EL ARCHIVO BINARIO EN ESCRITURA");
    }

    char linea[256];
    Producto prod;
    while(fgets(linea,256,fArchTxt))
    {
        parsearChubutTxt_ALU(linea,&prod);
        fwrite(&prod,sizeof(Producto),1,fArchBin);
    }



    fclose(fArchTxt);
    fclose(fArchBin);
    return 0;

}

int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp)
{
    FILE * fArch1 = fopen(nombreArchivo1, "rb");
    FILE * fArch2 = fopen(nombreArchivo2, "rb");
    FILE * fArchFus = fopen(nombreArchivoFus, "wb");

    if(!fArch1  || !fArch2 )
    {
        fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO EN LECTURA\n");
    }

    if(!fArchFus)
    {
        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO EN ESCRITURA\n");
    }

    void * d1 = malloc(tamReg);
    void *d2 = malloc(tamReg);

    void *dNuevo = malloc(tamReg);

    fread(d1,tamReg,1,fArch1);
    fread(d2,tamReg,1,fArch2);

    while(!feof(fArch1) && !feof(fArch2))
    {
        if(cmp(d1,d2) == 0)
        {
            fwrite(d1,tamReg,1,fArchFus);
            fwrite(d2,tamReg,1,fArchFus);
            fread(d1,tamReg,1,fArch1);
            fread(d2,tamReg,1,fArch2);
        }
        if(cmp(d1,d2)<0)
        {
            fread(d1,tamReg,1,fArch1);
        }
        if(cmp(d1,d2) >0)
        {
            fread(d2,tamReg,1,fArch2);
        }
    }

    while(!feof(fArch1))
    {
        fread(d1,tamReg,1,fArch1);
        fwrite(d1,tamReg,1,fArchFus);
    }
    while(!feof(fArch2))
    {
        fread(d2,tamReg,1,fArch2);
        fwrite(d2,tamReg,1,fArchFus);
    }

    free(d1);
    free(d2);
    free(dNuevo);
    fclose(fArch1);
    fclose(fArch2);
    fclose(fArchFus);
    return 1;
}

int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp)
{
    Lista l;
    crearLista(&l);
    FILE * fArch = fopen(nombreArchivo,"rb");
    if(!fArch)
    {
        fprintf(stderr," ERROR AL ABRIR EL ARCHIVO BINARIO EN LECTURA PARA ORDENAR" );
        return falso;
    }

    void * dato = malloc(tamReg);

    fread(dato,tamReg,1,fArch);
    while(!feof(fArch) && !listaLlena_ALU(&l,tamReg))
    {
        insertarEnListaAlFinal_ALU(&l,dato,tamReg);
        fread(dato,tamReg,1,fArch);
    }

    ordenarLista_ALU(&l,cmp);


    free(dato);
    fclose(fArch);

    FILE * fArch2 = fopen(nombreArchivo,"wb");
    if(!fArch2)
    {
        fprintf(stderr," ERROR AL ABRIR EL ARCHIVO BINARIO EN ESCRITURA PARA ORDENAR" );
        return falso;
    }
    void * dato2 =malloc(tamReg);
    while(!listaVacia(&l))
    {
        eliminarDeListaPrimero_ALU(&l,dato,tamReg);
        fwrite(dato,tamReg,1,fArch2);
    }

    vaciarLista(&l);
    fclose(fArch2);
    free(dato2);
    return verdadero;
}

int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar);

void actualizarClientes_ALU(void * actualizado, const void * actualizador)
{
///// ESTA FUNCION NO REALIZA NADA
}

void actualizarProductos_ALU(void * actualizado, const void * actualizador)
{
    int * stock = (int*)actualizado;
    const int * stock2 = (const int * )actualizador;

    *stock+=*stock2;
}

void mostrarArchivoClientes_ALU(const char * nombreArchivo)
{
    FILE * fArch = fopen(nombreArchivo, "rb");
    Cliente c;


    if(!fArch)
    {
        fprintf(stdout, "ERROR AL ABRIR EL ARCHIVO BINARIO CLIENTES PARA MOSTRAR");
        return;
    }

    fread(&c,sizeof(Cliente),1,fArch);
    while(!feof(fArch))
    {
        fprintf(stdout, "%d\t%s\n",c.codigo,c.apellidoYNombre);
        fread(&c,sizeof(Cliente),1,fArch);
    }

    fclose(fArch);
}

void mostrarArchivoProductosBin_ALU(const char * nombreArchivo)
{
    FILE * fArch = fopen(nombreArchivo, "rb");
    Producto p;

    if(!fArch)
    {
        fprintf(stdout, "ERROR AL ABRIR EL ARCHIVO BINARIO PRODUCTOS PARA MOSTRAR");
        return;
    }

    fread(&p,sizeof(Producto),1,fArch);
    while(!feof(fArch))
    {

        fprintf(stdout,"%-21s|%-52s|%-.2f|%-4d\n",p.codigo,p.descripcion,p.precio,p.stock);

        fread(&p,sizeof(Producto),1,fArch);
    }

    fclose(fArch);
}

void mostrarArchivoProductosTxt_ALU(const char* nombreArchivo)
{
    FILE * fArch = fopen(nombreArchivo,"rt");
    if(!fArch)
    {
        fprintf(stdout,"ERROR AL ABRIR EL ARCHIVO DE TEXTO PRODUCTOS PARA MOSTRAR" );
        return;
    }

    char linea [256];
    while(fgets(linea,256,fArch))
    {
        fputs(linea,fArch);
    }
    fclose(fArch);
}


////// FUNCIONES DE LISTA
void crearLista_ALU(Lista *l)
{
    *l = NULL;
}

void vaciarLista_ALU(Lista*l)
{
    Nodo * nae;
    while(*l)
    {
        nae = *l;
        *l= nae->sig;
        free(nae->elem);
        free(nae);
    }
}

booleano listaVacia_ALU(const Lista *l)
{
    return *l == NULL;
}

booleano listaLlena_ALU(const Lista *l, size_t tamDato)
{
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    void * dato = malloc(tamDato);
    free(nodo);
    free(dato);

    return !nodo || !dato;
}

int insertarEnListaAlFinal_ALU(Lista *l,void * dato,size_t tamDato)
{
    Nodo * nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue || !(nue->elem = malloc(tamDato)))
    {
        free(nue);
        fprintf(stdout,"LISTA LLENA al querer insertar al final\n");
        return falso;
    }

    while(*l)
    {
        l = &(*l)->sig;
    }

    memcpy(nue->elem,dato,tamDato);
    nue->sig = NULL;
    nue->tamElem = tamDato;
    *l = nue;
    return verdadero;
}


void ordenarLista_ALU(Lista *l, Cmp cmp)
{
    Lista lOrd;
    Lista *plOrd;
    Nodo * aux;

    while(*l)
    {
        // desacoplo el nodo
        aux = *l;
        *l = aux->sig;
        plOrd= &lOrd;
        // mientras el nodo de la lista nueva sea menor al nodo a insertar. paso el puntero de lista al siguiente  elemento hasta encontrar donde insertar el nuevo
        while(*plOrd && cmp((*plOrd)->elem,aux->elem)<0)
            plOrd = &(*plOrd)->sig;

        aux->sig = *plOrd;
        *plOrd = aux;
    }
}

int eliminarDeListaPrimero_ALU(Lista*l, void * dato, size_t tamDato)
{
    if(!*l)
        return falso;

    Nodo * nae = *l;
    *l = nae->sig;
    memcpy(dato,nae->elem,MIN_ALU(tamDato,nae->tamElem));

    return verdadero;
}
