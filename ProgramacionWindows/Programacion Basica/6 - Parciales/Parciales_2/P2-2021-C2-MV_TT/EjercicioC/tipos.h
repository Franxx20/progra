#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct{
    char code;
    unsigned cantMuelles;
} tSector;


typedef struct{
    long timestamp;
    char dominio[11];
    char tipo;
    char sector;
} tEntradaSalida;

#endif
