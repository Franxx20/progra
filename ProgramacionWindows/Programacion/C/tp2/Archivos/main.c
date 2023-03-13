#include "Lista.h"
#include "Producto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define CANT_PRODS 10

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Uso: %s <archivo>\n", argv[0]);
    return 1;
  }
  // CREAR ARCHIVO
  FILE *archivo = fopen(argv[1], "wb");
  FILE *fIndice = fopen(argv[2], "wb");

  if (!archivo) {
    printf("No se pudo abrir el archivo");
    return ERR_ARCHIVO;
  }
  if (!fIndice) {
    printf("No se puede abrir el archivo indice");
    return ERR_ARCHIVO;
  }

  Indice indice;
  Producto productos[CANT_PRODS] = {
      {"Coca", "Coca cola", 120.50, 10},
      {"PEPSI", "Pepsi", 200.70, 10},
      {"SPRITE", "Sprite", 150.40, 20},
      {"FANTA", "Fanta", 130.10, 50},
      {"MANAOS", "Manaos", 100.20, 40},
      {"CERVEZA", "Cerveza", 250.40, 30},
      {"VINO_TORO", "Vino Toro", 280.35, 80},
      {"AGUA_VICEN", "Agua Villavicencia", 80.90, 90},
      {"BRAHMA", "Cerveza Brahma", 300.23, 70},
      {"FERNET", "Fernet", 170.40, 100}};

  Lista productoLista;
  crearLista(&productoLista);
  Lista indiceLista;
  crearLista(&indiceLista);

  fwrite(productos, sizeof(Producto), 10, archivo);

  for (int i = 0; i < CANT_PRODS; i++) {
    strcpy(indice.codigo, productos[i].codigo);
    indice.pos = i;
    insertarAlFinal(&productoLista, &(productos[i]), sizeof(Producto));
    insertarAlFinal(&indiceLista, &indice, sizeof(Indice));
    fwrite(&indice, sizeof(Indice), 1, fIndice);
  }

  fclose(fIndice);
  fclose(archivo);
  // FIN CREAR ARCHIVO

  // MOSTRAR PRODUCTO LISTA
  Producto prodLista;
  while (!listaVacia(&productoLista)) {
    sacarAlInicio(&productoLista, &prodLista, sizeof(Producto));
    printf("\ncodigo %s descripcion %s precio %.2f stock %d\n",
           prodLista.codigo, prodLista.descripcion, prodLista.precio,
           prodLista.cant);
  }
  // FIN MOSTRAR PRODUCTO LISTA

  // ACTUALIZAR PRODUCTOS
  archivo = fopen(argv[1], "r+b");
  if (!archivo) {
    printf("Error al abrir el archivo de productos en actualizacion");
    return ERR_ARCHIVO;
  }

  Producto producto;
  fread(&producto, sizeof(Producto), 1, archivo);
  while (!feof(archivo)) {
    producto.precio *= 1.20;
    fseek(archivo, (long)-sizeof(Producto), SEEK_CUR);
    fwrite(&producto, sizeof(Producto), 1, archivo);
    fseek(archivo, 0, SEEK_CUR);
    fread(&producto, sizeof(Producto), 1, archivo);
  }

  fclose(archivo);

  // FIN ACTUALIZAR PRODUCTOS

  // MOSTRAR PRODUCTOS
  fIndice = fopen(argv[2], "rb");
  archivo = fopen(argv[1], "rb");
  Indice indices[CANT_PRODS];

  if (!archivo) {
    printf("Error al abrir el archivo de productos en lectura");
    return ERR_ARCHIVO;
  }
  if (!fIndice) {
    printf("Error al abrir el archivo de indices");
    return ERR_ARCHIVO;
  }

  int i = 0;
  fread(&(indices[i]), sizeof(Indice), 1, fIndice);
  while (!feof(fIndice)) {
    printf("codigo %s pos %d\n", indices[i].codigo, indices[i].pos);
    i++;
    fread(&(indices[i]), sizeof(Indice), 1, fIndice);
  }

  puts("\n PRODUCTOS \n");

  fread(&producto, sizeof(Producto), 1, archivo);
  while (!feof(archivo)) {
    printf("%s - %s - %.2f - %d\n", producto.codigo, producto.descripcion,
           producto.precio, producto.cant);
    fread(&producto, sizeof(Producto), 1, archivo);
  }
  fclose(archivo);
  fclose(fIndice);

  // FIN MOSTRAR PRODUCTOS
  // BUSCAR POR CODIGO
  archivo = fopen(argv[1], "rb");
  if (!archivo) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO EN MODO BUSQUEDA DE CODIGO");
    return ERR_ARCHIVO;
  }
  char codigo[20];
  int pos;
  Producto prod;
  printf("\nIngrese un codigo a buscar: ");
  scanf("%s", codigo);

  while (strcmp(codigo, "fin") != 0) {
    for (int i = 0; i < CANT_PRODS; i++) {
      if (!strcmp(codigo, indices[i].codigo)) {
        pos = indices[i].pos;
        break;
      }
    }

    fseek(archivo, sizeof(Producto) * pos, SEEK_SET);
    fread(&prod, sizeof(Producto), 1, archivo);
    printf("%s - %s - %.2f - %d\n", prod.codigo, prod.descripcion, prod.precio,
           prod.cant);
    printf("\nIngrese un codigo a buscar: ");
    scanf("%s", codigo);
  }

  fclose(archivo);
  // FIN BUSCAR POR CODIGO

  return 0;
}
