#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Solucion1erParcialArmadoPC.h>
#include <Lista.h>

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2
#define ERR_AP_ARCH 0


int main(int argc, char* argv[])
{
    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

	puts("Componentes antes de actualizar:");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
	puts("");

	puts("Armados/Reparaciones:");
	mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
	puts("");

	actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
//  actualizarComponentes_res(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);

	puts("Componentes despues de actualizar:");
	mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

    return 0;
}


void actualizarComponentes(const char* pathComponentes, const char* pathArmadoYRep)
{

    t_lista* lArmados;
    ///t_indComponente ind[8]; ///no puede ser 8 ya que ES UN PUNTERO!!! pero que va?
    t_componente comp;
    t_armadoYRep arm;
    FILE* armadoYRepA;
    FILE* componentesA;
    FILE* tempA = fopen("Temporal.tmp","wb");
    armadoYRepA = fopen(pathArmadoYRep,"rb");
    componentesA = fopen(pathComponentes,"r+b");
    if(!armadoYRepA || !tempA)
        return;

    ///ind=cargarIndiceComponentes(pathComponentes,8);
    crear_lista_res(lArmados);
    cargarArmadosYRepEnLista(pathArmadoYRep,lArmados);
    lista_ordenar_asc_res(lArmados, comparacion);
    eliminar_duplicados_de_lista_ord(lArmados,comparacion,actualizar);
    fclose(armadoYRepA);

    lista_sacar_primero_res(lArmados, &arm);
    ///buscarEnIndice_res(ind,8,arm.codigo); ///accede al archivo de componentes y busca el código.
    fread(&comp,sizeof(t_componente),1,componentesA);
//    while(!*lArmados || !feof(componentesA))
//    {
//        if(strcmp((*lArmados)->info.codigo,comp.codigo)==0)
//        {
//            comp.stock-=(*lArmados)->info.cantidad;
//            fread(&comp,sizeof(t_componente),1,componentesA);
//
//        }
//        if(strcmp((*lArmados)->info.codigo,comp.codigo)<0)
//        {
//            lista_sacar_primero_res(lArmados,&arm);
//            fwrite(&comp,sizeof(t_componente),1,tempA);
//        }
//        if(strcmp((*lArmados)->info.codigo,comp.codigo)>0)
//        {
//
//            fread(&comp,sizeof(t_componente),1,componentesA);
//        }
//
//    }
    fclose(componentesA);
    fclose(tempA);
    /**
    rename(tempA);
    remove("Componentes.dat",tempA);
    **/
}

t_indComponente* cargarIndiceComponentes(const char* pathComponentesIdx, int* ceInd)
{

    t_indComponente* ind;
    t_componente* comp;
    FILE* indComponentesA = (FILE*)pathComponentesIdx;
    FILE* componentesA = fopen("Componentes.dat","rb");
    indComponentesA=fopen("Componentes.idx","r");
    if(!indComponentesA || !componentesA)
        return ERR_AP_ARCH;

    fread(&ind,sizeof(t_indComponente),1,indComponentesA);
    fread(&comp,sizeof(t_indComponente),1,componentesA);
    while(!indComponentesA)
    {
        ind=(t_indComponente*)malloc(sizeof(t_indComponente));
        strcpy(ind->codigo,comp->codigo);

        fseek(componentesA,0L,SEEK_CUR);
        ind->nroReg = ftell(componentesA);

        fread(&ind,sizeof(t_indComponente),1,indComponentesA);
        fread(&comp,sizeof(t_indComponente),1,componentesA);
///        free(ind);
    }
    *ceInd=ftell(componentesA)/sizeof(t_indComponente);
    fclose(componentesA);
    fclose(indComponentesA);
    return ind;
}

void eliminar_duplicados_de_lista_ord(t_lista* plista, t_cmp cmp, t_actualizar actualizar)
{
    while(cmp(&(*plista)->info,&(*plista)->psig->info)>0)
        plista=&(*plista)->psig;
    while(*plista)
    {
        while((*plista)->psig && cmp(&(*plista)->info,&(*plista)->psig->info)==0)
        {
            actualizar(&(*plista)->info,&(*plista)->psig->info);
            t_nodo* elim = (*plista)->psig;
            (*plista)->psig=elim->psig;
            free(elim);
        }
        plista=&(*plista)->psig;
    }
}

int buscarEnIndice(t_indComponente* indice, int ce, const char* codigo)
{

    //fseek(componentes,indice*sizeof(t_componente),SEEK_SET);
}

void obtenerPathIdx(const char* pathComponentes, char* pathComponentesIdx)
{
//    remove(pathComponentes);
//    rename(pathComponentes,pathComponentesIdx);
}

int comparacion(const void* dato1, const void* dato2)
{
    t_armadoYRep* d1 = (t_armadoYRep*) dato1;
    t_armadoYRep* d2 = (t_armadoYRep*) dato2;
    return strcmp(d1->codigo,d2->codigo);
}

void actualizar(void* dato1, const void* dato2)
{
    t_armadoYRep* d1 = (t_armadoYRep*) dato1;
    t_armadoYRep* d2 = (t_armadoYRep*) dato2;
    d1->cantidad+=d2->cantidad;
}

