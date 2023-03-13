#include<actas.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define ES_PROMO(x) (x<=10 && x>=7)
#define ES_APROB(x) (x<=6 && x>=4)
#define ES_DESAP(x) (x<=3 && x>=1)
#define HAY_RECU1(x) (x.r1!=0?x.r1:x.p1)
#define HAY_RECU2(x) (x.r2!=0?x.r2:x.p2)


void generar_acta(const char * path_alus, const char * path_notas, const char * path_acta, const char * path_obs) {

    t_alumno alumno;
    t_acta acta;
    t_nota nota;
    t_lista lactas;
    crear_lista_res(&lactas);
    char cad[90];
    char* aux;
    FILE *arch_alus=fopen(path_alus,"rb"),
        *arch_notas=fopen(path_notas,"r"),
        *arch_acta=fopen(path_acta,"w"),
        *arch_obs=fopen(path_obs,"w");
    if(!arch_alus || !arch_notas || !arch_acta || !arch_obs)
        return;
    fread(&alumno,sizeof(t_alumno),1,arch_alus);
    aux=fgets(cad,sizeof(cad),arch_notas); ///va a leer hasta el \n
    ///sabe si llegó al final del archivo
    texto_a_nota(cad,&nota);

    while(!feof(arch_alus))
    {
        acta.p1 = acta.p2 = acta.r1 = acta.r2 = 0;
        while(aux)
        {
           if(comparar(alumno.dni,nota.dni)==0)
            {
                strcpy(acta.apyn,alumno.apyn);
                acta.dni = alumno.dni;

//                if(!strcmp(nota.tipo,"p1")) acta.p1 = nota.nota;
//                if(!strcmp(nota.tipo,"p2")) acta.p2 = nota.nota;
//                if(!strcmp(nota.tipo,"r1")) acta.r1 = nota.nota;
//                if(!strcmp(nota.tipo,"r2")) acta.r2 = nota.nota;
//                aux=fgets(cad,sizeof(cad),arch_notas);
//                texto_a_nota_res(cad,&nota);

                while(aux && !comparar(acta.dni,nota.dni))
                {

                    if(!strcmp(nota.tipo,"p1")) acta.p1 = nota.nota;
                    if(!strcmp(nota.tipo,"p2")) acta.p2 = nota.nota;
                    if(!strcmp(nota.tipo,"r1")) acta.r1 = nota.nota;
                    if(!strcmp(nota.tipo,"r2")) acta.r2 = nota.nota;
                    aux=fgets(cad,sizeof(cad),arch_notas);
                    texto_a_nota(cad,&nota);
                }
                break;
           }
            aux=fgets(cad,sizeof(cad),arch_notas);
            texto_a_nota(cad,&nota);
        }
        insertar_lista_res(&lactas,&acta,comp_info);
        fread(&alumno,sizeof(t_alumno),1,arch_alus);
    }

    while(!lista_vacia_res(&lactas))
    {
        sacar_primero_lista_res(&lactas,&acta);
        if(acta.r1!= 0 && acta.r2!= 0)
        {
            strcpy(acta.cond,"Err");
            acta.nota = 0;
            fprintf(arch_obs,"El alumno %s (%ld) rindio los 2 recuperatorios\n",acta.apyn,acta.dni);
        }

        if(acta.p1>=7 && acta.r1!=0)
            fprintf(arch_obs,"Advertencia, El alumno %s (%ld) recupero el parcial 1 con %d\n",acta.apyn,acta.dni,acta.p1);

        if(acta.p2>=7 && acta.r2!=0)
            fprintf(arch_obs,"Advertencia, El alumno %s (%ld) recupero el parcial 2 con %d\n",acta.apyn,acta.dni,acta.p2);

        if(ES_PROMO(HAY_RECU1(acta)))
        {
            if(ES_PROMO(HAY_RECU2(acta)))
            {
                strcpy(acta.cond,"Pro");
                acta.nota = (HAY_RECU1(acta)+HAY_RECU2(acta))/2;
                break;
            }

            if(ES_APROB(HAY_RECU2(acta)))
            {
                strcpy(acta.cond,"Apr");
                acta.nota = HAY_RECU2(acta);
                break;
            }

            if(ES_DESAP(HAY_RECU2(acta)))
            {
                strcpy(acta.cond,"Rec");
                acta.nota = HAY_RECU2(acta);
                break;
            }

            strcpy(acta.cond,"Aus");
            acta.nota = HAY_RECU2(acta);
        }

        if(ES_APROB(HAY_RECU1(acta)))
        {
            if(ES_PROMO(HAY_RECU2(acta)) || ES_APROB(HAY_RECU2(acta)))
            {
                strcpy(acta.cond,"Apr");
                acta.nota = (HAY_RECU1(acta)+HAY_RECU2(acta))/2;
                break;
            }
            if(ES_DESAP(HAY_RECU2(acta)))
            {
                strcpy(acta.cond,"Rec");
                acta.nota = HAY_RECU2(acta);
                break;
            }

            strcpy(acta.cond,"Aus");
            acta.nota = 0;
        }

        if(ES_DESAP(HAY_RECU1(acta)))
        {
            if(HAY_RECU2(acta)!=0)
            {
                strcpy(acta.cond,"Rec");
                acta.nota = (HAY_RECU1(acta)+HAY_RECU2(acta))/2;
                break;
            }

            strcpy(acta.cond,"Aus");
            acta.nota = 0;
        }

        if(HAY_RECU1(acta)==0)
        {
            strcpy(acta.cond,"Aus");
            acta.nota = 0;
        }

        fprintf(arch_acta,"%ld %s\t%d %d %d %d %d %s\n",acta.dni,acta.apyn,acta.p1,acta.p2,acta.r1,acta.r2,acta.nota,acta.cond);
        sacar_primero_lista_res(&lactas,&acta);

    }

}
