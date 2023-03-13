#include "Complejo.h"

Complejo::Complejo() {
    this->real = 0;
    this->imaginario = 0;
}

Complejo::Complejo(int r, int i) {
    this->real = r;
    this->imaginario = i;
}

Complejo Complejo::operator+(const Complejo& otro) {
    Complejo aux;
    aux.real = this->real + otro.real;
    aux.imaginario = this->imaginario + otro.imaginario;
    return aux;
}


Complejo operator*(int escalar,const Complejo & otro) {
    Complejo aux;
    aux.real = escalar * otro.real;
    aux.imaginario= escalar * otro.imaginario;
    return aux;
}

Complejo Complejo::operator*(const Complejo& otro) {
    Complejo aux;
    aux.real = this->real * otro.real - this->imaginario * otro.imaginario;
    aux.imaginario = this->real * otro.imaginario + this->imaginario * otro.real;
    return aux;
}

ostream& operator <<(ostream& os, const Complejo& otro) {
    os << "(" << otro.real << "," << otro.imaginario<<")";
    return os;
}


istream& operator >>(istream& is, Complejo& otro);
