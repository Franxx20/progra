#include "VectorEnteros.h"

VectorEnteros::VectorEnteros()
{
    vec=new int[1];
    cant=1;
    *vec=0;
}



VectorEnteros::VectorEnteros(int * vec1, unsigned cant)
{
    unsigned cont;
    vec=new int[cant];
    this->cant=cant;
    for(cont=0;cont<cant;cont++)
    {
        vec[cont]=vec1[cont];
    }


}

VectorEnteros::~VectorEnteros()
{
    delete[]this->vec;
}
//
//
VectorEnteros& VectorEnteros::agregar(const int * vec1,unsigned cant1)
{
    unsigned i,j,k=0;
    unsigned tam=this->cant+cant1;
    int vetor[tam];
    for(i=0; i<this->cant; i++)
    {
        vetor[i]=vec[i];
    }
    for(j=this->cant; j<tam; j++)
    {
        vetor[j]=vec1[k];
        k++;
    }
    this->cant=tam;
    delete [] vec;
    vec =new int [tam];
    for(i=0; i<tam; i++)
    {
        vec[i]=vetor[i];
    }



    return *this;
}
//
VectorEnteros& VectorEnteros::operator=(const VectorEnteros & otro)
{
    unsigned i=0;
    if(this==&otro)
        return *this;

    delete [] vec;
    vec=new int [otro.cant];
    cant=otro.cant;
    for(i=0; i<otro.cant; i++)
    {
        vec[i]=otro.vec[i];
    }
    return *this;
//    unsigned i=0;
//
//        delete[] this->vec;
//        this->vec = new int[otro.cant];
//
//
//    this->cant = otro.cant;
//    for (; i<this->cant ; i++ )
//    {
//        this->vec[i] = otro.vec[i];
//    }
//
//    return *this;
}

VectorEnteros VectorEnteros::operator+(int num)const
{
    unsigned i;
    unsigned cantidad= this->cant + 1;
    int vecaux[cantidad];

    for(i=0; i<this->cant; i++)
    {
        vecaux[i]=vec[i];
    }
    vecaux[cantidad-1]=num;
    VectorEnteros v1(vecaux,cantidad);
    return v1;

}
//
VectorEnteros VectorEnteros::operator+(const VectorEnteros & otro)const
{
    unsigned i,j,k;
    k=0;
    unsigned cantidad= this->cant + otro.cant;
    int vecaux[cantidad];
    for(i=0; i<this->cant; i++)
    {
        vecaux[i]=vec[i];
    }
    for(j=this->cant; j<cantidad; j++)
    {
        vecaux[j]=otro.vec[k];
        k++;
    }

    VectorEnteros vec1(vecaux,cantidad);
    return vec1;



}
//{
////    VectorEnteros res ;
////
////
////    int * auxDer = otro.vec;
////    int * auxRes = this->vec;
////    int cantRes = this->cant + otro.cant;
////    res.vec = new int[cantRes];
////    int * auxIzq = this->vec;
////
////    res.cant = cantRes;
////
////    unsigned i=0,j=0;
////
////    for (; i<this->cant ; i++ )
////    {
////        *auxRes = *auxIzq;
////        auxRes++;
////        auxIzq++;
////    }
////
////    for (; j<otro.cant; j++ )
////    {
////        *auxRes = *auxDer;
////        auxRes++;
////        auxDer++;
////    }
////
//    int tamRes = this->cant + otro.cant;
//    int * vecRes = new int[tamRes];
//    unsigned i=0,j=0;
//    for (; i<this->cant ; i++ )
//    {
//        vecRes[i] = this->vec[i];
//        //vecRes++;
//    }
//    for (; j<otro.cant ; j++ )
//    {
//        vecRes[i+j] = otro.vec[j];
//        //vecRes++;
//    }
//
//
//    return VectorEnteros(vecRes,tamRes);
//}
//
ostream& operator<<(ostream& os, VectorEnteros & otro)
{
    unsigned i=0;
    os << '[';
    for (; i<otro.cant -1 ; i++ )
    {
        os << otro.vec[i] << ',';
    }
    os<< otro.vec[i]<<']'<< endl;
    return os;
}
