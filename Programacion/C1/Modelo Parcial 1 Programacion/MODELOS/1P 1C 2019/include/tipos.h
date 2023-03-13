#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct{
    char isbn[18];
    char titulo[60];
    char autor[40];
    int stock;
}t_libro;

typedef struct{
    char isbn[18];
    int stock;
}t_libro_stock;

typedef t_libro t_info;

#endif // TIPOS_H_INCLUDED
