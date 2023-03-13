#include "Medicion.h"
#include <string.h>

Medicion::Medicion()
{
    this->unidad = new char [1];
    this->unidad[0] = '\0';
    this->cant =0;
}

Medicion::Medicion(float cant, const char * unidad):cant(cant)
{
    int tamUnidad = strlen(unidad)+1;
    this->unidad = new char[tamUnidad];
    strncpy(this->unidad, unidad,tamUnidad);

    this->cant= cant;

}

    Medicion::Medicion(const Medicion& otro):Medicion(otro.cant,otro.unidad){

    }

Medicion::~Medicion()
{
    delete[] this->unidad;
}

Medicion Medicion::operator-(const Medicion& otro)const
{

    int  res = strcmp(this->unidad, otro.unidad);
    if(res==0)
    {
        Medicion nue(this->cant - otro.cant, otro.unidad);
        return nue;
    }
    else
        throw(res);

}

Medicion operator+(int cant, const Medicion &otro)
{
    Medicion nue(otro.cant + cant,otro.unidad);

    return nue;
}

Medicion& Medicion::operator=(const Medicion & otro)
{
    size_t tamUnidad= strlen(otro.unidad)+1;

    if(strlen(this->unidad)!= tamUnidad-1)
    {
        delete []this->unidad;
        this->unidad = new char [tamUnidad];
    }

    strncpy(this->unidad,otro.unidad,tamUnidad);
    this->cant  = otro.cant;


    return * this;



}


ostream& operator<<(ostream &os, const  Medicion &otro)
{
    os << "cantidad: "<<otro.cant << " unidad: "<< otro.unidad;
    return os;
}
