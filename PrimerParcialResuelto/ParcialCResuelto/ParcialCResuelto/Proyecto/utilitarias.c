
#include "../Comunes/Tipos.h"
#include "../Comunes/Cola.h"
#include "../Comunes/Utilitarias.h"

int ciclos_espera_paquete()
{
    int ciclos[]={0,11,15,20};
    return ciclos[rand()%4];
}
int sim_cola(t_cola* cola, int* tam_max)
{
    FILE* arch=fopen(PATH_ARCH,"rb");
    t_dato dato;
    t_dato act;
    char* cad;
    int res=0;
    int espera=0,i=0;
    int tammax=0;
    if(!arch)
        return SIMULACION_FALLIDA;
    espera=ciclos_espera_paquete();//espera de llegada de paquetes
    while(i!=espera) //ciclos
        i++;




    fread(&dato,sizeof(t_dato),1,arch);
    res=aColar(cola,&dato);// ingresa el paquete a la cola
    espera=ciclos_espera_paquete();//calculo espera de llegada de paquetes
    i=0;
    while(!feof(arch)&&res!=MEMORIA_INSUFICIENTE)
    {

        res=deColar_res(cola,&dato);// saco el paquete de la cola
        act=dato; //proceso el paquete
        cad=act.palabra;
        while(*cad) //representa un ciclo
            {
                if(i==espera)
                {
                    fread(&dato,sizeof(t_dato),1,arch);
                    res=aColar(cola,&dato);// ingresa el paquete a la cola
                    verTope_res(cola,&dato);
                    if(cola->cant>tammax)
                        tammax=cola->cant;
                    espera=ciclos_espera_paquete();//calculo espera de llegada de paquetes
                    i=0;
                }
                cad++;
                if(espera!=i)
                    i++;
//        fread(&dato,sizeof(t_dato),1,arch);
//        res=aColar_res(cola,&dato);// ingresa el paquete a la cola
            }

        while(verTope_res(cola,&dato)==0&&i!=espera)
            i++;

        if(i==espera)
        {
            fread(&dato,sizeof(t_dato),1,arch);
            res=aColar(cola,&dato);// ingresa el paquete a la cola
            verTope_res(cola,&dato);
            if(cola->cant>tammax)
                    tammax=cola->cant;
            espera=ciclos_espera_paquete();//calculo espera de llegada de paquetes
            i=0;
        }

    }
    *tam_max=tammax;
    if(res==MEMORIA_INSUFICIENTE)
        return res;
    return EJECUCION_EXITOSA;
}
