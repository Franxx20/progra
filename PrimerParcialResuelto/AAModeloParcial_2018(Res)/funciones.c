#include "Modelo_Parcial.h"

FILE *abrirArch (char *nombre, char* modo)
{
    FILE *pf1;
    pf1 = fopen(nombre, modo);
    if (!pf1)
        exit(1);

    return pf1;
}

void mostrar_archivo(FILE* pc)
{
    t_cuenta cta;
    pc=abrirArch(FCUENTAS,"rb");
    fread(&cta, sizeof(t_cuenta),1,pc);
    ///fseek(pc,sizeof(t_cuenta),SEEK_SET); NO VA!!
    while(!feof(pc))
    {
        printf("%s %s %.2f\n",cta.nrocuenta,cta.nombre,cta.saldo);
        fread(&cta, sizeof(t_cuenta),1,pc);
        printf("\n");
    }
    fclose(pc);
}

void crearLista(t_lista *l)
{
    *l=NULL;
}

int comparar(const void *dato1,const void *dato2)
{
    t_movimiento *d1;
    t_movimiento *d2;

    d1=(t_movimiento*)dato1;
    d2=(t_movimiento*)dato2;
    return strcmp(d1->nrocuenta,d2->nrocuenta);
}

int ponerListaOrdenada(t_lista *l,const t_movimiento *info,t_cmp comparar,t_act actualizar)
{
    int c;
    t_nodo* nuevo;
    while(*l && (c=(comparar(info,&(*l)->info)))>0)
        l = &(*l)->sig;
    if(*l && c==0)
    {
        actualizar(&(*l)->info,info);
        return DUPLICADO;
    }
    nuevo=(t_nodo*)malloc(sizeof(t_nodo));
    if(!nuevo)
        return LISTA_LLENA;
    nuevo->info = *info;
    nuevo->sig = *l;
    *l = nuevo;

    return TODO_BIEN;
}

void actualizar(void* datoact, const void* datonue)
{
    t_movimiento*d1=(t_movimiento*)datoact; ///dato nuevo
    t_movimiento*d2=(t_movimiento*)datonue; /// dato que ya tenia en la lista

    d1->importe+=d2->importe;
}

void copiarListaEnArchivo(FILE* pm,t_lista* l)
{
    t_movimiento mov;
    while(*l)
    {
        mov = (*l)->info;
        l = &(*l)->sig;
        fprintf(pm,"\n%02d%02d%04d%02d%02d%8s%1s%9.2f\n",mov.fecha.di,mov.fecha.me,
            mov.fecha.an,mov.hora.h,mov.hora.m,
            mov.nrocuenta,mov.movimiento,mov.importe);
    }
}
/// SACAR PRIMERO DE LA LISTA
int sacarPrimeroLista(t_lista *l,t_movimiento *info)
{
    t_nodo *aux;
    if(!*l)
        return LISTA_VACIA;
    aux=*l;
    *info=aux->info;
    *l=aux->sig;
    free(aux);
    return TODO_BIEN;

}

/// M E R G E ///
void actualizaCuentas(FILE* pc, t_lista *l)
{
    t_cuenta cta;
    t_movimiento mov;

    FILE*temp;
    temp=abrirArch("temporal.tmp","wb");
    pc=abrirArch(FCUENTAS,"r+b");

    fread(&cta,sizeof(t_cuenta),1,pc);
    ///sacarPrimeroLista(l,&mov); no iría porque el puntero ya esta al principio

    int cmp;

    while(*l!=NULL && !feof(pc))
    {
        cmp=strcmp(cta.nrocuenta, (*l)->info.nrocuenta);
        if(cmp==0)
        {
            cta.saldo+=(*l)->info.importe;
            sacarPrimeroLista(l,&mov);
            //fwrite(&cta,sizeof(t_cuenta),1,temp);
        }

        if(cmp<0)
        {
            fwrite(&cta,sizeof(t_cuenta),1,temp);
            fread(&cta,sizeof(t_cuenta),1,pc);
        }

        if(cmp>0)
            return;
    }
//    fseek(pc,sizeof(t_cuenta),SEEK_CUR);
    fwrite(&cta,sizeof(t_cuenta),1,temp);
    fclose(temp);
    fclose(pc);
    remove(FCUENTAS);
    rename("temporal.tmp",FCUENTAS);

}
