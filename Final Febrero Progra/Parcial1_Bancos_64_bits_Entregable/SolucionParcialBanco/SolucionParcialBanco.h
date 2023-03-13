#ifndef SOLUCIONPARCIALBANCO_H
#define SOLUCIONPARCIALBANCO_H


void generarArchivos();

int procesarTransferencias(
	const char* nombreTransf, const char* nombreTransfSentander, const char* nombreTransfYCBC, const char* nombreCuentas,
	const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado);

int convertirTxtABinario(const char* nombreTransfTxt, const char* nombreTransfBin);

int mergeTransfer(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge);

int actualizarCuentasYTransferencias(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf);

int mostrarCuentas(const char* nombreCuentas);

int mostrarTransferencias(const char* nombreTransferencias);


int procesarTransferencias_alu(
	const char* nombreTransf, const char* nombreTransfSentander, const char* nombreTransfYCBC, const char* nombreCuentas,
	const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado);

int convertirTxtABinario_alu(const char* nombreTransfTxt, const char* nombreTransfBin);

int mergeTransfer_alu(const char* nombreTransf1, const char* nombreTransf2, const char* nombreTransfMerge);

int actualizarCuentasYTransferencias_alu(
	const char* nombreTransfMerge, const char* nombreCuentas, const char* nombreTransfSantanderEstado, const char* nombreTransfYCBCEstado,
	const char* nombreTransf);


#endif // SOLUCIONPARCIALBANCO_H
