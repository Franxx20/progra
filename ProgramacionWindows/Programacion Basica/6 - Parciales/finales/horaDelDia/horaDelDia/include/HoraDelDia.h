#ifndef HORADELDIA_H
#define HORADELDIA_H

#include <iostream>

class HoraDelDia
{
	private:
		int hora, minutos, segundos;
		void verificarHora(HoraDelDia& hora);

	public:
		HoraDelDia(int _h = 0, int _m = 0, int _s = 0);

		bool operator >=(const HoraDelDia& h2);
		bool operator <(const HoraDelDia& h2);
		HoraDelDia operator ++(int);
		HoraDelDia operator +(const HoraDelDia& h2);
		friend HoraDelDia operator +(const int seconds, HoraDelDia& hora);
		void operator +=(const int seconds);

		HoraDelDia getHoraMaxima();

		friend std::ostream& operator <<(std::ostream& out, const HoraDelDia& hora);
		friend std::istream& operator >>(std::istream& in, HoraDelDia& hora);
};

#endif // HORADELDIA_H
