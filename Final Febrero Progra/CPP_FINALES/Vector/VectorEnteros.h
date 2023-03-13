#ifndef VECTORENTEROS_H_INCLUDED
#define VECTORENTEROS_H_INCLUDED

#include <iostream>

using namespace std;
class VectorEnteros
{
private:
    int *_valor;
    int _tamano;
public:
    VectorEnteros(int *valor,int cantelementos);
    VectorEnteros();
    ~VectorEnteros();
    VectorEnteros operator+(const VectorEnteros &obj)const;
    VectorEnteros operator+(const int valor)const;
    VectorEnteros& agregar(int *valor,int cantelemtnos);
    VectorEnteros& operator=(const VectorEnteros &obj);
    friend ostream& operator<<(ostream& sal,const VectorEnteros & obj);
};

#endif // VECTORENTEROS_H_INCLUDED
