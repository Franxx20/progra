#include "fechas.h"
#define esBisiesto(a) ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)

int cant_dias_mes(int m, int a);
int contar_dias(tFecha *f, tFecha *f1);

void ingresar_fecha(tFecha *f)
{
    printf("Ingrese fecha (d/m/a): ");
    fflush(stdin);
    scanf("%d/%d/%d", &f->dia, &f->mes, &f->anio);
}

//	Ej. 14
int cant_dias_mes(int m, int a)
{
	static int diasMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if (m == 2 && esBisiesto(a))
		return 29;

    return diasMes[m];
}


int validar_fecha(tFecha *f)
{
	if (f->anio < 1600)
		return 0;

	if (f->mes < 1 || f->mes > 12)
		return 0;

	if (f->dia < 1 || f->dia > cant_dias_mes(f->mes, f->anio))
		return 0;

    return 1;
}

//	Ej. 15
void dia_siguiente(tFecha *f)
{
	f->dia++;

	if (f->dia > cant_dias_mes(f->mes, f-> anio))
	{
		f->mes++;
		f->dia = 1;
	}

	if (f->mes > 12)
	{
		f->anio++;
		f->mes = 1;
	}
}

//	Ej. 16
void sum_N_dias(tFecha *f, short int N)
{
	int aux;

	for (aux = 0; aux < N; aux++)
		dia_siguiente(f);
}

//	Ej. 17
void res_N_dias(tFecha *f, short int N)
{
	int aux;

	for (aux = N; aux > 0; aux--)
	{
		f->dia--;

		if (f->dia < 1)
		{
			f->mes--;
			f->dia = cant_dias_mes(f->mes, f->anio);
		}

		if (f->mes < 1)
		{
			f->anio--;
			f->mes = 12;
			f->dia = cant_dias_mes(f->mes, f->anio);
		}
	}
}

//	Ej. 18
int diferencia(tFecha *f, tFecha *f1)
{
	int cant_dias = 0;

	if (f->anio == f1->anio && f->mes == f1->mes && f->dia == f1->dia)
		cant_dias = 0;
	else if (f->anio >= f1->anio && f->mes >= f1->mes && f->dia >= f1->dia)//	F es mayor a F1
	{
		cant_dias = contar_dias(f1, f);
	}
	else
	{
		cant_dias = contar_dias(f, f1);
	}

	return cant_dias;
}

int contar_dias(tFecha *f, tFecha *f1)
{
	int cont = 0;
	tFecha fAux = *f;
	do
	{
		cont++;
		dia_siguiente(&fAux);
	} while (!(fAux.anio == f1->anio && fAux.mes == f1->mes && fAux.dia == f1->dia));

	return cont;
}

//	Ej. 19
void dia_de_la_semana(tFecha *f)
{
	static tFecha fBase = {1, 1, 1601};

	int _diff = diferencia(&fBase, f);

	switch ((_diff % 7) + 1)
	{
		case 0: printf("Domingo\n");
			break;
		case 1: printf("Lunes\n");
			break;
		case 2: printf("Martes\n");
			break;
		case 3: printf("Miercoles\n");
			break;
		case 4: printf("Jueves\n");
			break;
		case 5: printf("Viernes\n");
			break;
		case 6: printf("Sabado\n");
			break;
	}
}
