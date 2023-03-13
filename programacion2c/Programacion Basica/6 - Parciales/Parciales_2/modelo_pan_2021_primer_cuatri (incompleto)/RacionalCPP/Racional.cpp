#include "Racional.h"

using namespace std;

static int mcd(int num, int den);
Racional::Racional()
{
    this->numerador = 0;
    this->denominador = 1;
}

Racional::Racional(int num, int den)
{
    this->numerador=num;
    this->denominador=den;
    if(this->denominador==0)
        throw runtime_error("El denominador no puede ser 0");
    simplificar();
}

Racional Racional::operator+(const Racional& otra)
{
    Racional resultado(this->numerador*otra.denominador+otra.numerador*this->denominador,
                       this->denominador*otra.denominador);
    return resultado;
}

Racional operator+(int numero, Racional& frac)
{
    Racional r1(numero,1);
    Racional res;
///Otra opción ///
//    frac.numerador=(numero+frac.numerador);
//    frac.denominador=frac.denominador;
    res=r1+frac;
    return res;
}

/** NO NECESARIA **/

Racional& Racional::operator=(const Racional& otra)
{
    if(this==&otra)
        return *this;
    this->numerador=otra.numerador;
    this->denominador=otra.denominador;
    return *this;
}

float Racional::real()
{
    return (float)numerador/denominador;
}

void Racional::simplificar()
{
    int mcdRes = mcd(this->numerador,this->denominador);
    this->denominador/=mcdRes;
    this->numerador/=mcdRes;
}

static int mcd(int num, int den)
{
    if(den==0)
        return num;
    return mcd(den,num%den);
}

ostream& operator <<(ostream& os, const Racional rac)
{
    os<<rac.numerador<<'/'<<rac.denominador;
    return os;
}
