#ifndef LLAMADA_H
#define LLAMADA_H
#include <iostream>

class Llamada
{
    private:
        char *numero_origen;
        char *numero_destino;
        int duracion;
    public:
        Llamada(const char *p_origen = NULL,
                const char *p_destino = NULL,
                int p_duracion = 0);
        Llamada(const Llamada& p_llamada);
        ~Llamada();

        Llamada operator+(const Llamada& p_llamada);
        Llamada& operator=(const Llamada& p_llamada);
        friend Llamada operator+(const int segundos, const Llamada& p_llamada);
        friend std::ostream& operator<<(std::ostream& out, const Llamada& p_llamada);
};

#endif // LLAMADA_H
