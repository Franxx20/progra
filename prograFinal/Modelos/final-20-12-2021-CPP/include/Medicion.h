#ifndef MEDICION_H
#define MEDICION_H
#include<iostream>
using namespace std;
class Medicion
{
private:
    float cant;
    char  * unidad;


public:
    Medicion();
    Medicion(float cant, const char * unidad);
    Medicion(const Medicion& otro);
    ~Medicion();


    Medicion operator-(const Medicion& otro)const;
    Medicion& operator=(const Medicion & otro);

    friend Medicion operator+(int cant, const Medicion &otro);
    friend ostream& operator<<(ostream &os, const  Medicion &otro);
};

#endif // MEDICION_H
