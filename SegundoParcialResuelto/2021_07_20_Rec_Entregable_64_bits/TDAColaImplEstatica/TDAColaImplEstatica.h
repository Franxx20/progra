#ifndef TDACOLAIMPLESTATICA_H
#define TDACOLAIMPLESTATICA_H

#define TAM_COLA 5000


typedef struct
{
	char vCola[TAM_COLA];
	unsigned frente;
	unsigned fondo;
	unsigned tamDisponible;
}
Cola;


#endif // TDACOLAIMPLESTATICA_H
