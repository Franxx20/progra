#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#include <iostream>

using namespace std;

class empleado
{
	private:
		struct nombre_emp
		{
			char nombre[20];
			char primer_apel[20];
			char segundo_apel[20];
		}nom;

		struct horas_emp
		{
			double horas;
			double salario_base;
			double salario_extra;
		}hor;

	public:
		empleado(){ cout << "Welcome extranger!\n"; } //CONSTRUCTOR
		~empleado(){ cout << "Goodbye extranger!" << endl; } //DESTRUCTOR
		void entrada_emp(void);
		void salida_emp(void);
};

#endif // EMPLEADO_H_INCLUDED
