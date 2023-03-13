#include "Cuadrado.h"

Cuadrado::Cuadrado()
{
    //ctor
}

Cuadrado::Cuadrado(const char * nombre, int lado):FiguraGeometrica(nombre),lado(lado)
{

}

Cuadrado::~Cuadrado()
{
    //dtor
}


double Cuadrado::area()const
{
    return this->lado * this->lado;
}

double Cuadrado::perimetro()const
{

    return 4 * this->lado;
}
