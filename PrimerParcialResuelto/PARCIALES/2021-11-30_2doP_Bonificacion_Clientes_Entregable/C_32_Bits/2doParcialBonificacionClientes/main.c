#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Solucion2doParcialBonificacionClientes/Utilitarias2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/Solucion2doParcialBonificacionClientes.h"
#include "../Solucion2doParcialBonificacionClientes/TiposArchivos.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);
void listarClientesOrdXBonifDesc_ALU(const char* clientes);


/***/
int cmpCodCliente_ALU(const void* first, const void* second);
int cmpClientesBonif_ALU(const void* first, const void* second);
booleano recorrerListaInicio_ALU( Lista *listaClientes, void (*Accion)(void* elem));
void printClientes_ALU( void* cliente);

int cargarArbolIdx_ALU(Arbol * arbolIdx, int start, int end, FILE * archivo, Cmp cmp);
int cargarArbolDeArchivoOrdenado_ALU (Arbol *arbolIdx, Cmp cmp, const char * archNombre);
int cmpIndice_ALU(const void* first, const void* second);
//void printClientes_ALU( void* cliente, void* datosAccion);

void crearArbol_ALU (Arbol *arbol);
void crearLista_ALU(Lista *lista);
/***/
int main()
{
	generarArchivoClientes();
	generarIndiceArchivoClientes();
	generarArchivoVentas();

	mostrarArchivoClientes();
	puts("\n");

	mostrarArchivoVentas();
	puts("\n");

    /***/
	bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
	///bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");
    /***/

	puts("Clientes Bonificados");
	mostrarArchivoClientes();
	puts("\n");
    /***/
	listarClientesOrdXBonifDesc_ALU("Clientes.dat");
	///listarClientesOrdXBonifDesc("Clientes.dat");
	/***/
	return 0;
}


void bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.
    FILE *archClientes = fopen( clientes, "r + b" );
    if( !archClientes ){
        return;
    }

    FILE *archVentas = fopen(ventas, "rb");
        if( !archVentas ){
        fclose(archClientes);
        //fclose(archClientesUpd);
        return;
    }

    Arbol arbolIdx;
    crearArbol_ALU( &arbolIdx );
    cargarArbolDeArchivoOrdenado( &arbolIdx, sizeof( Indice ), clientesInd );
    //cargarArbolDeArchivoOrdenado_ALU( &arbolIdx, cmpIndice_ALU , clientesInd );

    Venta ventaAct;
    fread( &ventaAct, sizeof(Venta), 1,  archVentas);
    while( !feof(archVentas) ){
        char codClienteAct[16];
        strcpy( codClienteAct, ventaAct.codCliente );

        int totalCompra = 0 ;

        while( !feof(archVentas) && strcmp( codClienteAct, ventaAct.codCliente ) == 0 ){
            totalCompra += ventaAct.precioUnit * ventaAct.cantidad;

            fread( &ventaAct, sizeof(Venta), 1, archVentas);
        }

        int bonifCliente = 0;
        if( totalCompra >= 300000 ){
            bonifCliente = 20;
        } else if( totalCompra > 200000 && totalCompra < 299999 ) {
            bonifCliente = 10;
        } else if( totalCompra > 100000 && totalCompra < 199999 ) {
            bonifCliente = 5;
        }

        Indice idxCliente;
        strcpy( idxCliente.codCliente, codClienteAct ); //Almaceno el cliente que voy a buscar
        buscarEnArbol( &arbolIdx, &idxCliente, sizeof( Indice ), cmpCodCliente_ALU );

        Cliente clienteUpd;
        fseek( archClientes, idxCliente.nroReg*sizeof(Cliente), SEEK_SET ); //Posiciono el cursor
        fread( &clienteUpd, sizeof(Cliente), 1, archClientes ); //Leo el valor deseado del cliente
                //printf("**%s\t%s**\n",clienteUpd.codigo,clienteUpd.nombre);
        if( bonifCliente != 0 ){ //Si efectivamente el cliente tiene alguna bonificacion en base a sus compras
            clienteUpd.porcBonif = bonifCliente;
            fseek( archClientes , -sizeof(Cliente) , SEEK_CUR );//Retrocedo un registro para escribir

            fwrite( &clienteUpd, sizeof(Cliente), 1, archClientes );
        }
    }

    vaciarArbol( &arbolIdx );
    fclose(archClientes);
    fclose(archVentas);
}

void listarClientesOrdXBonifDesc_ALU(const char* clientes)
{
/// Resuelva esta función y todas las que invoque. Coloque el sufijo _ALU a todas ellas. Resuelva todo en este archivo main.c. No modifique ningún otro.
/// main.c es el único archivo que deberá entregar del proyecto C.
    FILE *archClientes = fopen( clientes, "rb" );
    if( !archClientes ){
        return;
    }

    Lista listaClientes;
    crearLista_ALU( &listaClientes );

    Cliente clienteReg;
    fread( &clienteReg, sizeof(Cliente), 1,  archClientes);
    while( !feof(archClientes) ){
        insertarEnListaOrdCDup( &listaClientes, &clienteReg, sizeof(Cliente), cmpClientesBonif_ALU );
        fread( &clienteReg, sizeof(Cliente), 1,  archClientes);
    }
    printf( "Clientes Ord. X Bonificacion\n" );
    recorrerListaInicio_ALU( &listaClientes, printClientes_ALU );
    //recorrerLista( &listaClientes, printClientes_ALU, &clienteReg );
    //vaciarLista( &listaClientes );
    vaciarLista_ALU( &listaClientes );
    fclose( archClientes );
}

/**FUNCIONES IMPLEMENTADAS/LLAMADAS ALUMNO**/
//typedef int (*Cmp)(const void* e1, const void* e2);
int cmpClientesBonif_ALU(const void* first, const void* second){
    float bonifFirst = ((Cliente*)first)->porcBonif;
    float bonifSecond = ((Cliente*)second)->porcBonif;

    return bonifSecond - bonifFirst;
}
int cmpIndice_ALU(const void* first, const void* second){
    char* idxFirst = ((Indice*)first)->codCliente;
    char* idxSecond = ((Indice*)second)->codCliente;

    return strcmp( idxFirst, idxSecond );
}
int cmpCodCliente_ALU(const void* first, const void* second){
    char* idxFirst = ((Indice*)first)->codCliente;
    char* idxSecond = ((Indice*)second)->codCliente;

    return strcmp( idxFirst, idxSecond );
}
//typedef void (*Accion)(void* elem, void* datosAccion);
void printClientes_ALU( void* elem){
    printf("%-10s\t%-10s\t%05.2f\n", ((Cliente*)elem)->codigo, ((Cliente*)elem)->nombre, ((Cliente*)elem)->porcBonif );
}
booleano recorrerListaInicio_ALU( Lista *listaClientes, void (*Accion)(void* elem)){
    if( !listaClientes ){
        return falso;
    }

    while( (*listaClientes)->ant ){
        //Posicionado al inicio de la lista doble
        listaClientes = &(*listaClientes)->ant;
    }
    while(*listaClientes){
        Accion( (*listaClientes)->elem );
        listaClientes = &(*listaClientes)->sig;
    }

    return verdadero;
}

int cargarArbolDeArchivoOrdenado_ALU (Arbol *arbolIdx, Cmp cmp, const char * archNombre){
    FILE * archIdx = fopen("temp.idx","rb");
    if(!archIdx){
        return ERR_ARCHIVO;
    }


    fseek( archIdx, 0L, SEEK_END );
    int fileSize = ftell( archIdx ) / sizeof(Indice);
    fileSize = cargarArbolIdx_ALU( arbolIdx , 0, fileSize-1, archIdx, cmp);

    fclose(archIdx);

    return fileSize;
}

int  cargarArbolIdx_ALU(Arbol * arbolIdx, int start, int end, FILE * archivo, Cmp cmp){
    int medio = start+(end-start)/2;
    Indice idxCliente;

    if(start>end){ //Verifico que los punteros no se traspasen
        return 1;
    }

    fseek( archivo, medio*sizeof(Indice), SEEK_SET);
    fread( &idxCliente,sizeof(Indice),1,archivo );
    if(!insertarEnArbol(arbolIdx,&idxCliente,sizeof(Indice), cmp)){
        return 0;
    }

    return cargarArbolIdx_ALU(&(*arbolIdx)->hIzq, start, medio-1, archivo, cmp) &&
           cargarArbolIdx_ALU(&(*arbolIdx)->hDer, medio+1, end, archivo, cmp);
}


void crearArbol_ALU (Arbol *arbol){
    *arbol = NULL;
}

void crearLista_ALU(Lista *lista){
    *lista = NULL;
}
void vaciarLista_ALU(Lista* lista){
    NodoD *lectNodo = *lista;

    if( !lectNodo ){
        return;
    }
    while( lectNodo->ant ){
        lectNodo = lectNodo->ant;
    }
    while( lectNodo ){
        NodoD *nodoSig = lectNodo->sig;

        free(lectNodo->elem);
        free(lectNodo);
        lectNodo = nodoSig;
    }
    *lista = NULL;
}
