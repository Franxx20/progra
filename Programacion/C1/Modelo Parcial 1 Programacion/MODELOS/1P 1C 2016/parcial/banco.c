#include<banco.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>

void actualizar_cuentas(FILE * arch_ctas, FILE * arch_movs, FILE * arch_err, t_lista *plista)
{
    char cad_mov[19];
    t_movimiento_banco mov;
    t_cuenta_banco cuenta;
    while(fgets(cad_mov,sizeof(cad_mov),arch_movs)){
        texto_a_movimiento(cad_mov,&mov);
        if(!validar_nro_cuenta(&mov)){
            fprintf(arch_err,"%s, %c, %.2f",mov.cod_cta,mov.tipo_mov,mov.importe);
        }
        else{
            fread(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
            while(!feof(arch_ctas)){
                if(mov.cod_cta==cuenta.cod_cta){
                    cuenta.saldo+=mov.tipo_mov=='C'?mov.importe:-mov.importe;
                    fseek(arch_ctas,-sizeof(t_cuenta_banco),SEEK_CUR);
                    fwrite(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
                    fseek(arch_ctas,0L,SEEK_CUR);
                }
                fread(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
            }
        }
    }


}

int validar_nro_cuenta(const t_movimiento_banco * c1)
{
    int n_par=0,n_impar=0,num,verif,i=0;
    while(c1->cod_cta+i){
        if(*(c1->cod_cta+i)=='/'){
            i++;
            verif = *(c1->cod_cta+i)-48;
        }
        if(*(c1->cod_cta+i)-48%2==0){
            n_par*=10;
            n_par+=*(c1->cod_cta+i)-48;
        }
        else{
            n_impar*=10;
            n_impar+=*(c1->cod_cta+i)-48;
        }
        i++;
    }
    num = n_par - n_impar;
    while(num>9)
        num = (num/100) + (num%100)/10 + (num%10);
    if(num!=verif)
        return 0;
    return 1;
}

void ordenar_por_saldo(t_cuenta_banco vec_ctas[],FILE *arch_ctas){
    int i=0,j=0,ce=0;
    fread(&vec_ctas[i],sizeof(t_cuenta_banco),1,arch_ctas);
    while(!feof(arch_ctas)){
        ce++;
        fread(&vec_ctas[i],sizeof(t_cuenta_banco),1,arch_ctas);
    }
    for(;i<ce;i++){
        if(vec_ctas[i].)
    }
}
