#ifndef FECHA_H
#define FECHA_H


typedef struct
{
	int d;
	int m;
	int a;
}
t_fecha;


int es_fecha_valida(const t_fecha* fecha);
int cant_dias_mes(int mes, int anio);
int es_bisiesto(int anio);
void sumar_dias_a_fecha(const t_fecha* fecha, int dias, t_fecha* fecha_suma);
void txt_a_fecha(const char* txt, t_fecha* fecha);
int cmpFechas(const t_fecha* f1, const t_fecha* f2);
int es_fecha_valida_res(const t_fecha* fecha);
int cant_dias_mes_res(int mes, int anio);
int es_bisiesto_res(int anio);
void ingresarFecha(t_fecha* fecha);
void sumar_dias_a_fecha_res(const t_fecha* fecha, int dias, t_fecha* fecha_suma);
int txt_a_fecha_res(const char* txt, t_fecha* fecha);
int cmpFechas_res(const t_fecha* f1, const t_fecha* f2);


#endif // FECHA_H
