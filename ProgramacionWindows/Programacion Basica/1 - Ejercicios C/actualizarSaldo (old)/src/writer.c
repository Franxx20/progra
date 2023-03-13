#include "../headers/empleados.h"
#include "../headers/estudiantes.h"

void comandos();
void igualarDNI(char *f_emp, char *f_est);
empleado *buscarPorDNI(char *filename, unsigned dni);

int main(int argc, char *argv[])
{
	srand(time(0));
	
	if(argc < 3 || argc > 4)
	{
		comandos();
		exit(1);
	}


	if(strcmp(argv[1], "-g") == 0)
	{
		escribirArchivo_emp(argv[2]);
		escribirArchivo_est(argv[3]);
		igualarDNI(argv[2], argv[3]);
	}
	else if(strcmp(argv[1], "-memp") == 0)
	{
		verArchivo_emp(argv[2]);
	}
	else if(strcmp(argv[1], "-mest") == 0)
	{
		verArchivo_est(argv[2]);
	}
	else if(strcmp(argv[1], "-f") == 0)
	{
		empleado *emp = buscarPorDNI(argv[2], (unsigned)atoi(argv[3]));
		if(emp) mostrar_emp(emp, 0);
	}
	else
	{
		comandos();
	}

	return 0;
}


void comandos()
{
	puts("./writer <option> [file(s)]");
	puts("-g : Genera los archivos empleado y estudiante");
	puts("-memp : Muestra empleados");
	puts("-mest : Muestra estudiantes");
}


int buscarPersona_sinDNI(const empleado *emp, const estudiante *est)
{
	int cmp = strcmp(emp->apellido, est->apellido);

	if(cmp == 0)
	{
		cmp = strcmp(emp->nombre, est->nombre);
	}
	
	return cmp;	
}


void igualarDNI(char *f_emp, char *f_est)
{
	FILE *pf_emp = fopen(f_emp, "r+b"),
		 *pf_est = fopen(f_est, "r+b");
	int cmp, i = 0;
	empleado emp;
	estudiante est;
	
	if(!pf_emp || !pf_est)
	{
		puts("[Error] Abriendo archivos para actualizar");
		exit(1);
	}


	fread(&emp, sizeof(empleado), 1, pf_emp);
	fread(&est, sizeof(estudiante), 1, pf_est);

	while(!feof(pf_emp) && !feof(pf_est))
	{
		cmp = buscarPersona_sinDNI(&emp, &est);

		if (cmp == 0)
		{
			est.dni = emp.dni;

			mostrar_est(&est, ++i);

			fseek(pf_est, -(sizeof (estudiante)), SEEK_CUR);
			fwrite(&est, sizeof(estudiante), 1, pf_est);
			fseek(pf_est, 0, SEEK_CUR);

			fread(&emp, sizeof(empleado), 1, pf_emp);
		}
		else if (cmp > 0)
			fread(&est, sizeof(estudiante), 1, pf_est);
		else
			fread(&emp, sizeof(empleado), 1, pf_emp);
	}

	fclose(pf_emp);
	fclose(pf_est);
}


empleado *buscarPorDNI(char *filename, unsigned dni)
{
	empleado *aux = malloc(sizeof(empleado));
	FILE *pf = fopen(filename, "rb");
	if(!pf)
	{
		printf("[Error] No se pudo abrir archivo %s\n", filename);
		exit(3);
	}

	fread(aux, sizeof(empleado), 1, pf);
	while (!feof(pf))
	{
		if (aux->dni == dni)
		{
			fclose(pf);
			return aux;
		}
		fread(aux, sizeof(empleado), 1, pf);
	}
	
	fclose(pf);
	return NULL;
}