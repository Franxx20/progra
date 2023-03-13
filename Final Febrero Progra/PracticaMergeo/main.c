#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char codigo;
    char nombre[20];
    int stock;

} Producto;

typedef struct
{

    char codigo;
    int stock;
}
Movimiento;

typedef int (*Cmp) (const void * d1,const void * d2);
typedef void (*Parseador) (const char * cadena,  void * dato);
typedef void (*Actualizar) (void * actualizado, const void * actualizador);
typedef void (*Grabar)(const void * dato, FILE *fp);
typedef void (*Inicializar)(void * d1, const void * d2);

void crearArchivoActualizable(const char * nombreArchivo);
void crearArchivoActualizador(const char * nombreArchivo);
void actualizarArchivos(const char * nombreArchivoActualizado, const char * nombreArchivoActualizador,const char * nombreArchivoFinal,unsigned tamActualizado, unsigned tamActualizador, Cmp comparador,Actualizar actualizar,Grabar grabar,Parseador parseador,Inicializar inicializar);

int compararCodigos(const void * d1,const void * d2);
void parsearProductos(const char * cadena, void *Producto );
void actualizarProductos(void * actualizado, const void * actualizador);
void grabarProducto(const void * dato, FILE *fp);
void inicializarProducto(void * d1, const void * d2);
int main()
{
    crearArchivoActualizable("actualizado.txt");
    crearArchivoActualizador("actualizador.bin");
    actualizarArchivos("actualizado.txt","actualizador.bin","final.txt",sizeof(Producto),sizeof(Movimiento),compararCodigos,actualizarProductos,grabarProducto,parsearProductos,inicializarProducto);

    return 0;
}

void crearArchivoActualizable(const char * nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo, "wt");
    int i=0;
    Producto vectorProductos[]=
    {
        {'A',"Arvejas",5},
        {'B',"Banana",15},
        {'C',"Caracoles",23},
        {'F',"Fideos",30},
        {'H',"Harina",10},
        {'Y',"Yerba Mate",35}
    };
    if(!fp)
    {
        fprintf(stderr, "ERROR AL CREAR EL ARCHIVO DE TEXTO");
        return ;
    }



    for (; i<6 ; i++ )
    {
        fprintf(fp,"%c|%-20s|%d\n",vectorProductos[i].codigo,vectorProductos[i].nombre,vectorProductos[i].stock);
    }


    fclose(fp);
}

void crearArchivoActualizador(const char * nombreArchivo)
{
    int i =0;
    FILE * fp = fopen(nombreArchivo,"wb");
    Movimiento vectorMovimientos[] =
    {
        {'A', 5},
        {'A',-10},
        {'B',15},
        {'B',30},
        {'C',-3},
        {'C',20},
        {'F',20},
        {'R',10},
        {'R',1000},
        {'Y',15},
        {'Z',12},

    };
    if(!fp)
    {
        fprintf(stderr,"ERROR AL CREAR EL ARCHIVO BINARIO DE ACTUALIZACIONES");
        return;
    }
    for (; i<11 ; i++)
    {
        fwrite(&vectorMovimientos[i],sizeof(Movimiento),1,fp);
    }

    fclose(fp);

}

void actualizarArchivos(const char * nombreArchivoActualizado, const char * nombreArchivoActualizador,const char * nombreArchivoFinal,unsigned tamActualizado, unsigned tamActualizador, Cmp comparador,Actualizar actualizar,Grabar grabar,Parseador parseador,Inicializar inicializar)
{
    FILE * fpActualizado = fopen(nombreArchivoActualizado,"rt");
    FILE * fpActualizador = fopen(nombreArchivoActualizador, "rb");
    FILE * fpFinal = fopen(nombreArchivoFinal,"wt");

    int  resultado;

    char linea[35];
    void * actualizado = malloc(tamActualizado);
    void * actualizador = malloc(tamActualizador);
    void * nuevoElemento = malloc(tamActualizado);

    if(!fpActualizado || !fpActualizador || !fpFinal)
    {
        fprintf(stderr, "ERROR ACTUALIZAR ARCHIVOS");
        return;
    }

    fgets(linea,35,fpActualizado);
    parseador  (linea,actualizado);

    fread(actualizador,tamActualizador,1,fpActualizador);

    while(!feof(fpActualizador) && !feof(fpActualizado))
    {


        resultado = comparador(actualizado,actualizador);
        /* PRODUCTO SIN MOVIMIENTOS*/
        if(resultado < 0)
        {
            grabar(actualizado,fpFinal);
            if(fgets(linea,35,fpActualizado))
                parseador  (linea,actualizado);

        }
        /* PRODUCTOS CON MOVIMIENTOS */
        if(resultado ==0)
        {
            actualizar(actualizado,actualizador);
            fread(actualizador,tamActualizador,1,fpActualizador);
        }
        /* PRODUCTO NUEVO */
        if(resultado > 0)
        {
            inicializar(nuevoElemento,actualizador);
            actualizar(nuevoElemento,actualizador);
            fread(actualizador,tamActualizador,1,fpActualizador);
            while(!feof(fpActualizador) && comparador(nuevoElemento,actualizador)==0)
            {
                actualizar(nuevoElemento,actualizador);
                fread(actualizador,tamActualizador,1,fpActualizador);
            }
            grabar(nuevoElemento,fpFinal);
        }
    }

    while(!feof(fpActualizado))
    {
        grabar(actualizado,fpFinal);


        if(fgets(linea,35,fpActualizado))
            parseador(linea,actualizado);

    }

    while(!feof(fpActualizador))
    {
        inicializar(nuevoElemento,actualizador);
        actualizar(nuevoElemento,actualizador);
        fread(actualizador,tamActualizador,1,fpActualizador);
        while(!feof(fpActualizador) && comparador(nuevoElemento,actualizador)==0)
        {
            actualizar(nuevoElemento,actualizador);
            fread(actualizador,tamActualizador,1,fpActualizador);
        }
        grabar(nuevoElemento,fpFinal);
    }

    free(actualizado);
    free(actualizador);
    free(nuevoElemento);

    fclose(fpActualizado);
    fclose(fpActualizador);
    fclose(fpFinal);
}

int compararCodigos(const void * d1,const void * d2)
{
    const Producto * producto =(const Producto * )d1;
    const Movimiento * movimiento = ( const Movimiento * )d2;

    return producto->codigo - movimiento->codigo;

}

void parsearProductos(const char * cadena, void *prod )
{
    char * aux = strrchr(cadena,'\n');
    Producto * producto = (Producto*)prod;
    if(!aux)
    {
        fprintf(stdout, "ERROR DE FIN DE LINEA\n");
        return;
    }


    *aux = '\0';
    aux = strrchr(cadena,'|');
    sscanf(aux+1,"%d",&producto->stock);

    *aux = '\0';
    aux = strrchr(cadena,'|');
    strcpy(producto->nombre,aux+1);

    sscanf(cadena,"%c",&producto->codigo);


}

void actualizarProductos(void * actualizado, const void * actualizador)
{

    Producto * producto = (Producto *) actualizado;
    const Movimiento  * movimiento = (const Movimiento *) actualizador;

    producto->stock += movimiento->stock;
}

void grabarProducto(const void * dato, FILE *fp)
{
    const Producto * producto = (const Producto *) dato;
    fprintf(fp,"%c|%-20s|%d\n",producto->codigo,producto->nombre,producto->stock);
    fprintf(stdout,"%c|%-20s|%d\n",producto->codigo,producto->nombre,producto->stock);
}


void inicializarProducto(void * d1, const void *d2)
{
    Producto * producto = (Producto * )d1;
    Movimiento * actualizador = (Movimiento * )d2;

    producto->codigo = actualizador->codigo;
    strcpy(producto->nombre,&actualizador->codigo);


    producto->stock =0;
}
