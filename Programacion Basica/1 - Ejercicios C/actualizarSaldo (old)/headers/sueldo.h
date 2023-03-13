#include "base.h"
#include "estudiantes.h"
#include "empleados.h"

#define DEBUG 1
enum flags{POR_APELLIDO, POR_NOMBRE};


int abrirArchivo(FILE **fp, char *filename, char *modo)
{
	*fp = fopen(filename, modo);
	return (*fp)? 1: 0;
}


void actualizarSueldo(FILE **fp, empleado *emp)
{
	emp->sueldo += (7.28 / 100) * emp->sueldo;
	/*Retrocedemos el puntero hacia donde comienza
	el empleado para entrar en modo de escritura.*/
	fseek(*fp, -(sizeof (empleado)), SEEK_CUR);
	fwrite(emp, sizeof(empleado), 1, *fp);
	/*Volvemos al modo de lectura.*/
	fseek(*fp, 0, SEEK_CUR);
}


/*Dado dos archivos binarios y su correspondiente estructura
buscamos una palabra en comun indicada por flag.*/
/*Realmente no estoy conforme con esta implementacion,
asi que cualquier sugernecia seria realmente apreciada.*/
/*int buscarPersona_bak(FILE **file_1, empleado *emp,
				  FILE **file_2, estudiante *est, int flag)
{
	int cmp;
	enum flags word = flag;

	while(!feof(*file_1) && !feof(*file_2))
	{
		switch (word)
		{
		case POR_NOMBRE:
			cmp = strcmp(emp->nombre, est->nombre);
			break;

		case POR_APELLIDO:
		default:
			cmp = strcmp(emp->apellido, est->apellido);
			break;
		}

		if (cmp > 0)
			fread(est, sizeof(estudiante), 1, *file_2);
		else if (cmp < 0)
			fread(emp, sizeof(empleado), 1, *file_1);
		else return 1;
	}
	return 0;
}*/


int buscarPersona(const empleado *emp, const estudiante *est)
{
	int cmp = strcmp(emp->apellido, est->apellido);

	if(cmp == 0)
	{
		cmp = strcmp(emp->nombre, est->nombre);
		if(cmp == 0)
			return !(emp->dni == est->dni);
	}
	
	return cmp;	
}