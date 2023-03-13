#include "Racional.h"

void Racional::simplificar(int &num, int &den)
{
    while(num%2 == 0 && den %2 ==0)
    {
        num/=2;
        den/=2;
    }
}

Racional::Racional()
{
    this->numerador = 0;
    this->denominador = 1;
}

Racional::Racional(int num, int den)
{
    simplificar(num, den);
    this->numerador = num;
    this->denominador = den;
}

Racional& Racional::operator=(const Racional & r)
{
    this->numerador = r.numerador;
    this->denominador = r.denominador;

    return (*this);
}

Racional Racional::operator+(const Racional & otro) const
{
    Racional nue;
    nue.numerador = this->numerador*otro.denominador + this->denominador * otro.numerador;
    nue.denominador = this->denominador * otro.denominador;
    simplificar(nue.numerador, nue.denominador);

    return nue;
}

Racional operator+(int numero, const Racional & otro){
Racional nue;
nue.numerador = numero * otro.denominador + otro.numerador;
nue.denominador = otro.denominador;

return nue;

}

 float Racional::real(){
    return (float )this->numerador / this->denominador;
 }


ostream& operator<<(ostream & os, Racional & r)
{
    os << r.numerador << "/" << r.denominador;
    return os;
}


