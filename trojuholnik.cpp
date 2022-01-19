//
// Created by roman on 10. 11. 2021.
//
#include "inout.h"
#include "trojuholnik.h"
#include <cstring>
#include <cmath>
#include <random>

int VR::p = -10;

float Bod::getDistance(const Bod &other) const
{
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Bod Bod::getCenter(const Bod &other) const
{
    return ((*this) + other) / 2.f;
}

Bod Bod::operator+(const Bod &other) const
{
    return {x + other.x, y + other.y};
}

Bod Bod::operator-(const Bod &other) const
{
    return {x - other.x, y - other.y};
}

Bod Bod::operator/(float k) const
{
    return {x / k, y / k};
}

Bod Bod::operator*(float k) const
{
    return {x * k, y * k};
}

Bod operator*(float k, const Bod &other)
{
    return other * k;
}

std::ostream &operator<<(std::ostream &os, const Bod &other)
{
    os << std::noshowpos << "[ " << std::setprecision(4) << other.x << "," << other.y << " ]";
    return os;
}

Bod Bod::operator^(const Bod &other) const
{
    return this->getCenter(other);
}

Bod::operator float() const
{
    return this->getDistance(Bod(0, 0));
}

Bod *Bod::generujPoleBodov(int pocetBodov)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1, 50);
    Bod *poleBodov;
    try
    {
        poleBodov = new Bod[pocetBodov];
        for (int i = 0; i < pocetBodov; ++i)
        {
            (poleBodov + i)->x = (float) dis(gen);
            (poleBodov + i)->y = (float) dis(gen);
        }
    }
    catch (const std::bad_alloc &ex)
    {
        std::cout << "Chybna alokacia pamate";
        return nullptr;
    }
    return poleBodov;
}

void Bod::vypisPoleBodov(int pocetBodov, Bod *poleBodov)
{
    for (int i = 0; i < pocetBodov; ++i)
    {
        std::cout << *(poleBodov + i) << " ";
    }
}

int Bod::cmp(const void *prvy, const void *druhy)
{
    Bod *A = (Bod *) prvy;
    Bod *B = (Bod *) druhy;
    //return ((float)(*A)<(float)(*B))?1:((float)(*A)>(float)(*B))?-1:0;
    return ((*A) < (*B)) ? -1 : ((*A) > (*B)) ? 1 : 0;
}

bool Bod::operator<(const Bod &other)
{
    return (float) (*this) < (float) (other);
}

bool Bod::operator>(const Bod &other)
{
    return (float) (*this) > (float) (other);
}

int Bod::generujInt(int min, int max)
{
    std::random_device rd; // ziska random cislo z hardveru pocitaca
    std::mt19937 eng(rd()); // "osoli" generator
    std::uniform_int_distribution<> distr(min, max); // definuje interval z ktoreho sa generuju cisla
    return distr(eng); //generuje cislo
}

float Bod::generujFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return (float) dis(gen);
}

float Bod::operator*(const Bod &other) const
{
    return x * other.x + y * other.y;
}

Bod Bod::getJednotkovy() const
{
    //std::cout<<this->getDistance()<<std::endl;
    return {this->x / this->getDistance(), this->y / this->getDistance()};
}

bool Bod::operator==(const Bod &other)
{
    return (x==other.x && y==other.y);
}

std::ostream &operator<<(std::ostream &os, const Priamka &other)
{
    os << "Priamka: " << other.X << " " << other.Y << std::endl;
    return os;
}


Priamka::Priamka(Bod A, Bod B):X(A),Y(B)
{
    try
    {
        if(A==B)
        {
            throw MsgError("Dva rovnake body neurcuju priamku! Vytvorila sa implicitna priamka.\n");
        }
    }
    catch (const MsgError & ex)
    {
        std::cout<<ex.what();
        X={0,0};
        Y={1,0};
    }
}

Priamka::Priamka(Bod A):X(A)
{
    std::cout<<"Jeden bod neurcuje priamku. Bola vytvorena implicitna priamka iduca tymto bodom rovnobezna s osou x\n";
    Y={A.getX()+1,A.getY()};
}

Bod Priamka::getStred() const
{
    return X.getCenter(Y);
    //return X ^ Y;
}

float Priamka::getDlzka() const
{
    return X.getDistance(Y);
}

Vektor Priamka::getSmerovy() const
{
    return Y - X;
}

Vektor Priamka::getNormalovy() const
{
    Vektor smerovy = getSmerovy();
    return {smerovy.getY() * (-1), smerovy.getX()};
    //return Vektor (smerovy.getY()*(-1),smerovy.getX());
}

Priamka Priamka::getOsStrany() const
{
    Bod stred = getStred();
    return {stred, stred + getNormalovy()};
    //return Priamka(stred,stred+getNormalovy());
}

float Priamka::getUhol(const Priamka &other, char vrat) const
{
    Vektor smerovy1 = getSmerovy();
    Vektor smerovy2 = other.getSmerovy();
    if (this->jeRovnobezna(other))
    {
        return 0;
    }
    float uhol = std::acos((smerovy1 * smerovy2) / (smerovy1.getDistance() * smerovy2.getDistance()));
    return vrat == 'r' ? static_cast<float>(uhol) : static_cast<float>((180 / 3.14159265358) * uhol);
}

bool Priamka::operator==(const Priamka &other) const
{
    return ((jeRovnobezna(other)) && (leziNaPriamke(other.Y)));
}

bool Priamka::leziNaPriamke(const Bod &other) const
{
    VR vPriamka(*this);
    return vPriamka[0] * other.getX() + vPriamka[1] * other.getY() + vPriamka[2] == 0;
}

bool Priamka::jeRovnobezna(const Priamka &other) const
{
    return getSmerovy() * other.getNormalovy() == 0;
}

Priamka::Priesecnik Priamka::getPoloha(const Priamka &other) const
{
    if ((*this) == other)
    {
        return {{0, 0}, "totozne"};
    } else if ((*this).jeRovnobezna(other))
    {
        return {{0, 0}, "rovnobezne"};
    } else
    {
        VR prva(*this);
        VR druha(other);
        float D = prva[0] * druha[1] - prva[1] * druha[0];
        float D1 = -prva[2] * druha[1] - prva[1] * druha[2] * (-1);
        float D2 = -prva[0] * druha[2] - druha[0] * prva[2] * -1;
        return Priamka::Priesecnik{{D1 / D, D2 / D}, "roznobezne"};
    }
}

std::ostream &operator<<(std::ostream &os, const PR &other)
{
    using namespace inout;
    os << "Parametricka rovnica:" << std::endl << "x = " << setw(4) << std::noshowpos << other[0] << std::showpos
       << setw(4) << other[1] << "*t" << std::endl << "y = " << setw(4) << std::noshowpos << other[2] << std::showpos
       << setw(4) << other[3] << "*t" << "   t je z R" << std::noshowpos << std::endl;
    return os;
}

float *PR::getKoeficienty()
{
    return koeficienty;
}

PR::PR(Bod A, Bod B) : Priamka(A, B)
{
    setKoeficienty();
}

PR::PR(const Priamka &P) : Priamka(P)
{
    setKoeficienty();
}

void PR::setKoeficienty()
{
    Vektor smerovy = Priamka::getSmerovy();
    koeficienty[0] = X.getX();
    koeficienty[1] = smerovy.getX();
    koeficienty[2] = X.getY();//x = a1 + s1*t   y= a2 + s2*t
    koeficienty[3] = smerovy.getY();
}

Vektor PR::getSmerovy() const
{
    return {koeficienty[1], koeficienty[3]};
}

PR::PR():Priamka(),koeficienty{0,1,0,0}
{

}

PR::PR(float a1, float s1, float a2, float s2):Priamka()
{
    try
    {
        if(s1==0 && s2==0)
        {
            throw MsgError("Smerovy vektor nesmie byt nulovy! Bola vytvorena implictna priamka ktora je osou x");
        }
        koeficienty[0]=a1;
        koeficienty[1]=s1;
        koeficienty[2]=a2;
        koeficienty[3]=s2;
    }
    catch (const MsgError & ex)
    {
        std::cout<<ex.what();
        koeficienty[0]=0;
        koeficienty[1]=1;
        koeficienty[2]=0;
        koeficienty[3]=0;
    }
}

void VR::setKoeficienty()
{
    Vektor normalovy = Priamka::getNormalovy();
    koeficienty[0] = normalovy.getX();
    koeficienty[1] = normalovy.getY();
    koeficienty[2] = -(koeficienty[0] * X.getX() + koeficienty[1] * X.getY());
}

VR::VR():Priamka()
{
    setKoeficienty();
}

VR::VR(Bod A, Bod B) : Priamka(A, B)
{
    setKoeficienty();
}

VR::VR(const Priamka &P) : Priamka(P)
{
    setKoeficienty();
}

std::ostream &operator<<(std::ostream &os, const VR &other)
{
    using namespace inout;
    os << "Vseobecna rovnica:" << setw(4) << setprecision(2) << other[0] << "x" << std::showpos << setw(4) << other[1]
       << "y" << std::showpos << setw(4) << other[2] << " = 0" << endl;
    return os;
}

Vektor VR::getNormalovy() const
{
    return {(*this)[0], (*this)[1]};
}

VR::VR(float a, float b, float c) : Priamka()
{
    try
    {
        if (a == 0 && b==0)
        {
            throw MsgError("Takato priamka neexistuje! Bola vytvorena implicitna priamka ktora je osou x");
        }
        X = vypocitajBod(a, b, c);
        Y = vypocitajBod(a, b, c);
        koeficienty[0] = a;
        koeficienty[1] = b;
        koeficienty[2] = c;
    }
    catch (const MsgError & ex)
    {
        std::cout<<ex.what();
        koeficienty[0] = 0;
        koeficienty[1] = 1;
        koeficienty[2] = 0;
    }
}

Bod VR::vypocitajBod(float a, float b, float c) const
{
    ++p;
    float intpart;
    if (b != 0)
    {
        float vysledok = (-c - a * p) / b;
        while (p < 10 && std::modf(vysledok, &intpart) != 0)
        {
            ++p;
            //std::cout<<p<<" ";
            vysledok = (-c - a * p) / b;
        }
        return Bod(p, vysledok);
    } else
    {
        float vysledok = (-c - b * p) / a;
        while (p < 10 && std::modf(vysledok, &intpart) != 0)
        {
            ++p;
            vysledok = (-c - b * p) / a;;
        }
        return Bod(vysledok, p);
    }
}

float *VR::getKoeficienty()
{
    return koeficienty;
}

Priamka::Priesecnik::Priesecnik(const Bod &R, const char *msg) : P(R)
{
    std::strncpy(popis, msg, 10);
    popis[10] = '\0';
}

std::ostream &operator<<(std::ostream &os, const Priamka::Priesecnik &other)
{
    os << "Priamky su " << other.popis;
    if (std::strcmp(other.popis, "roznobezne") == 0)
    {
        os << " a ich priesecnik je " << other.P;
    }
    return os;
}

Priamka Priamka::getOsUhla(const Priamka &other) const
{
    Bod prvyBod = this->getPoloha(other).getBodPriesecnika();
    Vektor vektor1 = this->getSmerovy().getJednotkovy();
    //std::cout<<"Smerovy "<<this->getSmerovy()<<" jednotkovy"<<vektor1<<std::endl;
    Vektor vektor2 = other.getSmerovy().getJednotkovy();
    //std::cout<<"Smerovy "<<other.getSmerovy()<<" jednotkovy"<<vektor2<<std::endl;
    Bod druhyBod = vektor1 + vektor2 + prvyBod;
    //std::cout<<druhyBod<<std::endl;
    return {prvyBod, druhyBod};
}

Trojuholnik::Trojuholnik(Bod A1, Bod B1, Bod C1):A(A1),B(B1),C(C1)
{
    if(!existuje())
    {
        exit(1);
    }
}

bool Trojuholnik::existuje() const
{
    float a=A.getDistance(B);
    float b=A.getDistance(C);
    float c=B.getDistance(C);
    try
    {
        if(!((a+b>c)*(a+c>b)*(b+c>a)))
        {
            throw MsgError("Trojholnik sa neda zostrojit!");
        }
    }
    catch (const MsgError & ex)
    {
        std::cout<<ex.what();
        return false;
    }
    std::cout<<"Trojuholnik "<<*this<<" OK"<<std::endl;
    return true;
}

float Trojuholnik::getVelkostStrany(char strana) const
{
    float velkost=-1;
    if(strana=='a')
    {
        velkost =B.getDistance(C);
    }
    else if(strana=='b')
    {
        velkost=A.getDistance(C);
    }
    else if(strana=='c')
    {
        velkost= A.getDistance(B);
    }
    else
    {
        std::cout<<"Neznama strana!";
    }
    return velkost;
}

float Trojuholnik::getVelkostUhla(char uhol) const
{
    float velkost=-1;
    if(uhol=='a')
    {
        Priamka AC(A,C);
        Priamka AB(A,B);
        velkost =AC.getUhol(AB);
    }
    else if(uhol=='b')
    {
        Priamka BA(B,A);
        Priamka BC(B,C);
        velkost =BA.getUhol(BC);
    }
    else if(uhol=='c')
    {
        Priamka CA(C,A);
        Priamka CB(C,B);
        velkost =CA.getUhol(CB);
    }
    else
    {
        std::cout<<"Neznamy uhol!";
    }
    return velkost;
}

float Trojuholnik::getObvod() const
{
    return getVelkostStrany('a')+ getVelkostStrany('b')+ getVelkostStrany('c');
}

float Trojuholnik::getObsah() const
{
    float s=getObvod()/2;
    return std::sqrt(s*(s- getVelkostStrany('a'))*(s- getVelkostStrany('b'))*(s- getVelkostStrany('c')));
}

void Trojuholnik::vypisStrany() const
{
    using namespace inout;
    cout<<"Strany: "<<setprecision(4)<<"a ="<<setw(5)<<getVelkostStrany('a')<<" b ="<<setw(5)<<getVelkostStrany('b')<<" c ="<<setw(5)<<getVelkostStrany('c')<<endl;
}

void Trojuholnik::vypisUhly() const
{
    using namespace inout;
    cout<<"Uhly(stupne):"<<setprecision(4)<<"alfa ="<<setw(5)<<getVelkostUhla('a')<<" beta ="<<setw(5)<<getVelkostUhla('b')<<" gama ="<<setw(5)<<getVelkostUhla('c')<<endl;
}

std::ostream &operator<<(std::ostream &os, const Trojuholnik &other)
{
    os<<"ABC:"<<other.A<<other.B<<other.C;
    return os;
}

Priamka Trojuholnik::getVyska(char naStranu) const
{
    Vektor normalovy; //normalovy vektor strany je smerovy vektor vysky
    Bod Prvy;
    Bod Druhy;
    if(naStranu=='a')
    {
        normalovy = Priamka(B,C).getNormalovy();
        Prvy = A;
        Druhy = A+normalovy;
    }
    else if(naStranu=='b')
    {
        normalovy = Priamka(A,C).getNormalovy();
        Prvy = B;
        Druhy = B+normalovy;
    }
    else if(naStranu=='c')
    {
        normalovy = Priamka(A,B).getNormalovy();
        Prvy = C;
        Druhy = C+normalovy;
    }
    else
    {
        std::cout<<"Neznama strana";
        Prvy = Bod();
        Druhy = Bod();
    }
    return {Prvy,Druhy};
}

Bod Trojuholnik::getOrtocentrum() const
{
    return getVyska('a').getPoloha(getVyska('b')).getBodPriesecnika();
}

Priamka Trojuholnik::getTaznica(char naStranu) const
{
    Bod Stred; //stred strany
    Bod Vrchol; //smerovy vektor taznice
    if(naStranu=='a')
    {
        Stred = B.getCenter(C);
        Vrchol = A;
    }
    else if(naStranu=='b')
    {
        Stred = A.getCenter(C);
        Vrchol = B;
    }
    else if(naStranu=='c')
    {
        Stred = A.getCenter(B);
        Vrchol = C;
    }
    else
    {
        std::cout<<"Neznama strana";
    }
    return Priamka(Stred,Vrchol);
}

Bod Trojuholnik::getTazisko() const
{
    return getTaznica('a').getPoloha(getTaznica('b')).getBodPriesecnika();
}



