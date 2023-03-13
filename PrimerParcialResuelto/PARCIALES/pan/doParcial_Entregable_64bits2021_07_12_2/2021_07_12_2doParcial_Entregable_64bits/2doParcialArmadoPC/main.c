#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Solucion2doParcialArmadoPC/Solucion2doParcialArmadoPC.h"



#include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#include "../TDAArbol/TDAArbol.h"
#include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#include "../TDALista/TDALista.h"
#include "../TDA/TDA.h"
#include "../Solucion2doParcialArmadoPC/TiposArmadoPC.h"



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


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2


/**   COSAS ALUMNO **/
#define ERR 1
#define S printf("\n********************************\n");

///LISTA
void crearLista_ALU(Lista * lista);
int insertarEnListaAlFinal_ALU (Lista * lista, const void * dato, size_t tamBy);
int eliminarDeListaPrimero_ALU(Lista * lista, void * dato, size_t tamBy);
int eliminarDeListaDesordDuplicados_ALU(Lista * lista, int (*comparar)(const void *, const void *),void* acumularCantidad(void * acum, void *n) );
NodoD * buscarNodo_ALU(Lista * pl, void * elem, int(*comparar)(const void *, const void *));
int listaVacia_ALU(const Lista * lista);

///ARBOL
void crearArbol_ALU (Arbol * arbol);
int cargarIndiceComponentes_ALU(const char * arch, Arbol * arbol);
int cargar_Idx_ArchivoInord_ALU (Arbol * arbol, int ini, int fin, FILE * archivo, int (*comparar)(const void *, const void *));
int insertarArbol_ALU(Arbol * arbol, void * dato, size_t tamBy, int (*comparar)(const void *, const void *));
int buscarArbol_ALU(const Arbol * arbol, void * dato, size_t tamElem, int (*compar)(const void *, const void *));

///ACCIONES
int compCodIdx (const void * a, const void * b);
void* acumularCantidad(void * acum, void *n);
int compCodArmyRep (const void * a, const void * b);



///DEBUG
void recorrerListaIzq_ALU(Lista * pl, void(*accion)(const void *));
void mostrarArmyRep (const void * dato);
void inOrden_ALU (Arbol * arbol, void (*accion)(const void *));
void mostrarIndice_ALU (const void * dato);
int esBalanceado(Arbol * arbol);
int altura (Arbol * arbol);
int esCompletoAniv (Arbol * arbol, int nivel);
/********************/


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
	///******** Descomente esta línea y comente la de arriba para probar su código ********
    int resp = actualizarComponentes_alu(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
	///************************************************************************************

	if(resp != TODO_OK)
	{
		puts("Error actualizando los componentes.");
		return resp;
	}


	puts("\nComponentes despues de actualizar:\n");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}


int actualizarComponentes_alu(const char* pathComponentes, const char* pathArmadoYRep)
{
    FILE * archComps;
    FILE * archArmyRep;

    ArmadoYRep ArmyRep;

    Arbol arbolIdx;

    Lista listaArmyRep;

    IndComponente idx;

    Componente comp;

    archComps = fopen(pathComponentes,"r+b");
    if(!archComps)
        return ERR;

    archArmyRep = fopen(pathArmadoYRep,"rb");
     if(!archArmyRep)
    {
        fclose(archComps);
        return ERR;
    }

    crearLista_ALU(&listaArmyRep);
    crearArbol_ALU(&arbolIdx);

    if(cargarIndiceComponentes_ALU("Componentes.idx",&arbolIdx) != TODO_OK )
    {
        fclose(archComps);
        fclose(archArmyRep);
        return ERR;
    }
    ///archivos abiertos y arbol con indice cargado

    S
   /// inOrden_ALU(&arbolIdx,mostrarIndice_ALU);

///printf("balanceado %d",esBalanceado(&arbolIdx));


    fread(&ArmyRep,sizeof(ArmadoYRep),1,archArmyRep);
    while(!feof(archArmyRep))
    {
        insertarEnListaAlFinal_ALU(&listaArmyRep,&ArmyRep,sizeof(ArmadoYRep));
        fread(&ArmyRep,sizeof(ArmadoYRep),1,archArmyRep);
    }
//    S
//    recorrerListaIzq_ALU(&listaArmyRep,mostrarArmyRep);


    eliminarDeListaDesordDuplicados_ALU(&listaArmyRep,compCodArmyRep,acumularCantidad);
//    S
   /// recorrerListaIzq_ALU(&listaArmyRep,mostrarArmyRep);
    ///getch();

///lista cargada


///empiezo a sacar datos de lista para poder actualizar el archivo
S
S

    while(!listaVacia_ALU(&listaArmyRep))
    {
        eliminarDeListaPrimero_ALU(&listaArmyRep,&ArmyRep,sizeof(ArmadoYRep));
/// mostrarArmyRep(&ArmyRep);
        strcpy(idx.codigo,ArmyRep.codigo);
        buscarArbol_ALU(&arbolIdx,&idx,sizeof(IndComponente),compCodIdx);

        fseek(archComps,idx.nroReg*sizeof(Componente),SEEK_SET);///desde el inicio me muevo X registros
        fread(&comp,sizeof(Componente),1,archComps);

        comp.stock -= ArmyRep.cantidad;
///printf("%s\t\t%s\t\t%d\t\t%lf\n",comp.codigo,comp.descripcion,comp.stock,comp.precioUnitario);
        fseek(archComps,-sizeof(Componente),SEEK_CUR);///vuelvo 1 registro despues de haber leido
        fwrite(&comp,sizeof(Componente),1,archComps);
    }


    fclose(archArmyRep);
    fclose(archComps);

    return TODO_OK;
}



///LISTA
void crearLista_ALU(Lista * lista)
{
    *lista = NULL;
}

int insertarEnListaAlFinal_ALU (Lista * lista, const void * dato, size_t tamBy)
{
    NodoD * nue, * auxSig;

    nue = (NodoD*)malloc(sizeof(NodoD));
    if(!nue)
        return ERR;

    nue->dato = malloc (tamBy);
    if(!nue->dato)
    {
        free(nue);
        return ERR;
    }

    memcpy(nue->dato,dato,tamBy);
    memcpy(&(nue->tamElem),&tamBy,sizeof(unsigned));

    if(!*lista)
    {
        nue->ant = NULL;
        nue->sig = NULL;
        *lista = nue;
        return TODO_OK;
    }

    auxSig = *lista;

    while(auxSig->sig)
        auxSig = auxSig->sig;

    nue->sig = auxSig->sig;
    auxSig->sig = nue;
    nue->ant = auxSig;




    *lista = nue;

    return TODO_OK;
}

int eliminarDeListaPrimero_ALU(Lista * lista, void * dato, size_t tamBy)
{
    NodoD * elim;

    if(!*lista)
        return ERR;


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

int eliminarDeListaDesordDuplicados_ALU(Lista * pl, int (*comparar)(const void *, const void *),void* acumularCantidad(void * acum, void *n) )
{
    NodoD *elim, *auxSig, *auxAnt;

     if(!*pl){
        return ERR;
    }

    while((*pl)->ant){
        pl = &(*pl)->ant;
    }

    while((*pl)->sig){

        elim = buscarNodo_ALU(&(*pl)->sig,(*pl)->dato, comparar);
        if(elim)
        {
            acumularCantidad((*pl)->dato,elim->dato);
            auxAnt = elim->ant;
            auxSig = elim->sig;
            if(auxAnt)
                auxAnt->sig = auxSig;
            if(auxSig)
                auxSig->ant = auxAnt;
            free(elim->dato);
            free(elim);
        }
        else{
            pl = &(*pl)->sig;
        }
    }

    return TODO_OK;
}

NodoD * buscarNodo_ALU (Lista * pl, void * elem, int(*comparar)(const void *, const void *))
{
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

int listaVacia_ALU(const Lista * lista)
{
    return *lista == NULL;
}


///ARBOL
void crearArbol_ALU (Arbol * arbol)
{
    *arbol = NULL;
}

int cargarIndiceComponentes_ALU(const char * arch, Arbol * arbol)
{
    FILE * archIdx;

    archIdx = fopen(arch,"rb");
    if(!archIdx)
        return ERR;

    int tam;


    fseek(archIdx,0L,SEEK_END);
    tam = ftell(archIdx)/sizeof(IndComponente);
    tam = cargar_Idx_ArchivoInord_ALU(arbol,0,tam-1,archIdx,compCodIdx);

    fclose(archIdx);

    return TODO_OK;
}

int cargar_Idx_ArchivoInord_ALU (Arbol * arbol, int ini, int fin, FILE * archivo, int (*comparar)(const void *, const void *))
{
    int pm = ini+(fin-ini)/2;
    IndComponente index;

    if(ini>fin)///ya se guardaron todos los datos de ese lado
        return 1;

    fseek(archivo,pm*sizeof(IndComponente),SEEK_SET);
    fread(&index,sizeof(IndComponente),1,archivo);
    if(!insertarArbol_ALU(arbol,&index,sizeof(IndComponente),comparar))
        return 0;

    return cargar_Idx_ArchivoInord_ALU(&(*arbol)->hIzq,ini,pm-1,archivo,comparar) && cargar_Idx_ArchivoInord_ALU(&(*arbol)->hDer,pm+1,fin,archivo,comparar);
}

int insertarArbol_ALU(Arbol * arbol, void * dato, size_t tamBy, int (*comparar)(const void *, const void *))
{
    NodoA * nuevo;
    int comp;
    if(*arbol)
    {

        if((comp=comparar((*arbol)->dato,dato))>0)
        {
            return insertarArbol_ALU(&(*arbol)->hIzq,dato,tamBy,comparar);
        }
        else if(comp<0)
        {
            return insertarArbol_ALU(&(*arbol)->hDer,dato,tamBy,comparar);
        }
        else
        {
            return 0;
        }
    }

    nuevo=malloc(sizeof(NodoD));
    if(!nuevo)
    {
        return 0;
    }
    nuevo->dato=malloc(tamBy);
    if(!(nuevo->dato))
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->dato,dato,tamBy);
    nuevo->tamElem=tamBy;
    nuevo->hIzq=NULL;
    nuevo->hDer=NULL;
    *arbol=nuevo;

    return 1;



}

int buscarArbol_ALU(const Arbol * arbol, void * dato, size_t tamElem, int (*compar)(const void *, const void *))
{
    int comp;
    if(!*arbol)
        return 0;

    comp = compar( (*arbol)->dato,dato);

    if(comp == 0)
    {
        memcpy(dato,(*arbol)->dato,tamElem);
        return 1;
    }

    return buscarArbol_ALU(comp<0 ? &(*arbol)->hDer : &(*arbol)->hIzq, dato, tamElem, compar);
}






///acciones
int compCodIdx (const void * a, const void * b)
{
    return ( strcmp( ((IndComponente*)a)->codigo,((IndComponente*)b)->codigo ) );
}

int compCodArmyRep (const void * a, const void * b)
{
    return ( strcmp( ((ArmadoYRep*)a)->codigo,((ArmadoYRep*)b)->codigo ) );
}

void* acumularCantidad(void * acum, void *n)
{
    ///printf("%d += %d\n",((ArmadoYRep*)acum)->cantidad,((ArmadoYRep*)n)->cantidad);
    ((ArmadoYRep*)acum)->cantidad += ((ArmadoYRep*)n)->cantidad;

    return acum;
}





///usadas para debug
void recorrerListaIzq_ALU(Lista * pl, void(*accion)(const void *))
{
    while(*pl && (*pl)->ant){
        pl = &(*pl)->ant;
    }
    while(*pl){
        accion( (*pl)->dato );
        pl = &(*pl)->sig;
    }
}

void mostrarArmyRep (const void * dato)
{
    printf("%d %s %d %lf\n",((ArmadoYRep*)dato)->nroOp,((ArmadoYRep*)dato)->codigo,((ArmadoYRep*)dato)->cantidad,((ArmadoYRep*)dato)->precioUnitario);
}

void inOrden_ALU (Arbol * arbol, void (*accion)(const void *))
{
    if(!*arbol)
        return;

    inOrden_ALU(&(*arbol)->hIzq,accion);
    accion((*arbol)->dato);
    inOrden_ALU(&(*arbol)->hDer,accion);
}

void mostrarIndice_ALU (const void * dato)
{
    printf("%s %d\n",((IndComponente*)dato)->codigo,((IndComponente*)dato)->nroReg);
}

int esBalanceado(Arbol * arbol)
{
    return esCompletoAniv(arbol,altura(arbol)-2);
}

int altura (Arbol * arbol)
{
    int izq, der;
    if(!*arbol)
    {
        return 0;
    }

    izq = altura(&(*arbol)->hIzq);
    der = altura(&(*arbol)->hDer);

    return der>izq?der+1:izq+1;
}

int esCompletoAniv (Arbol * arbol, int nivel)
{
    if(!*arbol)
    {
        return nivel<0;
    }

    if(!nivel)
    {
        return 1;
    }

    return ( esCompletoAniv(&(*arbol)->hIzq,nivel-1) && esCompletoAniv(&(*arbol)->hDer,nivel-1) );
}

















