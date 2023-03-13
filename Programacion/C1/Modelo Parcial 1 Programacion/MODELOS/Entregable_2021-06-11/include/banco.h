#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED

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

int actualizar_cuentas(const char * path_ctas, const char * path_movs, const char * clave);
int actualizar_cuentas_res(const char * path_ctas, const char * path_movs, const char * clave);

#endif // BANCO_H_INCLUDED
