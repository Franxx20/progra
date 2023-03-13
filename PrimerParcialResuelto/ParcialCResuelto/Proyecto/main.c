#include <stdio.h>
#include <stdlib.h>

/*
Se desea realizar una simulacion que permita definir el tamaño maximo requerido para una cola
o "buffer" de procesamiento de paquetes.Los paquetes llegan con igual probabilidad
cada 0,12,15 o 20 ciclos. Los paquetes contienen palabras y el tiempo de procesamiento
del paquetes es de un ciclo por caracter en la palabra, solo es posible procesar un paquete
por vez.
El archivo binario "simulacion.dat" contiene una secuencia de paquetes obtenida
del sistema real, utilice el archivo como fuente de entrada de paquetes.


Tema b) Dado que simulacion final se correra sobre una plataforma que no acepta memoria
dinamica implemente una cola estatica para determinar el maximo. Verifique que siempre
sea posible encolar, caso contrario vuelva a ejecutar la simulacion cambiando los tamaños
segun corresponda.

Nota: para obtener resultados deterministas no realice ninguna llamada a srand()

*/

#include <stdlib.h>
#include "../Comunes/Tipos.h"
#include "../Comunes/Cola.h"
#include "../Comunes/Utilitarias.h"

int main()
{
    int tam_max;
    int res;

    CrearLoteSimulacion();
    t_cola cola;
    crearCola(&cola);
    res =  sim_cola(&cola, &tam_max);
//    res =  sim_cola_res(&cola, &tam_max);
    if(res==EJECUCION_EXITOSA){
        printf("El tamano maximo necesario para cola es %d\n", tam_max);
    }else if(res==MEMORIA_INSUFICIENTE){
        puts("Memoria insuficiente, considere mas espacio si la cola es estatica o");
        puts("considere compilacion en 64bits o mas hardware!");
    }else if(res==SIMULACION_FALLIDA){
        puts("Error inesperado, simulacion fallida");
    }

}

