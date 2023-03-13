///Maciel_Kevin_42144635
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int cmp(const void *d1, const void *d2);
void acum(void **d1,unsigned tam, const void *d2, unsigned cantBytes);

int main()
{
    printf("Hello world!\n");
    tVehiculo lote[] =
    {
        {"AAA111", 10, 200},
        {"BBB111", 5, 100},
        {"AAA222", 10, 300},
        {"CCC111", 1, 100},
        {"DDD111", 5, 500},
    };

    FILE *fp = fopen("vehiculos.dat","wb");
    if(!fp)
    {
        return 0;
    }
    fwrite(lote, sizeof(lote),1,fp);
    fclose(fp);

    ///crear lista
    tLista p;
    crearLista(&p);
    ///insertar archivo en lista
    insertarArchivoEnLista(&p, sizeof(tVehiculo),"vehiculos.dat",cmp, acum);
    ///grabar lista en archivo con promedio
    grabarListaEnArchivo(&p,"promXantig.txt");

    return 0;
}

int cmp(const void *d1, const void *d2)
{
    const tVehiculoProm *p1 = (tVehiculoProm*)d1;
    const tVehiculoProm *p2 = (tVehiculoProm*)d2;

    return p1->antiguedad - p2->antiguedad;
}

//en funcion acumular, sumarle a prom 1

 void acum(void **d1,unsigned tam, const void *d2, unsigned cantBytes)
 {
    tVehiculoProm **p1 = (tVehiculoProm**)d1;
    const tVehiculoProm *p2 = (tVehiculoProm*)d2;

    (*p1)->kilometros += p2->kilometros;
    (*p1)->cantVehiculos += 1;
 }
