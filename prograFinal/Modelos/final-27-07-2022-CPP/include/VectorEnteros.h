#ifndef VECTORENTEROS_H
#define VECTORENTEROS_H
#include<iostream>

using namespace std;

class VectorEnteros
{
    public:
        VectorEnteros();
        VectorEnteros(int * vec, unsigned cant);
        virtual ~VectorEnteros();

        VectorEnteros& agregar(const int * vec,unsigned cant);
        VectorEnteros& operator=(const VectorEnteros & otro);

        VectorEnteros operator+(int num)const;
        VectorEnteros operator+(const VectorEnteros & otro)const;

        friend ostream& operator<<(ostream& os, VectorEnteros & otro);



    private:
        unsigned cant;
        int * vec;
};

#endif // VECTORENTEROS_H
