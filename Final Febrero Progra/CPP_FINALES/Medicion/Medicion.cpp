#include "Medicion.h"

Medicion::Medicion(const float volt,const string tipo)
{
    _Volt=volt;
    _Tipo=tipo;
}
Medicion::Medicion()
{
    _Volt=0;
    _Tipo="Mv";
}
Medicion& Medicion::operator-(const Medicion &obj)
{
    if(this==&obj)
        return *this;
    if(_Tipo!=obj._Tipo)
    {
        throw Medicionexception();
    }
    _Volt-=obj._Volt;
    _Tipo=obj._Tipo;
    return *this;
}
ostream& operator<<(ostream& sal,const Medicion &obj)
{
    sal<<"("<<obj._Volt<<","<<obj._Tipo<<")"<<endl;
    return sal;
}
Medicion operator+(const float volt,const Medicion & obj)
{
    Medicion c1(obj._Volt+volt,obj._Tipo);
    return c1;
}
