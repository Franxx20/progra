#ifndef LLAMADA_H
#define LLAMADA_H

#include<iostream>

using namespace std;

class Llamada
{
private:
    char * numeroOrigen;
    char * numeroDestino;
    int duracion;



public:
    Llamada();
    virtual ~Llamada();
    Llamada(const Llamada& other);
    Llamada(const char* numeroOrigen, const char * numerodestino, int duracion);
    Llamada operator+(const Llamada &otro)const;
    Llamada& operator=(const Llamada& other);
//
//        char * GetnumeroOrigen() { return numeroOrigen; }
//        void SetnumeroOrigen(char * val) { numeroOrigen = val; }
//        char * GetnumeroDestino() { return numeroDestino; }
//        void SetnumeroDestino(char * val) { numeroDestino = val; }
//        int Getduracion() { return duracion; }
//        void Setduracion(int val) { duracion = val; }

    friend ostream & operator<<(ostream & out, const Llamada & otro);
    friend Llamada operator+(int duracion, const Llamada&otro);
};

#endif // LLAMADA_H
