#include "Medicion.h"

Medicion::Medicion()
{
    this->unidad= new char [1];
    this->unidad[0] = '\0';
    this->medida =0;
}

Medicion::Medicion(float medida, const char * unidad)
{


    this->unidad = new char[strlen(unidad) +1];
    strcpy(this->unidad,unidad);

    this->medida = medida;
}

Medicion::~Medicion()
{
    //dtor
    cout << "borrando unidad"<<endl;
    delete []this->unidad;
}

//Medicion::Medicion(const Medicion& other)
//{
//    //copy ctor
//}

Medicion Medicion::operator-(const Medicion & otro)const
{
    if(strcmp(this->unidad, otro.unidad)==0)
    {
        Medicion nue(this->medida-otro.medida,this->unidad);
        return nue;
    }
    else
    {
        throw "unidades distintas \n";
    }

}

Medicion& Medicion::operator=(const Medicion& otro)
{
    if (this == &otro) return *this; // handle self assignment
    //assignment operator

    this->unidad = new char [strlen(otro.unidad)+1];
    strcpy(this->unidad,otro.unidad);
    this->medida = otro.medida;

    return *this;
}
ostream & operator <<(ostream & out, const Medicion & otro)
{
    out << "unidad: " << otro.unidad << " medida: " << otro.medida;
    return out;
}

Medicion operator+(float medida, const Medicion & otro)
{
    Medicion nue(otro.medida +medida,otro.unidad);


    return nue;
}
