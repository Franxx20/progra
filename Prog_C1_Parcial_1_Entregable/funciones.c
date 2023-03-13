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

#define miToupper(c) ((c) >= 'a' && (c) <= 'z' ? ((c) - 32) : (c))
#define miTolower(c) ((c) >= 'A' && (c) <= 'Z' ? ((c) + 32) : (c))
#define noLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') ? 0 : 1)

#include <stdlib.h>
#include <string.h>

/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO HASTA ACÁ *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"


/** para el PUNTO 1 **/
char *normalizarCadena_MIO(char *str)
{
    char *aux = str;
    char *cadNor = (char*)malloc(100);
    unsigned contCaract = 0;

    while(*aux)
    {
        while(*aux == ' ')
            aux++;
        if(!noLetra(*aux))
            aux = normalizarPalabra(aux,cadNor,&contCaract);
    }

    strcpyMIO(str,cadNor);


    return cadNor;
}

char* strcpyMIO(char* dest, const char* origen)
{
    while(*origen)
    {
        *dest = *origen;
        origen++;
        dest++;
    }
    *dest = '\0';
    return dest;
}

char* normalizarPalabra(char *palabra, char* cadNor,unsigned *contCaract)
{
    unsigned contCarac = 0;

    cadNor+=*contCaract;

    if(!*cadNor)
    {
        *cadNor = ' ';
        cadNor++;
        contCarac++;
    }

    *cadNor = miToupper(*palabra);
    cadNor++;
    palabra++;

    while(*palabra != ' ' && *palabra != '\n' && *palabra)
    {
        if(!noLetra(*palabra))
        {
            *cadNor = miTolower(*palabra);
            cadNor++;
            palabra++;
            contCarac++;
        }
        else
        {
            *cadNor = *palabra;
            cadNor++;
            palabra++;
            contCarac++;
        }
    }

    *cadNor = '\0';
    contCarac++;

    *contCaract += contCarac;

    return palabra;
}

/** FIN de PUNTO 1 **/


/** para el PUNTO 2 **/
int fusionarMaestros_MIO(char *nombreArchivo1,
                         char *nombreArchivo2,
                         char *nombreArchivoF)
{
    FILE *pf1 = fopen(nombreArchivo1,"rb");
    FILE *pf2 = fopen(nombreArchivo2,"rb");
    FILE *pfF = fopen(nombreArchivoF,"wb");

    if(!pf1 || !pf2 || !pfF)
    {
        puts("Uno de los archivos no se abrio");
        return -1;
    }

    tProducto regArch1;
    tProducto regArch2;

    fread(&regArch1,sizeof(tProducto),1,pf1);
    fread(&regArch2,sizeof(tProducto),1,pf2);
    while(!feof(pf1) && !feof(pf2))
    {
        int compId = regArch1.idProducto - regArch2.idProducto;

        if(compId < 0)
        {
            normalizarCadena_MIO(regArch1.descripcion);
            fwrite(&regArch1,sizeof(tProducto),1,pfF);
            fread(&regArch1,sizeof(tProducto),1,pf1);
        }
        if(compId > 0)
        {
            normalizarCadena_MIO(regArch2.descripcion);
            fwrite(&regArch2,sizeof(tProducto),1,pfF);
            fread(&regArch2,sizeof(tProducto),1,pf2);
        }
        if(compId == 0)
        {
            int compFechaAnio = regArch1.fecUltAct.anio - regArch2.fecUltAct.anio;
            if(compFechaAnio > 0)
            {
                normalizarCadena_MIO(regArch1.descripcion);
                fwrite(&regArch1,sizeof(tProducto),1,pfF);
                fread(&regArch1,sizeof(tProducto),1,pf1);
            }
            if(compFechaAnio < 0)
            {
                normalizarCadena_MIO(regArch2.descripcion);
                fwrite(&regArch2,sizeof(tProducto),1,pfF);
                fread(&regArch2,sizeof(tProducto),1,pf2);
            }
            if(compFechaAnio == 0)
            {
                int compFechaMes = regArch1.fecUltAct.mes - regArch2.fecUltAct.mes;
                if(compFechaMes < 0)
                {
                    normalizarCadena_MIO(regArch1.descripcion);
                    fwrite(&regArch1,sizeof(tProducto),1,pfF);
                    fread(&regArch1,sizeof(tProducto),1,pf1);
                }
                if(compFechaMes > 0)
                {
                    normalizarCadena_MIO(regArch2.descripcion);
                    fwrite(&regArch2,sizeof(tProducto),1,pfF);
                    fread(&regArch2,sizeof(tProducto),1,pf2);
                }
                if(compFechaMes == 0)
                {
                    int compFechaDia = regArch1.fecUltAct.dia -regArch2.fecUltAct.dia;
                    if(compFechaDia < 0)
                    {
                        normalizarCadena_MIO(regArch1.descripcion);
                        fwrite(&regArch1,sizeof(tProducto),1,pfF);
                        fread(&regArch1,sizeof(tProducto),1,pf1);
                    }

                    if(compFechaDia > 0)
                    {
                        normalizarCadena_MIO(regArch2.descripcion);
                        fwrite(&regArch2,sizeof(tProducto),1,pfF);
                        fread(&regArch2,sizeof(tProducto),1,pf2);
                    }
                    if(compFechaDia == 0)
                    {
                        normalizarCadena_MIO(regArch1.descripcion);
                        normalizarCadena_MIO(regArch2.descripcion);
                        fwrite(&regArch1,sizeof(tProducto),1,pfF);
                        fwrite(&regArch2,sizeof(tProducto),1,pfF);
                        fread(&regArch1,sizeof(tProducto),1,pf1);
                        fread(&regArch2,sizeof(tProducto),1,pf2);
                    }
                }
            }
        }
    }

    while(!feof(pf1))
    {
        normalizarCadena_MIO(regArch1.descripcion);
        fwrite(&regArch1,sizeof(tProducto),1,pfF);
        fread(&regArch1,sizeof(tProducto),1,pf1);
    }

    while(!feof(pf2))
    {
        normalizarCadena_MIO(regArch2.descripcion);
        fwrite(&regArch2,sizeof(tProducto),1,pfF);
        fread(&regArch2,sizeof(tProducto),1,pf2);
    }

    fclose(pf1);
    fclose(pf2);
    fclose(pfF);

    return 1;
}
/** FIN de PUNTO 2 **/


/** para el PUNTO 3 **/
int cargarMaestroEnLista_MIO(char *nombreArchivoMaestro,
                             tLista *pl,
                             FILE *fpPantalla)
{
    FILE *pfArchMaestro = fopen(nombreArchivoMaestro,"rb");
    if(!pfArchMaestro)
    {
        puts("No se pudo abrir el archivo");
        return -34;
    }

    tProducto regArch;

    fread(&regArch,sizeof(tProducto),1,pfArchMaestro);
    while(!feof(pfArchMaestro))
    {
        tNodo *nue = malloc(sizeof(tNodo));
        nue->info = malloc(sizeof(tProducto));

        if(!nue->info || !nue)
        {
            free(nue);
            free(nue->info);
            return -132; ///SIN_MEM
        }

        memcpy(nue->info,&regArch,sizeof(tProducto));
        nue->tamInfo = sizeof(tProducto);

        if(!*pl)
        {
            *pl = nue;
            nue->sig = NULL;
        }
        else
        {
            while((*pl)->sig)
                pl = &(*pl)->sig;
            (*pl)->sig = nue;
            nue->sig = NULL;
        }

        fread(&regArch,sizeof(tProducto),1,pfArchMaestro);
    }

    fclose(pfArchMaestro);

    return 0;
}
/** FIN de PUNTO 3 **/


/** para el PUNTO 4 **/
int eliminarDupYsobrescibirMaestro_MIO(tLista *pl,
                                       int *cantDupEliminados,
                                       const char *nombreArchivoMaestro)
{

    FILE *pfArchMaestro = fopen(nombreArchivoMaestro,"rb");
    FILE *pfTemp = fopen("archTemp.temp","wb");

    if(!pfArchMaestro || !pfTemp)
        return -1;

    *cantDupEliminados = 0;

    while((*pl)->sig)
    {
        if(compararProd((*pl)->info,(*pl)->sig->info) != 0)
        {
            tProducto *reg;

            reg = (tProducto*)(*pl)->info;

            fwrite(reg,sizeof(tProducto),1,pfTemp);

            pl = &(*pl)->sig;

        }
        else
        {
            actualizarProd((*pl)->info,(*pl)->sig->info);
            tNodo* nae = (*pl)->sig;
            (*pl)->sig = (*pl)->sig->sig;
            free(nae->info);
            free(nae);
            *(cantDupEliminados)+= 1;
        }
    }

    tProducto *reg;

    reg = (tProducto*)(*pl)->info;

    fwrite(reg,sizeof(tProducto),1,pfTemp);

    fclose(pfArchMaestro);
    fclose(pfTemp);

    remove(nombreArchivoMaestro);
    rename("archTemp.temp",nombreArchivoMaestro);

    return 1;
}

int compararProd(const void* prod1, const void* prod2)
{
    tProducto *producto1 = (tProducto*)prod1;
    tProducto *producto2 = (tProducto*)prod2;

    return (producto1->idProducto - producto2->idProducto);
}

void actualizarProd(void* prodViejo, const void* prodNuevo)
{
    tProducto *producto1 = (tProducto*)prodViejo;
    tProducto *producto2 = (tProducto*)prodNuevo;

    producto1->cantidad += producto2->cantidad;
    producto1->fecUltAct = producto2->fecUltAct;
}

/** FIN de PUNTO 4 **/


/** para el PUNTO 5 **/
int actualizarMaestroDesdeArchivoDeNovedades_MIO(char *nombreArchivoMaestro,
        char *nombreArchivoNovedades,
        FILE *fpPantalla)
{
    FILE *pfMaestro = fopen(nombreArchivoMaestro,"rb");
    FILE *pfNovedades = fopen(nombreArchivoNovedades,"rt");
    FILE *pfTemp = fopen("ArchivoTemp.temp","wb");

    if(!pfMaestro || !pfNovedades || !pfTemp)
        return -1;

    tProducto regProd;
    unsigned cantAct = 0;

    fread(&regProd,sizeof(tProducto),1,pfMaestro);
    while(!feof(pfMaestro))
    {
        tNovedad regNovedad;
        char aux[10];
        while(fgets(aux,sizeof(aux),pfNovedades))
        {
            parceoNovedades(&regNovedad,aux);
            if(regNovedad.idProducto == regProd.idProducto)
            {
                switch(regNovedad.tipoMovimiento)
                {
                case 'E':
                    regProd.cantidad -= regNovedad.cantidad;
                    break;
                case 'I':
                    regProd.cantidad += regNovedad.cantidad;
                    break;
                }
                cantAct++;
            }
        }
        fwrite(&regProd,sizeof(tProducto),1,pfTemp);

        fseek(pfNovedades,0L,SEEK_SET);

        fread(&regProd,sizeof(tProducto),1,pfMaestro);

    }

    fclose(pfMaestro);
    fclose(pfNovedades);
    fclose(pfTemp);

    remove(nombreArchivoMaestro);
    rename("ArchivoTemp.temp",nombreArchivoMaestro);


    return cantAct;
}

void parceoNovedades(tNovedad *reg, char *cad)
{
    char *aux = cad;

    aux = strrchr(cad,'\n');
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;

    reg->cantidad = deCadenaAInt(aux);

    aux--;
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;

    reg->tipoMovimiento = *aux;

    aux--;
    *aux = '\0';

    reg->idProducto = deCadenaAInt(cad);
}

int deCadenaAInt(char *cad)
{
    char *aux = cad;
    int num = 0;

    unsigned digitos = strlen(aux);

    while(*aux)
    {
        int potencia = 1;
        for(int i = 1; i < digitos; i++)
            potencia *= 10;
        num += (*aux-'0')* potencia;
        aux++;
        digitos--;
    }

    return num;
}

/** FIN de PUNTO 5 **/

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

