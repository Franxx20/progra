#include "Ejercicio 2.h"


 int mi_strlen(char *cad){
    int cant = 0;
    while(*cad){
        cant++;
        cad++;
    }
    return cant;
 }

 void mi_tolower(char* cad){
    for(int i=0;i<mi_strlen(cad);i++){
        if(ES_MAYUS(*(cad+i)))
            *(cad+i) += 32;
    }
 }


 void borra_espacio(char *cad){
    while(*cad){
        if(*cad==32){
            for(int i=0;i<mi_strlen(cad);i++){
                *(cad+i) = *(cad+i+1);
            }
        }
        cad++;
    }
 }

 void borra_todos_espacios(char *cad){
    while(*cad){
        borra_espacio(cad);
        cad++;
    }
 }

 int es_palindromo(char *cad){
    int i = mi_strlen(cad);
    mi_tolower(cad);
    for(int j=0;j<mi_strlen(cad)/2;j++){
        if(*(cad+j)!= *(cad+i-1))
            return 0;
        i--;
    }
    return 1;
 }
