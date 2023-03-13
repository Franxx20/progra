#ifndef HORADELDIA_H_INCLUDED
#define HORADELDIA_H_INCLUDED

#include <iostream>
using namespace std;

class HoraDelDia
{
private:
    unsigned int _Hora;
    unsigned int _Min;
    unsigned int _Seg;
public:
    HoraDelDia();
    HoraDelDia( unsigned int hora, unsigned int minuto, unsigned int seg);
    int operator >=(const HoraDelDia &obj)const;
    int operator <(const HoraDelDia &obj)const;
    HoraDelDia& operator ++(const int a);
    HoraDelDia operator+(const HoraDelDia &obj)const;
    HoraDelDia& operator=(const HoraDelDia &obj);
    HoraDelDia& operator+=(const unsigned int v1);
    friend HoraDelDia operator+(const unsigned int v1,const HoraDelDia &obj);
    friend ostream& operator<<(ostream& sal,const HoraDelDia &obj);
    friend istream& operator>>(istream& sal,HoraDelDia & obj);


};

#endif // HORADELDIA_H_INCLUDED
