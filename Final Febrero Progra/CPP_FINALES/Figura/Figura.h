#ifndef FIGURA_H_INCLUDED
#define FIGURA_H_INCLUDED

class Figura
{
private:
    unsigned int _Cantlados;
    unsigned int _Perimetro;
public:
    Figura(unsigned int cantlados,unsigned int perimetro);
    const unsigned int cantidadLados()const;
    const unsigned int perimetro()const;
};

#endif // FIGURA_H_INCLUDED
