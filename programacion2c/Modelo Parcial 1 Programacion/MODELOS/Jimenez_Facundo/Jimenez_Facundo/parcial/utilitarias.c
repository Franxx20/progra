#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <utilitarias.h>
#include <banco.h>


int compararNroCuenta(const char* nroCuentaBanco, const char* nroCuentaMov){
    while(*nroCuentaBanco){
        if(*nroCuentaBanco == '/')
            nroCuentaBanco++;
        if(*nroCuentaBanco != *nroCuentaMov)
            return *nroCuentaBanco - *nroCuentaMov;
        nroCuentaBanco++;
        nroCuentaMov++;
    }
    return 0;
}

char * desencriptar (char * cad, const char * clave){

    char* aux = miStrrchr(cad, '\n');
    *aux = '\0';
    char* pFinRegistro = cad + strlen(cad) - 1;

    ///paso 3
    restarPalabraClave(cad, clave);
    ///paso 2
    invertirCadena(pFinRegistro - (*pFinRegistro - '0'), pFinRegistro - 1);
    ///paso 1
    invertirCadena(cad + 1, cad + (*cad - '0'));
    return cad;
}


void invertirCadena(char* ini, char* fin){
    char aux;
    while(ini < fin){
        aux = *ini;
        *ini = *fin;
        *fin = aux;
        ini++;
        fin--;
    }
}

void SumarPalabraClave(char* cad, const char* clave){
    static char vecAlfabeto[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //62 sin el \0
//    static int largoClave = miStrlen(clave);
    char *claveIni = (char*)clave;
    int posCad,
        nuevaPos;
    while(*cad){
        posCad = buscarPosicion(vecAlfabeto, *cad);
        nuevaPos = (posCad + buscarPosicion(vecAlfabeto, *clave)) % 62;
        *cad = vecAlfabeto[nuevaPos];
        cad++;
        clave++;
        if(!clave)
            clave = claveIni;
    }

}

void restarPalabraClave(char* cad, const char* clave){
    static char vecAlfabeto[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //62 sin el \0
    char *claveIni = (char*)clave;
    int posCad,
        nuevaPos;
    while(*cad){
        if((posCad = buscarPosicion(vecAlfabeto, *cad)) != -1){
            posCad = buscarPosicion(vecAlfabeto, *cad);
            nuevaPos = (posCad - buscarPosicion(vecAlfabeto, *clave)) >= 0 ?  (posCad - buscarPosicion(vecAlfabeto, *clave)) : (posCad - buscarPosicion(vecAlfabeto, *clave) + 62);
            *cad = vecAlfabeto[nuevaPos];
        }
        cad++;
        clave++;
        if(!*clave)
            clave = claveIni;
    }

}

int buscarPosicion(const char* cad, char letra){
    int pos = 0;
    while(*cad){
        if(*cad == letra)
            return pos;
        pos++;
        cad++;
    }
    return -1;
}


int miStrlen(const char* cad){
    int contador = 0;
    while(*cad){
        contador++;
        cad++;
    }
    return contador;
}


char *miStrrchr(char *s, int c){

    char *punteroLetra = NULL;
    while(*s){
        if(*s == c)
            punteroLetra = s;
        s++;
    }
    return punteroLetra;
}
