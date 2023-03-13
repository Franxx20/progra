#ifndef RACIONAL_H
#define RACIONAL_H

#include <iostream>

using namespace std;

class Racional
{
    private:
        int numerador;
        int denominador;

    public:
        Racional();
        Racional(int num, int den);
        Racional& operator=(const Racional& rac);
        Racional operator+(const Racional& rac2) const;
        float real() const;

        friend Racional operator+(const int num, const Racional& rac);
        friend ostream& operator<<(ostream& os, const Racional& rac);
};
void simplificar(int& num, int& den);

#endif // RACIONAL_H
