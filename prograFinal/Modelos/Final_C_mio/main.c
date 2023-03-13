#include <stdio.h>
#include <stdlib.h>

#include <memory.h>

#define minimo(x,y) ((x) <= (y)? (x) : (y))

typedef struct
{
    char dominio[7];
    int antiguedad;
    float kmRecorridos;
} Vehiculo;

typedef struct
{
    int antiguedad;
    float kmPromedio;
    int cantAnios;
} VehiculoRes;

typedef struct sNodo
{
    void* elem;
    size_t tamElem;
    struct sNodo* sig;
    struct sNodo* ant;
} Nodo;

typedef Nodo* Lista;

typedef int (*Cmp)(const void* dato1, const void* dato2);
typedef void (*Actualizar)(void* actualizado, const void* actualizador);
typedef void (*Mostrar)(const void* dato);

void crearLista(Lista* pl);
void vaciarLista(Lista* pl);
int insertarEnListaCDup(Lista* pl,const void* elem, size_t tamElem, Cmp cmp);
int eliminarDeListaIgualAElem(Lista *pl, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int eliminarPrimeroDeLista(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
void recorrerLista(Lista* pl, Mostrar mostrar);
int listaVacia(const Lista* pl);

void genArch();
int cargarEnListaArchVehiculos(Lista* pl, const char* nomArch);
int compararVehiculos(const void* dato1, const void* dato2);
int compararVehiculosRes(const void* dato1, const void* dato2);
void mostrarVehiculos(const void* dato);
void mostrarVehiculosRes(const void* dato);
void actualizarVehiculos(void* actualizado, const void* actualizador);

int main()
{
    ///  genArch();

    Lista listaVehiculo;
    crearLista(&listaVehiculo);

    Lista listaRes;
    crearLista(&listaRes);

    cargarEnListaArchVehiculos(&listaVehiculo,"Vehiculos.bin");

    recorrerLista(&listaVehiculo,mostrarVehiculos);

    VehiculoRes regRes;
    Vehiculo regV;
    Vehiculo regAux;

    while(!listaVacia(&listaVehiculo))
    {
        eliminarPrimeroDeLista(&listaVehiculo,&regV,sizeof(Vehiculo),compararVehiculos);

        regRes.antiguedad = regV.antiguedad;
        regRes.cantAnios = 1;

        regAux.antiguedad = regV.antiguedad;
        regAux.kmRecorridos = regV.kmRecorridos;

        while(eliminarDeListaIgualAElem(&listaVehiculo,&regAux,sizeof(Vehiculo),compararVehiculos,actualizarVehiculos))
        {
            regRes.cantAnios++;
        }

        regRes.kmPromedio = regAux.kmRecorridos/regRes.cantAnios;

        insertarEnListaCDup(&listaRes,&regRes,sizeof(VehiculoRes),compararVehiculosRes);
    }

    recorrerLista(&listaRes,mostrarVehiculosRes);

    return 1;
}

int cargarEnListaArchVehiculos(Lista* pl, const char* nomArch)
{
    FILE *pf = fopen(nomArch,"rb");
    if(!pf)
    {
        fclose(pf);
        return 0;
    }

    Vehiculo regVehiculo;

    fread(&regVehiculo,sizeof(Vehiculo),1,pf);
    while(!feof(pf))
    {
        insertarEnListaCDup(pl,&regVehiculo,sizeof(Vehiculo),compararVehiculos);
        fread(&regVehiculo,sizeof(Vehiculo),1,pf);
    }

    fclose(pf);

    return 1;
}

int compararVehiculos(const void* dato1, const void* dato2)
{
    Vehiculo* v1 = (Vehiculo*)dato1;
    Vehiculo* v2 = (Vehiculo*)dato2;

    return v1->antiguedad-v2->antiguedad;
}

int compararVehiculosRes(const void* dato1, const void* dato2)
{
    VehiculoRes* v1 = (VehiculoRes*)dato1;
    VehiculoRes* v2 = (VehiculoRes*)dato2;

    return v1->antiguedad - v2->antiguedad;
}

void mostrarVehiculos(const void* dato)
{
    Vehiculo* veh = (Vehiculo*)dato;

    printf("%s %d %f\n",veh->dominio,veh->antiguedad,veh->kmRecorridos);
}

void mostrarVehiculosRes(const void* dato)
{
    VehiculoRes* v = (VehiculoRes*)dato;

    printf("%d %f\n",v->antiguedad,v->kmPromedio);
}

void actualizarVehiculos(void* actualizado, const void* actualizador)
{
    Vehiculo* vActualizado = (Vehiculo*)actualizado;
    Vehiculo* vActualizador = (Vehiculo*)actualizador;

    vActualizado->kmRecorridos += vActualizador->kmRecorridos;
}

void genArch()
{
    FILE *pf = fopen("Vehiculos.bin","wb");

    Vehiculo vec[] =
    {
        {"AAA111",10,200},
        {"BBB111",5,100},
        {"AAA222",10,300},
        {"CCC111",1,100},
        {"DDD111",5,500}
    };

    fwrite(vec,sizeof(Vehiculo),5,pf);

    fclose(pf);
}

void crearLista(Lista* pl)
{
    *pl = NULL;
}

void vaciarLista(Lista* pl)
{

}

int insertarEnListaCDup(Lista* pl,const void* elem, size_t tamElem, Cmp cmp)
{
    Nodo *nue = malloc(sizeof(Nodo));
    nue->elem = malloc(tamElem);

    if(!nue->elem || !nue)
    {
        free(nue->elem);
        free(nue);
        return 0;
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

            nue->sig = sig;
            nue->ant = ant;

            *pl = nue;

            return 1;
        }

        if(comp >= 0)
        {
            Nodo* ant = act->ant;
            Nodo* sig = act;

            ant->sig = nue;
            sig->ant = nue;

            nue->sig = sig;
            nue->ant = ant;

            *pl = nue;

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

            *pl = nue;

            return 1;
        }

        if(comp <= 0)
        {
            Nodo* ant = act;
            Nodo* sig = act->sig;

            ant->sig = nue;
            sig->ant = nue;

            nue->sig = sig;
            nue->ant = ant;

            *pl = nue;

            return 1;
        }
    }

    Nodo* ant = (*pl)->ant;
    Nodo* sig = (*pl);

    if(ant)
        ant->sig = nue;

    nue->sig = sig;
    nue->ant = ant;

    *pl = nue;

    return 1;
}

int eliminarDeListaIgualAElem(Lista *pl, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return 0;

    if(cmp((*pl)->elem,elem) < 0)
    {
        Nodo* act = *pl;

        while(act->sig && cmp(act->elem,elem) < 0)
            act = act->sig;

        int comp = cmp(act->elem,elem);

        if(comp == 0)
        {
            actualizar(elem,act->elem);
            Nodo* nae = act;

            if(nae->ant)
                nae->ant->sig = act->sig;
            if(nae->sig)
                nae->sig->ant = act->ant;

            act = act->sig;

            free(nae->elem);
            free(nae);

            return 1;
        }

        return 0;
    }

    if(cmp((*pl)->elem,elem) > 0)
    {
        Nodo* act = *pl;

        while(act->ant && cmp(act->elem,elem) > 0)
            act = act->ant;

        int comp = cmp(act->elem,elem);

        if(comp == 0)
        {
            actualizar(elem,act->elem);
            Nodo* nae = act;

            if(nae->ant)
                nae->ant->sig = act->sig;
            if(nae->sig)
                nae->sig->ant = act->ant;

            act = act->ant;

            free(nae->elem);
            free(nae);

            return 1;
        }

        return 0;
    }

    actualizar(elem,(*pl)->elem);
    Nodo* nae = *pl;

    if(nae->ant)
        nae->ant->sig = (*pl)->sig;
    if(nae->sig)
        nae->sig->ant = (*pl)->ant;

    if((*pl)->ant)
        *pl = (*pl)->ant;
    else if((*pl)->sig)
        *pl = (*pl)->sig;
    else
        *pl = NULL;

    free(nae->elem);
    free(nae);

    return 1;
}

int eliminarPrimeroDeLista(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return 0;

    Nodo* act = *pl;

    while(act->ant)
        act = act->ant;

    Nodo* nae = act;

    if(nae->sig)
    {
        nae->sig->ant = NULL;
        act = act->sig;
    }
    else
        act = NULL;

    memcpy(elem,nae->elem,minimo(tamElem,nae->tamElem));

    *pl = act;

    free(nae->elem);
    free(nae);

    return 1;
}

void recorrerLista(Lista* pl, Mostrar mostrar)
{
    if(!*pl)
        return;

    while((*pl)->ant)
        pl = &(*pl)->ant;

    while(*pl)
    {
        mostrar((*pl)->elem);
        pl = &(*pl)->sig;
    }
}

int listaVacia(const Lista* pl)
{
    return *pl == NULL;
}
