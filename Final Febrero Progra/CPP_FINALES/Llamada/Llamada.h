#ifndef LLAMADA_H_INCLUDED
#define LLAMADA_H_INCLUDED

#include "ExceptionLLamada.h"
#include <iostream>

using namespace std;

class Llamada
{
private:
    string _NumOrigen;
    string _NumDestino;
    unsigned int _Recargo;
public:
    Llamada(const string numorigen,const string numdestino,const unsigned int recargo);
    Llamada & operator=(const Llamada &obj);
    Llamada operator+(const Llamada &obj)const;
    friend Llamada operator+(const unsigned int num,const Llamada &obj);
    friend ostream& operator<<(ostream& sal,const Llamada &obj);

};

#endif // LLAMADA_H_INCLUDED
