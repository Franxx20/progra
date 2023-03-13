/* --------------------------------o---x---o--------------------------------
 *		    			cola.c     COLA DINÁMICA CIRCULAR3    
 *--------------------------------o---x---o-------------------------------- */
 
#include "cola.h"

void crearCola(tCola *p)
{
    *p = NULL;
}

int colaLlena(const tCola *p, unsigned cantBytes)
{
    tNodo   *aux = (tNodo *)malloc(sizeof(tNodo));
    void    *info = malloc(cantBytes);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnCola(tCola *p, const void *d, unsigned cantBytes)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));

    if(nue == NULL || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, cantBytes);
    nue->tamInfo = cantBytes;
	if(*p == NULL)
		nue->sig = nue;
	else
	{
		nue->sig = (*p)->sig;
		(*p)->sig = nue;
	}
	*p = nue;
    return 1;
}

int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes)
{
	if(*p == NULL)
		return 0;
	memcpy(d, (*p)->sig->info, minimo(cantBytes, (*p)->sig->tamInfo));
	return 1;
}

void vaciarCola(tCola *p)
{
    while(*p)
    {
        tNodo *aux = (*p)->sig;
		
		if(*p == aux)
			*p = NULL;
		else
			(*p)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int colaVacia(const tCola *p)
{
    return *p == NULL;
}

int sacarDeCola(tCola *p, void *d, unsigned cantBytes)
{
    tNodo *aux;

    if(*p == NULL)
        return 0;

    aux = (*p)->sig;
    memcpy(d, aux->info, minimo(aux->tamInfo, cantBytes));
	if(aux == *p)
		*p = NULL;
	else
		(*p)->sig = aux->sig;
	
    free(aux->info);
    free(aux);
    return 1;
}

/* --------------------------------o---x---o-------------------------------- */