#ifndef COMPLEJO_H
#define COMPLEJO_H
#include<iostream>
using namespace std;

class Complejo
{
private:
    int r;
    int i;


public:
    Complejo();
    Complejo(int r,int i);
    Complejo operator+(Complejo& derecha);
    friend Complejo operator*(int escalar, const Complejo& derecha);
    Complejo operator*(Complejo & derecha);

    friend ostream & operator<<(ostream &out, const Complejo& c);
    friend istream & operator>>(istream&in, Complejo& c);
};



#endif // COMPLEJO_H
