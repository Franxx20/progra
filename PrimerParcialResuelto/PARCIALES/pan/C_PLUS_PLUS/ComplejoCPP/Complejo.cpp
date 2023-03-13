#include "Complejo.h"

Complejo::Complejo(){
    this->real = 0;
    this->imaginario = 0;
}

Complejo::Complejo( int real, int imaginario ){
    this->real = real;
    this->imaginario = imaginario;
}

Complejo Complejo::operator +( const Complejo& compOp ){
    //Suma =(a, b) + (c, d) = (a+c, b+d)
    int sumReal = this->real + compOp.real;
    int sumImg = this->imaginario + compOp.imaginario;
    Complejo sumFinal( sumReal, sumImg );
    return sumFinal;
}

Complejo operator *( const int escalar, const Complejo& compOp ){
    //r * (a, b) = (r*a, r*b)
    Complejo prodFinal( compOp.real * escalar, compOp.imaginario * escalar );
    return prodFinal;
}

Complejo operator *( const Complejo& compOp1,  const Complejo& compOp2 ){
    //(a, b) * (c, d) = (a*c – b*d, a*d + b*c)
    int prodReal = compOp1.real*compOp2.real - compOp1.imaginario*compOp2.imaginario ;
    int prodImg = compOp1.real*compOp2.imaginario + compOp1.imaginario*compOp2.real;
    Complejo prodFinal( prodReal, prodImg );
    return prodFinal;
}

Complejo& Complejo::operator =( const Complejo& compIg ){
    this->real = compIg.real;
    this->imaginario = compIg.imaginario;
    return *this;
}

Complejo::~Complejo()
{
    //dtor
}

ostream& operator <<( ostream& out, const Complejo& comp ){
    return out << "(" << comp.real << ", " << comp.imaginario << ")";
}
