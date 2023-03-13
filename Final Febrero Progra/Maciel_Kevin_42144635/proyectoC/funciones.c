///Maciel_Kevin_42144635
#include "funciones.h"

void crearLista(tLista *p)
{
    *p = NULL;
}
int insertarAcumulandoEnLista( tLista *p, void *d, unsigned cantBytes, int (*cmp)(const void*, const void*),
                               void (*acum)(void**,unsigned tam, const void*, unsigned cantBytes))
{
    tNodo *nue;

    while(*p && cmp(d,(*p)->info) )
    {
        p = &(*p)->sig;
    }

    if( *p && (cmp(d,(*p)->info)) == 0)
    {
        //acumular
        acum(&(*p)->info, (*p)->tamInfo, d, cantBytes);
        return 1;
    }
    if( (nue = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
            (nue->info = malloc(cantBytes)) == NULL )
    {
        free(nue);
        return 0;
    }

    //Creo nuevo nodo
    memcpy(nue->info, d,cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
     *p = nue;
    return 1;
}

int insertarArchivoEnLista(tLista *p, unsigned cantBytes, const char *path,
                           int (*cmp)(const void*, const void*),
                           void (*acum)(void**,unsigned tam, const void*, unsigned cantBytes)
                          )
{
    FILE *fp = fopen("vehiculos.dat","rb");
    tVehiculo leer;
    if(!fp)
    {
        return 0;
    }

    fread(&leer,sizeof(tVehiculo),1,fp);
    while(!feof(fp))
    {
        tVehiculoProm aInsertar;
        strcpy(aInsertar.dominio, leer.dominio);
        aInsertar.antiguedad = leer.antiguedad;
        aInsertar.kilometros = leer.kilometros;
        aInsertar.cantVehiculos = 1;

        insertarAcumulandoEnLista(p,&aInsertar,sizeof(tVehiculoProm),cmp,acum);
        fread(&leer,sizeof(tVehiculo),1,fp);
    }
    fclose(fp);
    return 1;
}

int grabarListaEnArchivo(tLista *p,const char *path)
{
    FILE *fp = fopen(path, "w");

    if(!fp)
    {
        return 0;
    }

    tVehiculoProm leer;
    while(sacarPrimeroDeLista(p,&leer,sizeof(tVehiculoProm)))
    {
        int prom = leer.kilometros / leer.cantVehiculos;
        fprintf(fp,"%d-%d\n",leer.antiguedad,prom);
    }

    fclose(fp);
    return 1;
}

int sacarPrimeroDeLista(tLista *p,void *d,unsigned cantBytes)
{
    tNodo *aux;
    if(!*p)
        return 0;

    aux = *p;
    *p = aux->sig;
    memcpy(d, aux->info,cantBytes);
    return 1;
}

