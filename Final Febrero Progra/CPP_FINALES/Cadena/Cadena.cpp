#include "Cadena.h"

Cadena::Cadena(const char *cad)
{
    _cad=new char[strlen(cad)+1];
    strcpy(_cad,cad);
}
Cadena::Cadena(const Cadena &obj)
{
    _cad=new char[strlen(obj._cad)+1];
    strcpy(_cad,obj._cad);
}
Cadena::Cadena()
{
    _cad=new char [1];
    *_cad='\0';
}
Cadena::~Cadena()
{
    delete [] _cad;
}
const unsigned int Cadena::longitud()const
{
    return strlen(_cad);
}
Cadena& Cadena::operator=(const char *cad)
{
    delete [] _cad;
    _cad=new char[strlen(cad)+1];
    strcpy(_cad,cad);
    return *this;
}
Cadena& Cadena::operator=(const Cadena &obj)
{
    if(this==&obj)
        return *this;
    delete [] _cad;
    _cad=new char[strlen(obj._cad)+1];
    strcpy(_cad,obj._cad);
    return *this;
}
Cadena Cadena::operator+(const char *cad)const
{
    char *aux=new char[strlen(_cad)+strlen(cad)+1];
    strcpy(aux,_cad);
    strcat(aux,cad);
    Cadena c1(aux);
    delete [] aux;
    return c1;
}
Cadena Cadena::operator+(const Cadena &obj)const
{
    char *aux=new char[strlen(_cad)+strlen(obj._cad)+1];
    strcpy(aux,_cad);
    strcat(aux,obj._cad);
    Cadena c1(aux);
    delete [] aux;
    return c1;
}
ostream& operator<<(ostream& sal,const Cadena& obj)
{
    sal<<obj._cad;
    return sal;
}
istream& operator>>(istream &sal,Cadena &obj)
{
    char *aux=new char[100];
    sal.getline(aux,100);
    delete [] obj._cad;
    obj._cad = new char[strlen(aux)];
    strcpy(obj._cad,aux);
    delete [] aux;
    return sal;
}
Cadena operator+(const char *cad,const Cadena &obj)
{
    char *aux=new char[strlen(cad)+strlen(obj._cad)+1];
    strcpy(aux,cad);
    strcat(aux,obj._cad);
    Cadena c1(aux);
    delete [] aux;
    return c1;
}
