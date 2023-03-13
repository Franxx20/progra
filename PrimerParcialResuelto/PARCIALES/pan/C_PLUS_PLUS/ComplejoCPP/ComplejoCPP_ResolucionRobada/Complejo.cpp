#include <Complejo.h>

Complejo::Complejo(int r,int i):real(r),imaginario(i)
{}


Complejo Complejo::operator+(const Complejo c2)
{
    int a = this->real + c2.real;
    int b = this->imaginario + c2.imaginario;
    return Complejo(a,b);
}
std::ostream & operator <<(std::ostream &sal,Complejo &c)
{
    sal<<'('<<c.real<<','<<c.imaginario<<')';
    return sal;
}
Complejo operator *(int n, Complejo c)
{
    int a = n*c.real;
    int b = n*c.imaginario;
    return Complejo (a,b);
}
Complejo Complejo::operator * (const Complejo c2)const
{
    int a = (this->real*c2.real - this->imaginario*c2.imaginario);
    int b = (this->real*c2.imaginario + this->imaginario*c2.real);
    return Complejo (a,b);
}

