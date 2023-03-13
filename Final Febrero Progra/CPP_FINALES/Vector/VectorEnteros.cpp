#include "VectorEnteros.h"

VectorEnteros::VectorEnteros(int *valor,int cantelementos)
{
    int i;
    _valor=new int[cantelementos];
    for(i=0; i<cantelementos; i++)
    {
        _valor[i]=valor[i];
    }
    _tamano=cantelementos;
}
VectorEnteros::VectorEnteros()
{
    _valor=new int[1];
    *_valor=0;
    _tamano=1;
}
VectorEnteros::~VectorEnteros()
{
    delete [] _valor;
}
VectorEnteros& VectorEnteros::agregar(int *valor,int cantelemtnos)
{
    if(_tamano==1 && *_valor==0)
    {
        _tamano=0;
    }
    int i,k=0;
    int *nuevo=new int[_tamano+cantelemtnos];
    int nuevotam=_tamano+cantelemtnos;
    for(i=0; i<_tamano; i++)
    {
        nuevo[i]=_valor[i];
    }
    for(i=_tamano; i<nuevotam; i++)
    {
        nuevo[i]=valor[k];
        k++;
    }
    for(i=0;i<nuevotam;i++)
    {
           _valor[i]=nuevo[i];
    }
    _tamano=nuevotam;
    delete [] nuevo;
    return *this;

}
VectorEnteros VectorEnteros::operator+(const VectorEnteros &obj)const
{
    int i,k=0;
    int *nuevo=new int[_tamano+obj._tamano];
    int nuevotam=_tamano+obj._tamano;
    for(i=0; i<_tamano; i++)
    {
        nuevo[i]=_valor[i];
    }
    for(i=_tamano; i<nuevotam; i++)
    {
        nuevo[i]=obj._valor[k];
        k++;
    }
    VectorEnteros c1 (nuevo,nuevotam);
    delete [] nuevo;
    return c1;
}
VectorEnteros VectorEnteros::operator+(const int valor)const
{
    int i;
    int *nuevo=new int[_tamano+1];
    int nuevotam=_tamano+1;
    for(i=0; i<_tamano; i++)
    {
        nuevo[i]=_valor[i];
    }
    nuevo[_tamano]=valor;
    VectorEnteros c1(nuevo,nuevotam);
    delete [] nuevo;
    return c1;

}
VectorEnteros& VectorEnteros::operator=(const VectorEnteros &obj)
{
    int i;
    if(this==&obj)
        return *this;
    delete [] _valor;
    _valor=new int [obj._tamano];
    _tamano=obj._tamano;
    for(i=0; i<_tamano; i++)
    {
        _valor[i]=obj._valor[i];
    }
    return *this;
}
ostream& operator<<(ostream& sal,const VectorEnteros & obj)
{
    int i;
    sal<<"[";
    for(i=0; i<obj._tamano; i++)
    {
        sal<<obj._valor[i]<<",";
    }
    sal<<"]"<<endl;
    return sal;
}
