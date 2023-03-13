#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include <iostream>
#include <math.h>

using namespace std;

const double grad_a_rad = 0.0174532925; //radianes, global variable

class grado
{
	private:
		double valor_dato;

	public:
		void pone_valor(double);
		double calc_sen(void);
		double calc_cos(void);
		double calc_tang(void);
		double calc_sec(void);
		double calc_cosec(void);
		double calc_cotang(void);
};

#endif // TRIANGLE_H_INCLUDED
