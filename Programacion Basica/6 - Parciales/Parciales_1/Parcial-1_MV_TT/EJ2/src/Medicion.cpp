#include "Medicion.h"

Medicion::Medicion(	const float& med,
					const char*  uni ):
					medida(med),
					unidad((char *)uni)
{
	//ctor
}

/*unidad clase::funcion*/
void Medicion::setMedida(float& val)
{
	this->medida = val;
}

void Medicion::setUnidad(char* uni)
{
	this->unidad = uni;
}

float Medicion::getMedida()const
{
	return this->medida;
}

char* Medicion::getUnidad()const
{
	return this->unidad;
}

Medicion operator +(Medicion& m1, Medicion& m2)
{
	char* uni_m1 = m1.getUnidad();
	char* uni_m2 = m2.getUnidad();

	if(strcmp(uni_m1, uni_m2)) {
		/*Si no tiramos algo el programa termina*/
		throw 7;
	}

	return Medicion(m1.getMedida() + m2.getMedida(), uni_m1);
}

float operator -(float med, Medicion& m2)
{
	return (med - m2.getMedida());
}

std::ostream& operator <<(std::ostream& out, const Medicion& m1)
{
	return out << "{" << m1.getMedida() << m1.getUnidad() << "}";
}
