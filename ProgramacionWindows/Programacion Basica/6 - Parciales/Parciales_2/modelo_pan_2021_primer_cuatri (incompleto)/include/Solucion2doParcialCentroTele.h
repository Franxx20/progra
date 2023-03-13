#ifndef SOLUCION2DOPARCIALCENTROTELE
#define SOLUCION2DOPARCIALCENTROTELE

#include <../include/Arbol.h>
#include <../include/ListaD.h>

void generarArchivoClientes(const char* path);
void generarArchivoPagos(const char* path);

void procesarPagos_res(const char* pathCli, const char* pathPagos, const char* pathListado);
void procesarPagos(const char* pathCli, const char* pathPagos, const char* pathListado);

void generarPathIndex_res(const char* pathCli, char* pathIndex);
void generarPathIndex(const char* pathCli, char* pathIndex);


#endif // SOLUCION2DOPARCIALCENTROTELE
