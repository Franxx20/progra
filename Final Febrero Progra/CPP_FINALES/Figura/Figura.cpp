#include "Figura.h"

Figura::Figura(unsigned int cantlados,unsigned int perimetro)
{
    _Cantlados=cantlados;
    _Perimetro=perimetro;
}
const unsigned int Figura::cantidadLados()const
{
    return _Cantlados;
}
const unsigned int Figura::perimetro()const
{
    return _Perimetro;
}
