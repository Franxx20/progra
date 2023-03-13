#include "Llamada.h"
#include<string.h>
#include<iostream>
Llamada::Llamada()
{
    //ctor
}

Llamada::~Llamada()
{
    //dtor
}

Llamada::Llamada(const Llamada& other)
{
    //copy ctor
}

Llamada::Llamada(const char* numeroOrigen, const char * numerodestino, int duracion)
{
    this->numeroOrigen = new char[strlen(numeroOrigen)+1];
    this->numeroDestino = new char[strlen(numerodestino)+1];
    strcpy(this->numeroDestino,numerodestino);
    strcpy(this->numeroOrigen,numeroOrigen);
    this->duracion = duracion;
}

Llamada Llamada::operator+(const Llamada &otro)const
{

    if(strcmp(this->numeroOrigen,otro.numeroOrigen)==0)
    {
        return Llamada  (this->numeroOrigen,"",this->duracion+otro.duracion);
    }
    else
    {

        throw "ERROR";
    }

}

Llamada& Llamada::operator=(const Llamada& otro)
{
    if (this == &otro) return *this; // handle self assignment
    //assignment operator

    delete[]this->numeroDestino;
    delete[]this->numeroOrigen;

    this->numeroOrigen = new char[strlen(otro.numeroOrigen)+1];
    this->numeroDestino = new char[strlen(otro.numeroDestino)+1];
    strcpy(this->numeroDestino,otro.numeroDestino);
    strcpy(this->numeroOrigen,otro.numeroOrigen);
    this->duracion = otro.duracion;


    return *this;
}
Llamada operator+(int duracion, const Llamada&otro)
{
    Llamada nuevo (otro.numeroOrigen,otro.numeroDestino,duracion+otro.duracion);

    return nuevo;
}

ostream & operator<<(ostream & out, const Llamada & otro)
{
    return out << '('<<otro.numeroOrigen<<','<<otro.numeroDestino<<','<<otro.duracion<<')';
}
