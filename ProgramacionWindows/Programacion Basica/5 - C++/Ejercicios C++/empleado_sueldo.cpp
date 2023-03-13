#include "triangle.h"

int main ()
{
	empleado emp_corte_ingles;

	emp_corte_ingles.entrada_emp();
	emp_corte_ingles.salida_emp();

	return 0;
}

void empleado::entrada_emp(void)
{
	cout << "Nombre del empleado: ";
	cin  >> nom.nombre;

	cout << "Primer apellido del empleado: ";
	cin  >> nom.primer_apel;

	cout << "Segundo apellido del empleado: ";
	cin  >> nom.segundo_apel;

	cout << "Total de horas trabajadas: ";
	cin  >> hor.horas;

	cout << "Sueldo base por hora: ";
	cin  >> hor.salario_base;

	cout << "Pago por horas extra: ";
	cin  >> hor.salario_extra;

	cout << "\n\n";
}

void empleado::salida_emp(void)
{
	cout << nom.nombre << " "
		 << nom.primer_apel << " "
		 << nom.segundo_apel << endl;

	if(hor.horas <= 40)
		cout << "Pago basico: $"
			 << hor.horas * hor.salario_base
			 << endl;
	else
	{
		cout << "Pago basico: $"
			 << 40 * hor.salario_base
			 << endl;

		cout << "Pago extra: $"
			 << (hor.horas - 40) * hor.salario_extra
			 << endl;
	}
}
