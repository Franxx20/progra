#include<actas.h>
#include<lista.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void generar_acta(const char * path_alus, const char * path_notas, const char * path_acta, const char * path_obs) {
    FILE *pfn,*pfa;
    t_alumno alumno;
    t_nota nota;
    t_lista lista;
    t_info info;

    char texto[100];

    pfa=fopen(path_alus,"rb");
    if(!pfa)
        exit(1);
    pfn=fopen(path_notas,"rt");
    if(!pfn)
    {
        fclose(pfa);
        exit(1);
    }

    ///cargar_datos(FILE *)

    ///void cargar_datos(FILE *pf)
    crear_lista(&lista);

    fread(&alumno,sizeof(t_alumno),1,pfa);
    fgets(texto,sizeof(texto),pfn); ///validar que se pudo leer el dato.
    sscanf(texto,"%li %s %d",&nota.dni,nota.tipo,&nota.nota);

    while(!feof(pfa)) {
        info.dni=alumno.dni;
        strcpy(info.apyn,alumno.apyn);
        while(alumno.dni==nota.dni) {
            if(nota.tipo[0]=='P') {
                if(nota.tipo[1]=='1')
                    info.p1=nota.nota;
                else
                    info.p2=nota.nota;

            } else {
                if(nota.tipo[1]=='1')
                    info.r1=nota.nota;
                else
                    info.r2=nota.nota;
            }
            fgets(texto,sizeof(texto),pfn);
            sscanf(texto,"%li %s %d",&nota.dni,nota.tipo,&nota.nota);

        }
        insertar_lista_res(&lista,&info,cmp_apyn);
        fread(&alumno,sizeof(t_alumno),1,pfa);

    }

}
