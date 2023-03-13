
/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:   My Tomás

* DNI: 43.669.624

***************************************************************************************/

#include <iostream>
#include <string.h>

using namespace std;

class Cadena
{
    private:
        char* cadena;

    public:
        Cadena();
        Cadena(const char* str);
        ~Cadena();

        char* getCadena();

        Cadena& operator =(const char* str);

        friend ostream& operator <<(ostream& output, const Cadena& cad1);
};

Cadena::Cadena(){
    cadena = new char[1];
    cadena[0]= '\0';
}

Cadena::Cadena(const char* str){

    this->cadena = new char[strlen(str)+1];
    strcpy(this->cadena,str);
}

Cadena::~Cadena(){
    delete [] this->cadena;
}

char* Cadena::getCadena()
{
    return this->cadena;
}

Cadena& Cadena::operator =(const char* str){

    if(strlen(this->cadena)!=strlen(str)){
        delete [] this->cadena;
        this->cadena = new char[strlen(str)+1];
    }

    strcpy(this->cadena,str);

    return *this;
}

ostream& operator <<(ostream& output,const Cadena& cad1)
{
    return output << cad1.cadena;
}

class Producto
{
    private:
        Cadena codigo, descripcion;
        float precio;
        int stock;

    public:
        Producto();
        Producto(Cadena cod, Cadena des, float pre, int sto);

        void setCodigo(Cadena cad);
        void setDescripcion(Cadena cad);
        void setPrecio(float pre);
        void setStock(int sto);

        Cadena getCodigo();
        Cadena getDescripcion();
        float getPrecio();
        int getStock();

        Producto& operator +=(int cant);
        friend Producto operator +(int x , Producto& producto);

        friend ostream& operator <<(ostream& output, Producto producto);
};

Producto::Producto()
{
    this->codigo = "";
    this->descripcion = "";
    this->precio = 0;
    this->stock = 0;
}

Producto::Producto(Cadena cod, Cadena des, float pre, int sto)
{
    this->codigo = cod.getCadena();
    this->descripcion = des.getCadena();
    this->precio = pre;
    this->stock = sto;
}

void Producto::setCodigo(Cadena cad)
{
    this->codigo = cad;
}
void Producto::setDescripcion(Cadena cad)
{
    this->descripcion = cad;
}

void Producto::setPrecio(float pre)
{
    this->precio = pre;
}
void Producto::setStock(int sto)
{
    this->stock = sto;
}

Cadena Producto::getCodigo()
{
    return this->codigo;
}

Cadena Producto::getDescripcion()
{
    return this->descripcion;
}

float Producto::getPrecio()
{
    return this->precio;
}

int Producto::getStock()
{
    return this->stock;
}

Producto& Producto::operator +=(int cant)
{
    this->stock += cant;
    return *this;
}

Producto operator +(int x , Producto& producto)
{
    Producto res = producto;
    res += x;
    return res;
}

ostream& operator <<(ostream& output, Producto producto)
{
    return output << "Codigo: " << producto.codigo << '\n' << "Descripcion: " << producto.descripcion << '\n' << "Precio: " << producto.precio << '\n' << "Stock: " << producto.stock << '\n';
}

class ProductoConDescuento : public Producto
{
    private:
        float descuento;

    public:
        ProductoConDescuento();
        ProductoConDescuento(Cadena cod, Cadena des, float pre, int sto, float desc);

        friend ProductoConDescuento operator +(int x , ProductoConDescuento& prod);

        friend ostream& operator <<(ostream& output, ProductoConDescuento producto);
};

ProductoConDescuento::ProductoConDescuento()
{
    this->setCodigo("");
    this->setDescripcion("");
    this->setPrecio(0);
    this->setStock(0);
    this->descuento = 0;
}

ProductoConDescuento::ProductoConDescuento(Cadena cod, Cadena des, float pre, int sto, float desc)
{
    this->setCodigo(cod);
    this->setDescripcion(des);
    this->setPrecio(pre);
    this->setStock(sto);
    this->descuento = desc;
}

ProductoConDescuento operator +(int x , ProductoConDescuento& prod)
{
    ProductoConDescuento res = prod;
    res.setStock(res.getStock() + x);
    return res;
}

ostream& operator <<(ostream& output, ProductoConDescuento prod)
{
    return output << "Codigo: " << prod.getCodigo() << '\n' << "Descripcion: " << prod.getDescripcion() << '\n' << "Precio: " << prod.getPrecio() << '\n' << "Stock: " << prod.getStock() << '\n' << "Descuento: " << prod.descuento << '\n' << "Precio con descuento: " << prod.getPrecio()- (prod.getPrecio()*prod.descuento /100) << '\n';
}

int main()
{
    Producto p1("123", "Pizza", 10.0, 15);
    Producto p2("456", "Pollo", 20.0, 25);
    ProductoConDescuento p3("789", "Hamburguesa", 30.0, 35, 10);
    ProductoConDescuento p4("012", "Arroz", 40.0, 45, 20);

    p2 += 100;
    ProductoConDescuento p5 = 200 + p3;

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    cout << p4 << endl;
    cout << p5 << endl;

    return 0;
}


/// ARBOL ///


NodoA* crearNodoA(const void* elem,size_t tamElem)
{
    NodoA* nue = malloc(sizeof(NodoA));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);
        return NULL;
    }
    memcpy(elemNodo,elem,tamElem);

    nue->elem=elemNodo;
    nue->tamElem=tamElem;
    nue->hIzq=NULL;
    nue->hDer=NULL;

    return nue;
}

void crearArbol(Arbol* pa)
{
    *pa=NULL;
}

int vaciarArbol(Arbol* pa)
{
    if(!pa)
        return 0;

    vaciarArbol(&(*pa)->hIzq);
    vaciarArbol(&(*pa)->hDer);
    free((*pa)->elem);
    free(*pa);
    *pa = NULL;
    return TODO_OK;
}

//Producto producto;
bool buscarEnArbol(const Arbol* pa,void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pa)
        return false;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        memcpy(elem,(*pa)->elem,min((*pa)->tamElem,tamElem));
        return true;
    }

    if(comp < 0)
    {
        return buscarEnArbol(&(*pa)->hIzq,elem,tamElem,cmp);
    }
    else
        return buscarEnArbol(&(*pa)->hDer,elem,tamElem,cmp);
}

int insertarEnArbolSinDup(Arbol* pa, void* elem,size_t tamElem,Cmp cmp, Actualizar actualizar)
{
    if(!*pa)
    {
        *pa=crearNodoA(elem,tamElem);
        if(!*pa)
            return SIN_MEM;
        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        actualizar((*pa)->elem,elem);
        return DUPLICADO;
    }

    return insertarEnArbolSinDup(comp<0 ? &(*pa)->hIzq : &(*pa)->hDer,elem,tamElem,cmp,actualizar);
}

int insertarEnArbol(Arbol* pa, void* elem,size_t tamElem,Cmp cmp)
{
    if(!*pa)
    {
        *pa=crearNodoA(elem,tamElem);
        if(!*pa)
            return SIN_MEM;
        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    return insertarEnArbol(comp<0 ? &(*pa)->hIzq : &(*pa)->hDer,elem,tamElem,cmp);
}

bool eliminarDeArbol(Arbol* pa, void* elem, size_t tamElem,Cmp cmp)
{
    Arbol* pnae=buscarNodoA(pa,elem,cmp);

    if(!pnae)
        return false;

    memcpy(elem, (*pnae)->elem, min(tamElem, (*pnae)->tamElem));
    free((*pnae)->elem);

    eliminarNodoA(pnae);
    return true;
}

Arbol* buscarNodoA(Arbol* pa,void* elem,Cmp cmp)
{
    if(!*pa)
        return NULL;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
        return pa;

    if(comp < 0)
    {
        return buscarNodoA(&(*pa)->hIzq,elem,cmp);
    }
    else
        return buscarNodoA(&(*pa)->hDer,elem,cmp);
}

void eliminarNodoA(Arbol* pnae)
{
    if(!(*pnae)->hIzq && !(*pnae)->hDer)
    {
        free(*pnae);
        *pnae=NULL;
        return;
    }
    int hi= alturaArbol(&(*pnae)->hIzq);
    int hd= alturaArbol(&(*pnae)->hDer);

    Arbol* pNodoRmp;
    if(hi>=hd)
        pNodoRmp=nodoMayorA(&(*pnae)->hIzq);
    else
        pNodoRmp=nodoMenorA(&(*pnae)->hDer);

    (*pnae)->elem = (*pNodoRmp)->elem;
    (*pnae)->tamElem = (*pNodoRmp)->tamElem;

    eliminarNodoA(pNodoRmp);
}

Arbol* nodoMenorA(Arbol* pa)
{
    while((*pa)->hIzq)
        pa=&(*pa)->hIzq;

    return pa;
}

Arbol* nodoMayorA(Arbol* pa)
{
    while((*pa)->hDer)
        pa=&(*pa)->hDer;

    return pa;
}

int alturaArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;
    int hi=alturaArbol(&(*pa)->hIzq);
    int hd=alturaArbol(&(*pa)->hDer);

    return ((hi>hd ? hi:hd)+1);
}

int podarArbol(Arbol* pa, int nivel) //él mismo incluido
{
    if(!*pa)
        return 0;
    if(nivel==0)
        return vaciarArbol(pa);
return podarArbol(&(*pa)->hIzq,nivel-1)+
       podarArbol(&(*pa)->hDer,nivel-1);
}

int contarNodosArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;
    return contarNodosArbol(&(*pa)->hIzq)+
           contarNodosArbol(&(*pa)->hDer)+1;
}

//RID-> preOrden / IRD-> EnOrden / IDR->posOrden
void recorrerArbolPre(Arbol* pa, Accion accion, void* dAcc)
{
    if(!*pa)
        return;
    accion((*pa)->elem,dAcc); //R
    recorrerArbolPre(&(*pa)->hIzq,accion,dAcc); //I
    recorrerArbolPre(&(*pa)->hDer,accion,dAcc); //D
}

void recorrerArbolEn(Arbol* pa, Accion accion, void* dAcc)
{
    recorrerArbolEn(&(*pa)->hIzq,accion,dAcc); //I
    accion((*pa)->elem,dAcc); //R
    recorrerArbolEn(&(*pa)->hDer,accion,dAcc); //D
}

void recorrerArbolPos(Arbol* pa, Accion accion, void* dAcc)
{
    recorrerArbolPos(&(*pa)->hIzq,accion,dAcc); //I
    recorrerArbolPos(&(*pa)->hDer,accion,dAcc); //D
    accion((*pa)->elem,dAcc); //R
}

//cantReg=12
void cargarArchivoEnArbol(FILE* arch,Arbol* pa,Cmp cmp,size_t tamElem)
{
    if(!pa || !arch)
        return;
    fseek(arch,0L,SEEK_END);
    int cantReg = ftell(arch)/tamElem;
    int li = 0;
    int ls = cantReg - 1;
    cargarArbolRec(arch,pa,tamElem,cmp,li,ls);
}

void cargarArbolRec(FILE* arch,Arbol* pa,size_t tamElem,Cmp cmp,int li,int ls)
{
    if(li > ls)
        return;
    int m = (li+ls)/2;
    void* elem=malloc(tamElem);
    fseek(arch,m*tamElem,SEEK_SET);
    fread(elem,tamElem,1,arch);
    insertarEnArbol(pa,elem,tamElem,cmp);
    cargarArbolRec(arch,pa,tamElem,cmp,li,m-1); //insPorIzq
    cargarArbolRec(arch,pa,tamElem,cmp,m+1,ls); //insPorDer
}

void actualizarProd(void* e1, const void* e2)
{
    Producto* p1 = (Producto*)e1;
    Producto* p2 = (Producto*)e2;
    p1->stock += p2->stock;
    if(p1->precio < p2->precio)
        p1->precio=p2->precio;
    return;
}

int compProd(const void* e1, const void* e2)
{
    Producto* p1 = (Producto*)e1;
    Producto* p2 = (Producto*)e2;
    return strcmp(p1->codigo,p2->codigo);
}

int compInt(const void* e1, const void* e2)
{
    int* p1 = (int*)e1;
    int* p2 = (int*)e2;
    return *p1 - *p2;
}

void graficarArbol(const Arbol* pa,MostrarElemArbol mostrarElemArbol)
{
    graficarArbolRec(pa,mostrarElemArbol,0);
}

void graficarArbolRec(const Arbol* pa, MostrarElemArbol mostrarElemArbol,int nivel)
{
    if(!*pa)
        return;

    graficarArbolRec(&(*pa)->hDer, mostrarElemArbol,nivel+1);
    mostrarElemArbol((*pa)->elem, nivel);
    graficarArbolRec(&(*pa)->hIzq, mostrarElemArbol, nivel+1);
}

void mostrarInt(const void* elem, int nivel)
{
    for(int i=0; i < nivel; i++)
        printf("            ");
    printf("%d\n", *(int*)elem);
}

bool esArbolCompleto(const Arbol* pa)
{
    int altura = alturaArbol(pa);

    int cantNodosPrevistos = pow(2,altura) - 1;
    int cantNodosReales = contarNodosArbol(pa);
    if(cantNodosPrevistos==cantNodosReales)
        return true;
    else return false;
}

bool esArbolAVL(const Arbol* pa)
{
    if(!*pa)
        return true;

    if(ABSS(    (alturaArbol(&(*pa)->hIzq) - alturaArbol(&(*pa)->hDer))     ) > 1)
        return false;

    return (esArbolAVL(&(*pa)->hIzq) && esArbolAVL(&(*pa)->hDer));
}

/// MODELO C ///
void actualizarFacturas_ALU(const char* nombreArchFactAuto, const char* nombreArchParche, const char* nombreArchFactInex) {
    FILE* pfParche=fopen(nombreArchParche,"rb");
    FILE* pfFacturas=fopen(nombreArchFactAuto,"rb+");
    FILE* pfInex=fopen(nombreArchFactInex,"wb");
    char nombreArchIndice[200];
    generarPathIndice_alu(nombreArchIndice,nombreArchFactAuto);
    if(!pfParche||!pfFacturas||!pfInex) {
        fclose(pfParche);
        fclose(pfFacturas);
        fclose(pfInex);
        return;///No se encontro el archivo
    }
    Arbol arbolFacturas;
    crearArbol_alu(&arbolFacturas);
    cargarArbolDeArchivoOrdenado(&arbolFacturas,sizeof(IndFactura),nombreArchIndice);
    Lista listaParche;
    crearLista_alu(&listaParche);

    ParcheFacturaAutomotor lecturaParche;
    IndFactura busquedaIndice;
    FacturaAutomotor actualizadorFacturas;

    fread(&lecturaParche,sizeof(ParcheFacturaAutomotor),1,pfParche);
    while(!feof(pfParche)) {
        busquedaIndice.cuota=lecturaParche.cuota;
        strcpy(busquedaIndice.patente,lecturaParche.patente);

        booleano res=buscarEnArbol(&arbolFacturas,&busquedaIndice,sizeof(IndFactura),compararIndices_alu);
        if(res==falso||(res==verdadero&&(busquedaIndice.nroRegistro==-1))) {
            eliminarDeArbol(&arbolFacturas,&busquedaIndice,sizeof(IndFactura),compararIndices_alu);
            insertarEnListaOrd(&listaParche,&lecturaParche,sizeof(ParcheFacturaAutomotor),compararParche_alu);
        } else {
            fseek(pfFacturas,busquedaIndice.nroRegistro*sizeof(FacturaAutomotor),SEEK_SET);
            fread(&actualizadorFacturas,sizeof(FacturaAutomotor),1,pfFacturas);
            actualizadorFacturas.importeAPagar+=lecturaParche.importeAdicionalAPagar;
            fseek(pfFacturas,busquedaIndice.nroRegistro*sizeof(FacturaAutomotor),SEEK_SET);
            fwrite(&actualizadorFacturas,sizeof(FacturaAutomotor),1,pfFacturas);
        }
        fread(&lecturaParche,sizeof(ParcheFacturaAutomotor),1,pfParche);
    }
    while(!listaVacia_alu(&listaParche)) {
        eliminarDeListaPrimero_alu(&listaParche,&lecturaParche,sizeof(ParcheFacturaAutomotor));
        fwrite(&lecturaParche,sizeof(ParcheFacturaAutomotor),1,pfInex);
    }
    vaciarArbol(&arbolFacturas);
    vaciarLista(&listaParche);
    fclose(pfParche);
    fclose(pfFacturas);
    fclose(pfInex);
    return;
}
void generarPathIndice_alu(char*pathIndice,const char*pathBase) {
    strcpy(pathIndice,pathBase);
    pathIndice=strchr(pathIndice,'.');
    strcpy(pathIndice,".idx");
}
int compararIndices_alu(const void*ind1,const void*ind2) {
    IndFactura* cInd1=(IndFactura*)ind1;
    IndFactura* cInd2=(IndFactura*)ind2;
    int res=strcmp(cInd1->patente,cInd2->patente);
    if(res==0)
        res=cInd1->cuota-cInd2->cuota;
    return res;
}
int compararParche_alu(const void* parch1, const void*parch2) {
    ParcheFacturaAutomotor* cParch1=(ParcheFacturaAutomotor*)parch1;
    ParcheFacturaAutomotor* cParch2=(ParcheFacturaAutomotor*)parch2;
    int res=strcmp(cParch1->patente,cParch2->patente);
    if(res==0)
        res=cParch1->cuota-cParch2->cuota;
    return res;
}
void crearLista_alu(Lista*pLis) {
    *pLis=NULL;
}
booleano listaVacia_alu(Lista*pLis) {
    return *pLis==NULL;
}
void eliminarDeListaPrimero_alu(Lista*pLis,void* elem, size_t tamElem) {
    if(!*pLis)
        return;
    while((*pLis)->ant)
        *pLis=(*pLis)->ant;///Me posiciono al principio
    NodoD* siguiente=(*pLis)->sig;
    memcpy(elem,(*pLis)->elem,MIN(tamElem,(*pLis)->tamElem));
    free((*pLis)->elem);
    free(*pLis);
    if(siguiente)
        siguiente->ant=NULL;
    *pLis=siguiente;
}

void crearArbol_alu(Arbol*pArb) {
    *pArb=NULL;
}
booleano eliminarDeArbol_alu(Arbol*pArb,void* elem, size_t tamElem,Cmp criterio) {///No funciona, utilizo la de la libreria en el main

    if(!*pArb)
        return falso;///No encontrado o ya eliminado
    int res=criterio(elem,(*pArb)->elem);
    if(res==0) {
        memcpy(elem,(*pArb)->elem,MIN(tamElem,(*pArb)->tamElem));
        free((*pArb)->elem);
        return verdadero;
    }
    if(res<0) {
        res=eliminarDeArbol(&(*pArb)->hIzq,elem,tamElem,criterio);
        if(res==verdadero) {
            NodoA*izq, *izqDeizq,*der;
            izq=(*pArb)->hIzq->hIzq;
            izqDeizq=(*pArb)->hIzq->hIzq->hIzq;
            der=(*pArb)->hIzq->hDer;
            (*pArb)->hIzq=izq;
            (*pArb)->hIzq->hIzq=izqDeizq;
            (*pArb)->hIzq->hDer=der;
        }
        return verdadero;
    } else {
        res=eliminarDeArbol(&(*pArb)->hDer,elem,tamElem,criterio);
        if(res==verdadero) {
            NodoA*izq=NULL, *izqDeizq=NULL,*der=NULL;
            if((*pArb)->hIzq) {
                izq=(*pArb)->hIzq->hIzq;
                der=(*pArb)->hIzq->hDer;
            }
            if((*pArb)->hIzq->hIzq)
                izqDeizq=(*pArb)->hIzq->hIzq->hIzq;
            free(*pArb);
            izq->hIzq=izqDeizq;
            izq->hDer=der;
            (*pArb)->hIzq=izq;
        }
        return verdadero;
    }
}
/*
insertarEnArbolDesdeArchivo_alu(&arbolFacturas,nombreArchFactInex,sizeof(IndFactura),compararIndices);
booleano insertarEnArbolDesdeArchivo_alu(Arbol*pArb,const char* pathPF,size_t tamReg,Cmp criterio) {
    FILE* pfReg=fopen(pathPF,"rb");
    if(!pfReg) {
        fclose(pfReg);
        return falso;
    }
    fseek(pfReg,0L,SEEK_END);
    int cantReg=ftell(pfReg)/tamReg;
    cargarArchivoEnArbol_alu(pArb,pfReg,tamReg,criterio,0,cantReg-1);
}
int cargarArchivoEnArbol_alu(Arbol*pArb,FILE*pfReg,size_t tamReg,Cmp criterio, int limInf,int limSup) {
    if(limInf>limSup)
        return TODO_OK;
    if(!(*pArb)) {
        int medio=(limInf+limSup)/2;
        void* registro=malloc(tamReg);
        fseek(pfReg,medio*tamReg,SEEK_SET);
        fread(registro,tamReg,1,pfReg);
        insertarEnArbol_alu(pArb,registro,tamReg,criterio);
    }
    cargarArchivoEnArbol_alu(pArb,pfReg,tamReg,criterio,limInf,medio-1);
    cargarArchivoEnArbol_alu(pArb,pfReg,tamReg,criterio,medio+1,limSup);
}
*/

/// MODELO C++ ///

///MATTER MATIAS ARIEL 43049457
#include <iostream>
#include <math.h>
using namespace std;

class Punto {
  private:
    double x;
    double y;
  public:
    Punto();
    Punto(const double equis,const double yGriega);
    friend ostream& operator<<(ostream& sal,const Punto& puntoSalida);

    double getX()const {
        return x;
    }
    void Setx(double val) {
        x = val;
    }
    double getY() const {
        return y;
    }
    void Sety(double val) {
        y = val;
    }
};
Punto::Punto() {};
Punto::Punto(const double equis,const double yGriega) {
    this->x=equis;
    this->y=yGriega;
}
ostream& operator<<(ostream& sal, const Punto& puntoSalida) {
    sal<<"("<<puntoSalida.getX()<<","<<puntoSalida.getY()<<")";
    return sal;
}

class Recta {
  private:
    Punto punto1;
    Punto punto2;
  public:
    Recta();
    Punto getPunto1() const {
        return punto1;
    }
    Punto getPunto2() const {
        return punto2;
    }
    Recta(Punto puntoNue1,Punto puntoNue2);
    friend ostream& operator<<(ostream& sal, const Recta& rectaSalida);
    Punto operator&&(const Recta r2)const;
    friend double operator -(const Recta rectaDist, const Punto puntoDist);
};
Recta::Recta(Punto puntoNue1,Punto puntoNue2) {
    this->punto1=puntoNue1;
    this->punto2=puntoNue2;
}

ostream& operator<<(ostream& sal, Recta& rectaSalida) {
    sal<<rectaSalida.getPunto1()<<rectaSalida.getPunto2();
    return sal;
}
Punto Recta::operator&&(const Recta r2)const {
    double x1=this->punto1.getX();
    double y1=this->punto1.getY();
    double x2=this->punto2.getX();
    double y2=this->punto2.getY();
    double x3=r2.punto1.getX();
    double y3=r2.punto1.getY();
    double x4=r2.punto2.getX();
    double y4=r2.punto2.getY();

    double primerTermino=((x1*y2)-(y1*x2));
    double segundoTermino=((x3*y4)-(y3*x4));
    double division=(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
    double xRetorno=(primerTermino*(x3-x4))-(((x1-x2)*segundoTermino));
    xRetorno/=division;
    double yRetorno=(primerTermino*(y3-y4))-(((y1-y2)*segundoTermino));
    yRetorno/=division;

    Punto retorno(xRetorno,yRetorno);
    return retorno;

}
double operator -(const Recta rectaDist, const Punto puntoDist) {
    double x0=puntoDist.getX();
    double y0=puntoDist.getY();
    double x1=rectaDist.punto1.getX();
    double y1=rectaDist.punto1.getY();
    double x2=rectaDist.punto2.getX();
    double y2=rectaDist.punto2.getY();
    double numerador=((y2-y1)*x0)-((x2-x1)*y0)+(x2*y1)-(y2*x1);
    if(numerador<0)
        numerador*=-1;
    double primerTermino=y2-y1;
    double segundoTermino=x2-x1;
    double denominador=(pow(primerTermino,2))+(pow(segundoTermino,2));
    denominador=sqrt(denominador);
    return numerador/denominador;
}

int main() {
    Recta r1(Punto(2, 0), Punto(0, 2));
    Recta r2(Punto(1, 0), Punto(1, 2));

    Punto p(2, 2);

    cout << "Punto de Interseccion entre las rectas " << r1 << " y " << r2 << ": " << (r1 && r2) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r1 << ": " << (r1 - p) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r2 << ": " << (r2 - p) << endl;

    return 0;
}

/// C ++ ///
#include "Cuadrado.h"


Cuadrado::Cuadrado(double lado)
: lado(lado)
{}


double Cuadrado::area() const
{
	return lado * lado;
}


double Cuadrado::perimetro() const
{
	return 4 * lado;
}

#ifndef CUADRADO_H
#define CUADRADO_H

#include "Figura.h"


class Cuadrado : public Figura
{
private:
	double lado;

public:
	Cuadrado(double lado);

	double area() const override;
    double perimetro() const override;
};


#endif // CUADRADO_H

/// MODELO FULL ///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SolucionPatentes/SolucionPatentes.h"

#define ARG_ARCH_FACTURAS 1
#define ARG_ARCH_PARCHE	2
#define ARG_ARCH_FACT_INEX 3

#define MIN(X,Y) (X>Y? Y:X)
#define MAX(X,Y) (X>Y? X:Y)

void eliminarDeListaPrimero_ALU(Lista* pl,void* elem, size_t tamElem);
int alturaArbol_ALU(Arbol* pa);
void eliminarRaizDeArbol_ALU(Arbol* pae);
Arbol* buscarRaizDeArbol_ALU(Arbol* pa, void* elem,size_t tamElem,Cmp cmp);
void eliminarDeArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp);
booleano insertarEnListaAlFinal_ALU(Lista* pl,void* elem, size_t tamElem);
booleano buscarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
booleano insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp);
void cargarRegistroMedio_ALU(Arbol* pa,int ini, int fin, size_t tamElem,FILE* pf,Cmp cmp);
void cargarArbolDeArchivoOrdenado_ALU(Arbol* pa,size_t tamElem,const char* archivo,Cmp cmp);
void crearLista_ALU(Lista* pl);
void crearArbol_ALU(Arbol* pa);
void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem);
NodoD* crearNodoD_ALU(void* elem,size_t tamElem);
void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem);
NodoA* crearNodoA_ALU(void* elem,size_t tamElem);
Arbol* menorDeArbol_ALU(Arbol* pa);
Arbol* mayorDeArbol_ALU(Arbol* pa);
booleano listaVacia_ALU(Lista* pl);
void vaciarArbol_ALU(Arbol* pa);


int comparaIndices(const void* i1,const void* i2){

	IndFactura* indice1 = (IndFactura*)i1;
	IndFactura* indice2 = (IndFactura*)i2;

	int compPatente = strcmp(indice1->patente,indice2->patente);
	if(compPatente==0){
		int compCuota = indice1->cuota-indice2->cuota;
		if(compCuota==0){
			return 0;
		}
		return compCuota;
	}
	else{
		return compPatente;
	}

}

int main(int argc, char* argv[])
{
	generarArchivoFacturas();
	generarArchivoPatentesParche();

	puts("Archivo Facturas Automotor");
	mostrarFacturasAuto(argv[ARG_ARCH_FACTURAS]);

	puts("\nArchivo Parche");
	mostrarParche(argv[ARG_ARCH_PARCHE]);

	//actualizarFacturas(argv[ARG_ARCH_FACTURAS], argv[ARG_ARCH_PARCHE], argv[ARG_ARCH_FACT_INEX]);
    actualizarFacturas_ALU(argv[ARG_ARCH_FACTURAS], argv[ARG_ARCH_PARCHE], argv[ARG_ARCH_FACT_INEX]);

	puts("\nArchivo Facturas Automotor actualizado");
	mostrarFacturasAuto(argv[ARG_ARCH_FACTURAS]);

	puts("\nFacturas Inexistentes");
	mostrarParche(argv[ARG_ARCH_FACT_INEX]);

	return 0;
}


void actualizarFacturas_ALU(const char* nombreArchFactAuto, const char* nombreArchParche, const char* nombreArchFactInex){

	int elemEncontrado;
	char nombreArchIndices[21];
	strcpy(nombreArchIndices,nombreArchFactAuto);
	nombreArchIndices[17]='\0';
	strcat(nombreArchIndices,".idx");

	FILE* pfFacturas = fopen(nombreArchFactAuto,"r+b");
	FILE* pfParche = fopen(nombreArchParche,"rb");
	FILE* pfInexistentes = fopen(nombreArchFactInex,"rb");

	if(!pfFacturas || !pfParche || !pfInexistentes){
		return;
	}

	Arbol arbolIndices;
	crearArbol_ALU(&arbolIndices);

	Lista listaErrores;
	crearLista_ALU(&listaErrores);

	cargarArbolDeArchivoOrdenado_ALU(&arbolIndices,sizeof(IndFactura),nombreArchIndices,comparaIndices);

	FacturaAutomotor facturaLeida;
	ParcheFacturaAutomotor parcheLeido;
	IndFactura indiceAux;
	fread(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfParche);
	while(!feof(pfParche)){

		strcpy(indiceAux.patente,parcheLeido.patente);
		indiceAux.cuota=parcheLeido.cuota;
		elemEncontrado = buscarEnArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndFactura),comparaIndices);


		if(elemEncontrado && indiceAux.nroRegistro!=-1){
			fseek(pfFacturas,indiceAux.nroRegistro*sizeof(FacturaAutomotor),SEEK_SET);
			fread(&facturaLeida,sizeof(FacturaAutomotor),1,pfFacturas);
			facturaLeida.importeAPagar+=parcheLeido.importeAdicionalAPagar;
			fseek(pfFacturas,-1L*(long)sizeof(FacturaAutomotor),SEEK_CUR);
			fwrite(&facturaLeida,sizeof(FacturaAutomotor),1,pfFacturas);
		}
		else{
			if(indiceAux.nroRegistro==-1){
				eliminarDeArbol_ALU(&arbolIndices,&indiceAux,sizeof(IndFactura),comparaIndices);
			}
			insertarEnListaAlFinal_ALU(&listaErrores,&parcheLeido,sizeof(ParcheFacturaAutomotor));
		}

		fread(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfParche);
	}

	do{
		eliminarDeListaPrimero_ALU(&listaErrores,&parcheLeido,sizeof(ParcheFacturaAutomotor));
		fwrite(&parcheLeido,sizeof(ParcheFacturaAutomotor),1,pfInexistentes);
	}while(!listaVacia_ALU(&listaErrores));

	fclose(pfInexistentes);
	fclose(pfParche);
	fclose(pfFacturas);

	vaciarArbol_ALU(&arbolIndices);

}

void vaciarArbol_ALU(Arbol* pa){

	if(!*pa){
		return;
	}
	vaciarArbol_ALU(&(*pa)->hIzq);
	vaciarArbol_ALU(&(*pa)->hDer);
	destruirNodoA_ALU(*pa,NULL,0);

}

booleano listaVacia_ALU(Lista* pl){
	return *pl? falso:verdadero;
}

NodoA* crearNodoA_ALU(void* elem,size_t tamElem){
	NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
	void* nueElem = malloc(tamElem);

	if(!nue || !nueElem){
		free(nue);
		free(nueElem);
		return NULL;
	}

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->tamElem = tamElem;
	nue->hDer = NULL;
	nue->hIzq = NULL;

	return nue;
}
void destruirNodoA_ALU(NodoA* nae,void* elem,size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}

NodoD* crearNodoD_ALU(void* elem,size_t tamElem){
	NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
	void* nueElem = malloc(tamElem);

	if(!nue || !nueElem){
		free(nue);
		free(nueElem);
		return NULL;
	}

	memcpy(nueElem,elem,tamElem);

	nue->elem = nueElem;
	nue->tamElem = tamElem;
	nue->ant = NULL;
	nue->sig = NULL;

	return nue;
}
void destruirNodoD_ALU(NodoD* nae,void* elem,size_t tamElem){
	memcpy(elem,nae->elem,MIN(tamElem,nae->tamElem));
	free(nae->elem);
	free(nae);
}

void crearArbol_ALU(Arbol* pa){
	*pa = NULL;
}
void crearLista_ALU(Lista* pl){
	*pl = NULL;
}

void cargarArbolDeArchivoOrdenado_ALU(Arbol* pa,size_t tamElem,const char* archivo,Cmp cmp){

	FILE* pf = fopen(archivo,"rb");
	if(!pf){
		return;
	}
	int ini = 0,fin;
	fseek(pf,0,SEEK_END);
	fin = (ftell(pf)/tamElem) - 1;
	cargarRegistroMedio_ALU(pa,ini,fin,tamElem,pf,cmp);
	fclose(pf);

}

void cargarRegistroMedio_ALU(Arbol* pa,int ini, int fin, size_t tamElem,FILE* pf,Cmp cmp){

	if(ini > fin){
		return;
	}

	char buffer[tamElem];
	int medio = (ini+fin)/2;
	fseek(pf,medio*tamElem,SEEK_SET);
	fread(buffer,tamElem,1,pf);
	insertarEnArbol_ALU(pa,buffer,tamElem,cmp);
	cargarRegistroMedio_ALU(pa,ini,medio-1,tamElem,pf,cmp);
	cargarRegistroMedio_ALU(pa,medio+1,fin,tamElem,pf,cmp);
}

booleano insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp){

	if(!*pa){
		NodoA* nue = crearNodoA_ALU(elem,tamElem);
		if(!nue){
			return falso;
		}
		*pa = nue;
		return verdadero;
	}

	int comp = cmp(elem,(*pa)->elem);

	return insertarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

booleano buscarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem,Cmp cmp){

	if(!*pa){
		return falso;
	}

	int comp = cmp(elem,(*pa)->elem);
	if(comp == 0){
		memcpy(elem,(*pa)->elem,MIN(tamElem,(*pa)->tamElem));
		return verdadero;
	}

	return buscarEnArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);

}

booleano insertarEnListaAlFinal_ALU(Lista* pl,void* elem, size_t tamElem){

	NodoD* act = *pl;
	NodoD* nue = crearNodoD_ALU(elem,tamElem);
	if(!nue){
		return falso;
	}
	if(!act){
        act = nue;
        return verdadero;
	}
	while(act->sig){
		act = act->sig;
	}
	act->sig = nue;
	nue->ant = act;
	return verdadero;

}
void eliminarDeArbol_ALU(Arbol* pa,void* elem,size_t tamElem,Cmp cmp){

	Arbol* pae = buscarRaizDeArbol_ALU(pa,elem,tamElem,cmp);

	if(!pae){
		return;
	}

	memcpy(elem,(*pae)->elem,MIN(tamElem,(*pae)->tamElem));
	free((*pae)->elem);

	eliminarRaizDeArbol_ALU(pae);

}

Arbol* buscarRaizDeArbol_ALU(Arbol* pa, void* elem,size_t tamElem,Cmp cmp){

	if(!*pa){
		return NULL;
	}

	int comp = cmp(elem,(*pa)->elem);

	if(comp == 0){
		return pa;
	}

	return buscarRaizDeArbol_ALU(comp<0?&(*pa)->hIzq:&(*pa)->hDer,elem,tamElem,cmp);
}

void eliminarRaizDeArbol_ALU(Arbol* pae){

	if(!(*pae)->hDer && !(*pae)->hIzq){
		free(*pae);
		*pae=NULL;
		return;
	}

	int hIzq = alturaArbol_ALU(&(*pae)->hIzq);
	int hDer = alturaArbol_ALU(&(*pae)->hDer);

	Arbol* par = hIzq>hDer? mayorDeArbol_ALU(&(*pae)->hIzq):menorDeArbol_ALU(&(*pae)->hDer);
	(*pae)->elem = (*par)->elem;
	(*pae)->tamElem = (*par)->tamElem;

	eliminarRaizDeArbol_ALU(par);
}

Arbol* mayorDeArbol_ALU(Arbol* pa){
	if(!(*pa)->hDer){
		return pa;
	}
	return mayorDeArbol_ALU(&(*pa)->hDer);
}

Arbol* menorDeArbol_ALU(Arbol* pa){
	if(!(*pa)->hIzq){
		return pa;
	}
	return menorDeArbol_ALU(&(*pa)->hIzq);
}

int alturaArbol_ALU(Arbol* pa){

	if(!*pa){
		return 0;
	}

	return MAX(alturaArbol(&(*pa)->hIzq), alturaArbol(&(*pa)->hDer)) + 1;
}

void eliminarDeListaPrimero_ALU(Lista* pl,void* elem, size_t tamElem){

	NodoD* nae = *pl;

	if(!*pl){
		return;
	}

	while(nae->ant){
		nae = nae->ant;
	}

	if(nae->sig){
		*pl = nae->sig;
		nae->sig->ant = NULL;
	}
	else{
		*pl = NULL;
	}

	destruirNodoD_ALU(nae,elem,tamElem);

}
