#ifndef HORA_H
#define HORA_H

#include <iostream>

class Hora
{
	private:
		int 	horas = 0,
				minutos = 0,
				segundos = 0;
		void verificarHora(Hora& hora);

	public:
		Hora();
		Hora(int segundosTotales);

		Hora& operator ++();
		Hora operator ++(int);
		Hora operator +(const Hora& h1);

		friend std::ostream& operator <<(std::ostream& out, const Hora& hora);
};

#endif // HORA_H
