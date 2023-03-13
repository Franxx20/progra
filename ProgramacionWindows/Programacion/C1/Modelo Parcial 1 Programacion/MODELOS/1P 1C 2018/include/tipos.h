#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct{
    char cod_cta[9];
    long dni;
    char apyn[40];
    float saldo;
}t_cuenta_banco;

typedef struct{
    char cod_cta[9];
    char tipo_mov;
    float importe;
}t_movimiento_banco;
typedef t_movimiento_banco t_info;

#endif // TIPOS_H_INCLUDED
