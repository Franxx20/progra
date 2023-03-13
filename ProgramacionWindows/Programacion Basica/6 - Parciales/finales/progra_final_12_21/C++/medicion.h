#include <iostream>

class Medicion
{
	private:
		double valor;
		char *unidad;
	public:
		Medicion(const double p_valor, const char *p_unidad);
		Medicion(const Medicion& p_medicion);
		~Medicion();

		Medicion operator-(const Medicion& p_medicion);
		friend double operator+(const double p_valor, const Medicion& p_medicion);
		friend std::ostream& operator<<(std::ostream& out, const Medicion& p_medicion);
};