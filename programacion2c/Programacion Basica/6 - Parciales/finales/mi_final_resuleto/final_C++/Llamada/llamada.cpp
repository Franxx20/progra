#include <string.h>
#include <stdexcept>
#include "llamada.h"

Llamada::Llamada(const char *p_origen, const char *p_destino, int p_duracion)
{
    if(p_origen) {
        size_t origen_size = strlen(p_origen)+1;
        numero_origen = new char[origen_size];
        strncpy(numero_origen, p_origen, origen_size);
    }
    else {
        numero_origen = new char[1];
        numero_origen[0] = '\0';
    }

    if(p_destino) {
        size_t destino_size = strlen(p_destino)+1;
        numero_destino = new char[destino_size];
        strncpy(numero_destino, p_destino, destino_size);
    }
    else {
        numero_destino = new char[1];
        numero_destino[0] = '\0';
    }
    duracion = p_duracion;
}

Llamada::~Llamada()
{
    delete []numero_origen;
    delete []numero_destino;
}

Llamada::Llamada(const Llamada& p_llamada)
    : Llamada(
        p_llamada.numero_origen,
        p_llamada.numero_destino,
        p_llamada.duracion
    )
{

}

Llamada Llamada::operator+(const Llamada& p_llamada)
{
    if(strcmp(numero_origen, p_llamada.numero_origen) != 0) {
        throw std::invalid_argument("Numeros de origen distintos");
    }
    return Llamada(numero_origen, NULL, duracion + p_llamada.duracion);
}

Llamada& Llamada::operator=(const Llamada& p_llamada)
{
    size_t origen_size = strlen(p_llamada.numero_origen)+1;
    size_t destino_size = strlen(p_llamada.numero_destino)+1;

    if(strlen(numero_origen) != origen_size) {
        delete []numero_origen;
        numero_origen = new char[origen_size];
    }
    strncpy(numero_origen, p_llamada.numero_origen, origen_size);

    if(strlen(numero_destino) != destino_size) {
        delete []numero_destino;
        numero_destino = new char[destino_size];
    }
    strncpy(numero_destino, p_llamada.numero_destino, destino_size);

    duracion = p_llamada.duracion;
    return *this;
}

/** FRIEND FUNCTIONS **/
Llamada operator+(const int segundos, const Llamada& p_llamada)
{
    return Llamada(
                   p_llamada.numero_origen,
                   p_llamada.numero_destino,
                   segundos + p_llamada.duracion
            );
}

std::ostream& operator<<(std::ostream& out, const Llamada& p_llamada)
{
    out << "( " << p_llamada.numero_origen
        << ", " << p_llamada.numero_destino
        << ", " << p_llamada.duracion
        << " )";
    return out;
}
