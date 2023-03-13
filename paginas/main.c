#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * fp;
    int carillas = 0;
    int i = 0;
    int j = 0;
    int k =0;
    int h = 1;
    int flag =0;
    int cantHojas =0;

    int * vec;

    fp = fopen("ordenImpresionManga.txt","wt");
    if(!fp)
    {
        fprintf(stderr,"ERROR AL CREAR EL ARCHIVO DE TEXTO");
        return 1;
    }

    printf("Ingrese el numero de paginas a imprimir: ");
    scanf("%d", &carillas);
    cantHojas = carillas/4;


    vec = (int*) calloc(carillas,sizeof(int));




    for (; i<carillas ; i+=2 )
    {
        if(flag == 0)
        {
            vec[i]=j+1;

            vec[i+1] = carillas-j;
            flag =1;
        }
        else if(flag != 0)
        {
            vec[i]= carillas-j;

            vec[i+1] = j+1;
            flag =0;
        }


        j++;
    }

    for (k =0; k<carillas ; k++ )
    {
        if(k != 0 && k%4 == 0)
        {
            fprintf(fp,"  hoja %d\n",h);
            h++;
        }
        fprintf(fp,"%d ",vec[k]);

    }
        fprintf(fp,"  hoja %d\n",h);
        fprintf(stdout,"  hoja %d\n",h);
   fprintf(fp,"\nCantidad de hojas: %d",cantHojas);
 fprintf(stdout,"\nCantidad de hojas: %d",cantHojas);

    free(vec);
    fclose(fp);
    return 0;
}
