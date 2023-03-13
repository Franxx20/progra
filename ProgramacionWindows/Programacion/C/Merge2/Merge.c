#include "Merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool escribirArchivos(const char *productos, const char *movimientos) {
  FILE *archProds = fopen(productos, "wb");
  FILE *archProdsTxt = fopen("Productos.txt", "wt");
  FILE *archMovs = fopen(movimientos, "wb");

  if (!archProds) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS EN ESCRITURA");
    return false;
  }
  if (!archProdsTxt) {
    fprintf(stderr,
            "ERROR AL ABRIR EL ARCHIVO DE TEXTO PRODUCTOS EN ESCRITURA");
    return false;
  }
  if (!archMovs) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE MOVIMIENTOS EN ESCRITURA");
    return false;
  }

  // Producto prods[5] = {{"ana", "anana", 100, 200},
  //                      {"ban", "banana", 120, 200},
  //                      {"cer", "cereza", 200, 300},
  //                      {"dur", "durazno", 150, 1000},
  //                      {"nar", "naranja", 120, 500}};

  Producto prodsDes[5] = {
      {"nar", "naranja", 120, 500}, {"dur", "durazno", 150, 1000},
      {"cer", "cereza", 200, 300},  {"ban", "banana", 120, 200},
      {"ana", "anana", 100, 200},
  };
  // Movimiento movs[10] = {
  //     {"ban", 50},  {"ban", -20}, {"dur", -100}, {"dur", -150}, {"man", 100},
  //     {"man", 160}, {"nar", -50}, {"zan", 100},  {"zan", 200},  {"zan",
  //     150}};

  Movimiento movsDes[10] = {
      {"ban", -20}, {"dur", -100}, {"man", 160}, {"zan", 200}, {"zan", 100},
      {"nar", -50}, {"zan", 150},  {"ban", 50},  {"man", 100}, {"dur", -150}};

  ordenarSeleccion(prodsDes, sizeof(Producto), 5, compararProdPorCodigo);
  ordenarSeleccion(movsDes, sizeof(Movimiento), 10, compararMovPorCodigo);

  for (int i = 0; i < 5; i++) {
    fprintf(archProdsTxt, "Codigo %s descripci?n %s stock %d precio %.2f\n",
            prodsDes[i].cod, prodsDes[i].desc, prodsDes[i].stock,
            prodsDes[i].precio);
    fwrite(&prodsDes[i], sizeof(Producto), 1, archProds);
  }

  fwrite(movsDes, sizeof(Movimiento), 10, archMovs);

  fclose(archProds);
  fclose(archProdsTxt);
  fclose(archMovs);

  return true;
}

bool actualizarProductos(const char *productos, const char *movimientos) {

  FILE *archProds = fopen(productos, "rb");
  FILE *archMovs = fopen(movimientos, "rb");

  FILE *archTemp = fopen("Productos.temp", "wb");
  FILE *actualizados = fopen("Actualizados.txt", "wt");

  if (!archProds) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS EN ACTUALIZACION");
    return false;
  }
  if (!archMovs) {
    fprintf(stderr,
            "ERROR AL ABRIR EL ARCHIVO DE MOVIMIENTOS EN ACTUALIZACION");
    return false;
  }
  if (!archTemp) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE TEMPORALES EN ACTUALIZACION");
    return false;
  }
  if (!actualizados) {
    fprintf(stderr,
            "ERROR AL ABRIR EL ARCHIVO DE ACTUALIZADOS TXT EN ESCRITURA");
    return false;
  }
  Producto prod, prodNue = {"", "", 0, 0};
  Movimiento mov;
  int comp;
  char tipoFormato = ' ';
  char *formato =
      tipoFormato == 'v' ? "%s\t%s\t%.2f\t%d\n" : "%-10s%-10s%9.2f%5d\n";

  fread(&prod, sizeof(Producto), 1, archProds);
  fread(&mov, sizeof(Movimiento), 1, archMovs);
  while (!feof(archMovs) && !feof(archProds)) {
    comp = strcmp(prod.cod, mov.cod);
    //  el producto no tiene movimientos
    if (comp < 0) {
      fwrite(&prod, sizeof(Producto), 1, archTemp);
      fprintf(actualizados, formato, prod.cod, prod.desc, prod.precio,
              prod.stock);
      fread(&prod, sizeof(Producto), 1, archProds);
    }
    // el producto tiene movimientos
    else if (comp == 0) {
      prod.stock += mov.cant;
      fread(&mov, sizeof(Movimiento), 1, archMovs);
    }
    // si el movimiento es un producto nuevo
    else if (comp > 0) {
      strcpy(prodNue.cod, mov.cod);
      prodNue.stock = mov.cant;
      fread(&mov, sizeof(Movimiento), 1, archMovs);
      while (!feof(archMovs) && strcmp(mov.cod, prodNue.cod) == 0) {
        prodNue.stock += mov.cant;
        fread(&mov, sizeof(Movimiento), 1, archMovs);
      }
      fwrite(&prodNue, sizeof(Producto), 1, archTemp);
      fprintf(actualizados, formato, prodNue.cod, prod.desc, prodNue.precio,
              prodNue.stock);
    }
  }

  // si me quedo primero sin movimientos nuevos para actualizar
  while (!feof(archProds)) {
    fread(&prod, sizeof(Producto), 1, archProds);
    fwrite(&prod, sizeof(Producto), 1, archTemp);
    fprintf(actualizados, formato, prod.cod, prod.desc, prod.precio,
            prod.stock);
  }

  // si me quedo primero sin productos nuevos para actualizar
  while (!feof(archMovs)) {
    strcpy(prodNue.cod, mov.cod);
    prodNue.stock = mov.cant;
    fread(&mov, sizeof(Movimiento), 1, archMovs);

    while (!feof(archMovs) && strcmp(prodNue.cod, mov.cod) == 0) {
      prod.stock += mov.cant;
      fread(&mov, sizeof(Movimiento), 1, archMovs);
    }
    fwrite(&prodNue, sizeof(Producto), 1, archTemp);
    fprintf(actualizados, formato, prodNue.cod, prodNue.desc, prodNue.precio,
            prodNue.stock);
  }
  convertirTxtABin("Actualizados.txt", tipoFormato, productos);

  fclose(archTemp);
  fclose(archProds);
  fclose(archMovs);
  fclose(actualizados);

  remove(productos);
  rename("Productos.temp", productos);

  return true;
}

bool mostrarArchivo(const char *productos) {
  FILE *archProds = fopen(productos, "rb");
  if (!archProds) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS PARA MOSTRAR");
    return false;
  }

  Producto prod;
  fread(&prod, sizeof(Producto), 1, archProds);

  while (!feof(archProds)) {
    printf("Codigo %s Descripcion %s stock %d precio %.2f\n", prod.cod,
           prod.desc, prod.stock, prod.precio);
    fread(&prod, sizeof(Producto), 1, archProds);
  }

  fclose(archProds);
  return true;
}

void ordenarSeleccion(void *vec, unsigned tamDato, int ce, Cmp cmp) {
  void *fin = vec + tamDato * (ce - 1);
  for (void *i = vec; i < fin; i += tamDato) {
    void *menor = buscarMenor(i, fin, tamDato, cmp);
    if (menor != i)
      intercambiar(menor, i, tamDato);
  }
}

void *buscarMenor(void *ini, void *fin, unsigned tamDato, Cmp cmp) {
  void *menor = ini;
  for (void *i = ini + tamDato; i <= fin; i += tamDato)
    if (cmp(i, menor) < 0)
      menor = i;

  return menor;
}

void intercambiar(void *a, void *b, unsigned tamDato) {

  void *aux = malloc(tamDato);
  memcpy(aux, a, tamDato);
  memcpy(a, b, tamDato);
  memcpy(b, aux, tamDato);

  free(aux);
}

int compararProdPorCodigo(const void *p1, const void *p2) {
  const Producto *prod1 = p1;
  const Producto *prod2 = p2;

  return strcmp(prod1->cod, prod2->cod);
}

int compararMovPorCodigo(const void *m1, const void *m2) {

  const Movimiento *mov1 = m1;
  const Movimiento *mov2 = m2;

  return strcmp(mov1->cod, mov2->cod);
}

bool convertirTxtABin(const char *nombreTxt, char tipoFormato,
                      const char *nombreBin) {

  FILE *txt = fopen(nombreTxt, "rt");
  FILE *bin = fopen(nombreBin, "wb");
  if (!txt) {
    fprintf(stderr, "NO SE PUDO ABRIR EL ARCHIVO DE TEXTO EN LECTURA");
    return false;
  }
  if (!bin) {
    fprintf(stderr, "NO SE PUDO ABRIR EL ARCHIVO BINARIO EN ESCRITURA");
    return false;
  }

  Producto prod;
  char *formato =
      tipoFormato == 'v' ? "%s\t%s\t%.2f\t%d\n" : "%-10s%-10s%9.2f%5d\n";
  fscanf(txt, formato, prod.cod, prod.desc, prod.precio, prod.stock);
  while (!feof(txt)) {
    fwrite(&prod, sizeof(Producto), 1, bin);
    fscanf(txt, formato, prod.cod, prod.desc, prod.precio, prod.stock);
  }

  fclose(txt);
  fclose(bin);

  fprintf(stdout, "MOSTRANDO EL ARCHIVO BINARIO DE PRODUCTOS ACTUALIZADOS\n");
  mostrarArchivo(nombreBin);

  return true;
}

bool parsearCadenaVar(char *linea, Producto *prod) {
  char *aux = strrchr(linea, '\n');

  if (!aux) {
    fprintf(stderr, "NO SE ENCONTRE EL CARACTER DE SALGO DE LINEA");
    return false;
  }

  *aux = '\0';
  // STOCK
  aux = strrchr(linea, '\t');
  sscanf(aux + 1, "%d", &prod->stock);
  *aux = '\0';

  // PRECIO
  aux = strrchr(linea, '\t');
  sscanf(linea + 1, "%f", &prod->precio);
  *aux = '\0';

  // DESCRIPCION
  aux = strrchr(linea, '\t');
  strncpy(prod->desc, aux + 1, 20);
  *aux = '\0';

  // CLAVE
  aux = strrchr(linea, '\t');
  strncpy(prod->cod, aux + 1, 5);

  return true;
}

bool parsearCadenaFijo(char *linea, Producto *prod) {
  char *aux = strrchr(linea, '\n');
  if (!aux) {
    fprintf(
        stderr,
        "ERROR NO SE ENCONTRO EL CARACTER DE SALTO DE LINEA EN TAMANIO FIJO");
    return false;
  }
  *aux = '\0';

  // STOCK
  aux -= 5;
  sscanf(aux, "%5d", &prod->stock);
  *aux = '\0';

  // PRECIO
  aux -= 9;
  sscanf(aux, "%9f", &prod->precio);
  *aux = '\0';

  // DESCRIPCION
  aux -= 10;
  sscanf(aux, "%10s", prod->desc);
  *aux = '\0';

  // CLAVE
  aux -= 10;
  sscanf(aux, "%10s", prod->cod);

  return true;
}

bool cambiarExtension(const char *nombreOriginal, char *nombreCambiado,
                      const char *extension) {

  strcpy(nombreCambiado, nombreOriginal);
  char *punto = strrchr(nombreCambiado, '.');
  if (!punto)
    return false;

  strcpy(punto + 1, extension);
  return true;
}
