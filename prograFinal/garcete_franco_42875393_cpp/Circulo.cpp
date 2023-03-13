#include "Circulo.h"

Circulo::Circulo():FiguraGeometrica(),radio(0)
{
    //ctor
}

Circulo::Circulo(const char * nombre, double radio):FiguraGeometrica(nombre),radio(radio){
}
Circulo::~Circulo()
{
    //dtor
}
double Circulo::area()const
{
    return this->radio * this->radio * 3.14;
}
double Circulo::perimetro()const
{
    return 2 * 3.14 * this->radio;
}
