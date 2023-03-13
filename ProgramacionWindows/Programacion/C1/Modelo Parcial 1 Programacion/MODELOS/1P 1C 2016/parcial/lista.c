#include<lista.h>
#include<stdlib.h>
#include<stdio.h>

int insertar_prim5_lista(t_lista * plista, const t_info * pinfo, int (*comp)(const t_info *, const t_info*))
{

}

int comparar(const t_info * dato1,const t_info *dato2)
{
    return dato1->saldo-dato2->saldo;
}
