#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char cod;
    char nombre[20];
    int stock;
} Producto;

typedef struct
{
    char cod;
    int stock;
} Movimiento;

typedef int(*Cmp)(const void* elem1, const void* elem2);
typedef void(*Parseo)(char* cad, void* reg);
typedef void(*Actualizar)(void* elemActualizado, const void* elemActualizador);
typedef void(*Conversor)(void* elemActualizado,const void* elemActualizador);

void crearArchAAct();
void crearArchMov();
void actualizarArchivos(const char* nomArchActualizado, const char* nomArchActualizador,
                        const char* nomArchFinal,unsigned tamActualizado,
                        unsigned tamActualizador, Cmp cmp, Parseo parseo,
                        Actualizar actualizar, Conversor conversor);
int compararCodigo(const void* elem1, const void* elem2);
void parseoActualizado(char* cad, void* reg);
void actualizarProducto(void* elemActualizado, const void* elemActualizador);
void mostrarArchivoFinal(const char* nomArch);
void conversorMovAProd(void* elemActualizado, const void* elemActualizador);

int main()
{
    crearArchAAct();
    crearArchMov();
    actualizarArchivos("actualizado.txt","actualizador.dat","Final.dat",
                       sizeof(Producto),sizeof(Movimiento),compararCodigo,
                       parseoActualizado,actualizarProducto,conversorMovAProd);
    mostrarArchivoFinal("Final.dat");
    return 0;
}




void mostrarArchivoFinal(const char* nomArch)
{
    FILE *pf = fopen(nomArch,"rb");
    Producto regProd;
    if(!pf)
    {
        puts("Error al abrir el archivo");
        fclose(pf);
        return;
    }

    fread(&regProd,sizeof(Producto),1,pf);

    while(!feof(pf))
    {
        printf("Codigo = %c Nombre = %s Stock = %d\n",regProd.cod,regProd.nombre,regProd.stock);
        fread(&regProd,sizeof(Producto),1,pf);
    }

    fclose(pf);
}

int compararCodigo(const void* elem1, const void* elem2)
{
    Producto *prod = (Producto*)elem1;
    Movimiento *mov = (Movimiento*)elem2;

    return prod->cod-mov->cod;
}

void crearArchAAct()
{
    FILE *pf = fopen("actualizado.txt","wt");
    int i = 0;
    Producto vecProd[] =
    {
        {'A',"Arvejas",5},
        {'B',"Banana",15},
        {'C',"Caracoles",23},
        {'F',"Fideos",30},
        {'H',"Harina",10},
        {'Y',"Yerba Mate",35},
        {'X',"Xavier",1},
    };

    if(!pf)
    {
        puts("No se pudo crear el archivo");
        fclose(pf);
        return;
    }

    for(; i < 7; i++)
        fprintf(pf,"%c|%s|%d\n",vecProd[i].cod,vecProd[i].nombre,vecProd[i].stock);

    fclose(pf);
}

void crearArchMov()
{
    FILE *pf = fopen("actualizador.dat","wb");
    Movimiento vecMov[] =
    {
        {'A', 5},
        {'A',-10},
        {'B',15},
        {'B',30},
        {'C',-3},
        {'C',20},
        {'F',20},
        {'R',10},
        {'R',1000},
        {'Y',15},
        {'Z',12},
    };
    if(!pf)
    {
        puts("No se pudo crear el archivo");
        fclose(pf);
        return;
    }

    fwrite(vecMov,sizeof(Movimiento),11,pf);

    fclose(pf);
}

void parseoActualizado(char* cad, void* reg)
{
    Producto* regProd = (Producto*)reg;

    char* aux = strrchr(cad,'\n');
    if(!aux)
        return;
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;
    sscanf(aux,"%d",&regProd->stock);
    aux--;
    *aux = '\0';

    aux = strrchr(cad,'|');
    aux++;
    strncpy(regProd->nombre,aux,20);
    aux--;
    *aux = '\0';

    regProd->cod = *cad;

    memcpy(reg,regProd,sizeof(Producto));
}

void actualizarProducto(void* elemActualizado, const void* elemActualizador)
{
    Producto *actualizado = (Producto*)actualizado;
    Movimiento *actualizador = (Movimiento*)actualizador;

    actualizado->stock+=actualizador->stock;
}

void conversorMovAProd(void* elemActualizado,const void* elemActualizador)
{
    Producto* actualizado = (Producto*)elemActualizado;
    Movimiento* actualizador = (Movimiento*)elemActualizador;

    actualizado->cod = actualizador->cod;
    actualizado->stock = 0;
    strcpy(actualizado->nombre," ");
}

void actualizarArchivos(const char* nomArchActualizado, const char* nomArchActualizador,
                        const char* nomArchFinal,unsigned tamActualizado,
                        unsigned tamActualizador, Cmp cmp, Parseo parseo,
                        Actualizar actualizar, Conversor conversor)
{
    FILE *pfActualizado = fopen(nomArchActualizado,"rt");
    FILE *pfActualizador = fopen(nomArchActualizador,"rb");
    FILE *pfFinal = fopen(nomArchFinal,"wb");
    void* regActualizado = malloc(tamActualizado);
    void* regActualizador = malloc(tamActualizador);
    char cadReg[50];
    char* codError;

    if(!pfActualizado || !pfActualizador || !pfFinal)
    {
        puts("No se pudieron abrir los archivos");
        fclose(pfActualizado);
        fclose(pfActualizador);
        fclose(pfFinal);
        return;
    }

    codError = fgets(cadReg,sizeof(cadReg),pfActualizado);
    fread(regActualizador,tamActualizador,1,pfActualizador);

    while(!feof(pfActualizador) && codError)
    {
        parseo(cadReg,regActualizado);
        if(cmp(regActualizado,regActualizador) == 0)
        {
            while(!feof(pfActualizador) && cmp(regActualizado,regActualizador) == 0)
            {
                actualizar(regActualizado,regActualizador);
                fread(regActualizador,tamActualizador,1,pfActualizador);
            }
            fwrite(regActualizado,tamActualizado,1,pfFinal);
            codError = fgets(cadReg,sizeof(cadReg),pfActualizado);
        }
        else if(cmp(regActualizado,regActualizador) > 0)
        {
            void* auxActualizado = malloc(tamActualizado);
            conversor(auxActualizado,regActualizador);
            while(!feof(pfActualizador) && cmp(auxActualizado,regActualizador) == 0)
            {
                actualizar(auxActualizado,regActualizador);
                fread(regActualizador,tamActualizador,1,pfActualizador);
            }
            fwrite(auxActualizado,tamActualizado,1,pfFinal);
            free(auxActualizado);
        }
        else
        {
            fwrite(regActualizado,tamActualizado,1,pfFinal);
            codError = fgets(cadReg,sizeof(cadReg),pfActualizado);
        }
    }

    while(!feof(pfActualizador))
    {
        void* auxActualizado = malloc(tamActualizado);
        conversor(auxActualizado,regActualizador);
        while(!feof(pfActualizador) && cmp(auxActualizado,regActualizador) == 0)
        {
            actualizar(auxActualizado,regActualizador);
            fread(regActualizador,tamActualizador,1,pfActualizador);
        }
        fwrite(auxActualizado,tamActualizado,1,pfFinal);
        free(auxActualizado);
    }

    while(fgets(cadReg,sizeof(cadReg),pfActualizado))
    {
        parseo(cadReg,regActualizado);
        fwrite(regActualizado,tamActualizado,1,pfFinal);
    }

    free(regActualizado);
    free(regActualizador);

    fclose(pfActualizado);
    fclose(pfActualizador);
    fclose(pfFinal);
}
