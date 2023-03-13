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
#include <stdlib.h>
#include <memory.h>
#include<string.h>

#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include "../Comun/Comun.h"
#include "../Cadena/Cadena.h"
#include "../Archivo/Archivo.h"
#include "../Solucion1erParcialFabricasComputadoras/Solucion1erParcialFabricasComputadoras.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define PROD_CHU_BIN "Productos-chu.bin"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"

#define minimo_ALU(x,y) ((x) <= (y) ? (x) : (y))
#define ERR_MEM -5
#define ERR_LINEA -6

//#define SOLUCION_DOC
#define SOLUCION_ALU

// FUNCIONES GENERALES
int productosTxtABin_ALU(const char* nombreArchivoTxt, const char* nombreArchivoBin);
int parsearLineaProductos_ALU(char * linea,Producto * producto );

int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp);
int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp);
int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar);


// FUNCIONES PUNTERO
void actualizarClientes_ALU(void * d1, const void * d2);

int procesarArchivos_ALU(
    const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
    const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
    const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus);



// FUNCIONES DE LISTA
Nodo * crearNodo(const void * dato, unsigned tamDato);

void crearLista_ALU(Lista* pl);
void vaciarLista_ALU(Lista* pl);

booleano listaVacia_ALU(const Lista* pl);
booleano listaLlena_ALU(const Lista* pl, size_t tamElem);

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato);
int insertarEnListaOrd_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarOActualizarEnListaOrd_ALU(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);

booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem);





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

    return 0;
}

int procesarArchivos_ALU(
    const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
    const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
    const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus)
{

    productosTxtABin_ALU(nombreArchivoProductosChu,PROD_CHU_BIN);

    ordenarArchivo_ALU(PROD_CHU_BIN,sizeof(Producto),cmpProductos);
    ordenarArchivo_ALU(nombreArchivoProductosCor,sizeof(Producto),cmpProductos);

    ordenarArchivo_ALU(nombreArchivoClientesChu,sizeof(Cliente),cmpClientes);
    ordenarArchivo_ALU(nombreArchivoClientesCor,sizeof(Cliente),cmpClientes);

    fusionarArchivos_ALU(PROD_CHU_BIN,nombreArchivoProductosCor,nombreArchivoProductosFus,sizeof(Producto),cmpProductos);
    fusionarArchivos_ALU(nombreArchivoClientesChu,nombreArchivoClientesCor,nombreArchivoClientesFus,sizeof(Cliente),cmpClientes);

    eliminarDuplicadosArchivoOrd_ALU(nombreArchivoProductosFus,sizeof(Producto),cmpProductos,actualizarProductos);
    eliminarDuplicadosArchivoOrd_ALU(nombreArchivoClientesFus,sizeof(Cliente),cmpClientes,actualizarClientes_ALU);



    return TODO_OK;
}



// FUNCIONES GENERALES
int parsearLineaProductos_ALU(char * linea,Producto * producto )
{
    char * aux = strchr(linea,'\n');
    if(!aux)
    {
        fprintf(stdout,"ERROR NO HAY SALTO DE LINEA\n");
        return ERR_LINEA;
    }

    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%d",&producto->stock);

    *aux = '\0';
    aux = strrchr(linea,'|');
    sscanf(aux+1,"%f",&producto->precio);

    *aux = '\0';
    aux = strrchr(linea,'|');
    strncpy(producto->descripcion,aux+1,51);

    *aux = '\0';
    strcpy(producto->codigo,linea);

    return TODO_OK;
}

int productosTxtABin_ALU(const char* nombreArchivoTxt, const char* nombreArchivoBin)
{
    FILE * fpTXT = fopen(nombreArchivoTxt, "rt");
    FILE * fpBIN = fopen(nombreArchivoBin, "wb");
    Producto producto;

    Lista listaProductos;
    crearLista_ALU(&listaProductos);


    if(!fpTXT || !fpBIN)
    {
        fprintf(stderr,"ERROR EN LA APERTURA DE ARCHIVOS");
        return ERR_ARCHIVO;
    }

    char * linea = calloc(256,sizeof(char));
//    char linea[256];



    while(fgets(linea,256,fpTXT) && !listaLlena(&listaProductos,sizeof(Producto)))
    {
        parsearLineaProductos_ALU(linea,&producto);
        insertarEnListaAlFinal_ALU(&listaProductos,&producto,sizeof(Producto));
    }

    while(!listaVacia(&listaProductos))
    {
        eliminarDeListaPrimero_ALU(&listaProductos,&producto,sizeof(Producto));
        fwrite(&producto,sizeof(Producto),1,fpBIN);
    }


    free(linea);

    vaciarLista_ALU(&listaProductos);

    fclose(fpTXT);
    fclose(fpBIN);
    return TODO_OK;
}


int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp)
{
    FILE * fp = fopen(nombreArchivo,"rb");
    FILE * fpTemp = fopen("temp.bin","wb");
    void * dato = calloc(1,tamReg);
    Lista listaDato;

    if(!fp || !fpTemp)
    {
        fprintf(stderr, "ERROR APERTURA ARCHIVO PARA ORDENAR\n");
        return ERR_ARCHIVO;
    }

    crearLista_ALU(&listaDato);

    fread(dato,tamReg,1,fp);
    while(!feof(fp) && !listaLlena(&listaDato,tamReg))
    {
        insertarEnListaOrd_ALU(&listaDato,dato,tamReg,cmp);

        fread(dato,tamReg,1,fp);
    }


    while(!listaVacia(&listaDato))
    {
        eliminarDeListaPrimero_ALU(&listaDato,dato,tamReg);
        fwrite(dato,1,tamReg,fpTemp);
    }


    vaciarLista_ALU(&listaDato);
    fclose(fpTemp);
    fclose(fp);

    remove(nombreArchivo);
    rename("temp.bin",nombreArchivo);

    return TODO_OK;
}

int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp)
{
    FILE * fpArchivo1  = fopen(nombreArchivo1,"rb");
    FILE * fpArchivo2 = fopen(nombreArchivo2,"rb");
    FILE * fpArchivoFus = fopen(nombreArchivoFus, "wb");

    void * actualizado = calloc(1,tamReg);
    void * movimientos = calloc(1,tamReg);
    void * nuevo = calloc(1,tamReg);



    int resultado;



    if(!fpArchivo1 || !fpArchivo2 || !fpArchivoFus)
    {
        fprintf(stderr, "ERROR EN LA APERTURA DE ARCHIVOS PARA FUSION\n");
        fclose(fpArchivo1);
        fclose(fpArchivo2);
        fclose(fpArchivoFus);
        return ERR_ARCHIVO;
    }

    fread(actualizado,tamReg,1,fpArchivo1);
    fread(movimientos,tamReg,1,fpArchivo2);

    while(!feof(fpArchivo1) && !feof(fpArchivo2))
    {
        // sin movimientos 2 3
        resultado = cmp(actualizado,movimientos);
        if(resultado < 0)
        {
            fwrite(actualizado,tamReg,1,fpArchivoFus);
            fread(actualizado,tamReg,1,fpArchivo1);
        }

        // con movimientos 4 4
        if(resultado == 0)
        {
            fwrite(actualizado,tamReg,1,fpArchivoFus);
            fwrite(movimientos,tamReg,1,fpArchivoFus);
            fread(movimientos,tamReg,1,fpArchivo2);
            fread(actualizado,tamReg,1,fpArchivo1);

        }
        // nuevo 6 5
        if(resultado > 0)
        {
            fwrite(movimientos,tamReg,1,fpArchivoFus);
            fread(movimientos,tamReg,1,fpArchivo2);
        }

    }

    while(!feof(fpArchivo1))
    {
        fwrite(actualizado,tamReg,1,fpArchivoFus);
        fread(actualizado,tamReg,1,fpArchivo1);

    }

    while(!feof(fpArchivo2))
    {
        fwrite(movimientos,tamReg,1,fpArchivoFus);
        fread(movimientos,tamReg,1,fpArchivo2);

    }

    fclose(fpArchivo1);
    fclose(fpArchivo2);
    fclose(fpArchivoFus);

    free(actualizado);
    free(movimientos);
    free(nuevo);

    return TODO_OK;
}

int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar)
{
    FILE * fp  = fopen(nombreArchivo,"rb");
    FILE * fpTemp = fopen("temp.bin", "wb");
    Lista listaDato;
    void * dato = calloc(1,tamReg);
    if(!fp|| !fpTemp)
    {
        fprintf(stderr, " ERROR AL ABRIR EL ARCHIVO PARA ELIMINAR DUPLICADOS");
        fclose(fpTemp);
        fclose(fp);
        return ERR_ARCHIVO;
    }


    crearLista_ALU(&listaDato);

    fread(dato,tamReg,1,fp);
    while(!feof(fp) && !listaLlena_ALU(&listaDato,tamReg))
    {
        insertarOActualizarEnListaOrd_ALU(&listaDato,dato,tamReg,cmp,actualizar);

        fread(dato,tamReg,1,fp);
    }

    while(!listaVacia(&listaDato))
    {
        eliminarDeListaPrimero_ALU(&listaDato,dato,tamReg);
        fwrite(dato,tamReg,1,fpTemp);
    }

    vaciarLista_ALU(&listaDato);
    fclose(fpTemp);
    fclose(fp);
    remove(nombreArchivo);
    rename("temp.bin",nombreArchivo);
    return TODO_OK;
}

// FUNCIONES PUNTERO
void actualizarClientes_ALU(void * actualizado, const void * actualizador)
{

}

// FUNCIONES DE LISTA
Nodo* crearNodo( const void * dato, unsigned tamDato)
{
    Nodo * nue = (Nodo *)calloc(1,sizeof(Nodo));
    if(!nue || !(nue->elem = calloc(1,tamDato)))
    {
        free(nue);
        return NULL;
    }



    memcpy(nue->elem,dato,tamDato);
    nue->tamElem = tamDato;
    nue->sig = NULL;

    return nue;
}

void crearLista_ALU(Lista* l)
{
    *l = NULL;
}
void vaciarLista_ALU(Lista* l)
{
    Nodo * nae;
    while(*l)
    {
        nae  = *l;
        *l = nae->sig;

        free(nae->elem);
        free(nae);
    }


}

booleano listaVacia_ALU(const Lista* l)
{
    return * l == NULL;
}

booleano listaLlena_ALU(const Lista* l, size_t tamElem)
{
    Nodo * auxNodo = (Nodo * )calloc(1,sizeof(Nodo));
    void *dato = (Nodo *)calloc(1,tamElem);
    free(auxNodo);
    free(dato);
    return !auxNodo || !dato;
}

int insertarEnListaOrd_ALU(Lista* l, const void* dato, size_t tamElem, Cmp cmp)
{
    Nodo * nue = crearNodo(dato,tamElem);
    if(!nue)
    {
        return ERR_MEM;
    }

    while(*l && cmp((*l)->elem,nue->elem) < 0)
        l = &(*l)->sig;


    nue->sig = *l;
    *l = nue;

    return TODO_OK;
}

int insertarEnListaAlFinal_ALU(Lista *l, const void * dato, size_t tamDato)
{
    Nodo * nue = crearNodo(dato,tamDato);

    if(!nue)
        return ERR_MEM;

    while(*l)
        l = &(*l)->sig;

    nue->sig = *l;
    *l = nue;
    return TODO_OK;
}

int insertarOActualizarEnListaOrd_ALU(Lista* l, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    Nodo* nue = crearNodo(elem,tamElem);
    if(!nue)
    {
        return ERR_MEM;

    }
//1 2 3 4 5 6    7
    while(*l && cmp((*l)->elem,nue->elem)< 0)
    {
        l = &(*l)->sig;
    }

    if(*l && cmp((*l)->elem,nue->elem) ==0)
    {
        if(actualizar)
            actualizar((*l)->elem,nue->elem);
        return TODO_OK;
    }

    nue->sig = *l;
    *l = nue;

    return TODO_OK;
}

booleano eliminarDeListaPrimero_ALU(Lista* l, void* elem, size_t tamElem)
{
    Nodo * nae;
    if(!*l)
        return falso;

    nae = *l;
    *l = nae->sig;

    memcpy(elem,nae->elem,minimo_ALU(nae->tamElem,tamElem));
    free(nae->elem);
    free(nae);

    return verdadero;
}

