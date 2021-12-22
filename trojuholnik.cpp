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
            throw ("Takato priamka neexistuje! Bola vytvorena implicitna priamka ktora je osou x");
        }
        X = vypocitajBod(a, b, c);
        Y = vypocitajBod(a, b, c);
        koeficienty[0] = a;
        koeficienty[1] = b;
        koeficienty[2] = c;
    }
    catch (const char * ex)
    {
        std::cout << ex;
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

Priamka::Priamka(Bod A, Bod B)
{
    try
    {
        if(A==B)
        {
            throw "Dva rovnake body neurcuju priamku! Vytvorila sa implicitna priamka.\n";
        }
        X=A;
        Y=B;
    }
    catch (const char * msg)
    {
        std::cout<<msg;
        X={0,0};
        Y={1,0};
    }
}

Priamka::Priamka(Bod A)
{
    std::cout<<"Jeden bod neurcuje priamku. Bola vytvorena implicitna priamka iduca tymto bodom rovnobezna s osou x\n";
    X=A;
    Y={A.getX()+1,A.getY()};
}
