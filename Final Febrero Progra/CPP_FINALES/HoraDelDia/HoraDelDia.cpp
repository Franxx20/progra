#include "HoraDelDia.h"

HoraDelDia::HoraDelDia()
{
    _Hora=0;
    _Min=0;
    _Seg=0;
}
HoraDelDia::HoraDelDia( unsigned int hora, unsigned int minuto, unsigned int seg)
{
    if(seg>=60)
    {
        minuto+=seg/60;
        seg=seg%60;
    }
    if(minuto>=60)
    {
        hora+=minuto/60;
        minuto=minuto%60;
    }
    while(hora>=24)
        hora-=24;

    _Hora=hora;
    _Min=minuto;
    _Seg=seg;

}
int HoraDelDia::operator >=(const HoraDelDia &obj)const
{
    if(_Hora>obj._Hora)
        return 1;
    if(_Hora==obj._Hora)
    {
        if(_Min>obj._Min)
        {
            return 1;
        }
        if(_Min==obj._Min)
        {
            if(_Seg>=obj._Seg)
            {
                return 1;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    return 0;


}
int HoraDelDia::operator <(const HoraDelDia &obj)const
{
    if(_Hora<obj._Hora)
        return 1;

    if(_Hora==obj._Hora)
    {
        if(_Min<obj._Min)
            return 1;
        if(_Min==obj._Min)
        {
            if(_Seg<obj._Seg)
                return 1;
        }
        else
            return 0;
    }
    return 0;

}
HoraDelDia& HoraDelDia::operator ++(const int a)
{
    if(_Seg<60)
        _Seg+=1;
    if(_Seg==60)
    {
        _Seg=0;
        _Min+=1;
        if(_Min==60)
        {
            _Min=0;
            _Seg=0;
            _Hora+=1;
            if(_Hora>=24)
            {
                _Hora=0;
                _Min=0;
                _Seg=0;
            }
        }
    }
    return *this;
}
HoraDelDia HoraDelDia::operator+(const HoraDelDia &obj)const
{
    HoraDelDia c1(_Hora+obj._Hora,_Min+obj._Min,_Seg+obj._Seg);
    return c1;
}
HoraDelDia& HoraDelDia::operator=(const HoraDelDia &obj)
{
    if(this==&obj)
        return *this;
    _Hora=obj._Hora;
    _Min=obj._Min;
    _Seg=obj._Seg;
    return *this;
}
HoraDelDia& HoraDelDia::operator+=(const unsigned int v1)
{
    if(_Seg<60&&_Seg+v1<60)
        _Seg+=v1;
    if(_Seg>=60&&_Seg+v1>=60)
    {
        _Seg=(_Seg+v1)%60;
        _Min+=(_Seg+v1)/60;
        if(_Min>=60)
        {
            _Min=_Min%60;
            _Hora+=(_Min)/60;
            if(_Hora>=24)
            {
                _Hora=_Hora/24;
                _Min=_Hora%24;
                if(_Min>=60)
                {
                    _Min=_Min/60;
                    _Seg=_Min%60;
                }
            }
        }
    }
    return *this;
}
HoraDelDia operator+(const unsigned int v1,const HoraDelDia &obj)
{
    HoraDelDia c1(obj._Hora,obj._Min,obj._Seg+v1);
    return c1;
}
ostream& operator<<(ostream& sal,const HoraDelDia &obj)
{
    sal<<obj._Hora<<":"<<obj._Min<<":"<<obj._Seg<<endl;
    return sal;
}
istream& operator>>(istream& sal,HoraDelDia & obj)
{
    int hora;
    int minuto;
    int seg;
    cout<<"Ingrese Hora"<<endl;
    cin>>hora;
    cout<<"Ingrese Minuto"<<endl;
    cin>>minuto;
    cout<<"Ingrese Segundos"<<endl;
    cin>>seg;
    obj._Min=minuto;
    obj._Seg=seg;
    obj._Hora=hora;
    return sal;
}
