#include <iostream>
#include<string.h>
using namespace std;

class Medicion
{

private:
    float cant;
    char * unidad;


public:
    Medicion();
    Medicion(float cant,const char * unidad);
    ~Medicion();

    Medicion & operator = (const Medicion &otro);
    Medicion& operator - (const Medicion & otro);

    friend ostream& operator<<(ostream & out, const Medicion & medicion);
    friend Medicion  operator+(const float cant,const Medicion & otro);

};


int main()
{
    Medicion m1mv(100,"Mv");
    Medicion m2mv(20,"Mv");
    Medicion m4amp(3,"Amp");

    Medicion m3mv = m1mv - m2mv;



    cout << "Resultado 1: " << 180+m3mv<< endl;

    try
    {
        cout <<m3mv - m4amp<<endl;
    }
    catch(...)
    {
        cout <<"No se puede restar mediciones de distinta unidad de medida"<< endl;
    }



    return 0;
}

Medicion::Medicion(float cant,const char * unidad):cant(cant)
{
    size_t tam = strlen(unidad);
    this->unidad = new char[tam+1];
    strcpy(this->unidad,unidad);
}

Medicion::~Medicion()
{
    delete []this->unidad;
}
Medicion & Medicion::operator= (const Medicion &otro)
{
size_t tam = strlen(otro.unidad);
this->unidad = new char[tam+1];
strcpy(this->unidad ,otro.unidad);
this->cant = otro.cant;

return *this;
}

Medicion& Medicion::operator-(const Medicion & otro)
{
    if(this == &otro)
        return *this;
    if(strcmp(this->unidad,otro.unidad)!=0)
        throw "hola";

    this->cant -=otro.cant;
    this->unidad = otro.unidad;

    return *this;

}


ostream & operator<<(ostream & out, const Medicion & medicion)
{
    return out << "unidad " << medicion.unidad << " medida " << medicion.cant;
}

Medicion operator+(const float cant, const Medicion &otro){
Medicion nue (otro.cant + cant,otro.unidad);

return nue;
}
