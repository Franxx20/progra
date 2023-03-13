#include "main.h"
#define printFecha	printf("Fecha: %d/%d/%d\n", f->dia, f->mes, f->anio);

void add_fecha(tFecha *f, tFecha *f1, int repetir);
void next_day(tFecha *f);
void plus_day(tFecha *f);
void rest_day(tFecha *f);
void diff(tFecha *f, tFecha *f1);

int main()
{
    tFecha fecha, fecha2;
    tFecha *fAux = &fecha;
    int max_fechas, opcion, opcion_fecha;

	printf("Cantidad de fechas a ingresar (2 max): ");
	scanf("%d", &max_fechas);

	if(max_fechas <= 0 || max_fechas > 2)
	{
		puts("Fuck you...");
		return 69;
	}
	add_fecha(&fecha, &fecha2, max_fechas);

	do
	{
		puts("-------------------------------");
		puts("Que hacer despues?");
		printf("0 - Siguente Dia\n1 - Sumarle dias\n2 - Restarle dias\n3 - Dia de la semana\n4 - Contar dias entre fechas\n5 - Exit\n> ");
		fflush(stdin);
		scanf("%d", &opcion);

		if (max_fechas == 2 && (opcion >= 0 && opcion < 4))
		{
			printf("Que fecha desea modificar?: ");
			fflush(stdin);
			scanf("%d", &opcion_fecha);

			(opcion_fecha == 2) ? (fAux = &fecha2) : (fAux = &fecha);
		}

		switch(opcion)
		{
			case 0: next_day(fAux);
				break;
			case 1: plus_day(fAux);
				break;
			case 2: rest_day(fAux);
				break;
			case 3: dia_de_la_semana(fAux);
				break;
			case 4: (max_fechas == 2) ? diff(&fecha, &fecha2) : puts("Funcion invalida con una sola fecha...");
				break;
			case 5: puts("Bye bye...");
				break;
			default: puts("Fuck you...");
				return 69;
		}
	} while(opcion != 5);

    return 0;
}

void add_fecha(tFecha *f, tFecha *f1, int repetir)
{
	do
	{
		printf("1° ");
		ingresar_fecha(f);
	} while(!validar_fecha(f));

	if (repetir == 2)
		do
		{
			printf("2° ");
			ingresar_fecha(f1);
		} while(!validar_fecha(f1));
}

void next_day(tFecha *f)
{
	dia_siguiente(f);
	printFecha;
}

void plus_day(tFecha *f)
{
	short int plus_dias = 0;

	puts("Dias a sumarle:\t");
	fflush(stdin);
	scanf("%hd", &plus_dias);
	sum_N_dias(f, plus_dias);
	printFecha;
}

void rest_day(tFecha *f)
{
	short int plus_dias = 0;

	puts("Dias a restarle:\t");
	fflush(stdin);
	scanf("%hd", &plus_dias);
	res_N_dias(f, plus_dias);
	printFecha;
}

void diff(tFecha *f, tFecha *f1)
{
	int diferencia_en_dias = 0;

	diferencia_en_dias = diferencia(f, f1);
	printf("Diferencia: %d\n", diferencia_en_dias);
}
