/*****************************************************************************************************************
** Apellido/s, Nombre/s: Gonzalez, Agustin Elias                                   													**
** DNI: 42629319                                                     													**
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
        Complejo(int real, int imaginario);

        Complejo operator+(const Complejo& comp);
        Complejo operator*(const Complejo& comp);

        friend Complejo operator*(int escalar, const Complejo& comp);

        friend ostream& operator<<(ostream& os, const Complejo& comp);
};

int main()
{
    Complejo c1(1, 2);
    Complejo c2(2, 1);

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
    this->real = 0;
    this->imaginario = 0;
}

Complejo::Complejo(int real, int imaginario)
{
    this->real = real;
    this->imaginario = imaginario;
}

Complejo Complejo::operator+(const Complejo& comp)
{
    Complejo res;
    res.real = this->real + comp.real;
    res.imaginario = this->imaginario + comp.imaginario;
    return res;
}

Complejo Complejo::operator*(const Complejo& comp)
{
    Complejo res;
    res.real = this->real * comp.real - this->imaginario * comp.imaginario;
    res.imaginario = this->real * comp.imaginario + this->imaginario * comp.real;
    return res;
}

Complejo operator*(int escalar, const Complejo& comp)
{
    Complejo res;
    res.real = escalar * comp.real;
    res.imaginario = escalar * comp.imaginario;
    return res;
}

ostream& operator<<(ostream& os, const Complejo& comp)
{
    os << '(' << comp.real << ',' << comp.imaginario << ')';
    return os;
}
