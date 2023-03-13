#include "triangle.h"

int main ()
{
	//Pone angulo a 25.0 grados
	grado grad;
	grad.pone_valor(25.0);
	cout << "El seno del angulo es:" 		<< grad.calc_sen() << endl; //endl == \n
	cout << "El coseno del ángulo es:" 		<< grad.calc_cos() << endl;
	cout << "La tangente del ángulo es:" 	<< grad.calc_tang() << endl;
	cout << "La secante del ángulo es:" 	<<  grad.calc_sec() << endl;
	cout << "La cosecante del ángulo es:" 	<<  grad.calc_cosec()  << endl;
	cout << "La cotangente del ángulo es:"	<<  grad.calc_cotang() << endl;

	return 0;
}

void grado::pone_valor(double ang)
{
	valor_dato = ang;
}

double grado::calc_sen(void)
{
	double respuesta;
	respuesta = sin(grad_a_rad * valor_dato);
	return respuesta;
}

double grado::calc_cos(void)
{
	double respuesta;
	respuesta = cos(grad_a_rad * valor_dato);
	return respuesta;
}

double grado::calc_tang(void)
{
	double respuesta;
	respuesta = tan(grad_a_rad * valor_dato);
	return respuesta;
}

double grado::calc_sec(void)
{
	double respuesta;
	respuesta = 1.0/sin(grad_a_rad * valor_dato);
	return respuesta;
}

double grado::calc_cosec(void)
{
	double respuesta;
	respuesta = 1.0/cos(grad_a_rad * valor_dato);
	return respuesta;
}

double grado::calc_cotang(void)
{
	double respuesta;
	respuesta = 1.0/tan(grad_a_rad * valor_dato);
	return respuesta;
}
