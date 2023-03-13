#include "Llamada.h"


Llamada::Llamada(const string numorigen,const string numdestino,const unsigned int recargo)
{
    _NumOrigen=numorigen;
    _NumDestino=numdestino;
    _Recargo=recargo;
}
Llamada& Llamada::operator=(const Llamada &obj)
{
    if(this==&obj)
        return *this;
    _NumOrigen=obj._NumOrigen;
    _NumDestino=obj._NumDestino;
    _Recargo=obj._Recargo;
    return *this;
}
Llamada Llamada::operator+(const Llamada &obj)const
{
    if(_NumOrigen!=obj._NumOrigen)
        throw ExceptionLLamada();
    int recargo=obj._Recargo+_Recargo;
    Llamada c1(obj._NumOrigen," ",recargo);
    return c1;

}
Llamada operator+(const unsigned int num,const Llamada &obj)
{
    int recargo=obj._Recargo+num;
    Llamada c1(obj._NumOrigen,obj._NumDestino,recargo);
    return c1;
}
ostream& operator<<(ostream& sal,const Llamada &obj)
{
    sal<<"("<<obj._NumOrigen<<","<<obj._NumDestino<<","<<obj._Recargo<<")"<<endl;
    return sal;
}
