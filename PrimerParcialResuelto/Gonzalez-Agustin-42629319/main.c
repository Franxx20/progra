/*****************************************************************************************************************
** Apellido/s, Nombre/s: Gonzalez, Agustin Elias                                      													**
** DNI: 42629319                                               													**
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
#include "../Solucion1erParcialFabricasComputadoras/Solucion1erParcialFabricasComputadoras.h"

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"

//#define SOLUCION_DOC
#define SOLUCION_ALU

#include <string.h>
#include <stdlib.h>

#define ERR_PUNTO_ALU 5
#define ERR_LINEA_LARGA_ALU 6
#define MINIMO(a,b) ((a) < (b) ? (a) : (b))

int procesarArchivos_ALU(const char* nombreArchivoProdCor, const char* nombreArchivoProdChuTxt, const char* nombreArchivoCliCor,
                         const char* nombreArchivoCliChu, const char* nombreArchivoProdFu, const char* nombreArchivoCliFu);
int convertirArchivoProductosABin_ALU(const char* nombreArchivoProdTxt, const char* nombreArchivoProdBin);
int cambiarExtension_ALU(char* nombre, const char* extension);
int parsearCadena_ALU(char* linea, Producto* prod);
int compararCodigoProd_ALU(const void* dato1, const void* dato2);
int compararCodigoCliente_ALU(const void* dato1, const void* dato2);
void actualizarProductos_ALU(void* actualizado, const void* actualizador);
int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp);
Lista* buscarMenorDeLista_ALU(Lista* pl, Cmp cmp);
void ordenarLista_ALU(Lista* pl, Cmp cmp);
void crearLista_ALU(Lista* pl);
int insertarEnListaAlFinal_ALU(Lista* pl, const void* elem, size_t tamElem);
booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem);
booleano listaVacia_ALU(const Lista* pl);
booleano listaLlena_ALU(const Lista* pl, size_t tamElem);
void vaciarLista_ALU(Lista* pl);
int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp);
int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar);
int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);



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

int procesarArchivos_ALU(const char* nombreArchivoProdCor, const char* nombreArchivoProdChuTxt, const char* nombreArchivoCliCor,
                         const char* nombreArchivoCliChu, const char* nombreArchivoProdFu, const char* nombreArchivoCliFu)
{

    char nombreArchivoProdChuBin[50];
    strncpy(nombreArchivoProdChuBin,nombreArchivoProdChuTxt,50);

    int ret = cambiarExtension_ALU(nombreArchivoProdChuBin,".dat");
    if(ret != TODO_OK)
        return ret;

    ret = convertirArchivoProductosABin_ALU(nombreArchivoProdChuTxt, nombreArchivoProdChuBin);
    if(ret != TODO_OK)
        return ret;

    ret = ordenarArchivo_ALU(nombreArchivoProdCor,sizeof(Producto),compararCodigoProd_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = ordenarArchivo_ALU(nombreArchivoProdChuBin, sizeof(Producto), compararCodigoProd_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = ordenarArchivo_ALU(nombreArchivoCliChu, sizeof(Cliente), compararCodigoCliente_ALU);
     if(ret != TODO_OK)
        return ret;

    ret = ordenarArchivo_ALU(nombreArchivoCliCor, sizeof(Cliente), compararCodigoCliente_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = fusionarArchivos_ALU(nombreArchivoProdCor, nombreArchivoProdChuBin, nombreArchivoProdFu, sizeof(Producto), compararCodigoProd_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = fusionarArchivos_ALU(nombreArchivoCliCor, nombreArchivoCliChu, nombreArchivoCliFu, sizeof(Cliente), compararCodigoCliente_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = eliminarDuplicadosArchivoOrd(nombreArchivoProdFu, sizeof(Producto), compararCodigoProd_ALU, actualizarProductos_ALU);
    if(ret != TODO_OK)
        return ret;

    ret = eliminarDuplicadosArchivoOrd(nombreArchivoCliFu, sizeof(Cliente), compararCodigoCliente_ALU, actualizarProductos);
    if(ret != TODO_OK)
        return ret;

    return TODO_OK;
}

int convertirArchivoProductosABin_ALU(const char* nombreArchivoProdTxt, const char* nombreArchivoProdBin)
{
    FILE* archProductosTxt = fopen(nombreArchivoProdTxt, "rt");
    FILE* archProductosBin = fopen(nombreArchivoProdBin, "wb");

    if(!archProductosTxt || !archProductosBin)
    {
        fclose(archProductosTxt);
        return ERR_ARCHIVO;
    }

    char linea[256];
    Producto prod;
    int ret;

    while(fgets(linea, 256, archProductosTxt))
    {
        ret = parsearCadena_ALU(linea, &prod);
        if(ret != TODO_OK)
            return ret;
        fwrite(&prod, sizeof(Producto), 1, archProductosBin);
    }

    fclose(archProductosBin);
    fclose(archProductosTxt);

    return TODO_OK;
}

int cambiarExtension_ALU(char* nombre, const char* extension)
{
    char* aux = strrchr(nombre,'.');

    if(!aux)
        return ERR_PUNTO_ALU;

    strcpy(aux,extension);

    return TODO_OK;
}

int parsearCadena_ALU(char* linea, Producto* prod)
{
    char* actual = strchr(linea,'\n');

    if(!actual)
        return ERR_LINEA_LARGA_ALU;

    *actual = '\0';

    // stock entero
    actual = strrchr(linea, '|');
    sscanf(actual + 1, "%d", &prod->stock);
    *actual = '\0';

    // precio float
    actual = strrchr(linea, '|');
    sscanf(actual + 1, "%f", &prod->precio);
    *actual = '\0';

    // descripcion cadena tam 50
    actual = strrchr(linea, '|');
    strncpy(prod->descripcion, actual + 1, 50);
    prod->descripcion[49] = '\0';

    // nombre codigo tam 20
    strncpy(prod->codigo, linea, 20);
    char* aux = strchr(prod->codigo,'|');
    *aux = '\0';

    return TODO_OK;
}

int compararCodigoProd_ALU(const void* dato1, const void* dato2)
{
    Producto* prod1 = (Producto*)dato1;
    Producto* prod2 = (Producto*)dato2;

    return strcmp(prod1->codigo, prod2->codigo);
}

int compararCodigoCliente_ALU(const void* dato1, const void* dato2)
{
    Cliente* cliente1 = (Cliente*)dato1;
    Cliente* cliente2 = (Cliente*)dato2;

    return cliente1->codigo - cliente2->codigo;
}


void actualizarProductos_ALU(void* actualizado, const void* actualizador)
{
    Producto* prod1 = (Producto*)actualizado;
    Producto* prod2 = (Producto*)actualizador;

    if(prod2->precio > prod1->precio)
        prod1->precio = prod2->precio;

    prod1->stock += prod2->stock;
}


int ordenarArchivo_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp)
{
    FILE* arch = fopen(nombreArchivo, "rb");

    if(!arch)
        return ERR_ARCHIVO;

    Lista listaOrdenada;
    crearLista_ALU(&listaOrdenada);

    Producto prod;
    Cliente cli;

    int comp = tamReg == sizeof(Producto) ? 1 : 0;

    if(comp == 1)
    {
        fread(&prod, tamReg, 1, arch);
    }
    else
    {
        fread(&cli, tamReg, 1, arch);
    }


    while(!feof(arch) && !listaLlena(&listaOrdenada, tamReg))
    {
        if(comp == 1)
        {
            insertarEnListaAlFinal_ALU(&listaOrdenada, &prod, tamReg);
            fread(&prod, tamReg, 1, arch);
        }
        else
        {
            insertarEnListaAlFinal_ALU(&listaOrdenada, &cli, tamReg);
            fread(&cli, tamReg, 1, arch);
        }
    }

    if(!feof(arch))
    {
        vaciarLista_ALU(&listaOrdenada);
        fclose(arch);
        return ERR_ARCHIVO;
    }

    fclose(arch);

    if(comp == 1)
    {
        ordenarLista_ALU(&listaOrdenada, compararCodigoProd_ALU);
    }
    else
    {
        ordenarLista_ALU(&listaOrdenada, compararCodigoCliente_ALU);
    }


    FILE* archNuevo = fopen(nombreArchivo, "wb");

    if(!archNuevo)
        return ERR_ARCHIVO;

    while(!listaVacia(&listaOrdenada))
    {
        if(comp == 1)
        {
            eliminarDeListaPrimero_ALU(&listaOrdenada, &prod, tamReg);
            fwrite(&prod, tamReg, 1, archNuevo);
        }
        else
        {
            eliminarDeListaPrimero_ALU(&listaOrdenada, &cli, tamReg);
            fwrite(&cli, tamReg, 1, archNuevo);
        }
    }

    vaciarLista_ALU(&listaOrdenada);
    fclose(archNuevo);

    return TODO_OK;
}

/*
Lista* buscarMenorDeLista_ALU(Lista* pl, Cmp cmp)
{
    Lista* menor = pl;
    Lista* actual = &(*pl)->sig;

    while(*actual)
    {
        if(cmp((*menor)->elem, (*actual)->elem) > 0)
            menor = actual;

        actual = &(*actual)->sig;
    }

    return menor;
}

*/
Lista * buscarMenorDeLista_ALU(Lista *l,  Cmp cmp){
    Lista * menor = l;
    Lista * sig =&(*l)->sig;

    while(*sig)
    {
        if(cmp((*menor)->elem,(*sig)->elem)>0)
        menor = sig;

        sig = &(*sig)->sig;
    }

    return menor;
}
/*
void ordenarLista_ALU(Lista* pl, Cmp cmp)
{
    Lista ord;
    Lista* ult = &ord;
    Lista* menor;

    while(*pl)
    {
        menor = buscarMenorDeLista_ALU(pl, cmp);
        *ult = *menor;
        *menor = (*menor)->sig;
        ult = &(*ult)->sig;
    }
    *pl = ord;
}
*/

void ordenarLista_ALU(Lista *l, Cmp  cmp){
    Lista lOrd;
    Lista * ult = &lOrd;
    Lista * menor ;

    while(*l)
    {
        menor = buscarMenorDeLista_ALU(l,cmp);
        *ult = *menor;
       *menor = (*menor)->sig;
       ult =&(*ult)->sig;
        
    }
    *l = lOrd;
}
void crearLista_ALU(Lista* pl)
{
    *pl = NULL;
}

int insertarEnListaAlFinal_ALU(Lista* pl, const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));

    if(nue == NULL || (nue->elem = malloc(tamElem)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    while(*pl)
        pl = &(*pl)->sig;

    memcpy(nue->elem, elem, tamElem);
    nue->tamElem = tamElem;
    nue->sig = NULL;
    *pl = nue;
    return TODO_OK;
}
booleano eliminarDeListaPrimero_ALU(Lista* pl, void* elem, size_t tamElem)
{
    if(*pl == NULL)
        return falso;

    Nodo* nae = *pl;
    *pl = nae->sig;

    memcpy(elem, nae->elem, MINIMO(nae->tamElem, tamElem));
    free(nae->elem);
    free(nae);

    return verdadero;
}
booleano listaVacia_ALU(const Lista* pl)
{
    return *pl == NULL;
}

booleano listaLlena_ALU(const Lista* pl, size_t tamElem)
{
    Nodo* aux = (Nodo*)malloc(sizeof(Nodo));
    void* elem = malloc(tamElem);

    free(aux);
    free(elem);
    return !aux || !elem;
}

void vaciarLista_ALU(Lista* pl)
{
    Nodo* aux;

    while(*pl)
    {
        aux = *pl;
        *pl = aux->sig;
        free(aux->elem);
        free(aux);
    }
}


int fusionarArchivos_ALU(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp)
{
    FILE* arch1 = fopen(nombreArchivo1, "rb");
    FILE* arch2 = fopen(nombreArchivo2, "rb");
    FILE* archFu = fopen(nombreArchivoFus, "wb");

    if(!arch1 || !arch2 || !archFu)
    {
        fclose(arch1);
        fclose(arch2);
        fclose(archFu);
        return ERR_ARCHIVO;
    }

    void* elem = malloc(tamReg);
    void* elem2 = malloc(tamReg);

    int comp = tamReg == sizeof(Producto) ? 1 : 0;

    fread(elem, tamReg, 1, arch1);
    fread(elem2, tamReg, 1, arch2);

    int comparacion;

    while(!feof(arch1) && !feof(arch2))
    {
        if(comp == 1)
            comparacion = compararCodigoProd_ALU(elem, elem2);
        else
            comparacion = compararCodigoCliente_ALU(elem, elem2);

        if(comparacion < 0)
        {
            fwrite(elem, tamReg, 1, archFu);
            fread(elem, tamReg, 1, arch1);
        }
        else if(comparacion > 0)
        {
            fwrite(elem2, tamReg, 1, archFu);
            fread(elem2, tamReg, 1, arch2);
        }
        else
        {
            fwrite(elem, tamReg, 1, archFu);
            fwrite(elem2, tamReg, 1, archFu);
            fread(elem, tamReg, 1, arch1);
            fread(elem2, tamReg, 1, arch2);
        }
    }

    while(!feof(arch1))
    {
        fwrite(elem, tamReg, 1, archFu);
        fread(elem, tamReg, 1, arch1);
    }

    while(!feof(arch2))
    {
        fwrite(elem2, tamReg, 1, archFu);
        fread(elem2, tamReg, 1, arch2);
    }

    free(elem);
    free(elem2);

    fclose(arch1);
    fclose(arch2);
    fclose(archFu);

    return TODO_OK;
}

int eliminarDuplicadosArchivoOrd_ALU(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar)
{
    FILE* arch = fopen(nombreArchivo, "rb");

    if(!arch)
        return ERR_ARCHIVO;

    void* elem = malloc(tamReg);

    Lista list;
    crearLista_ALU(&list);

    fread(elem, tamReg, 1, arch);

    while(!feof(arch))
    {
        insertarEnListaAlFinal_ALU(&list, elem, tamReg);
        fread(elem, tamReg, 1, arch);
    }

    if(!feof(arch))
    {
        vaciarLista_ALU(&list);
        fclose(arch);
        return ERR_ARCHIVO;
    }

    fclose(arch);

    eliminarDeListaOrdDuplicados(&list, cmp, actualizar);

    FILE* archNu = fopen(nombreArchivo, "wb");

    if(!archNu)
    {
        vaciarLista_ALU(&list);
        return ERR_ARCHIVO;
    }

    while(!listaVacia(&list))
    {
        eliminarDeListaPrimero_ALU(&list, elem, tamReg);
        fwrite(elem, tamReg, 1, archNu);
    }

    free(elem);
    vaciarLista_ALU(&list);

    return TODO_OK;
}

int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(*pl == NULL)
        return 1;

    Nodo* actual;
    Nodo* nae;

    while(*pl)
    {
        actual = (*pl)->sig;

        while(actual && cmp((*pl)->elem, actual->elem) == 0)
        {
            if(actualizar != NULL)
                actualizar((*pl)->elem, actual->elem);

            nae = actual;
            actual = nae->sig;
            free(nae->elem);
            free(nae);
        }

        pl = &(*pl)->sig;
    }
    return TODO_OK;
}
