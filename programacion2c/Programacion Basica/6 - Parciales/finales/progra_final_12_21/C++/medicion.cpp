#include <stdexcept>
#include <string.h>
#include "medicion.h"

Medicion::Medicion(const double p_valor, const char *p_unidad):valor(p_valor) {
	size_t p_size = strlen(p_unidad);
	unidad = new char[p_size+1];
	memcpy(unidad, p_unidad, p_size);
	unidad[p_size] = '\0';
}


Medicion::Medicion(const Medicion& p_medicion) :
	valor(p_medicion.valor), unidad(p_medicion.unidad) {}


Medicion::~Medicion() {
	delete []unidad;
}

Medicion Medicion::operator-(const Medicion& p_medicion) {
	if(strcmp(unidad, p_medicion.unidad) != 0) {
		throw std::invalid_argument("[ERROR] - Unidades distintas.");
	}
	return Medicion(valor - p_medicion.valor, unidad);
}


double operator+(const double p_valor, const Medicion& p_medicion) {
	return p_valor + p_medicion.valor;
}


std::ostream& operator<<(std::ostream& out, const Medicion& p_medicion) {
	out << "Unidad: " << p_medicion.unidad << " | Valor: " << p_medicion.valor;
	return out;
}