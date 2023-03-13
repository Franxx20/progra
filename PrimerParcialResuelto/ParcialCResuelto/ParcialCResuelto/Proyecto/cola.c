#include "../Comunes/Tipos.h"
#include "../Comunes/Cola.h"
void crearCola(t_cola* cola)
{
    cola->iin=0;
    cola->ifi=0;
    cola->cant=0;
}
int aColar(t_cola* cola, const t_dato* dato)
{
    if(cola->cant==MAX_TAM_COLA-1)
        return MEMORIA_INSUFICIENTE;
    if((cola->iin==cola->ifi)==0)
    {
        cola->icola[cola->ifi]=*dato;
        cola->cant++;
        cola->iin=0;
        cola->ifi=1;
        return EJECUCION_EXITOSA;
    }
    cola->icola[cola->ifi]=*dato;
    cola->cant++;
    cola->ifi++;
    return EJECUCION_EXITOSA;
}

void vaciarCola1(t_cola* cola)
{
    cola->iin=0;
    cola->ifi=0;
    cola->cant=0;
}


