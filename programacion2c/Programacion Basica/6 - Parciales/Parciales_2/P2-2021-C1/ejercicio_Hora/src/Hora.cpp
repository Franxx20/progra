#include<iomanip>
#include "Hora.h"

Hora::Hora() : horas(0),
	minutos(0), segundos(0) {}


Hora::Hora(int segundosTotales)
{
	horas = segundosTotales / 3600;
	minutos = (segundosTotales / 60) % 60;
	segundos = segundosTotales % 60;

	verificarHora(*this);
}


void Hora::verificarHora(Hora& hora)
{
	while(hora.segundos > 59) {
		hora.segundos = hora.segundos - 60;
		hora.minutos++;
	}

	while(hora.minutos > 59) {
		hora.minutos = hora.minutos - 60;
		hora.horas++;
	}

	while(hora.horas > 23) {
		hora.horas = hora.horas - 24;
	}
}


Hora& Hora::operator ++()
{
	this->segundos++;
	verificarHora(*this);
	return *this;
}


Hora Hora::operator ++(int)
{
	Hora h(*this);
	this->segundos++;
	verificarHora(*this);
	return h;
}


Hora Hora::operator +(const Hora& h1)
{
	Hora aux;
	aux.horas = this->horas + h1.horas;
	aux.minutos = this->minutos + h1.minutos;
	aux.segundos = this->segundos + h1.segundos;
	verificarHora(aux);
	return aux;
}


std::ostream& operator <<(std::ostream& out, const Hora& hora)
{
	out << std::setfill('0') << std::setw(2) << hora.horas << ":"
		 << std::setfill('0') << std::setw(2) << hora.minutos << ":"
		 << std::setfill('0') << std::setw(2) << hora.segundos;

	return out;
}

