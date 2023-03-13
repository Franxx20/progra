#include "Circulo.h"
#include <cmath>

Circulo::Circulo(): radio(0.0)
{

}

Circulo::Circulo(const float& r): radio(r)
{
}

Circulo::Circulo(const Circulo& circ): radio(circ.getRadio())
{
}

void Circulo::setRadio(const float& r)
{
	this->radio = r;
}

float Circulo::getRadio()const
{
	return this->radio;
}

float Circulo::perimetro()
{
	return (2.0 * 3.145 * this->getRadio());
}

float Circulo::area()
{
	return (3.145 * pow(this->getRadio(), 2.0) );
}

char *Circulo::mostrar()
{
	char *aux = "A la grande le puse cuca";
	return aux;
}

Circulo operator --(Circulo& circ)
{
	Circulo aux;
	aux.radio = circ.getRadio() - 1;
	return aux;
}

std::ostream& operator <<(std::ostream& out, const Circulo& circ)
{
	return out << "Radio[" << circ.getRadio() << "]";
}

std::istream& operator >>(std::istream& in, Circulo& circ)
{
	return in >> circ.radio;;
}
