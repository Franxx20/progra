#include "Racional.h"

using namespace std;

Racional::Racional()
{
    ///puedo darle un valor original
    this->numerador = 0;
    if(this->denominador==0)
        throw bad_alloc();
    this->denominador = 1;
}

Racional::Racional(int numerador, int denominador)
{
    this->numerador=numerador;
    this->denominador=denominador;
    simplificar();
}

void Racional::setDenominador(int denominador)
{
    this->denominador=denominador;
}

void Racional::setNumerador(int numerador)
{
    this->numerador=numerador;
}

int Racional::getDenominador()
{
    return denominador;
}

int Racional::getNumerador()
{
    return numerador;
}

void Racional::simplificar()
{
    if(this->numerador>this->denominador)
        this->numerador/=this->denominador;

    if(this->numerador<this->denominador)
    {

        this->denominador = this->denominador/this->numerador;
        this->numerador/=this->denominador;
    }
}

Racional Racional::operator+(const Racional& otra)
{
//    this->denominador*=otra.denominador;
//    this->numerador*=otra.denominador;
//    otra.numerador*=this->denominador;
//    this->numerador+=otra.numerador;
//    return *this;
}

Racional Racional::operator=(const Racional& otra)
{
    this->numerador=otra.numerador;
    this->denominador=otra.denominador;
    return *this;
}

ostream& operator <<(ostream& os, const Racional num)
{
    os<<num.numerador<<'/'<<num.denominador;
    return os;
}
