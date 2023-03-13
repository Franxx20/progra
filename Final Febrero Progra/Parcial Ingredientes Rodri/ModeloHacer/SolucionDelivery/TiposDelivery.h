#ifndef TIPOS_DELIVERY_H
#define TIPOS_DELIVERY_H


typedef struct
{
    int nroPedido;
    char codReceta[11];
    int cantidad;
}
Pedido;


typedef struct
{
	char codReceta[11];
	char codIngr[11];
	int cantidad;
}
Receta;


typedef struct
{
	char codIngr[11];
	int stock;
}
Ingrediente;


typedef struct
{
	char codReceta[11];
	int nroReg;
}
IndReceta;


typedef struct
{
	char codIngr[11];
	int nroReg;
}
IndIngrediente;


#endif // TIPOS_DELIVERY_H
