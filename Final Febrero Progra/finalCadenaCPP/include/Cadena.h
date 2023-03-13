#ifndef CADENA_H
#define CADENA_H
#include<string.h>
#include<iostream>
using namespace std;

class Cadena
{
    private:
        char * _cadena;


    public:
        Cadena();
        virtual ~Cadena();
//        Cadena(const Cadena& other);
        Cadena(const char * cadena);
//        Cadena& operator+(const char *cadena);
        Cadena operator+(const char * cadena)const;
        Cadena& operator=(const Cadena& other);


        friend ostream & operator<<(ostream & out, Cadena & otro);

};

#endif // CADENA_H
