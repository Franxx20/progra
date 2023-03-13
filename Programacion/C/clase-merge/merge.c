#include "merge.h"
#include <stdio.h>
#include <string.h>
bool escribirArchivos(const char *productos, const char *movimientos) {
  FILE *archProds = fopen(productos, "wb");
  FILE *archProdsTxt = fopen("Productos.txt", "wt");

  FILE *archMovs = fopen(movimientos, "wb");
  if (!archProdsTxt) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODS TXT EN ESCRITURA");
    return false;
  }
  if (!archProds) {

    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODS EN ESCRITURA");
    return false;
  }
  if (!archMovs) {

    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE MOVS EN ESCRITURA");
    return false;
  }
  Producto prods[5] = {{"ana", "anana", 100, 200},
                       {"ban", "banana", 120, 200},
                       {"cer", "cereza", 200, 300},
                       {"dur", "durazno", 150, 1000},
                       {"nar", "naranja", 120, 500}};
  Movimiento movs[10] = {
      {"ban", 50},  {"ban", -20}, {"dur", -100}, {"dur", -150}, {"man", 100},
      {"man", 160}, {"nar", -50}, {"zan", 100},  {"zan", 200},  {"zan", 150}};
  for (int i = 0; i < 5; i++) {
    fprintf(archProdsTxt, "Codigo %s Descripcion %s stock %d precio %.2f\n",
            prods[i].Cod, prods[i].Desc, prods[i].Stock, prods[i].Precio);
    fwrite(&prods[i], sizeof(Producto), 1, archProds);
  }

  fwrite(movs, sizeof(Movimiento), 10, archMovs);

  fclose(archProds);
  fclose(archMovs);
  fclose(archProdsTxt);

  return true;
}
bool actualizarProds(const char *productosA, const char *movimientosA) {

  FILE *archProds = fopen(productosA, "rb");

  FILE *archMovs = fopen(movimientosA, "rb");

  FILE *archProdsTmp = fopen("Productos.tmp", "wb");
  if (!archProds) {

    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODS EN LECTURA");
    return false;
  }
  if (!archMovs) {

    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE MOVS EN LECTURA");
    return false;
  }
  if (!archProdsTmp) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODSTEMP EN ESCRITURA");
    return false;
  }
  int comp;

  // Ver si abrieron

  Producto prod, prodNue = {"", "", 0, 0};

  Movimiento mov;

  fread(&prod, sizeof(Producto), 1, archProds);

  fread(&mov, sizeof(Movimiento), 1, archMovs);

  while (!feof(archProds) && !feof(archMovs))

  {

    comp = strcmp(prod.Cod, mov.Cod);

    if (comp < 0)

    {

      fwrite(&prod, sizeof(Producto), 1, archProdsTmp);

      fread(&prod, sizeof(Producto), 1, archProds);
    }

    if (comp == 0)

    {

      prod.Stock += mov.Cant;

      fread(&mov, sizeof(Movimiento), 1, archMovs);
    }

    if (comp > 0)

    {

      strcpy(prodNue.Cod, mov.Cod);

      prodNue.Stock = mov.Cant;

      fread(&mov, sizeof(Movimiento), 1, archMovs);

      while (!feof(archMovs) && strcmp(prodNue.Cod, mov.Cod) == 0)

      {

        prodNue.Stock += mov.Cant;

        fread(&mov, sizeof(Movimiento), 1, archMovs);
      }

      fwrite(&prodNue, sizeof(Producto), 1, archProdsTmp);
    }
  }

  while (!feof(archProds))

  {

    fwrite(&prod, sizeof(Producto), 1, archProdsTmp);

    fread(&prod, sizeof(Producto), 1, archProds);
  }

  while (!feof(archMovs))

  {

    // Procesar productoNuevo (&mov,archMovs, archProdsTmp)

    strcpy(prodNue.Cod, mov.Cod);

    prodNue.Stock = mov.Cant;

    fread(&mov, sizeof(Movimiento), 1, archMovs);

    while (!feof(archMovs) && strcmp(prodNue.Cod, mov.Cod) == 0)

    {

      prodNue.Stock += mov.Cant;

      fread(&mov, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNue, sizeof(Producto), 1, archProdsTmp);
  }

  fclose(archProds);

  fclose(archMovs);

  fclose(archProdsTmp);

  remove(productosA);

  rename("Productos.tmp", productosA);
  return true;
}

bool mostrarArchivo(const char *producto) {
  FILE *archProds = fopen(producto, "rb");
  if (!archProds) {
    fprintf(stderr, "ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS ACTUALIZADO");
    return false;
  }
  Producto prod;

  fread(&prod, sizeof(Producto), 1, archProds);
  while (!feof(archProds)) {
    printf("Codigo %s Descripcion %s stock %d precio %.2f\n", prod.Cod,
           prod.Desc, prod.Stock, prod.Precio);
    fread(&prod, sizeof(Producto), 1, archProds);
  }
  fclose(archProds);
  return true;
}
