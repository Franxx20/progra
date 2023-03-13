#include <biblioteca.h>
#include <utilitarias.h>
#include <string.h>
#include <lista.h>

#define ISNUM(x) ('0' <= (x) && (x) <= '9')

void actualizar_stock(FILE * arch_libros, FILE * arch_stock, FILE * arch_err)
{
    rewind(arch_libros);
    rewind(arch_stock);

    size_t tamStock = sizeof(t_libro_stock);
    char linea[tamStock];
    t_libro_stock libroStock;
    t_libro libro;

    fread(&libro,sizeof(t_libro),1,arch_libros);
    fgets(linea,tamStock,arch_stock);
    texto_a_stock(linea,&libroStock);

    while (!feof(arch_libros) && !feof(arch_stock))
    {
        while (!isbn_valido(libroStock.isbn))
        {
            fprintf(arch_err,"%18s, %1d - %s",libroStock.isbn,libroStock.stock,"ERROR DE IBSN");
            fgets(linea,tamStock,arch_stock);
            texto_a_stock(linea,&libroStock);
        }
        if (cmp_stock_libro(&libro,&libroStock))
        {
            libro.stock+=libroStock.stock;
            fseek(arch_libros,-1L * sizeof(t_libro),SEEK_CUR);
            fwrite(&libro,sizeof(t_libro),1,arch_libros);
            fseek(arch_libros,0L,SEEK_CUR);

            fread(&libro,sizeof(t_libro),1,arch_libros);
        }
        else
        {
            fprintf(arch_err,"%18s, %1d - %s",libroStock.isbn,libroStock.stock,"LIBRO INEXISTENTE");

            fgets(linea,tamStock,arch_stock);
            texto_a_stock(linea,&libroStock);
        }

        fread(&libro,sizeof(t_libro),1,arch_libros);
        fgets(linea,tamStock,arch_stock);
        texto_a_stock(linea,&libroStock);
    }
}
int isbn_valido(const char * isbn)
{
    int dig, pares=0, impares=0, band=0;
    char d;

    while (*isbn)
    {
        sscanf(isbn,"%c",&d);
        if (ISNUM(d))
        {
            dig = d - '0';
            if (band==0)
            {
                impares+=dig;
                band=1;
            }
            if (band==1)
            {
                pares+=dig;
                band=0;
            }
        }
        else
            isbn++;

        isbn++;
    }
    return ((impares + 3*pares)% 10 == 0)? 1 : 0;
}
int cmp_stock_libro(const t_libro * l1, const t_libro_stock * l2)
{
    return strcmp(l1->isbn,l2->isbn);
}
