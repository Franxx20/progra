#ifndef MEDICION_H
#define MEDICION_H
#include <iostream>

// FUNCIONES string
int strcmp_ALU(const char * s1,const char * s2);
char* strcpy_ALU(char * destino,const char *origen);
int strlen_ALU(const char * str);

char* strrchr_ALU(const char * str,int car);
char * strchr_ALU(const char * str,int car);

using namespace std;

class Medicion
{
    private:
        char *unidad;
        float medida;

    public:
//        Medicion();
        Medicion(float medida,const char * unidad);
        virtual ~Medicion();
//        Medicion(const Medicion& other);
        Medicion& operator=(const Medicion& other);
        Medicion operator-(const Medicion & otro)const;
//

        friend ostream& operator<<(ostream & out, const Medicion & otro);
        friend Medicion operator+(float medida,const Medicion & otro);
//


};

#endif // MEDICION_H
