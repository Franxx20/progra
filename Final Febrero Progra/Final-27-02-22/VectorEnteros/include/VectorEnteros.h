#ifndef VECTORENTEROS_H
#define VECTORENTEROS_H
#include<iostream>
using namespace std;

class VectorEnteros
{

    private:
        int * vec;
        unsigned tamVec;


    public:
        VectorEnteros();
        virtual ~VectorEnteros();
        VectorEnteros(const VectorEnteros& other);
        VectorEnteros(const int * vec,unsigned tamVec);
        VectorEnteros& operator=(const VectorEnteros& other);

        VectorEnteros & agregar(const int * vec,unsigned tamVec);
        VectorEnteros operator+(const VectorEnteros& otro)const;
        VectorEnteros operator+(int numero)const;

        friend ostream & operator<<(ostream & out, const VectorEnteros & otro );

};

#endif // VECTORENTEROS_H
