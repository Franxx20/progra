#include<banco.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>

void actualizar_cuentas(FILE * arch_ctas, const char * path_movs, const char * clave){

    puts("-----MI VERSION------");
    t_cuenta_banco cuentaRead;
    FILE *pfMov = fopen(path_movs, "rt");
    if(!pfMov)
        return;
//    while(fgets(linea, sizeof(linea), pfMov)){
//        decodificarRegistro(linea, nroLinea, clave);
//        texto_a_movimiento(linea, &movimientoRead);
//        printf("%8s %c %8.2f\n", movimientoRead.cod_cta, movimientoRead.tipo_mov, movimientoRead.importe);
//        nroLinea++;
//    }
    fread(&cuentaRead, sizeof(cuentaRead), 1, arch_ctas);
    while(!feof(arch_ctas)){
        operarSaldos(&cuentaRead, pfMov, clave);
        fseek(arch_ctas, -1L * sizeof(cuentaRead), SEEK_CUR);
        fwrite(&cuentaRead, sizeof(cuentaRead), 1, arch_ctas);
        fseek(arch_ctas, 0L, SEEK_CUR);
        printf("%s %s %f\n", cuentaRead.cod_cta, cuentaRead.apyn, cuentaRead.saldo);
        fread(&cuentaRead, sizeof(cuentaRead), 1, arch_ctas);
    }
    fclose(pfMov);
    puts("-----MI VERSION------");
}

//int cmp_cuenta(const t_info *e1,const t_info *e2)
//{
//    return strcmp(e1->cod_cta,e2->cod_cta);
//}
//void acumularSaldo(t_info *e1,const t_info *e2)
//{
//    if(e2->tipo_mov=='D' && e1->tipo_mov=='D')
//        e1->importe+=e2->importe;
//    if(e2->tipo_mov=='D' && e1->tipo_mov=='C')
//    {
//        e1->importe-=e2->importe;
//        if(e1->importe<0)
//            {
//                e1->tipo_mov='D';
//                e1->importe*=(-1);
//            }
//    }
//    if(e2->tipo_mov=='C' && e1->tipo_mov=='C')
//        e1->importe+=e2->importe;
//    if(e2->tipo_mov=='C' && e1->tipo_mov=='D')
//    {
//        e1->importe-=e2->importe;
//        if(e1->importe<0)
//            {
//                e1->tipo_mov='C';
//                e1->importe*=(-1);
//            }
//    }
//}
//
//void actualizar_cuentas(FILE * arch_ctas, const char * path_movs, const char * clave)
//{
//    FILE *pf=fopen(path_movs,"rt");
//    char linea[100],lineaD[100];
//    t_lista lista;
//    t_movimiento_banco reg;
//    t_cuenta_banco cuenta;
//    t_info auxiliar;
//    int numreg=0,comp;
//    if(!pf)
//        exit(0);
//    crear_lista(&lista);
//    while(fgets(linea,sizeof(linea),pf))
//    {
//        if(strchr(linea,'\n'))
//        {
//            strcpy(lineaD,desencriptar(linea,numreg,clave));
//            texto_a_movimiento_res(lineaD,&reg);
//            instertar_lista(&lista,&reg,cmp_cuenta,acumularSaldo);
//            numreg++;
//        }
//    }
//    imprimir_lista(&lista);
//    fread(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
//    sacar_primero_lista(&lista,&reg);
//    while(!feof(arch_ctas)&& !lista_vacia(&lista))
//    {
//        strcpy(auxiliar.cod_cta,cuenta.cod_cta);
//        if(!(comp=cmp_cuenta(&reg,&auxiliar)))
//        {
//            if(reg.tipo_mov=='D')
//                cuenta.saldo-=reg.importe;
//            else cuenta.saldo+=reg.importe;
//            fseek(arch_ctas,-sizeof(t_cuenta_banco),SEEK_CUR);
//            fwrite(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
//            fseek(arch_ctas,0L,SEEK_CUR);
//            sacar_primero_lista(&lista,&reg);
//            fread(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
//        }
//        else if(comp>0)
//                fread(&cuenta,sizeof(t_cuenta_banco),1,arch_ctas);
//             else sacar_primero_lista(&lista,&reg);
//    }
//    vaciar_lista_res(&lista);
//    fclose(pf);
//}
