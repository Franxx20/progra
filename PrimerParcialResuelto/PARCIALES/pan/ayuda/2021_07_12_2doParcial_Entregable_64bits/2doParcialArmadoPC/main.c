#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

/**/
#define ERROR_ALU 404
/**/


#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"
#include "../TDA/TDA.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"

int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep);



int obtenerReg(ArmadoYRep* ayr, Arbol* idxComp);
void eliminarDuplicadosDeLista(Lista* aYrLista, Cmp cmp, Actualizar actualizar);
int cmpCod(const void* pv1, const void* pv2);
void actualizarAYR(void* pvpActualizado, const void* pvpActualizador);
int cmpAYR(const void* pv1, const void* pv2);
int eliminarDeListaPrimero2(Lista* armYrep,void* aYr, size_t ArmadoYRep);
int buscarEnListaDesord2(const Lista* armYrep,void* compont, size_t Componente,Cmp cmpCod);
void cargar_arbol_de_archivo_ordenado(Arbol* pa,size_t componente, const char* path);
int comparacion(const void *d1, const void *d2);
int tam_arch(FILE arch);
int generar_arbol_indice_rec(Arbol *pa, FILE arch_indice, int li, int ls);
int insertar_en_arbol_bin_busq(Arbol pa, const void* pd, Cmp comp);

/***/
void recorrerListaIzq_ALU(Lista* pl, void(*accion)(const void *));
void printArmRep_ALU(const void *elem);
int cmpCodigo_ALU (const void* first, const void* second);
int cmpAYR_ALU (const void* first, const void* second);
void actualizarAYR_ALU(void* actualizado, const void* actualizador);
int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);
NodoD *buscarNodo_ALU(Lista * pl, void * elem, int(*comparar)(const void *, const void *));
int cargarIndiceComponentes_ALU (const char* pathComponentesIdx, Arbol* pa);
int cargar_Idx_ArchivoInord_i (Arbol * arbol, int ini, int fin, FILE * archivo, Cmp  cmp);
//void printInxArbol_ALU(void* dato, void* datosAccion);
void printInxArbol_ALU(const void* dato);
void inOrden_ALU (Arbol * arbol, void (*accion)(const void *));
void vaciarLista_ALU(Lista* pl);
int listaVacia_ALU(const Lista * lista);
int eliminarDeListaPrimero_ALU(Lista * lista, void * dato, size_t tamBy);

/***/


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

	puts("Componentes antes de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");
    //int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************
	/** Descomente esta línea y comente la de arriba para probar su código              **/
	int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK){
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep){
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_alu" a todas las funciones que genere.FILE* bin;
    Lista listaArmRep;
    crearLista( &listaArmRep );
    cargarArmadosYRepEnLista( pathArmadoYRep, &listaArmRep );

        printf( "/***ACA MI LISTA CARGADA***/\n" );
        recorrerListaIzq_ALU( &listaArmRep, printArmRep_ALU );
        printf( "/**************************/\n" );


    //eliminarDeListaOrdDuplicados( &listaArmRep, cmpAYR_ALU , actualizarAYR_ALU );
    eliminarDeListaOrdDuplicados_ALU( &listaArmRep, cmpAYR_ALU , actualizarAYR_ALU );

        printf("/*ACA MI LISTA ACTUALIZADA*/\n");
        recorrerListaIzq_ALU( &listaArmRep, printArmRep_ALU );
        printf("/*************************/\n");

    Arbol arbolInxComp;
    crearArbol( &arbolInxComp );
    cargarIndiceComponentes_ALU( "Componentes.idx" , &arbolInxComp );
            int status = arbolBalanceado( &arbolInxComp );
            printf("EL ARBOL ES BALANCEADO? : %d\n", status);
            printf("\n/*ARBOL INDICE DE LOS REGISTROS*/\n");
            inOrden_ALU( &arbolInxComp, printInxArbol_ALU); //, &index
            printf("/*******************************/\n");


    FILE *fileComp = fopen( pathComponentes , "r+w");
    if( !fileComp ){
        return ERROR_ALU;
    }

    NodoA registroIndx;

    while(!listaVacia_ALU(&listaArmRep)){
        ArmadoYRep registroArmRep;

        eliminarDeListaPrimero_ALU( &listaArmRep, &registroArmRep, sizeof(ArmadoYRep) );
        //eliminarDeListaPrimero (&listaArmRep, &registroArmRep, sizeof(ArmadoYRep) );
        //buscarEnArbol( &arbolInxComp, &registroArmRep , sizeof(ArmadoYRep), cmpCodigo_ALU );
        printf("Elimino nodo\n");

    }

    vaciarArbol( &arbolInxComp );
    vaciarLista_ALU( &listaArmRep );
    fclose( fileComp );

    return TODO_OK;
}
void vaciarLista_ALU(Lista* pl){
    NodoD *actual = *pl;

    if( actual ){
        while( actual->ant ){
            actual = actual->ant;
        }
        while( actual ){
            NodoD *aux = actual->sig;

            free(actual->dato);
            free(actual);
            actual = aux;
        }
        *pl = NULL;
    }
}
void inOrden_ALU (Arbol * arbol, void (*accion)(const void *))
{
//A, B, C, D, E, F, G, H, I (izquierda, raíz, derecha)
    if(!*arbol)
        return;

    inOrden_ALU(&(*arbol)->hIzq,accion);
    accion((*arbol)->dato);
    inOrden_ALU(&(*arbol)->hDer,accion);
}
void printInxArbol_ALU(const void* dato){ //, void* datosAccion
    printf( "/* %d\t%s */\n" , ((IndComponente*)dato)->nroReg, ((IndComponente*)dato)->codigo );
}

int cargarIndiceComponentes_ALU (const char* pathComponentesIdx, Arbol* pa){
//int cargar_Idx_ArchivoInord (t_arbol * arbol,int (*comparar)(const void *, const void *))
    int tam;
    FILE * fp = fopen( pathComponentesIdx ,"rb");
    if(!fp){
        return ERROR;
    }

    fseek( fp, 0L, SEEK_END);
    tam = ftell(fp) / sizeof(IndComponente);
    tam = cargar_Idx_ArchivoInord_i( pa, 0, tam-1, fp, cmpCodigo_ALU );

    fclose(fp);

    return tam;
}

///a partir del archivo que fue escrito como inorden se rearma el arbol para poder balancearlo
///complementa a cargar_Idx_ArchivoInord
///_interna
int cargar_Idx_ArchivoInord_i (Arbol * arbol, int ini, int fin, FILE * archivo, Cmp  cmp){
    int pm = ini+(fin-ini)/2;
    IndComponente index;

    if(ini>fin)///ya se guardaron todos los datos de ese lado
        return 1;

    fseek(archivo,pm*sizeof(IndComponente),SEEK_SET);
    fread(&index,sizeof(IndComponente),1,archivo);
    //if(!insertarArbol( arbol,&index,sizeof(IndComponente), cmpCodigo_ALU ))
    if(insertarEnArbol( arbol,&index,sizeof(IndComponente), cmp ) != TODO_OK ){
        return ERROR_ALU;
    }
    return cargar_Idx_ArchivoInord_i(&(*arbol)->hIzq,ini,pm-1,archivo, cmp) && cargar_Idx_ArchivoInord_i(&(*arbol)->hDer,pm+1,fin,archivo, cmp);
}

int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar){
    //(void* actualizado, const void* actualizador)
    NodoD *elim, *auxSig, *auxAnt;

    if(!*pl){
        return ERROR;
    }
    while((*pl)->ant){
        pl = &(*pl)->ant;
    }

    while( (*pl)->sig ){
        elim = buscarNodo_ALU( &(*pl)->sig,(*pl)->dato, cmp );
        if( elim ){
            actualizar( (*pl)->dato,(elim)->dato );
            auxAnt = elim->ant;
            auxSig = elim->sig;
            if( auxAnt ){
                auxAnt->sig = auxSig;
            }
            if( auxSig ){
                auxSig->ant = auxAnt;
            }

            free(elim->dato);
            free(elim);
        } else {
            pl = &(*pl)->sig;
        }
    }

    return TODO_OK;
}

NodoD *buscarNodo_ALU(Lista * pl, void * elem, int(*comparar)(const void *, const void *)){
    int comp = comparar( (*pl)->dato, elem );
    while((*pl)->sig && comp!=0){
        pl = &(*pl)->sig;
        comp = comparar((*pl)->dato, elem);
    }
    if(comp == 0){
        return *pl;
    }

    return NULL;
}

int cmpCodigo_ALU (const void* first, const void* second){
    ArmadoYRep firstArmRep = *(ArmadoYRep*)first;
    ArmadoYRep secondArmRep = *(ArmadoYRep*)second;

    return strcmp( firstArmRep.codigo, secondArmRep.codigo );
}
int cmpAYR_ALU (const void* first, const void* second){
    ArmadoYRep firstArmRep = *(ArmadoYRep*)first;
    ArmadoYRep secondArmRep = *(ArmadoYRep*)second;

    return strcmp( firstArmRep.codigo, secondArmRep.codigo );

}

void actualizarAYR_ALU(void* actualizado, const void* actualizador){
    ((ArmadoYRep*)actualizado)->cantidad += ((ArmadoYRep*)actualizador)->cantidad;
}

void recorrerListaIzq_ALU(Lista* pl, void(*accion)(const void *)){
    while(*pl && (*pl)->ant){
        pl = &(*pl)->ant;
    }
    while(*pl){
        accion( (*pl)->dato );
        pl = &(*pl)->sig;
    }
}

void printArmRep_ALU(const void *elem){
    printf( "%-4d%-20s\t%2d%8.2lf\n", ((ArmadoYRep*)elem)->nroOp, ((ArmadoYRep*)elem)->codigo, ((ArmadoYRep*)elem)->cantidad, ((ArmadoYRep*)elem)->precioUnitario );
}
int listaVacia_ALU(const Lista * lista)
{
    return *lista == NULL;
}
int eliminarDeListaPrimero_ALU(Lista * lista, void * dato, size_t tamBy)
{
    NodoD * elim;

    if(!*lista)
        return ERROR_ALU;


    while((*lista)->ant)
        (lista) = &(*lista)->ant;

    elim = *lista;

    if(!(elim->sig))///era el ultimo nodo
    {
        memcpy(dato,elim->dato,tamBy);
        free(elim->dato);
        free(elim);
        *lista = NULL;
        return TODO_OK;
    }

    *lista = elim->sig;
    (*lista)->ant = elim->ant;///NULL

    memcpy(dato,elim->dato,tamBy);
    free(elim->dato);
    free(elim);

    return TODO_OK;
}
