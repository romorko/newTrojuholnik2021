#include "inout.h"
#include "trojuholnik.h"
int main()
{
    using namespace inout;
    Priamka priamka1= Priamka({1,1},{2,2});
    Priamka priamka2=  Priamka({0,1},{1,2});
    cout<<priamka1.getUhol(priamka2,'s');
    cout<<VR(priamka1)<<VR(priamka2);
    cout<<priamka1.getPoloha(priamka2);
    //cout<<*((PR *)(priamky[0]))<<(*priamky[1]);
/*    const int pocet = 50;
    Bod *mojePole =Bod::generujPoleBodov(pocet);
    Bod::vypisPoleBodov(pocet,mojePole);
    qsort(mojePole,pocet, sizeof(Bod),Bod::cmp);
    cout<<"Utriedene:"<<std::endl;
    Bod::vypisPoleBodov(pocet,mojePole);
    delete [] mojePole;*/

    return 0;
}
