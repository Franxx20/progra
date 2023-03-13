#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <utilitarias.h>
#include <banco.h>

void operarSaldos(t_cuenta_banco *cuenta, FILE *pfMov, const char* clave){

    char linea[TAM_LINEA_MOV];
    int nroRegistro = 0;
    rewind(pfMov);
    t_movimiento_banco movRead;
    while(fgets(linea, sizeof(linea), pfMov)){
        decodificarRegistro(linea, nroRegistro, clave);
        texto_a_movimiento(linea, &movRead);
        if(compararNroCuenta(cuenta->cod_cta, movRead.cod_cta) == 0){
            if(movRead.tipo_mov == 'D')
                cuenta->saldo -= movRead.importe;
            else
                cuenta->saldo += movRead.importe;
        }
        nroRegistro++;
    }
}


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

void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov){
    char* aux = strrchr(cadena, '\0');

    aux -= 9;
    sscanf(aux, "%f", &pmov->importe);
    *aux = '\0';

    aux -= 1;
    sscanf(aux, "%c", &pmov->tipo_mov);
    *aux = '\0';

    sscanf(cadena, "%s", pmov->cod_cta);
}

void codificarRegistro(char* registro, int posRegistro, const char* palabraClave){
    char* pFinRegistro = registro + strlen(registro);

    ///paso 1
    if(posRegistro % 2 != 0)
        invertirCadena(registro, pFinRegistro);
    ///paso 2
    invertirCadena(registro + 1, registro + *registro);
    ///paso 3
    invertirCadena(pFinRegistro - *pFinRegistro, pFinRegistro - 1);
    ///paso 4
    sumarPalabraClave(registro, palabraClave);

}

void decodificarRegistro(char* registro, int posRegistro, const char* palabraClave){
    char* aux = strrchr(registro, '\n');
    *aux = '\0';
    char* pFinRegistro = registro + strlen(registro) - 1;

    ///paso 4
    restarPalabraClave(registro, palabraClave);
    ///paso 3
    invertirCadena(pFinRegistro - (*pFinRegistro - '0'), pFinRegistro - 1);
    ///paso 2
    invertirCadena(registro + 1, registro + (*registro - '0'));
    ///paso 1
    if(posRegistro % 2 != 0)
        invertirCadena(registro, pFinRegistro);
}

void sumarPalabraClave(char* cad, const char* palabraClave){
    static char vecAlfabeto[26] = "abcdefghijklmnopqrstuvwxy";
    char* palabraClaveIni = (char*)palabraClave;
    while(*cad){
        *cad += buscarPosicion(vecAlfabeto, *palabraClave);
        cad++;
        palabraClave++;
        if(!palabraClave)
            palabraClave = palabraClaveIni;
    }
}

void restarPalabraClave(char* cad, const char* palabraClave){
    static char vecAlfabeto[26] = "abcdefghijklmnopqrstuvwxy";
    char* palabraClaveIni = (char*)palabraClave;
    while(*cad){
        *cad -= buscarPosicion(vecAlfabeto, *palabraClave);
        cad++;
        palabraClave++;
        if(!*palabraClave)
            palabraClave = palabraClaveIni;
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

int miStrlen(const char* cad){
    int contador = 0;
    while(*cad){
        contador++;
        cad++;
    }
    return contador;
}
