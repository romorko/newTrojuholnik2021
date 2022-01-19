#include "inout.h"
#include "trojuholnik.h"
int main()
{
    using namespace inout;
    Trojuholnik ABC({1,1},{5,1},{8,6});
    cout<<setprecision(4)<<"Obvod: "<<ABC.getObvod()<<endl<<"Obsah: "<<ABC.getObsah()<<endl;
    ABC.vypisStrany();
    ABC.vypisUhly();
    cout<<"Ortocentrum:"<<ABC.getOrtocentrum()<<endl;
    cout<<"Tazisko:"<<ABC.getTazisko()<<endl;
    ABC.vypisOpisanaKruznica();
        /*   Priamka priamka1= Priamka({4,2},{-6,2});
       Priamka priamka2 = Priamka ({4,2},{-1,10.66});
       cout<<priamka1.getUhol(priamka2,'s')<<std::endl;
       //cout<<priamka1.getPoloha(priamka2);
       cout<<VR(priamka1.getOsUhla(priamka2));

       //cout<<*((PR *)(priamky[0])<(*priamky[1]);
   /*    const int pocet = 50;
       Bod *mojePole =Bod::generujPoleBodov(pocet);
       Bod::vypisPoleBodov(pocet,mojePole);
       qsort(mojePole,pocet, sizeof(Bod),Bod::cmp);
       cout<<"Utriedene:"<<std::endl;
       Bod::vypisPoleBodov(pocet,mojePole);
       delete [] mojePole;*/

    return 0;
}
