/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER MODIFICACIÓN QUE HAGA NO SERÁ TENIDA EN CUENTA.      *//**/
/**//**//*                                                                *//**/
/**//**//*     ¡No debería hacer ninguna modificación en este archivo!    *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>

#include "que_hice.h"
#include "tda_definiciones.h"

#define NOMBRE_ARCHIVO_1      "maestro1.dat"
#define NOMBRE_ARCHIVO_2      "maestro2.txt"
#define NOMBRE_ARCHIVO_FUSION "maestro_fusion.dat"
#define NOMBRE_ARCHIVO_NOV    "novedades.bin"

typedef struct
{
    int dia,
        mes,
        anio;
}tFecha;

typedef struct
{
    long idProducto;
    char descripcion[26];
    tFecha fecUltAct;
    int cantidad;
    float precioUnitario;
}tProducto;

typedef struct
{
    long idProducto;
    char tipoMovimiento;
    int cantidad;
}tNovedad;

/** funciones de servicio **/
int crearArchivos(char *nombreArchivo1, char *nombreArchivo2);
int crearArchivoNovedades(char *nombreArchivo);
void mostrarProducto(const void *d, FILE *fpPantalla);
void mostrarArchivoMaestro(char *nomnreArchivoMaestro, FILE *fpPantalla);
void mostrarArchivoNovedades(char *nombreArchivoNovedades, FILE *fpPantalla);
void crearLista(tLista *p);
void vaciarLista(tLista *p);
void recorrerLista(const tLista *p,
                   unsigned cantBytes,
                   FILE *fpPantalla,
                   void (*mostrar)(const void *, FILE *));



/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/** para el PUNTO 1 **/
void *mi_memmove(void *str1, const void *str2, size_t n);
void *mi_memmove_MIO(void *str1, const void *str2, size_t n);

/** para el PUNTO 2 **/
int fusionarMaestros(char *nombreArchivo1,
                     char *nombreArchivo2,
                     char *nombreArchivoF);

int fusionarMaestros_MIO(char *nombreArchivo1,
                         char *nombreArchivo2,
                         char *nombreArchivoF);

/** para el PUNTO 3 **/
int cargarMaestroEnListaYeliminarDuplicados(char *nombreArchivoMaestro,
                                            tLista *pl,
                                            FILE *fpPantalla);

int cargarMaestroEnListaYeliminarDuplicados_MIO(char *nombreArchivoMaestro,
                                                tLista *pl,
                                                FILE *fpPantalla);

/** para el PUNTO 4 **/
int elimnarUltimosNelementosDeLista(tLista *pl, unsigned int n);
int elimnarUltimosNelementosDeLista_MIO(tLista *pl, unsigned int n);


/** para el PUNTO 5 **/
int actualizarMaestroDesdeArchivoDeNovedades(char *nombreArchivoMaestro,
                                             char *nombreArchivoNovedades,
                                             FILE *fpPantalla);

int actualizarMaestroDesdeArchivoDeNovedades_MIO(char *nombreArchivoMaestro,
                                                 char *nombreArchivoNovedades,
                                                 FILE *fpPantalla);

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#endif

