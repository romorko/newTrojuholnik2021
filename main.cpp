#include "inout.h"
#include "trojuholnik.h"
int main()
{
    using namespace inout;
/*    const int pocet = 50;
    Bod *mojePole =Bod::generujPoleBodov(pocet);
    Bod::vypisPoleBodov(pocet,mojePole);
    qsort(mojePole,pocet, sizeof(Bod),Bod::cmp);
    cout<<"Utriedene:"<<std::endl;
    Bod::vypisPoleBodov(pocet,mojePole);
    delete [] mojePole;*/
    Priamka AB({1,2},{3,4});
    Priamka CD(Bod(4,6),Bod(6,10));
    PR EF({1,2},{6,4});
    PR GH(CD);
    cout<<GH;
    cout<<EF;
    return 0;
}
