#include "Complejo.h"
using namespace std;



Complejo::Complejo()
{
    this->r = 0;
    this->i = 0;
}
Complejo::Complejo(int r,int i)
{
    this->r = r;
    this->i = i;
}

Complejo Complejo::operator+(Complejo& derecha){
Complejo respuesta;
respuesta.r = this->r + derecha.r;
respuesta.i = this->i + derecha.i;

return respuesta;
}

Complejo operator*(int escalar, const Complejo& derecha){
Complejo respuesta;
respuesta.i = escalar * derecha.i;
respuesta.r = escalar * derecha.r;

return respuesta;
}

Complejo Complejo::operator*(Complejo & derecha){
Complejo respuesta;
respuesta.r = this->r * derecha.r - this->i * derecha.i;
respuesta.i = this->r * derecha.i + this->i * derecha.r;


    return respuesta;
}

ostream & operator<<(ostream &out, const Complejo& c){
return out << "(" << c.r << "," << c.i  << ")";

}

istream & operator>>(istream&in, Complejo& c){
return in >> c.r >> c.i ;
}
