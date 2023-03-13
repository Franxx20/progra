#ifndef FIGURAGEOMETRICA_H
#define FIGURAGEOMETRICA_H


class FiguraGeometrica
{
    public:
        FiguraGeometrica();
        FiguraGeometrica(const char * nombre);
        virtual ~FiguraGeometrica();


        char * Getnombre()const { return nombre; }

        virtual double area() const =0;
        virtual double perimetro()const =0;

    protected:
        char * nombre;

    private:
};

#endif // FIGURAGEOMETRICA_H
