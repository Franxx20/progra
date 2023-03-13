#include "../Solucion1erParcialEcommerce/Solucion1erParcialEcommerce.h"
#include <stdio.h>

/* Librerias Agregadas */
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include <stdlib.h>
#include <string.h>

#define ARG_CLIENTES 1
#define ARG_PRODUCTOS 2
#define ARG_REGLAS 3
#define ARG_OFERTAS 4

#define minimo(X, Y) ((X) <= (Y) ? (X) : (Y))

/* Funciones Extras */
void paresarRegla(Regla *regla, char *str);
int cmp_reglas(const void *regla, const void *nivel);

void crear_lista(Lista *list);
int vaciar_lista(Lista *list);
int lista_insertarFinal(Lista *list, const void *data, unsigned cantBytes);
int lista_verPosicion(const Lista *list, void *data, unsigned cantBytes,
                      unsigned pos);
size_t lista_buscar(const Lista *list, const void *data, unsigned cantBytes,
                    Cmp comparar);

int main(int argc, char *argv[]) {
  generarArchivoClientes(argv[ARG_CLIENTES]);
  generarArchivoProductos(argv[ARG_PRODUCTOS]);
  generarArchivoReglas(argv[ARG_REGLAS]);

  // generarArchivoOfertas(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS],
  // argv[ARG_REGLAS], argv[ARG_OFERTAS]);
  generarArchivoOfertas_ALU(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS],
                            argv[ARG_REGLAS], argv[ARG_OFERTAS]);

  if (mostrarArchivoOfertas(argv[ARG_OFERTAS]) != TODO_OK)
    printf("\n\nError al mostrar el archivo de ofertas.\n");

  char nombreArchivoOfertasTxt[251];
  cambiarExtension(argv[ARG_OFERTAS], nombreArchivoOfertasTxt, ".txt");

  // generarArchivoOfertasTxt(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);
  generarArchivoOfertasTxt_ALU(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);

  if (mostrarArchivoOfertasTxt(nombreArchivoOfertasTxt))
    printf("\n\nError al mostrar el archivo de ofertas txt.\n");

  return 0;
}

int generarArchivoOfertas_ALU(const char *nombreArchClientes,
                              const char *nombreArchProductos,
                              const char *nombreArchReglas,
                              const char *nombreArchOfertas) {
  Lista lista_reglas;

  Regla t_regla;
  Oferta t_oferta;
  Cliente t_cliente;
  Producto t_producto;

  char str[512] = "";
  char actual_usuario[512] = "";

  FILE *f_reglas = fopen(nombreArchReglas, "rt"),
       *f_clientes = fopen(nombreArchClientes, "rb"),
       *f_prods = fopen(nombreArchProductos, "rb"),
       *f_ofertas = fopen(nombreArchOfertas, "wb");

  crear_lista(&lista_reglas);

  fgets(str, 512, f_reglas); // Omitimos el Header
  while (fgets(str, 512, f_reglas)) {
    paresarRegla(&t_regla, str);
    lista_insertarFinal(&lista_reglas, &t_regla, sizeof(Regla));
  }

  fclose(f_reglas); // Terminamos con este archivo

  fread(&t_cliente, sizeof(Cliente), 1, f_clientes);
  while (!feof(f_clientes)) {

    if (strcmp(actual_usuario, t_cliente.usuario) != 0) {
      strncpy(actual_usuario, t_cliente.usuario, strlen(t_cliente.usuario) + 1);

      int pos = lista_buscar(&lista_reglas, &t_cliente.nivel, sizeof(int),
                             cmp_reglas);
      lista_verPosicion(&lista_reglas, &t_regla, sizeof(Regla), pos);

      rewind(f_prods);
    }

    fread(&t_producto, sizeof(Producto), 1, f_prods);
    while (!feof(f_prods)) {
      float descuento = t_producto.precio * (100 - t_regla.porcDescuento) / 100;
      descuento = (t_producto.precio - descuento <= t_regla.topeDescuento)
                      ? descuento
                      : t_producto.precio - t_regla.topeDescuento;

      strncpy(t_oferta.usuario, t_cliente.usuario,
              strlen(t_cliente.usuario) + 1);
      strncpy(t_oferta.producto, t_producto.codigo,
              strlen(t_producto.codigo) + 1);
      t_oferta.precio = descuento;
      t_oferta.envioGratis = (t_regla.minimoParaEnvioGratis < descuento);

      fwrite(&t_oferta, sizeof(Oferta), 1, f_ofertas);
      fread(&t_producto, sizeof(Producto), 1, f_prods);
    }

    fread(&t_cliente, sizeof(Cliente), 1, f_clientes);
  }

  vaciar_lista(&lista_reglas);

  fclose(f_clientes);
  fclose(f_prods);
  fclose(f_ofertas);

  return TODO_OK;
}

int generarArchivoOfertasTxt_ALU(const char *nombreArchivoOfertas,
                                 const char *nombreArchivoOfertasTxt) {
  Oferta t_oferta;
  char *actual_usuario = calloc(
      1, sizeof(char)); // Calloc inicializa todos los bytes como nulos '\0'
  FILE *f_ofertas_bin = fopen(nombreArchivoOfertas, "rb"),
       *f_ofertas_txt = fopen(nombreArchivoOfertasTxt, "wt");

  fread(&t_oferta, sizeof(Oferta), 1, f_ofertas_bin);
  while (!feof(f_ofertas_bin)) {

    if (strcmp(actual_usuario, t_oferta.usuario) != 0) {
      actual_usuario = realloc(actual_usuario,
                               (strlen(t_oferta.usuario) + 1) * sizeof(char));
      strncpy(actual_usuario, t_oferta.usuario, strlen(t_oferta.usuario) + 1);
      fprintf(f_ofertas_txt, "%s\n", actual_usuario);
    }

    char *envio_gratis = t_oferta.envioGratis ? "Si" : "No";
    fprintf(f_ofertas_txt, "\t%-15s%15.2f\t%s\n", t_oferta.producto,
            t_oferta.precio, envio_gratis);
    fread(&t_oferta, sizeof(Oferta), 1, f_ofertas_bin);
  }

  free(actual_usuario);
  fclose(f_ofertas_bin);
  fclose(f_ofertas_txt);

  return TODO_OK;
}

void paresarRegla(Regla *regla, char *str) {
  char *aux = &str[strcspn(str, "\n")];
  *aux = '\0';

  aux = strrchr(str, '\t');
  sscanf(aux + 1, "%f", &regla->minimoParaEnvioGratis);
  *aux = '\0';

  aux = strrchr(str, '\t');
  sscanf(aux + 1, "%f", &regla->topeDescuento);
  *aux = '\0';

  aux = strrchr(str, '\t');
  sscanf(aux + 1, "%f", &regla->porcDescuento);
  *aux = '\0';

  sscanf(str, "%d", &regla->nivel);
}

int cmp_reglas(const void *regla, const void *nivel) {
  Regla *t_regla = (Regla *)regla;
  return t_regla->nivel - *((int *)nivel);
}

/* Lista Simple */
void crear_lista(Lista *list) { *list = NULL; }

int vaciar_lista(Lista *list) {
  int cant = 0;
  while (*list) {
    Nodo *aux = *list;
    *list = aux->sig;
    free(aux->elem);
    free(aux);
    cant++;
  }
  return cant;
}

int lista_insertarFinal(Lista *list, const void *data, unsigned cantBytes) {
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));

  if (!nuevo || !(nuevo->elem = malloc(cantBytes))) {
    free(nuevo);
    return 0;
  }

  while (*list) {
    list = &(*list)->sig;
  }

  memcpy(nuevo->elem, data, cantBytes);
  nuevo->tamElem = cantBytes;
  nuevo->sig = NULL;
  *list = nuevo;

  return 1;
}

size_t lista_buscar(const Lista *list, const void *data, unsigned cantBytes,
                    Cmp comparar) {
  size_t pos = 0;

  while (*list && comparar((*list)->elem, data) != 0) {
    list = &(*list)->sig;
    pos++;
  }

  if (*list == NULL) {
    pos = -1;
  }

  return pos;
}

int lista_verPosicion(const Lista *list, void *data, unsigned cantBytes,
                      unsigned pos) {
  size_t i;

  for (i = 0; i < pos && *list; i++) {
    list = &(*list)->sig;
  }

  if (*list == NULL) {
    return 0;
  }

  memcpy(data, (*list)->elem, minimo(cantBytes, (*list)->tamElem));

  return 1;
}
