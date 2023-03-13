#ifndef CIRCULO_H
#define CIRCULO_H

#include <iostream>

class Circulo
{
	private:
		float radio;

	public:
		Circulo();
		Circulo(const float& r);
		Circulo(const Circulo& circ);

		void setRadio(const float& r);
		float getRadio()const;

		float perimetro();
		float area();
		char *mostrar();

		friend Circulo operator --(Circulo& circ);
		friend std::ostream& operator <<(std::ostream& out, const Circulo& circ);
		friend std::istream& operator >>(std::istream& in, Circulo& circ);

};

#endif // CIRCULO_H
