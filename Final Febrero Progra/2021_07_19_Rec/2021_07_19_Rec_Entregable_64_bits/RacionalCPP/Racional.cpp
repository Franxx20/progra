#include "Racional.h"

Racional::Racional()
{
    this->numerador = 0;
    this->denominador = 1;
}

Racional::Racional(int num, int den)
{
    simplificar(num,den);

    this->numerador = num;
    this->denominador = den;
}

float Racional::real() const
{
    return ((float)this->numerador/this->denominador);
}

void simplificar(int& num, int& den)
{
    while(num%2 == 0 && den%2 == 0)
    {
        num /= 2;
        den /= 2;
    }
}

Racional& Racional::operator=(const Racional& rac)
{
    this->denominador = rac.denominador;
    this->numerador = rac.numerador;

    return *this;
}

Racional Racional::operator+(const Racional& rac2) const
{
    int num = (this->numerador* rac2.denominador) + (rac2.numerador*this->denominador);
    int den = (this->denominador *rac2.denominador);
    simplificar(num,den);

    Racional racRes;

    racRes.denominador = den;
    racRes.numerador = num;

    return racRes;
}

Racional operator+(const int num, const Racional& rac)
{
    int nume = (num*rac.denominador) + (rac.numerador*1);
    int den = (1*rac.denominador);

    Racional racRes;

    racRes.denominador = den;
    racRes.numerador = nume;

    return racRes;
}

ostream& operator<<(ostream& os, const Racional& rac)
{
    os << rac.numerador << "/" << rac.denominador;
    return os;
}
