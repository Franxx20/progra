#ifndef HORADELDIA_H
#define HORADELDIA_H

#include <iostream>

using namespace std;

class HoraDelDia
{
    private:
        int horas;
        int minutos;
        int segundos;
    public:
        HoraDelDia();
        HoraDelDia(int h, int m, int s);

        static HoraDelDia getHoraMaxima();

        int operator>=(const HoraDelDia& dia1);
        int operator<(const HoraDelDia& dia1);

        HoraDelDia& operator=(const HoraDelDia& dia);
        HoraDelDia operator+(const HoraDelDia& dia);
        HoraDelDia& operator+=(const int segundos);
        HoraDelDia operator++(int a);

        friend HoraDelDia operator+(const int s, const HoraDelDia& dia);
        friend ostream& operator<<(ostream& os, const HoraDelDia& dia);
        friend istream& operator>>(istream& in, HoraDelDia& dia);
};

#endif // HORADELDIA_H
