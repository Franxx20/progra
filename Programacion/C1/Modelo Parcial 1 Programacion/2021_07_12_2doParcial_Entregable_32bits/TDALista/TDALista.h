#ifndef TDALISTA_H
#define TDALISTA_H

#define TODO_OK		0
#define DUPLICADO	1
#define SIN_MEM		2


typedef int (*Cmp)(const void* e1, const void* e2);

typedef int (*Condicion)(const void* elem);

typedef void (*Actualizar)(void* actualizado, const void* actualizador);

typedef void (*Accion)(void* dato, void* datosAccion);


void crearLista(Lista* pl);
int insertarEnListaOrd(Lista* pl, const void* dato, size_t tamElem, Cmp cmp);
int insertarOActualizarEnListaOrd(Lista* pl, const void* dato, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarEnListaAlInicio(Lista* pl, const void* dato, size_t tamElem);
int insertarEnListaAlFinal(Lista* pl, const void* dato, size_t tamElem);
int insertarEnListaEnPosicion(Lista* pl, const void* dato, size_t tamElem, unsigned pos);
int buscarEnListaOrd(const Lista* pl, void* dato, size_t tamElem, Cmp cmp);
int buscarEnListaDesord(const Lista* pl, void* dato, size_t tamElem, Cmp cmp);
void recorrerLista(Lista* pl, Accion accion, void* datosAccion);
int eliminarDeListaOrdPorValor(Lista* pl, void* dato, size_t tamElem, Cmp cmp);
int eliminarDeListaDesordPorValor(Lista* pl, void* dato, size_t tamElem, Cmp cmp);
int eliminarDeListaOrdPorCondicion(Lista* pl, Condicion condicion);
int eliminarDeListaPrimero(Lista* pl, void* dato, size_t tamElem);
int eliminarDeListaUltimo(Lista* pl, void* dato, size_t tamElem);
int eliminarDeListaOrdDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar);
int eliminarDeListaDesordDuplicados(Lista* pl, Cmp cmp);
void ordenarLista(Lista* pl, Cmp cmp);
int listaVacia(const Lista* pl);
int listaLlena(const Lista* pl, size_t tamElem);
void vaciarLista(Lista* pl);


#endif // TDALISTA_H
