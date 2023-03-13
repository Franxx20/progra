#ifndef MEDICION_H
#define MEDICION_H
#include<iostream>
#include<string.h>

using namespace std;

class Medicion
{
    private:
        char * unidad;
        float medida;


    public:
        Medicion();
        Medicion(float medida, const char * unidad);

        Medicion operator-(const Medicion & otro)const;

        virtual ~Medicion();
//        Medicion(const Medicion& other);
        Medicion& operator=(const Medicion& other);


        friend ostream & operator <<(ostream & out, const Medicion & otro);
        friend Medicion operator+(float medida, const Medicion & otro);

};

#endif // MEDICION_H
