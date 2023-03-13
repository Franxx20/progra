#include "../TDALista/lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[50];
  int cantidad;
} Producto;

int crearArchivoBinarioLista(char *nombre);
void cargarEnLista(Lista *l, char *nombre);
void mostrarProducto(const void *p, FILE *stream);
void clean_stdin();

int main(int argc, char *argv[]) {
  int ce = crearArchivoBinarioLista(argv[1]);
  FILE *archivoDeTexto = fopen(argv[2], "wt");
  if (!archivoDeTexto) {
    fprintf(stderr, "Error al escribir el archivo de texto");
    return 1;
  }

  Lista listaCande;
  printf("\nLista de compras de cande!");
  crearLista(&listaCande);
  cargarEnLista(&listaCande, argv[1]);
  puts("");
  mostrarLista(&listaCande, ce, mostrarProducto, stdout);
  mostrarLista(&listaCande, ce, mostrarProducto, archivoDeTexto);
  fclose(archivoDeTexto);
  return 0;
}

int crearArchivoBinarioLista(char *nombre) {
  FILE *ListaCande = fopen(nombre, "wb");
  int ce = 0;

  if (!ListaCande) {
    fprintf(stderr, "La listas no se pudo abrir para su escritura");
    return 0;
  }

  Producto produ;
  int c;

  printf("Ingrese un producto: ");
  fgets(produ.nombre, 50, stdin);
  printf("Ingrese su cantidad: ");
  scanf("%d", &produ.cantidad);
  clean_stdin();
  while (produ.cantidad != -1) {
    ce++;
    fwrite(&produ, sizeof(Producto), 1, ListaCande);

    printf("Ingrese un producto: ");
    fgets(produ.nombre, 50, stdin);
    printf("Ingrese su cantidad: ");
    scanf("%d", &produ.cantidad);
    clean_stdin();
  }

  fclose(ListaCande);

  return ce;
}

void cargarEnLista(Lista *l, char *nombre) {

  FILE *ArchivoLista = fopen(nombre, "rb");
  if (!ArchivoLista) {
    fprintf(stderr, "La lista no se pudo abrir para su lectura");
    return;
  }

  Producto prod;
  while (!feof(ArchivoLista) && !listaLlena(l, sizeof(Producto))) {
    fread(&prod, sizeof(Producto), 1, ArchivoLista);
    ponerAlFinal(l, &prod, sizeof(Producto));
  }

  fclose(ArchivoLista);
}

void mostrarProducto(const void *p, FILE *stream) {
  const Producto *prod = (const Producto *)p;
  fprintf(stream, "Producto %s cantidad %d\n", prod->nombre, prod->cantidad);
}

void clean_stdin() {
  // esta funcion elimina los caracteres de fin de linea del buffer para que no
  // sean leidos por otras variables accidentalmente
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
