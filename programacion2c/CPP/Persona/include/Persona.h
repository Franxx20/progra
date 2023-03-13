#ifndef PERSONA_H
#define PERSONA_H
#include "../../CadenaClase/Cadena/Cadena.h"
#include "../../Fecha4/include/Fecha.h"

class Persona {
private:
  unsigned dni;
  Cadena apellido;
  Cadena nombre;
  Fecha fNac;

  Persona(unsigned dni, const Cadena &apelliod, const Cadena &nombre,
          const Fecha &fNac);

  static unsigned validarDni(unsigned dni);
  static const Cadena &validarApellido(const Cadena &apellido);
  static const Cadena &validarNombre(const Cadena &nombre);

public:
  Persona();
  Persona(const Persona &persona);
  Persona &operator=(const Persona &persona);

  inline unsigned getDni() const { return dni; };
  inline void setDni(unsigned dni) { this->dni = validarDni(dni); };

  inline const Cadena &getApellido() const { return apellido; };
  inline void setApellido(const Cadena &apellido) {
    this->apellido = validarApellido(apellido);
  };

  inline const Cadena &getNombre() const { return nombre; };
  inline void setNombre(const Cadena &nombre) {
    this->nombre = validarNombre(nombre);
  };

  inline const Fecha &getFechaNacimiento() const { return fNac; };
  inline void setFechaNacimiento(const Fecha &fNac) { this->fNac = fNac; };

  friend class PersonaBuilder;
};

#endif // PERSONA_H
