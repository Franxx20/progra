#include "../headers/sueldo.h"

int main(int argc, char *argv[])
{
	FILE *f_emp = NULL, 
		 *f_est = NULL;
	int i = 0, cmp;
	empleado emp;
	estudiante est;

	if(argc < 3)
	{
		puts("./sueldo <emplados> <estudiantes>");
		exit(1);
	}


	if( !abrirArchivo(&f_emp, argv[1], "r+b") || 
		!abrirArchivo(&f_est, argv[2], "rb") )
	{
		puts("Error abriendo archivo:");
		(f_emp)? puts(argv[2]) : puts(argv[1]);
		exit(2);
	}


	fread(&emp, sizeof(empleado), 1, f_emp);
	fread(&est, sizeof(estudiante), 1, f_est);

	while(!feof(f_emp) && !feof(f_est))
	{
		cmp = buscarPersona(&emp, &est);
		if (cmp == 0)
		{
			if (est.promedio > 7.0)
			{
				if(DEBUG) mostrar_emp(&emp, ++i);
				actualizarSueldo(&f_emp, &emp);
				if(DEBUG) mostrar_emp(&emp, i);
			}
			fread(&emp, sizeof(empleado), 1, f_emp);
			fread(&est, sizeof(estudiante), 1, f_est);
		}
		else if (cmp > 0)
			fread(&est, sizeof(estudiante), 1, f_est);
		else
			fread(&emp, sizeof(empleado), 1, f_emp);
	}

	fclose(f_emp);
	fclose(f_est);

	return 0;
}