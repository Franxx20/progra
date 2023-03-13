#include "Cuadrado.h"

Cuadrado::Cuadrado(){
    this->lado = 0;
}

Cuadrado::Cuadrado( const Cuadrado& otroCuadrado ){
    this->lado = otroCuadrado.lado;
}

Cuadrado::Cuadrado( Cuadrado& otroCuadrado ){
    this->lado = otroCuadrado.lado;
}

float Cuadrado::getLado() const{
    return this->lado;
}

Cuadrado::~Cuadrado(){
    //dtor
}

ostream& operator <<( ostream& out, const Cuadrado& cuadrado ){
    return out << cuadrado.lado << endl;
}
