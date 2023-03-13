#include "Medicion.h"
#include<string.h>

//Medicion::Medicion()
//{
//    //ctor
//    this->unidad = new char[1];
//    this->unidad[0]='\0';
//    this->medida = 0;
//}

// FUNCIONES string
int strcmp_ALU(const char * s1,const char * s2)
{
    while(*s1 && *s2)
    {
        if(*s1 != *s2)
            return *s1 -*s2;
        s1++;
        s2++;
    }
    return *s1 -*s2;
}
char* strcpy_ALU(char * destino,const char *origen)
{
    char * aux = destino;
    if(!destino)
        return NULL;

    while(*origen !='\0')
    {
        *destino = * origen;
        destino++;
        origen++;
    }
    return aux;
}
int strlen_ALU(const char * str)
{
    int cant= 0;
    if(!*str)
        return cant;
    while(*str)
    {
        cant++;
        str++;
    }

    return cant;
}

char* strrchr_ALU(const char * str,int car)
{

    int i=0;
    if(!*str)
        return NULL;

    while(*str)
    {
        str++;
        i++;
    }
    for (; i>0 ; i-- )
    {
        if(*str == car)
            return (char*)str;
        str--;
    }

    return NULL;
}
char * strchr_ALU(const char * str,int car)
{

    while(*str)
    {
        if(*str == car)
            return (char *)str;

        str++;
    }

    return NULL;
}

Medicion::Medicion(float medida,const char * unidad)
{
    this->unidad = new char[strlen_ALU(unidad)+1];
    if(!this->unidad)
        throw "no se puedo asignar la memoria\n";

    strcpy_ALU(this->unidad,unidad);
    this->medida = medida;
}
Medicion::~Medicion()
{
    //dtor
//    cout << " borrando unidad "<<endl;
    delete[]this->unidad;
}

//Medicion::Medicion(const Medicion& other)
//{
//    //copy ctor
//}

Medicion& Medicion::operator=(const Medicion& otro)
{
    if (this == &otro)
        return *this;

    this->unidad = new char [strlen_ALU(otro.unidad)+1];
    if(!this->unidad)
        throw "no se puedo asignar la memoria\n";
    strcpy_ALU(this->unidad,otro.unidad);
    this->medida = otro.medida;

    return *this;
}
Medicion Medicion::operator-(const Medicion & otro)const
{
    if(strcmp_ALU(this->unidad,otro.unidad)==0)
    {
        Medicion nue(this->medida- otro.medida,this->unidad);
        return nue;
    }
    else
    {
        throw "Unidades distintas\n";
    }
}

ostream& operator<<(ostream & out, const Medicion & otro)
{

    return out << "Unidad: " << otro.unidad <<" medida: "<< otro.medida;
}
Medicion operator+(float medida,const Medicion & otro)
{
    Medicion nue(otro.medida+medida,otro.unidad);

    return nue;
}
