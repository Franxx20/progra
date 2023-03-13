#include "Animal.h"

Animal::Animal()
{
    //ctor
}

//Animal::~Animal()
//{
//    //dtor
//}

ostream& operator<<(ostream & out, Animal & a)
{
    out << "EL ANIMAL " << a.nombre << " TIENE " << a.edad << " Anios" << endl;
    return out;
}
