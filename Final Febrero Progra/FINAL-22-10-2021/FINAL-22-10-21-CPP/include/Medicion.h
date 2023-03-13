#ifndef MEDICION_
#define MEDICION_


class Medicion
{
private:
    float cant;
    char * unidad;


public:
    Medicion();
    Medicion(float cant, char * unidad);

    virtual ~Medicion();

    float Getcant()
    {
        return cant;
    }
    void Setcant(float val)
    {
        cant = val;
    }
    char * Getunidad()
    {
        return unidad;
    }
    void Setunidad(char * val)
    {
        unidad = val;
    }



};

#endif // MEDICION_
