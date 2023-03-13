#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

using namespace std;

class Circulo
{
private:
    float x, y;
    unsigned diam;
    char* color;
public:
    Circulo();
    Circulo(const float, const float, const unsigned, const char* );
    Circulo(const Circulo& obj);
    ~Circulo();
    Circulo& operator = (const Circulo& obj);
    Circulo operator ++ (int);
    Circulo operator -- (int);
    void CambiarColor(const char* );
    friend ostream & operator << (ostream&, const Circulo&);
};

#endif // FUNCIONES_H_INCLUDED
