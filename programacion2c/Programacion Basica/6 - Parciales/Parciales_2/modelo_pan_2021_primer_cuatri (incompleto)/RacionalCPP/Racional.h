#ifndef RACIONAL_H
#define RACIONAL_H

#include <iostream>
#include <stdexcept>

using namespace std;

class Racional
{
    public:
        Racional();
        Racional(int,int);
        Racional operator+(const Racional&);
        Racional& operator=(const Racional&); /// NO NECESARIA
        ///Racional operator=(int);
        void simplificar();
        float real();

        friend ostream& operator <<(ostream& os, const Racional);
        friend Racional operator+(int, Racional&);

    private:
        int denominador;
        int numerador;
};


#endif // RACIONAL_H
