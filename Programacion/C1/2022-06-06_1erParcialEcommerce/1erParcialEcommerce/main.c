#include <stdio.h>
#include "../Solucion1erParcialEcommerce/Solucion1erParcialEcommerce.h"
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#include "../TDALista/TDALista.h"
#include <string.h>
#include<stdbool.h>
#define ARG_CLIENTES    1
#define ARG_PRODUCTOS   2
#define ARG_REGLAS      3
#define ARG_OFERTAS     4


int parsearCadena(const char * linea, Regla *regla);
int compararNivel(const void *r1, const void *r2);

int main(int argc, char* argv[])
{
    generarArchivoClientes(argv[ARG_CLIENTES]);
    generarArchivoProductos(argv[ARG_PRODUCTOS]);
    generarArchivoReglas(argv[ARG_REGLAS]);

//   generarArchivoOfertas(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS], argv[ARG_REGLAS], argv[ARG_OFERTAS]);
    generarArchivoOfertas_ALU(argv[ARG_CLIENTES], argv[ARG_PRODUCTOS], argv[ARG_REGLAS], argv[ARG_OFERTAS]);

    if(mostrarArchivoOfertas(argv[ARG_OFERTAS]) != TODO_OK)
        printf("\n\nError al mostrar el archivo de ofertas.\n");

    char nombreArchivoOfertasTxt[251];
    cambiarExtension(argv[ARG_OFERTAS], nombreArchivoOfertasTxt, ".txt");

//  generarArchivoOfertasTxt(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);
    generarArchivoOfertasTxt_ALU(argv[ARG_OFERTAS], nombreArchivoOfertasTxt);

    if(mostrarArchivoOfertasTxt(nombreArchivoOfertasTxt))
        printf("\n\nError al mostrar el archivo de ofertas txt.\n");

    return 0;
}


int generarArchivoOfertas_ALU(const char* nombreArchClientes, const char* nombreArchProductos, const char* nombreArchReglas, const char* nombreArchOfertas)
{
    FILE * archClientes = fopen(nombreArchClientes,"rb");
    FILE * archProductos = fopen(nombreArchProductos,"rb");
    FILE * archReglas = fopen(nombreArchReglas,"rt");
    FILE * archOfertas = fopen(nombreArchOfertas, "wb");

    if(!archClientes)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE CLIENTES EN LECTURA");
        return -1;
    }
    if(!archProductos)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE PRODUCTOS EN LECTURA");
        return -1;
    }
    if(!archReglas)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE REGLAS EN LECTURA");
        return -1;
    }
    if(!archOfertas)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE OFERTAS EN ESCRITURA");
        return -1;
    }

    // OBTENEMOS LA LISTA DE REGLAS
    Lista lRegla;
    crearLista(&lRegla);
    Regla regla;
    char linea[45];
    fgets(linea, 45, archReglas);
    while(fgets(linea,45,archReglas) && !listaLlena(&lRegla,sizeof(Regla)))
    {
        parsearCadena(linea,&regla);
        insertarEnListaOrd(&lRegla,&regla,sizeof(Regla),compararNivel);
    }
    // FIN DE OBTENER LA LISTA DE REGLAS

    //CREAMOS LOS DESCUENTSO PARA CADA USUARIO POR CADA PRODUCTO SEGUN SU NIVEL
    Cliente cliente;
    Producto prod;
    Oferta oferta;

    fread(&cliente,sizeof(Cliente),1,archClientes);
    while(!(feof(archClientes)))
    {
        Regla reglaCliente = {cliente.nivel,0,0,0};
        buscarEnListaOrd(&lRegla,&reglaCliente,sizeof(Regla),compararNivel);
        fread(&prod,sizeof(Producto),1,archProductos);
        while(!feof(archProductos))
        {

            strncpy(oferta.usuario,cliente.usuario,21);
            strncpy(oferta.producto,prod.codigo,16);

            float descuento = (prod.precio * reglaCliente.porcDescuento) /100 > reglaCliente.topeDescuento? reglaCliente.topeDescuento:(prod.precio * reglaCliente.porcDescuento) /100;

            float precioProdDescontado = prod.precio - descuento;

            bool EnvioGratis = precioProdDescontado>= reglaCliente.minimoParaEnvioGratis;

            oferta.precio = precioProdDescontado;
            oferta.envioGratis = EnvioGratis;

            fwrite(&oferta,sizeof(Oferta),1,archOfertas);
            fread(&prod,sizeof(Producto),1,archProductos);

        }
        fread(&cliente,sizeof(Cliente),1,archClientes);
        rewind(archProductos);
    }
    // FIN DE CREAMOS LOS DESCUENTSO PARA CADA USUARIO POR CADA PRODUCTO SEGUN SU NIVEL

    vaciarLista(&lRegla);
    fclose(archClientes);
    fclose(archOfertas);
    fclose(archProductos);
    fclose(archReglas);
    return TODO_OK;
}



int generarArchivoOfertasTxt_ALU(const char* nombreArchivoOfertas, const char* nombreArchivoOfertasTxt)
{
    FILE * archOfertas = fopen(nombreArchivoOfertas,"rb");
    FILE * archOfertasTxt = fopen(nombreArchivoOfertasTxt, "wt");


    if(!archOfertas)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE OFERTAS EN LECTURA");
        return -1;
    }

    if(!archOfertasTxt)
    {

        fprintf(stderr,"ERROR AL ABRIR EL ARCHIVO DE OFERTAS DE TEXTO EN ESCRITURA");
        return -1;
    }
    //fprintf(archOfertasTxt,"ofertas texto\n ===============\n");
    Oferta oferta;
    fread(&oferta,sizeof(Oferta),1,archOfertas);
    char usuario[21]="\0";
    strncpy(usuario,oferta.usuario,21);
    while(!feof(archOfertas))
    {
        if(strcmp(usuario,oferta.usuario)!= 0)
        {
            strncpy(usuario,oferta.usuario,21);
            fprintf(archOfertasTxt, "%-21s\n",usuario);

        }
        char *envio_gratis = oferta.envioGratis ? "Si" : "No";
        fprintf(archOfertasTxt, "\t%-15s%15.2f\t%s\n", oferta.producto,
                oferta.precio, envio_gratis);
        fread(&oferta, sizeof(Oferta), 1, archOfertas);

    }

    fclose(archOfertas);
    fclose(archOfertasTxt);
    return TODO_OK;
}

int parsearCadena(const char * linea, Regla *regla)
{
    char * car = strrchr(linea,'\n');
    if(!car)
        return -2;

    // BUSCAMOS FLOAT MINIMO PARA ENVIO GRATIS
    *car = '\0';
    car = strrchr(linea,'\t');
    sscanf(car+1,"%f",&regla->minimoParaEnvioGratis);

    // BUSCAMOS FLOAT TOPE DE DESCUENTO
    *car = '\0';
    car = strrchr(linea,'\t');
    sscanf(car+1,"%f",&regla->topeDescuento);

    // BUSCAMOS FLOAT PORCENTAJE DE DESCUENTO
    *car = '\0';
    car = strrchr(linea, '\t');
    sscanf(car+1,"%f", &regla->porcDescuento);

    // BUSCAMOS ENTERO NIVEL
    *car = '\0';
    sscanf(linea,"%d",&regla->nivel);

    return TODO_OK;

}

int compararNivel(const void *r1, const void *r2)
{
    const Regla * regla1 = (const Regla *)r1;
    const Regla * regla2 = (const Regla *)r2;

    return regla1->nivel-regla2->nivel;
}
