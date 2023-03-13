#include "Llamada.h"
#include "ExceptionLLamada.h"
int main()
{
    Llamada com1("1165551234","1165559876",21);
    Llamada com2("1165551234","2265554567",10);
    Llamada com3("3365556543","2265551234",9);


    try
    {
        Llamada com4 =com1+com2;

        cout<<"Llamada con recargo="<<9+com1<<endl;
        cout<<"Comunicacion 4="<<com4<<endl;
        cout<<com2+com3<<endl;
    }
    catch(ExceptionLLamada &ex)
    {
        cout<<ex.what()<<endl;
    }
    return 0;
}
