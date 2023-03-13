#include<banco.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>

#include "../include/cola_estatica.h"

int actualizar_cuentas(const char * path_ctas, const char * path_movs, const char * clave){
    tCola colaMovimientos;
    crear_cola_res(&colaMovimientos);

    t_cuenta_banco cuentaRead;
    t_movimiento_banco  moviRead,
                        moviCola;
    char registro[60];
    FILE *pfCuentasRead,
         *pfMoviRead,
         *pfDescubiertoWrite;

    pfCuentasRead = fopen(path_ctas, "r+b");
    if(!pfCuentasRead)
        return -1;
    pfMoviRead = fopen(path_movs, "rt");
    if(!pfMoviRead){
        fclose(pfCuentasRead);
        return -2;
    }
    pfDescubiertoWrite = fopen("../Archivos/movimientos_descubierto.txt", "wt");
    if(!pfDescubiertoWrite){
        fclose(pfCuentasRead);
        fclose(pfMoviRead);
        return -3;
    }

    fread(&cuentaRead, sizeof(cuentaRead), 1, pfCuentasRead);
    fgets(registro, sizeof(registro), pfMoviRead);
    desencriptar(registro, clave);
    texto_a_movimiento(registro, &moviRead);

    while(!feof(pfCuentasRead) && !feof(pfMoviRead)){
        while(!feof(pfCuentasRead) && compararNroCuenta(cuentaRead.cod_cta, moviRead.cod_cta) < 0){
            fread(&cuentaRead, sizeof(cuentaRead), 1, pfCuentasRead);
        }
        while(!feof(pfMoviRead) && compararNroCuenta(cuentaRead.cod_cta, moviRead.cod_cta) > 0){
            fgets(registro, sizeof(registro), pfMoviRead);
            if(!feof(pfMoviRead)){
                desencriptar(registro, clave);
                texto_a_movimiento(registro, &moviRead);
            }
        }
        while(!feof(pfMoviRead) && compararNroCuenta(cuentaRead.cod_cta, moviRead.cod_cta) == 0){
            if(moviRead.tipo_mov == 'D'){
                cuentaRead.saldo -= moviRead.importe;
            }
            else{
                cuentaRead.saldo += moviRead.importe;
            }
            if(cuentaRead.saldo < 0){
                if(!poner_en_cola_res(&colaMovimientos, &moviRead, sizeof(moviRead)))
                    return -4;
            }
            fgets(registro, sizeof(registro), pfMoviRead);
            if(!feof(pfMoviRead)){
                desencriptar(registro, clave);
                texto_a_movimiento(registro, &moviRead);
            }
        }

        while(!cola_vacia_res(&colaMovimientos)){
            sacar_de_cola_res(&colaMovimientos, &moviCola, sizeof(moviCola));
            fprintf(pfDescubiertoWrite, "%-7s, %c, %7.2f\n", moviCola.cod_cta, moviCola.tipo_mov, moviCola.importe);
        }

        fseek(pfCuentasRead, -1L * sizeof(t_cuenta_banco), SEEK_CUR);
        fwrite(&cuentaRead, sizeof(cuentaRead), 1, pfCuentasRead);
        fseek(pfCuentasRead, -0L, SEEK_CUR);
        fread(&cuentaRead, sizeof(cuentaRead), 1, pfCuentasRead);
    }



    fclose(pfCuentasRead);
    fclose(pfMoviRead);
    fclose(pfDescubiertoWrite);
    return 1;
}


void texto_a_movimiento(const char * cadena,t_movimiento_banco * pmov){
    char *aux = strrchr(cadena, '\0');
    *aux = '\0';

    aux -= 9;
    sscanf(aux, "%f", &pmov->importe);
    *aux = '\0';

    aux--;
    sscanf(aux, "%c", &pmov->tipo_mov);
    *aux = '\0';

    sscanf(cadena, "%s", pmov->cod_cta);
}
