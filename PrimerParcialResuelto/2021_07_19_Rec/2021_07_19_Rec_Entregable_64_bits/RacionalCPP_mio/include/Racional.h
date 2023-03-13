#ifndef RACIONAL_H
#define RACIONAL_H
#include<iostream>

using namespace std;

class Racional
{


    private:
        int numerador;
        int denominador;
        static void simplificar(int &num, int &den);

    public:
        Racional();
        Racional(int num, int den);

        Racional& operator=(const Racional & r);
        Racional operator+(const Racional & otro) const;
        float real();

        friend Racional operator+(int numero, const Racional & otro);
        friend ostream& operator<<(ostream & os, Racional & r);
};




#endif // RACIONAL_H
