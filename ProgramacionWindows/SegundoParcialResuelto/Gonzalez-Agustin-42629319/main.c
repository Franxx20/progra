/*****************************************************************************************************************
**
* Apellido/s, Nombre/s: Gonzalez, Agustin Elias
* **
**
** DNI: 42629319
* **
**
******************************************************************************************************************
**
* Corrección
* **
** **********
* **
**
******************************************************************************************************************
**
* Nota:
*****************************************************************************************************************/

/*****************************************************************************************************************
**
* Descomente SOLUCION_ALU y comente SOLUCION_DOC, para probar su código:
* **
**
*/
// #define SOLUCION_DOC
#define SOLUCION_ALU
/*
*****************************************************************************************************************/

#include "../Cadena/Cadena.h"
#include "../Fecha/Fecha.h"
#include "../Solucion2doParcialCentroTele/Solucion2doParcialCentroTele.h"
#include <stdio.h>
#include <stdlib.h>

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define PATH_CLI 1
#define PATH_PAGOS 2
#define PATH_LISTADO 3

#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ERR_LISTA_VACIA_ALU 10

typedef struct {
  int nroCliente;
  char nombre[201];
  int cantFactImpagasFueraTerm;
} FacturasImpagasFueraTerm_ALU;

int procesarPagos_ALU(const char *pathCli, const char *pathPagos,
                      const char *pathListado);

int cargarListaPagos_ALU(const char *pathPagos, Lista *pl);
int compararClientePago_ALU(const void *dato1, const void *dato2);
void mostrarFacturasImp_ALU(void *dato, void *datosAccion);
int compararFecha_ALU(const Fecha *f1, const Fecha *f2);

int insertarEnListaOrdCDup_ALU(Lista *pl, const void *elem, size_t tamElem,
                               Cmp cmp);
int eliminarDeListaPrimero_ALU(Lista *pl, void *elem, size_t tamElem);
void vaciarLista_ALU(Lista *pl);
int listaVacia_ALU(const Lista *pl);
void crearLista_ALU(Lista *pl);
void recorrerLista_ALU(Lista *pl, Accion accion, void *elemsAccion);

int comparacionArbol_ALU(const void *dato1, const void *dato2);
int compararFacturasImpagas_ALU(const void *dato1, const void *dato2);

int buscarEnArbol_ALU(const Arbol *pa, void *dato, size_t tamElem, Cmp cmp);
int insertarEnArbol_ALU(Arbol *pa, void *dato, size_t tamElem, Cmp cmp);
int vaciarArbol_ALU(Arbol *pa);
int cargarArbolDeArchivoOrdenado_ALU(Arbol *pa, size_t tamElem,
                                     const char *nomArch);
void cargarArbolRec_ALU(Arbol *pa, size_t tamElem, int li, int ls, FILE *arch,
                        Cmp cmp);
void crearArbol_ALU(Arbol *pa);

int main(int argc, char *argv[]) {
  generarArchivoClientes(argv[PATH_CLI]);
  generarArchivoPagos(argv[PATH_PAGOS]);

  mostrarArchivoClientes(argv[PATH_CLI]);

  char nombreIdx[201];
  reemplazarSubcad(argv[PATH_CLI], ".dat", ".idx", nombreIdx, 201);
  mostrarArchivoClientesIdx(nombreIdx);

  mostrarArchivoPagos(argv[PATH_PAGOS]);

#ifdef SOLUCION_DOC
  procesarPagos(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#else
  procesarPagos_ALU(argv[PATH_CLI], argv[PATH_PAGOS], argv[PATH_LISTADO]);
#endif

  getchar();

  return 0;
}

int procesarPagos_ALU(const char *pathCli, const char *pathPagos,
                      const char *pathListado) {
  /// Inserte el código acá ...
  Lista pagos;
  crearLista_ALU(&pagos);

  int ret = cargarListaPagos_ALU(pathPagos, &pagos);
  if (ret != TODO_OK)
    return ret;

  Arbol arbolClientesIdx;
  crearArbol_ALU(&arbolClientesIdx);

  char nombreIdx[201];
  strncpy(nombreIdx, pathCli, 201);
  char *aux = strrchr(nombreIdx, '.');
  strcpy(aux, ".idx");

  ret = cargarArbolDeArchivoOrdenado_ALU(&arbolClientesIdx, sizeof(IndCli),
                                         nombreIdx);
  if (ret != TODO_OK)
    return ret;

  FILE *archClientes = fopen(pathCli, "rb");

  if (!archClientes)
    return ERR_ARCHIVO;

  Lista deudores;
  crearLista_ALU(&deudores);

  IndCli idx;
  Cliente cli;
  Pago p;
  FacturasImpagasFueraTerm_ALU f;

  if (listaVacia_ALU(&pagos))
    return ERR_LISTA_VACIA_ALU;

  eliminarDeListaPrimero_ALU(&pagos, &p, sizeof(Pago));
  f.nroCliente = p.nroCliente;
  f.cantFactImpagasFueraTerm = 0;
  int comp3 = compararFecha_ALU(&p.fechaVencimiento, &p.fechaPago);
  if (comp3 < 0)
    f.cantFactImpagasFueraTerm++;

  while (!listaVacia_ALU(&pagos)) {
    eliminarDeListaPrimero_ALU(&pagos, &p, sizeof(Pago));
    int comp = f.nroCliente - p.nroCliente;
    if (comp != 0) {
      idx.nroCliente = f.nroCliente;
      if (buscarEnArbol_ALU(&arbolClientesIdx, &idx, sizeof(IndCli),
                            comparacionArbol_ALU)) {
        fseek(archClientes, idx.nroReg * sizeof(Cliente), SEEK_SET);
        fread(&cli, sizeof(Cliente), 1, archClientes);
        strncpy(f.nombre, cli.nombre, 201);
        insertarEnListaOrdCDup_ALU(&deudores, &f,
                                   sizeof(FacturasImpagasFueraTerm_ALU),
                                   compararFacturasImpagas_ALU);
      }
      f.nroCliente = p.nroCliente;
      f.cantFactImpagasFueraTerm = 0;
      int comp3 = compararFecha_ALU(&p.fechaVencimiento, &p.fechaPago);
      if (comp3 < 0)
        f.cantFactImpagasFueraTerm++;
    } else {
      int comp2 = compararFecha_ALU(&p.fechaVencimiento, &p.fechaPago);
      if (comp2 < 0)
        f.cantFactImpagasFueraTerm++;
    }
  }

  idx.nroCliente = f.nroCliente;
  if (buscarEnArbol_ALU(&arbolClientesIdx, &idx, sizeof(IndCli),
                        comparacionArbol_ALU)) {
    fseek(archClientes, idx.nroReg * sizeof(Cliente), SEEK_SET);
    fread(&cli, sizeof(Cliente), 1, archClientes);
    strncpy(f.nombre, cli.nombre, 201);
    insertarEnListaOrdCDup_ALU(&deudores, &f,
                               sizeof(FacturasImpagasFueraTerm_ALU),
                               compararFacturasImpagas_ALU);
  }

  printf("\nListado de Deudores:\n");
  printf("================================\n");
  printf("Nro Cliente\tNombre\t\tFacturas en mora\n");
  recorrerLista_ALU(&deudores, mostrarFacturasImp_ALU, NULL);

  fclose(archClientes);
  vaciarArbol_ALU(&arbolClientesIdx);
  vaciarLista_ALU(&pagos);

  FILE *archTxt = fopen("listado-deudores.txt", "wt");

  if (!archTxt)
    return ERR_ARCHIVO;

  FacturasImpagasFueraTerm_ALU deu;

  fprintf(archTxt, "Nro Cliente\tNombre\t\tFacturas en mora\n");

  while (!listaVacia_ALU(&deudores)) {
    eliminarDeListaPrimero_ALU(&deudores, &deu,
                               sizeof(FacturasImpagasFueraTerm_ALU));
    fprintf(archTxt, "%d\t%-20s\t%02d\n", deu.nroCliente, deu.nombre,
            deu.cantFactImpagasFueraTerm);
  }

  fclose(archTxt);
  vaciarLista_ALU(&deudores);

  return TODO_OK;
}

int cargarListaPagos_ALU(const char *pathPagos, Lista *pl) {
  FILE *archPagos = fopen(pathPagos, "rb");

  if (!archPagos)
    return ERR_ARCHIVO;

  Pago pago;
  fread(&pago, sizeof(Pago), 1, archPagos);

  while (!feof(archPagos)) {
    insertarEnListaOrdCDup_ALU(pl, &pago, sizeof(Pago),
                               compararClientePago_ALU);
    fread(&pago, sizeof(Pago), 1, archPagos);
  }

  fclose(archPagos);
  return TODO_OK;
}

int compararClientePago_ALU(const void *dato1, const void *dato2) {
  Pago *elem1 = (Pago *)dato1;
  Pago *elem2 = (Pago *)dato2;

  return elem1->nroCliente - elem2->nroCliente;
}

void mostrarFacturasImp_ALU(void *dato, void *datosAccion) {
  FacturasImpagasFueraTerm_ALU *elem = (FacturasImpagasFueraTerm_ALU *)dato;

  printf("%d\t%-20s\t%02d\n", elem->nroCliente, elem->nombre,
         elem->cantFactImpagasFueraTerm);
}

int insertarEnListaOrdCDup_ALU(Lista *pl, const void *elem, size_t tamElem,
                               Cmp cmp) {
  NodoD *act = *pl;
  NodoD *sig = NULL;
  NodoD *ant = NULL;

  if (act) {
    while (act->ant && cmp(act->elem, elem) > 0)
      act = act->ant;

    while (act->sig && cmp(act->elem, elem) < 0)
      act = act->sig;

    int comp = cmp(act->elem, elem);

    if (comp > 0) {
      sig = act;
      ant = act->ant;
    } else {
      ant = act;
      sig = act->sig;
    }
  }

  NodoD *nue = (NodoD *)malloc(sizeof(NodoD));

  if (nue == NULL || (nue->elem = malloc(tamElem)) == NULL) {
    free(nue);
    return 0;
  }

  memcpy(nue->elem, elem, tamElem);
  nue->tamElem = tamElem;
  nue->ant = ant;
  nue->sig = sig;

  if (ant)
    ant->sig = nue;

  if (sig)
    sig->ant = nue;

  *pl = nue;
  return 1;
}

int eliminarDeListaPrimero_ALU(Lista *pl, void *elem, size_t tamElem) {
  if (*pl == NULL)
    return 0;

  NodoD *nae = *pl;

  while (nae->ant)
    nae = nae->ant;

  if (nae->sig)
    nae->sig->ant = NULL;

  if (*pl == nae)
    *pl = nae->sig;

  memcpy(elem, nae->elem, MIN(nae->tamElem, tamElem));

  free(nae->elem);
  free(nae);
  return 1;
}

void vaciarLista_ALU(Lista *pl) {
  NodoD *act = *pl;
  NodoD *nae;

  if (act) {
    while (act->ant)
      act = act->ant;

    while (act) {
      nae = act;
      act = nae->sig;
      free(nae->elem);
      free(nae);
    }
    *pl = NULL;
  }
}

int listaVacia_ALU(const Lista *pl) { return *pl == NULL; }

void crearLista_ALU(Lista *pl) { *pl = NULL; }

int compararFecha_ALU(const Fecha *f1, const Fecha *f2) {
  if (f2->anio == 1900 && f2->mes == 1 && f2->dia == 1)
    return -1;

  int comp = f1->anio - f2->anio;

  if (comp == 0) {
    comp = f1->mes - f2->mes;
    if (comp == 0)
      comp = f1->dia - f2->dia;
  }

  return comp;
}

int comparacionArbol_ALU(const void *dato1, const void *dato2) {
  IndCli *elem1 = (IndCli *)dato1;
  IndCli *elem2 = (IndCli *)dato2;

  return elem1->nroCliente - elem2->nroCliente;
}

int compararFacturasImpagas_ALU(const void *dato1, const void *dato2) {
  FacturasImpagasFueraTerm_ALU *elem1 = (FacturasImpagasFueraTerm_ALU *)dato1;
  FacturasImpagasFueraTerm_ALU *elem2 = (FacturasImpagasFueraTerm_ALU *)dato2;

  return -(elem1->cantFactImpagasFueraTerm - elem2->cantFactImpagasFueraTerm);
}

void recorrerLista_ALU(Lista *pl, Accion accion, void *elemsAccion) {
  NodoD *act = *pl;

  if (act) {
    while (act->ant)
      act = act->ant;

    while (act) {
      accion(act->elem, elemsAccion);
      act = act->sig;
    }
  }
}

int buscarEnArbol_ALU(const Arbol *pa, void *dato, size_t tamElem, Cmp cmp) {
  if (*pa == NULL)
    return 0;

  int comp = cmp(dato, (*pa)->elem);

  if (comp == 0) {
    memcpy(dato, (*pa)->elem, MIN(tamElem, (*pa)->tamElem));
    return 1;
  }

  return buscarEnArbol_ALU(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, dato,
                           tamElem, cmp);
}

int insertarEnArbol_ALU(Arbol *pa, void *dato, size_t tamElem, Cmp cmp) {
  if (*pa == NULL) {
    NodoA *nue = (NodoA *)malloc(sizeof(NodoA));

    if (nue == NULL || (nue->elem = malloc(tamElem))) {
      free(nue);
      return 0;
    }

    memcpy(nue->elem, dato, tamElem);
    nue->tamElem = tamElem;
    nue->hDer = NULL;
    nue->hIzq = NULL;
    *pa = nue;
    return 1;
  }

  int comp = cmp(dato, (*pa)->elem);

  if (comp == 0)
    return DUPLICADO;

  return insertarEnArbol_ALU(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, dato,
                             tamElem, cmp);
}

int vaciarArbol_ALU(Arbol *pa) {
  int cne = 0;

  if (*pa == NULL)
    return 0;

  cne = vaciarArbol(&(*pa)->hIzq);
  cne += vaciarArbol(&(*pa)->hDer);

  free((*pa)->elem);
  free(*pa);
  *pa = NULL;
  return cne + 1;
}

int cargarArbolDeArchivoOrdenado_ALU(Arbol *pa, size_t tamElem,
                                     const char *nomArch) {
  FILE *arch = fopen(nomArch, "rb");

  if (!arch)
    return ERR_ARCHIVO;

  fseek(arch, 0l, SEEK_END);

  int ls = (ftell(arch) / tamElem) - 1;

  cargarArbolRec_ALU(pa, tamElem, 0, ls, arch, comparacionArbol_ALU);

  fclose(arch);

  return TODO_OK;
}

void cargarArbolRec_ALU(Arbol *pa, size_t tamElem, int li, int ls, FILE *arch,
                        Cmp cmp) {
  if (li > ls)
    return;

  int m = (li + ls) / 2;

  fseek(arch, m * tamElem, SEEK_SET);

  void *elem = malloc(tamElem);

  if (!elem)
    return;

  fread(elem, tamElem, 1, arch);

  insertarEnArbol(pa, elem, tamElem, cmp);

  free(elem);

  cargarArbolRec_ALU(pa, tamElem, li, m - 1, arch, cmp);
  cargarArbolRec_ALU(pa, tamElem, m + 1, ls, arch, cmp);
}

void crearArbol_ALU(Arbol *pa) { *pa = NULL; }
