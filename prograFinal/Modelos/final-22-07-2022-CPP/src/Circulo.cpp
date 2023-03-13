#include "Circulo.h"

Circulo::Circulo():FiguraGeometrica(),radio(0)
{

}
Circulo::Circulo(const char *nombre, int radio):FiguraGeometrica(nombre),radio(radio)
{

}



Circulo::~Circulo()
{
    //dtor
}


double Circulo::area()const
{
    return 3.14 * (radio * radio);
}

double Circulo::perimetro()const
{

    return 2 * 3.14 * radio;
}
