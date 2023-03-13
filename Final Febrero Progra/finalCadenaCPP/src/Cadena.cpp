#include "Cadena.h"

Cadena::Cadena()
{
    this->_cadena = new char[1];
    this->_cadena[0]='\0';
}

Cadena::~Cadena()
{
    //dtor
    delete []this->_cadena;
    cout << "se elimina la cadena\n" <<endl;
}

Cadena::Cadena(const char * cadena)
{
    int tam = strlen(cadena);
    this->_cadena = new char[tam +1];
    strcpy(this->_cadena,cadena);
}



//Cadena::Cadena(const Cadena& other)
//{
//
////    Cadena nuevo(this->_cadena);
////
////    return nuevo;
//}

//Cadena& Cadena::operator+(const char *cadena)
//{
//
//
//    int tamNuevo = strlen(cadena) + strlen(this->_cadena) +1;
//    char * nuevo = new char[tamNuevo];
//
//    strcpy(nuevo,this->_cadena);
//    strcat(nuevo,cadena);
//
//    delete []this->_cadena;
//
//    this->_cadena = nuevo;
//
//    return *this;
//
//}
Cadena Cadena::operator+(const char * cadena)const
{
    char * nuevaCad = new char[strlen(this->_cadena) + strlen(cadena) +1];
    strcpy(nuevaCad,this->_cadena);
    strcat(nuevaCad,cadena);

    return Cadena(nuevaCad);
}

Cadena& Cadena::operator=(const Cadena& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator

    int tamNuevo = strlen(rhs._cadena) +1;
    delete[]this->_cadena;
    this->_cadena = new char[tamNuevo];

    strcpy(this->_cadena,rhs._cadena);


    return *this;
}

ostream & operator<<(ostream & out, Cadena & otro)
{
    return out << otro._cadena;
}
