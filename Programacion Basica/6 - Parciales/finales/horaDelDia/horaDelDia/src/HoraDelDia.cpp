#include<iomanip>
#include "HoraDelDia.h"

HoraDelDia::HoraDelDia(int _h, int _m, int _s):
	hora(_h), minutos(_m), segundos(_s)
{
	//ctor
}

void HoraDelDia::verificarHora(HoraDelDia& hora)
{
	while(hora.segundos > 59) {
		hora.segundos = hora.segundos - 60;
		hora.minutos++;
	}

	while(hora.minutos > 59) {
		hora.minutos = hora.minutos - 60;
		hora.hora++;
	}

	while(hora.hora > 23) {
		hora.hora = hora.hora - 24;
	}
}

bool HoraDelDia::operator >=(const HoraDelDia& h2)
{
	if(hora > h2.hora) {
		return true;
	}
	else if(hora == h2.hora && minutos > h2.minutos) {
		return true;
	}
	else if(minutos == h2.minutos && segundos >= h2.segundos) {
		return true;
	}

	return false;
}

bool HoraDelDia::operator <(const HoraDelDia& h2)
{
	return !(*this >= h2);
}

HoraDelDia HoraDelDia::operator ++(int)
{
	HoraDelDia temp(*this);
	this->segundos++;
	verificarHora(*this);
	return temp;
}

HoraDelDia HoraDelDia::operator +(const HoraDelDia& h2)
{
	HoraDelDia aux(
		hora + h2.hora,
		minutos + h2.minutos,
		segundos + h2.segundos
	);

	verificarHora(aux);

	return aux;
}

HoraDelDia operator +(const int seconds, HoraDelDia& hora)
{
	HoraDelDia aux(
		hora.hora,
		hora.minutos,
		hora.segundos + seconds
	);

	aux.verificarHora(aux);

	return aux;
}

void HoraDelDia::operator +=(const int seconds)
{
	segundos += seconds;
	verificarHora(*this);
}

HoraDelDia HoraDelDia::getHoraMaxima()
{
	HoraDelDia aux(23, 59, 59);
	return aux;
}

std::ostream& operator <<(std::ostream& out, const HoraDelDia& hora)
{
	out << std::setfill('0') << std::setw(2) << hora.hora << ":"
		 << std::setfill('0') << std::setw(2) << hora.minutos << ":"
		 << std::setfill('0') << std::setw(2) << hora.segundos;

	return out;
}

std::istream& operator >>(std::istream& in, HoraDelDia& hora)
{
	in >> hora.hora >> hora.minutos >> hora.segundos;
	return in;
}
