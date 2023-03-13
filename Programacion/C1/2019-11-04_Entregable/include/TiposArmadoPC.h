#ifndef TIPOS_H
#define TIPOS_H


typedef struct
{
    char codigo[21];
    char descripcion[51];
    int stock;
    double precioUnitario;
}
t_componente;


typedef struct
{
    int nroOp;
    char codigo[21];
    int cantidad;
    double precioUnitario;
}
t_armadoYRep;


typedef struct
{
    char codigo[21];
    int nroReg;
}
t_indComponente;


#endif // TIPOS_H
