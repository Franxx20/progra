#include "VectorEnteros.h"

VectorEnteros::VectorEnteros()
{
    this->vec = new int[1];
    this->vec[0] =0;
    this->cant = 1;
}



VectorEnteros::VectorEnteros(int * vec, unsigned cant)
{
    unsigned i =0;
    this->vec = new int [cant];
    this->cant = cant;
    int * aux;

    aux = this->vec;
    for (; i<cant ; i++ )
    {
//       this->vec[i] = vec[i];
        *aux = *vec;
        aux++;
        vec++;

    }
}

VectorEnteros::~VectorEnteros()
{
    delete[]this->vec;
}


VectorEnteros& VectorEnteros::agregar(const int * vec,unsigned cant)
{
    unsigned i=0,j=0;
    int tamRes = this->cant + cant;
    int * res = new int [tamRes];

    for (;i<this->cant ;i++ )
    {
        res[i]=this->vec[i];
    }

    for (;j<cant ; j++)
    {
        res[i+j] = vec[j];
    }
    delete[]this->vec;

    this->vec = res;
    this->cant = tamRes;

    return *this;
}

VectorEnteros& VectorEnteros::operator=(const VectorEnteros & otro)
{
    unsigned i=0;

        delete[] this->vec;
        this->vec = new int[otro.cant];


    this->cant = otro.cant;
    for (; i<this->cant ; i++ )
    {
        this->vec[i] = otro.vec[i];
    }

    return *this;
}

VectorEnteros VectorEnteros::operator+(int num)const
{
    VectorEnteros res(this->vec, this->cant+1);

    res.vec[this->cant] = num;
    res.cant++;


    return res;
}

VectorEnteros VectorEnteros::operator+(const VectorEnteros & otro)const
{
//    VectorEnteros res ;
//
//
//    int * auxDer = otro.vec;
//    int * auxRes = this->vec;
//    int cantRes = this->cant + otro.cant;
//    res.vec = new int[cantRes];
//    int * auxIzq = this->vec;
//
//    res.cant = cantRes;
//
//    unsigned i=0,j=0;
//
//    for (; i<this->cant ; i++ )
//    {
//        *auxRes = *auxIzq;
//        auxRes++;
//        auxIzq++;
//    }
//
//    for (; j<otro.cant; j++ )
//    {
//        *auxRes = *auxDer;
//        auxRes++;
//        auxDer++;
//    }
//
    int tamRes = this->cant + otro.cant;
    int * vecRes = new int[tamRes];
    unsigned i=0,j=0;
    for (; i<this->cant ; i++ )
    {
        vecRes[i] = this->vec[i];
        //vecRes++;
    }
    for (; j<otro.cant ; j++ )
    {
        vecRes[i+j] = otro.vec[j];
        //vecRes++;
    }


    return VectorEnteros(vecRes,tamRes);
}

ostream& operator<<(ostream& os, VectorEnteros & otro)
{
    unsigned i=0;
    os << '[';
    for (; i<otro.cant -2 ; i++ )
    {
        os << otro.vec[i] << ',';
    }
    os<< otro.vec[i]<<']'<< endl;
    os << sizeof(otro.vec)<< endl;
    return os;
}
