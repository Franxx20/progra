#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H


class FiguraGeometrica
{

protected:
    char * nombre;

public:
    FiguraGeometrica();
    FiguraGeometrica(const char *nombre);
    virtual ~FiguraGeometrica();


    char * Getnombre()const;

    virtual double area()const=0 ;
    virtual double perimetro()const=0;


private:
};

#endif // FIGURAGEOMETRICA_H
