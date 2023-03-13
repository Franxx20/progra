/**//*             en los siguientes macroreemplazos indique:             *//**/
/**//*    su(s)         APELLIDO(S)     completo(s)                       *//**/
/**//*    su(s)         Nombre(S)       completo(s)                       *//**/
/**//*    su legajo     NÚMERO DE DNI   con los puntos de millón y de mil *//**/
/**//*    COMISIÓN                                                        *//**/
/**//*              reemplazando los que están como ejemplo               *//**/
#define APELLIDO    "PÉREZ DEL RÍO"
#define NOMBRE      "Juan Manuel"
#define DOCUMENTO   "22.333.444"
#define COMISION    "07(7299)"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/** aquí insertaremos nuestras observaciones y / o correcciones              **/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#undef APELLIDO
#undef NOMBRE
#undef DOCUMENTO
#undef COMISION
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO DESDE ACÁ *//**/



/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO HASTA ACÁ *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"


/** para el PUNTO 1 **/
void *mi_memmove_MIO(void *dest, const void *orig, size_t cant)
{
    const char *aux = orig;
    char *temp = dest;
    if(dest <= orig)
    {
        while(cant)
        {
            *temp = *aux;
            temp++;
            aux++;
            cant--;
        }
    }
    else
    {
        temp += cant;
        aux += cant;
        while(cant)
        {
            temp--;
            aux--;
            *temp=*aux;
            cant--;
        }
    }
    return dest;
}
/** FIN de PUNTO 1 **/


/** para el PUNTO 2 **/
int fusionarMaestros_MIO(char *nombreArchivo1,char *nombreArchivo2,char *nombreArchivoF)
{
    FILE* f1=fopen(nombreArchivo1,"rb"),* f2=fopen(nombreArchivo2,"rb"),* f=fopen(nombreArchivoF,"wb");
    if(!f1 || !f2 || !f)
    {
        fclose(f1);
        fclose(f2);
        fclose(f);
        return 1;
    }
    rewind(f1);
    rewind(f2);
    rewind(f);
    tProducto prod1, prod2;
    fread(&prod1,sizeof(tProducto),1,f1);
    fread(&prod2,sizeof(tProducto),1,f2);
    while(!feof(f1) || !feof(f2))
    {
        while (!feof(f1) && prod1.idProducto <= prod2.idProducto)
        {
            fwrite(&prod1,sizeof(tProducto),1,f);
            fread(&prod1,sizeof(tProducto),1,f1);
        }
        while (!feof(f2) && prod1.idProducto > prod2.idProducto)
        {
            fwrite(&prod2,sizeof(tProducto),1,f);
            fread(&prod2,sizeof(tProducto),1,f2);
        }
    }
    while (!feof(f1))
    {
        fwrite(&prod1,sizeof(tProducto),1,f);
        fread(&prod1,sizeof(tProducto),1,f1);
    }
    while (!feof(f2))
    {
        fwrite(&prod2,sizeof(tProducto),1,f);
        fread(&prod2,sizeof(tProducto),1,f2);
    }

    fclose(f1);
    fclose(f2);
    fclose(f);

    return 0;
}
/** FIN de PUNTO 2 **/


/** para el PUNTO 3 **/
int cargarMaestroEnListaYeliminarDuplicados_MIO(char *nombreArchivoMaestro, tLista *pl, FILE *fpPantalla)
{
    FILE* f=fopen(nombreArchivoMaestro,"rb");
    if(!f)
        return 0;
    tLista list;
    tProducto prod;
    crearLista(&list);
    fread(&prod,sizeof(tProducto),1,f);
    while(!listaVacia(&list))
    {
        insertarUltimo(&list,&prod,sizeof(tProducto));
        fread(&prod,sizeof(tProducto),1,f);
    }
    fclose(f);

    eliminarDuplicadosListaOrdAct(&list,compa,act);

    f=fopen(nombreArchivoMaestro,"rb");
    if(!f)
        return 0;

    while(!listaVacia(&list))
    {
        elimnarUltimosNelementosDeLista_MIO(&list,&prod);
        fwrite(&prod,sizeof(tProducto),1,f);
    }

    fclose(f);
    return 0;
}
/** FIN de PUNTO 3 **/


/** para el PUNTO 4 **/
int elimnarUltimosNelementosDeLista_MIO(tLista *pl, unsigned int n)
{
    return -1;
}
/** FIN de PUNTO 4 **/
int elimininarN(Lista* pl, Cmp cmp, int n)
{
   if (!*pl)
        return 0;

    Lista lOrd = NULL;
    Lista* plOrd = &lOrd;
    Nodo* nodo;
    int cont=0, i=0;

    while (*pl)
    {
        nodo = *pl; //desengancho
        *pl = nodo->sig;

        nodo->sig = *plOrd; //engancho
        *plOrd = nodo;

        cont++;
    }

    if (n>cont)
        return 1;

    while(i<n) //elimino los q dice
    {
        nodo = *plOrd; //desengancho
        *plOrd = nodo->sig;

        free(nodo->dato); //libero
        free(nodo);
    }
    while (*plOrd) //copio el resto
    {
        nodo = *plOrd; //desengancho
        *plOrd = nodo->sig;

        nodo->sig = *pl; //engancho
        *pl = nodo;
    }
    return 1;
}


/** para el PUNTO 5 **/
int actualizarMaestroDesdeArchivoDeNovedades_MIO(char *nombreArchivoMaestro,
                                                 char *nombreArchivoNovedades,
                                                 FILE *fpPantalla)
{
    return -1;
}

/** FIN de PUNTO 5 **/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

