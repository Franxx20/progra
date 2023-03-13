#include "Complejo.h"

Complejo::Complejo(){
    _real = 0;
    _imaginario = 0;
}

Complejo::Complejo(const int real, const int imaginario){
    _real = real;
    _imaginario = imaginario;
}

Complejo Complejo::operator+(const Complejo& complejoSuma)const{
    Complejo complejoResultado;
    complejoResultado._real = this->_real + complejoSuma._real;
    complejoResultado._imaginario = this->_imaginario + complejoSuma._imaginario;
    return complejoResultado;
}

Complejo Complejo::operator*(const Complejo& complejoMult)const{
    Complejo complejoResultado;
    complejoResultado._real = (this->_real * complejoMult._real) - (this->_imaginario * complejoMult._imaginario);
    complejoResultado._imaginario = (this->_real * complejoMult._imaginario) + (this->_imaginario * complejoMult._real);
    return complejoResultado;
}

Complejo operator*(const double escalar, const Complejo& objComplejo){
    Complejo complejoResultado;
    complejoResultado._real = objComplejo._real * escalar;
    complejoResultado._imaginario = objComplejo._imaginario * escalar;
    return complejoResultado;
}

ostream& operator<<(ostream& salida, const Complejo& objComplejo){
    salida  << "("
            << objComplejo._real
            << ","
            << objComplejo._imaginario
            << ")";
   return salida;
}


