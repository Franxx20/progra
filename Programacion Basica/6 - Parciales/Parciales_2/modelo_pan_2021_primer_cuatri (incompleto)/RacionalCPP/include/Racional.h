#ifndef RACIONAL_H
#define RACIONAL_H

#include <iostream>

using namespace std;

class Racional
{
    public:
        Racional();
        Racional(int,int);
        void setDenominador(int denominador);
        void setNumerador(int numerador);
        int getDenominador();
        int getNumerador();
        Racional operator+(const Racional&);
        Racional operator=(const Racional&);
        Racional operator=(int);
        void simplificar();

        friend ostream& operator <<(ostream& os, const Racional);
        ///friend operator+(int, const Racional);

    private:
        int denominador;
        int numerador;
};

#endif // RACIONAL_H
