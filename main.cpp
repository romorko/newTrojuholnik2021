#include "inout.h"
#include "trojuholnik.h"
int main()
{
    using namespace inout;
    const int pocet = 50;
    Bod *mojePole =Bod::generujPoleBodov(pocet);
    Bod::vypisPoleBodov(pocet,mojePole);
    qsort(mojePole,pocet, sizeof(Bod),Bod::cmp);
    cout<<"Utriedene:"<<std::endl;
    Bod::vypisPoleBodov(pocet,mojePole);

    delete [] mojePole;
    return 0;
}
