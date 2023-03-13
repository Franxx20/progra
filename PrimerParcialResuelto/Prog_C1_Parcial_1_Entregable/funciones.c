/**/ /*             en los siguientes macroreemplazos indique:             */ /**/
/**/ /*    su(s)         APELLIDO(S)     completo(s)                       */ /**/
/**/ /*    su(s)         Nombre(S)       completo(s)                       */ /**/
/**/ /*    su legajo     N�MERO DE DNI   con los puntos de mill�n y de mil */ /**/
/**/ /*    COMISI�N                                                        */ /**/
/**/ /*              reemplazando los que est�n como ejemplo               */ /**/
#define APELLIDO "P�REZ DEL R�O"
#define NOMBRE "Juan Manuel"
#define DOCUMENTO "22.333.444"
#define COMISION "07(7299)"
/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
/** aqu� insertaremos nuestras observaciones y / o correcciones              **/
/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
#undef APELLIDO
#undef NOMBRE
#undef DOCUMENTO
#undef COMISION
/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
/**/ /**/ /* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, H�GALO DESDE AC� */                 /**/

/**/ /**/ /* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, H�GALO HASTA AC� */                 /**/
/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/

#include "funciones.h"
#include <string.h>
#define ESLETRA(a) (((a) >= 'a' && (a) <= "z") || ((a) >= 'A' && (a) <= "Z")

/** para el PUNTO 1 **/
char *normalizarCadena_MIO(char *str)
{
    return str;
}
/** FIN de PUNTO 1 **/

/** para el PUNTO 2 **/
int fusionarMaestros_MIO(char *nombreArchivo1,
                         char *nombreArchivo2,
                         char *nombreArchivoF)
{
    return 0;
}
/** FIN de PUNTO 2 **/

/** para el PUNTO 3 **/
int cargarMaestroEnLista_MIO(char *nombreArchivoMaestro,
                             tLista *pl,
                             FILE *fpPantalla)
{
    return 0;
}
/** FIN de PUNTO 3 **/

/** para el PUNTO 4 **/
int eliminarDupYsobrescibirMaestro_MIO(tLista *pl,
                                       int *cantDupEliminados,
                                       const char *nombreArchivoMaestro)
{
    *cantDupEliminados = -1;
    return -1;
}
/** FIN de PUNTO 4 **/

/** para el PUNTO 5 **/
int actualizarMaestroDesdeArchivoDeNovedades_MIO(char *nombreArchivoMaestro,
                                                 char *nombreArchivoNovedades,
                                                 FILE *fpPantalla)
{
    return -1;
}

/** FIN de PUNTO 5 **/

/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
