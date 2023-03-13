#ifndef HORADELDIA_H
#define HORADELDIA_H

#define DIASEGUNDOS 86400
#define HORASEGUNDOS 3600
#define MINUTOSEGUNDOS 60

#include<iostream>
using namespace std;
class HoraDelDia
{

private:
    int _tiempoEnSegundos;

public:
    HoraDelDia();
    HoraDelDia(int hora,int minuto,int segundo);
    HoraDelDia(int horaEnSegundos);

    virtual ~HoraDelDia();
//        HoraDelDia(const HoraDelDia& other);

    bool operator>= (const HoraDelDia & otro)const;
    bool operator< (const HoraDelDia & otro)const;

    HoraDelDia& operator=(const HoraDelDia& other);
    HoraDelDia& operator+=(int segundos);
    HoraDelDia operator+(const HoraDelDia & otro)const;
    HoraDelDia operator++(int);

    void getHoraMinutoySegundo(int *h,int *m,int * s)const;
    static HoraDelDia getHoraMaxima();


    friend ostream & operator<<(ostream & out, const HoraDelDia&otro);
    friend istream & operator>>(istream & in,  HoraDelDia&otro);
    friend HoraDelDia operator+(int segundo, const HoraDelDia&otro);


};

#endif // HORADELDIA_H
