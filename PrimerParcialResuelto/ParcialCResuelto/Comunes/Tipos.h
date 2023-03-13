#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#define ARCHIVO_SIMULACION "simulacion.dat"
#define MAX_TAM_COLA 1000
#define MAX_PALABRA 15

#define SIMULACION_FALLIDA   10
#define MEMORIA_INSUFICIENTE 30
#define EJECUCION_EXITOSA    40


typedef struct {
    unsigned int n;
    char palabra[MAX_PALABRA];
}tpqt;

typedef tpqt t_dato;

typedef struct {
    t_dato icola[MAX_TAM_COLA];
    int iin;
    int ifi;
    int cant;
}t_cola;



#endif // TIPOS_H_INCLUDED
