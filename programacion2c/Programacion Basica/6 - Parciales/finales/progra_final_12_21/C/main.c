//1.Lista de compras (ordenada por codPro, acumula cantPedida total)
//2.Lista sectores (ordenada por codSector, acumula cantPedida x sector)
//3.Crear eliminarUltimosNdeLaLista
//4.Crear resultadoCompras.bin
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "lista/lista.h"
/*-----------------------------------------------------------------*/
#define MAX_CODPRO 	10
#define MAX_OFICINA 20

typedef struct s_pedidos {
	char oficina[MAX_OFICINA+1],
		 codPro[MAX_CODPRO+1],
		 codSector;
		 
	int nroPedido,
		cantPedida;
} Pedidos;
/*-----------------------------------------------------------------*/
int crear_lote_de_prueba(const char *filename);
int resolucion(const char *lote_filename, const char *bin_filename);
int comprobar_archivo_bin(const char *filename);
int cmp_productos(const void *data_1, const void *data_2);
int cmp_sectores(const void *data_1, const void *data_2);
int sum_productos(void *data_1, const void *data_2);
void parsear_pedidos(Pedidos *p_pedido, char *str);
void escribir_archivo(const void *data, FILE *stream);
/*-----------------------------------------------------------------*/
int main()
{
	char *lote_de_prueba = "pedidos.txt";
	char *compras_bin_nombre = "resultadoCompras.bin";

	if(!crear_lote_de_prueba(lote_de_prueba)) {return -1;}
	if(!resolucion(lote_de_prueba, compras_bin_nombre)) {return -1;}
	if(!comprobar_archivo_bin(compras_bin_nombre)) {return -1;}

	return 0;
}
/*-----------------------------------------------------------------*/
int crear_lote_de_prueba(const char *filename)
{
	const char *aux[] = {
		//nro|producto|stock|Sector|Oficina
		"",
		"2538|Producto_1|8|A|Valve_HQQQQQQQQQZZZZZZZAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
		"5897|Producto_2|4|B|Mic_HQ",
		"5897|Producto_2|4|G|Mic_HQ",
		"1235|Producto_3|6|A|FM_HQ",
		"4568|Producto_4|2|D|S_HQ",
		"9872|Producto_5|7|E|IBM_HQ",
		"4569|Producto_4|2|D|S_HQ",
		"6789|Producto_6|3|B|L_MQ",
		"2539|Producto_1|2|A|D_HQ",
		"2589|Producto_1|3|B|Q_HQ"
	};

	FILE *lote = fopen(filename, "wt");
	if(!lote) {
		return 0;
	}

	int i;
	for(i = 0; i < sizeof(aux)/sizeof(aux[0]); i++) {
		fprintf(lote, "%s\n", aux[i]);
	}

	fclose(lote);
    return 1;
}
/*-----------------------------------------------------------------*/
int resolucion(const char *lote_filename, const char *bin_filename)
{
	char	aux_str[124];
	Pedidos p_pedidos;
	tLista  lista_compras, 
			lista_sectores;
	FILE 	*file_pedidos;
	FILE	*bin_compras;
	
	file_pedidos = fopen(lote_filename, "rt");
	if(!file_pedidos) {
		return 0;
	}

	bin_compras = fopen(bin_filename, "wb");
	if(!bin_compras) {
		fclose(file_pedidos);
		return 0;
	}
	
	crear_lista(&lista_compras);
	crear_lista(&lista_sectores);

	while(fgets(aux_str, sizeof(aux_str), file_pedidos)) {
		memset(&p_pedidos,0,sizeof(Pedidos)); //Fix valgrind bug (struct padding problem)
		parsear_pedidos(&p_pedidos, aux_str);
		if(p_pedidos.nroPedido) {
			lista_insertar_ordenado(&lista_compras, &p_pedidos, sizeof(Pedidos), cmp_productos, sum_productos);
			lista_insertar_ordenado(&lista_sectores, &p_pedidos, sizeof(Pedidos), cmp_sectores, sum_productos);
		}
	}

	lista_eliminar_ultimos_n(&lista_compras, 2);
	lista_mostrar(&lista_compras, escribir_archivo, bin_compras);

	fclose(file_pedidos);
	fclose(bin_compras);
	vaciar_lista(&lista_sectores);
	vaciar_lista(&lista_compras);
	return 1;
}
/*-----------------------------------------------------------------*/
int comprobar_archivo_bin(const char *filename)
{
	Pedidos pedido;
	FILE *bin_compras = fopen(filename, "rb");
	
	if(!bin_compras) {
		return 0;
	}

	printf("%s contenido:\n---------------------------\n", filename);

	fread(&pedido, sizeof(Pedidos),1,bin_compras);
	while (!feof(bin_compras)) {
		fprintf(stdout, "|%d|%10s|%2d|%c|%20s|\n", pedido.nroPedido, pedido.codPro, 
			pedido.cantPedida, pedido.codSector, pedido.oficina);
		fread(&pedido, sizeof(Pedidos), 1, bin_compras);
	}
	
	fclose(bin_compras);
	return 1;
}
/*-----------------------------------------------------------------*/
int cmp_productos(const void *data_1, const void *data_2)
{
    Pedidos *pedido = (Pedidos *)data_1;
    Pedidos *compra = (Pedidos *)data_2;
    int rc = strcmp(pedido->codPro, compra->codPro);
    return rc;
}
/*-----------------------------------------------------------------*/
int cmp_sectores(const void *data_1, const void *data_2)
{
    Pedidos *pedido = (Pedidos *)data_1;
    Pedidos *compra = (Pedidos *)data_2;
	int rc = pedido->codSector - compra->codSector;
    return (rc)? rc : strcmp(pedido->codPro, compra->codPro);
}
/*-----------------------------------------------------------------*/
int sum_productos(void *data_1, const void *data_2)
{
    Pedidos *oc = (Pedidos *)data_1;
	Pedidos *dup = (Pedidos *)data_2;
	oc->cantPedida += dup->cantPedida;
    return 1;
}
/*-----------------------------------------------------------------*/
void parsear_pedidos(Pedidos *p_pedido, char *str)
{
	char *aux = strchr(str, '\n');
	*aux = '\0';

	if(!*str) {
		return;
	}

	aux = strrchr(str, '|');
	strncpy(p_pedido->oficina, aux + 1, MAX_OFICINA);
	p_pedido->oficina[MAX_OFICINA] = '\0';
	*aux = '\0';

	aux = strrchr(str, '|');
	sscanf(aux + 1, "%c", &p_pedido->codSector);
	*aux = '\0';

	aux = strrchr(str, '|');
	sscanf(aux + 1, "%d", &p_pedido->cantPedida);
	*aux = '\0';
	
	aux = strrchr(str, '|');
	strncpy(p_pedido->codPro, aux + 1, MAX_CODPRO);
	p_pedido->codPro[MAX_CODPRO] = '\0';
	*aux = '\0';

	sscanf(str, "%d", &p_pedido->nroPedido);
}
/*-----------------------------------------------------------------*/
void escribir_archivo(const void *data, FILE *stream)
{
	Pedidos *pedido = (Pedidos *)data;
	fwrite(pedido, sizeof(Pedidos), 1, stream);
}
/*-----------------------------------------------------------------*/