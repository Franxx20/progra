#include "VectorEnteros.h"

VectorEnteros::VectorEnteros()
{
    this->tamVec = 0;
    this->vec = NULL;
}

VectorEnteros::~VectorEnteros()
{
//    int * aux = this->vec;
    unsigned i=0;
    cout << "borrando vec" << endl;
    for (;i<this->tamVec ;i++ )
    {
     printf("%d ",this->vec[i]);
    }
    cout << endl;
    delete[] this->vec;
}

VectorEnteros::VectorEnteros(const VectorEnteros& other)
{
    //copy ctor

    this->vec = new int[other.tamVec];
    if(!this->vec)
    {
        throw "error de memoria al crear vector\n";
    }

    memcpy(this->vec,other.vec,sizeof(int)*other.tamVec);
    this->tamVec = other.tamVec;

}
VectorEnteros::VectorEnteros(const int * vec,unsigned tamVec)
{

    this->vec = new int[tamVec];
    if(!this->vec)
    {
        throw "error de memoria al crear vector\n";
    }

    memcpy(this->vec,vec,sizeof(int)*tamVec);
    this->tamVec = tamVec;
}

VectorEnteros & VectorEnteros::agregar(const int * vec,unsigned tamVec)
{
    int * vecAux = new int[(this->tamVec + tamVec)];
    if(!vecAux)
    {
        throw "error de memoria al crear vector\n";
    }

    memcpy(vecAux,this->vec,sizeof(int)*this->tamVec);
    memcpy(vecAux+(int)this->tamVec,vec,sizeof(int)*tamVec);

    delete this->vec;
    this->vec = vecAux;
    this->tamVec = this->tamVec + tamVec;


    return *this;
}


VectorEnteros VectorEnteros::operator+(const VectorEnteros& otro)const
{
    VectorEnteros nue;
//    delete[]nue.vec;

    nue.vec = new int[this->tamVec + otro.tamVec];

    memcpy(nue.vec,this->vec,sizeof(int)*this->tamVec);
    memcpy(nue.vec+(int)this->tamVec,otro.vec,sizeof(int)*tamVec);

    nue.tamVec = this->tamVec + otro.tamVec;

    return nue;
}

VectorEnteros VectorEnteros::operator+(int numero)const
{

    VectorEnteros nue(this->vec,this->tamVec);
    nue.agregar(&numero,1);
//    nue.tamVec;

    return nue;
}
VectorEnteros& VectorEnteros::operator=(const VectorEnteros& otro)
{
    if (this == &otro) return *this; // handle self assignment
    //assignment operator

    delete[]this->vec;
    this->vec = new int[otro.tamVec];
    this->tamVec = otro.tamVec;
    memcpy(this->vec,otro.vec,sizeof(int)*otro.tamVec);


    return *this;
}

ostream & operator<<(ostream & sal, const VectorEnteros & vec )
{
    unsigned i;
    sal << '[';

    for(i = 0; i < vec.tamVec-1; ++i)
    {

        sal << vec.vec[i] << ", ";
        //printf("%d, ",(int)vec.vec[i]);
    }
    sal << vec.vec[i] << ']';
    return sal;
}

