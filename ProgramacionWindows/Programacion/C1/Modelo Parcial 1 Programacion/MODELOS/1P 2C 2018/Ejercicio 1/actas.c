#include<actas.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void generar_acta(const char * path_alus, const char * arch_notas, const char * arch_acta, const char * arch_obs){
    FILE *arch_alus = fopen(path_alus,"rb"),*arch_nota = fopen(arch_notas,"r"),*arch_act = fopen(arch_acta,"w"),*arch_ob=fopen(arch_obs,"w");
    //if(arch_alus == NULL || arch_nota==NULL || arch_act==NULL || arch_ob==NULL)
        //return 10;
    t_alumno alum;
    t_nota nota;
    t_acta acta;
    t_lista lista;
    crear_lista(&lista);
    char cad[sizeof(t_nota)];

    rewind(arch_alus);
    rewind(arch_nota);

    fread(&alum,sizeof(t_alumno),1,arch_alus);
    while(!feof(arch_alus))
    {
        acta.dni=alum.dni;
        strcpy(acta.apyn,alum.apyn);
        acta.p1 = acta.p2 = acta.r1 = acta.r2 = acta.nota = 0;
        strcpy(acta.cond,"Aus");

        fgets(cad,sizeof(t_nota),arch_nota);
        texto_a_nota(cad,&nota);
        while (alum.dni == nota.dni)
        {
            if(strcmp(nota.tipo,"P1")==0)
                acta.p1=nota.nota;
            if(strcmp(nota.tipo,"P2")==0)
                acta.p2=nota.nota;
            if(strcmp(nota.tipo,"R1")==0)
                acta.r1=nota.nota;
            if(strcmp(nota.tipo,"R2")==0)
                acta.r2=nota.nota;

            fgets(cad,sizeof(t_nota),arch_nota);
            texto_a_nota(cad,&nota);
        }
        if (nota.dni < alum.dni)
        {
            strcpy(acta.cond,"Err");
            fprintf(arch_ob,"%ld %s\t%d %d %d %d %d %s\n",acta.dni,acta.apyn,acta.p1,acta.p2,acta.r1,acta.r2,acta.nota,acta.cond);
        }
        calcular_nota_final(&acta);
        if ((acta.p1 >= 7 && acta.r1 > 0) || (acta.p2 >= 7 && acta.r2 > 0))
             fprintf(arch_ob,"%ld %s\t%d %d %d %d %d %s\n",acta.dni,acta.apyn,acta.p1,acta.p2,acta.r1,acta.r2,acta.nota,acta.cond);
        if (strcmpi(acta.cond,"Err") && acta.nota == 0)
             fprintf(arch_ob,"%ld %s\t%d %d %d %d %d %s\n",acta.dni,acta.apyn,acta.p1,acta.p2,acta.r1,acta.r2,acta.nota,acta.cond);
        insertar_lista(&lista,&acta,comparar);
        fread(&alum,sizeof(t_alumno),1,arch_alus);
    }

    while(!lista_vacia(&lista))
    {
        sacar_primero_lista(&lista,&acta);
        fprintf(arch_act,"%ld %s\t%d %d %d %d %d %s\n",acta.dni,acta.apyn,acta.p1,acta.p2,acta.r1,acta.r2,acta.nota,acta.cond);
    }
}

void calcular_nota_final(t_acta *a)
{
    if(a->p1 < 0 || a->p2 < 0)
    {
        a->nota = 0;
        strcpy(acta.cond,"Aus");
    }
    if (a->p1 <= 3 || a->p2 <= 3)
    {
        a->nota = 0;
        strcpy(acta.cond,"Err");
    }

    if (a->p1 <= 3 && a->pl > 0)
        a->p1 = a->r1;
    if (a->p2 <= 3 && a->p2 > 0)
        a->p2 = a->r2;

    if (a->p1 >=7 && a->p2 >= 7)
        a->nota = (a->p1 + a->p2) / 2;
    if ((a->p1>0 && a->p1) <7 || (a->p2>0 && a->p2 < 7))
        a->nota = MIN(a->p1,a->p2); //hacer la macro

    if(acta.nota > 0 && acta.nota <=3)
        strcpy(acta.cond,"Rec");
    if(acta.nota > 3 && acta.nota <= 6)
        strcpy(acta.cond,"Apr");
    if(acta.nota >= 7)
        strcpy(acta.cond,"Pro");
}

void validar_nota_final(const t_acta *a, FILE * arch_obs){

}
