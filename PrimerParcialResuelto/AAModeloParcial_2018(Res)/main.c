#include "Modelo_Parcial.h"



int main()
{
    t_cuenta mcuenta[5]= {{"11111111","Juan",5000},{"22222222","Ariana",500},{"44444444","Dolores",320},{"55555555","Pepe",750},{"77777777","Pancho",50}};

//    t_movimiento mov[]={{{22,10,2019},{9,0},"55555555","D",100.50},
//    {{22,10,2019},{10,17},"77777777","C",550},
//    {{22,10,2019},{12,05},"22222222","C",1000},{{23,10,2019},{15,07},"11111111","D",800},
//    {{23,10,2019},{17,30},"77777777","D",600},{{24,10,2019},{00,10},"55555555","D",700.50}};

    FILE* pm;
    FILE* pc;
    t_movimiento mov;
    t_lista l;
    int i;

    pm=abrirArch(FMOVIMIENTOS,"rt");
    pc=abrirArch(FCUENTAS,"wb");
    crearLista(&l);

    for(i=0; i<5; i++) ///lote de prueba de clientes.dat
        fwrite(&mcuenta[i],sizeof(t_cuenta),1,pc);
    fclose(pc);


    while(fscanf(pm,"%02d%02d%04d%02d%02d%8s%1s%9f\n",&mov.fecha.di,&mov.fecha.me,
                 &mov.fecha.an,&mov.hora.h,&mov.hora.m,
                 mov.nrocuenta,mov.movimiento,&mov.importe)!=EOF) ///cargar la lista
    {
//          fprintf(pm,"%02d%02d%04d%02d%02d%8s%1s%09.2f\n",
//            mov->fecha.di,mov->fecha.me,mov->fecha.an,mov->hora.h,mov->hora.m,
//            mov->nrocuenta,mov->movimiento,mov->importe);
        if(strcmp(mov.movimiento,"D")==0)
            mov.importe*=(-1);
        ponerListaOrdenada(&l,&mov,comparar,actualizar);
    }
    fclose(pm);

    actualizaCuentas(pc,&l);
    mostrar_archivo(pc);
    return 0;
}
