#ifndef MUEBLES_COMUN_H
#define MUEBLES_COMUN_H


typedef struct
{
	int nroDep;
	char codProd[16];
	int stock;
}
Deposito;


typedef struct
{
	int depOrigen;
	int depDestino;
	char codProd[16];
	int cantidad;
}
Transferencia;


typedef struct
{
	int nroDep;
	char codProd[16];
	int cantidad;
}
TransferenciaLista;


typedef struct
{
	int nroDep;
	char codProd[16];
	long nroReg;
}
Indice;


void generarArchivos(booleano encriptarTransferencias, booleano generaIndice);
void mostrarArchivoTransferencias(const char* archTransferencias);
void mostrarArchivoDepositos(const char* archDepositos);
void encriptarTransferencias(const char* nombreArchivo);
void desencriptarTransferencias(const char* nombreArchivo);
int cmpTransfLista(const void* pvTr1, const void* pvtr2);
int cmpInd(const void* pvInd1, const void* pvInd2);
void actualizarTransf(void* pvTrActualizada, const void* pvTrActualizadora);
void imprimirIndice(const void* elem, void* datosImprimir, int nivel);


#endif // MUEBLES_COMUN_H
