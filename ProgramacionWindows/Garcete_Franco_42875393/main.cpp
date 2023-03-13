/*****************************************************************************************************************
** Apellido/s, Nombre/s:                                      													**
** DNI:                                                       													**
******************************************************************************************************************
** Corrección																								   	**
** **********																								   	**
**                      																					   	**
******************************************************************************************************************
** Nota:																									   	**
*****************************************************************************************************************/

#include <iostream>

using namespace std;


class Complejo
{

private:
    int real;
    int imaginario;

public:
    Complejo();
    Complejo(int r, int i);
    Complejo& operator=(const Complejo&c);
    Complejo operator+(const Complejo& c);
    friend Complejo operator*(int escalar, const Complejo & c);
    Complejo operator*(const Complejo & otro);
    friend ostream& operator<<(ostream& os, Complejo & c);


};


int main()
{
    Complejo c1(1, 2);
    Complejo c2(2, 1);
//
    Complejo c3 = c1 + c2;

    cout << c3 << " = " << c1 << " + " << c2 << endl;

    Complejo c4 = 5 * c3;

    cout << c4 << " = " << 5 << " * " << c3 << endl;

    Complejo c5 = c3 * c4;

    cout << c5 << " = " << c3 << " * " << c4 << endl;


    return 0;
}


Complejo::Complejo()
{
    this->real  =0;
    this->imaginario = 0;
}

Complejo::Complejo(int r, int i)
{
    this->real = r;
    this->imaginario = i;
}

Complejo& Complejo::operator=(const Complejo&c)
{
    this->real = c.real;
    this->imaginario = c.imaginario;

    return (*this);
}

Complejo Complejo::operator+(const Complejo& c)
{
    Complejo nue;
    nue.real = this->real + c.real;
    nue.imaginario = this->imaginario+ c.imaginario;


    return nue;
}

Complejo operator*(int escalar, const Complejo & c)
{
    Complejo nue;
    nue.real = escalar * c.real;
    nue.imaginario = escalar * c.imaginario;

    return nue;
}

Complejo Complejo::operator*(const Complejo & otro)
{
//    Multiplicación
//(a, b) * (c, d) = (a*c – b*d, a*d + b*c)

    Complejo nue;
    nue.real = this->real * otro.real - this->imaginario * otro.imaginario;
    nue.imaginario = this->real * otro.imaginario + this->imaginario * otro.real;

    return nue;
}

ostream& operator<<(ostream& os, Complejo & c)
{
    os << "(" <<  c.real << ", "<< c.imaginario<<")";

    return os;
}


