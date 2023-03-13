#include "Medicion.h"
#include "Medicionexception.h"

int main()
{
    Medicion m1mv(100.0,"Mv");
    Medicion m2mv(20.0,"Mv");
    Medicion m4amp(3.0,"Amp");
    Medicion m3mv;
    m3mv-m1mv-m2mv;
    cout<<"resultado 1:"<<180.0+m3mv<<endl;
    try
    {
        cout<<m3mv-m4amp<<endl;
    }
    catch(Medicionexception &ex)
    {
        cout<<ex.what()<<endl;
    }
    return 0;
}
