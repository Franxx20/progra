#ifndef MEDICION_H
#define MEDICION_H

#include <iostream>
#include <cstring>

class Medicion
{
	private:
		float medida;
		char *unidad;

	public:
		Medicion(const float& medida, const char* unidad);

		void setMedida(float& val);
		void setUnidad(char *uni);
		float getMedida()const;
		char *getUnidad()const;

		friend Medicion operator +(Medicion& m1, Medicion& m2);
		friend float operator -(float med, Medicion& m2);
		friend std::ostream& operator <<(std::ostream& out, const Medicion& m1);
};

#endif // MEDICION_H
