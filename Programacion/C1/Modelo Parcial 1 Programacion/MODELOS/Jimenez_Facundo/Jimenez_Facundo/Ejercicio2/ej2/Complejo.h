#ifndef COMPLEJO_H_INCLUDED
#define COMPLEJO_H_INCLUDED

#include <iostream>
using namespace std;

class Complejo{
private:
    int _real,
        _imaginario;
public:
    Complejo();
    Complejo(const int real, const int imaginario);
    Complejo operator+(const Complejo& complejoSuma)const;
    Complejo operator*(const Complejo& complejoMult)const;
    friend ostream& operator<<(ostream& salida, const Complejo& objComplejo);
    friend Complejo operator*(const double escalar, const Complejo& objComplejo);
};

#endif // COMPLEJO_H_INCLUDED
