//
// Created by roman on 10. 11. 2021.
//
#include "inout.h"
#include "trojuholnik.h"
#include <cmath>
#include <random>

float Bod::getDistance(const Bod &other) const
{
    return std::sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
}

Bod Bod::getCenter(const Bod &other) const
{
    return ((*this)+other)/2.f;
}

Bod Bod::operator+(const Bod &other) const
{
    return {x+other.x,y+other.y};
}

Bod Bod::operator-(const Bod &other) const
{
    return {x-other.x,y-other.y};
}

Bod Bod::operator/(float k) const
{
    return {x/k,y/k};
}

Bod Bod::operator*(float k) const
{
    return {x*k,y*k};
}

Bod operator*(float k, const Bod &other)
{
    return other*k;
}

std::ostream &operator<<(std::ostream &os, const Bod &other)
{
    os<<"[ "<<std::setprecision(4)<<other.x<<","<<other.y<<" ]";
    return os;
}

Bod Bod::operator^(const Bod &other) const
{
    return this->getCenter(other);
}

Bod::operator float() const
{
    return this->getDistance(Bod(0,0));
}

Bod *Bod::generujPoleBodov(int pocetBodov)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1,50);
    Bod *poleBodov;
    try
    {
        poleBodov= new Bod[pocetBodov];
        for(int i=0;i<pocetBodov;++i)
        {
            (poleBodov+i)->x=(float)dis(gen);
            (poleBodov+i)->y=(float)dis(gen) ;
        }
    }
    catch (const std::bad_alloc & ex)
    {
        std::cout<<"Chybna alokacia pamate";
        return nullptr;
    }
    return poleBodov;
}

void Bod::vypisPoleBodov(int pocetBodov, Bod *poleBodov)
{
    for(int i=0;i<pocetBodov;++i)
    {
        std::cout<<*(poleBodov+i)<<" ";
    }
}

int Bod::cmp(const void *prvy, const void *druhy)
{
    Bod * A = (Bod *)prvy;
    Bod * B = (Bod *)druhy;
    //return ((float)(*A)<(float)(*B))?1:((float)(*A)>(float)(*B))?-1:0;
    return ((*A)<(*B))?-1:((*A)>(*B))?1:0;
}

bool Bod::operator<(const Bod &other)
{
    return (float)(*this)<(float)(other);
}

bool Bod::operator>(const Bod &other)
{
    return (float)(*this)>(float)(other);
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
    std::uniform_real_distribution<> dis(min,max);
    return (float)dis(gen) ;
}

std::ostream &operator<<(std::ostream &os, const Priamka &other)
{
    os<<"Priamka: "<<other.X<<" "<<other.Y<<std::endl;
    return os;
}

Bod Priamka::getCenter() const
{
    return X.getCenter(Y);
}

float Priamka::getDlzka() const
{
    return X.getDistance(Y);
}

Vektor Priamka::getSmerovy() const
{
    return Y-X;
}

Vektor Priamka::getNormalovy() const
{
    Vektor smerovy = getSmerovy();
    return {smerovy.getY()*(-1),smerovy.getX()};
}

Priamka Priamka::getOsStrany() const
{
    Bod stred = getCenter();
    return {stred,stred+getNormalovy()};
}

std::ostream &operator<<(std::ostream &os, const PR &other)
{
    using namespace inout;
    os<<"Parametricka rovnica:"<<std::endl<<"x = "<<setw(4)<<std::noshowpos<<other[0]<<std::showpos<<setw(4)<<other[1]<<"*t"<<std::endl<<"y = "<<setw(4)<<std::noshowpos<<other[2]<<std::showpos<<setw(4)<<other[3]<<"*t"<<"   t je z R"<<std::endl;
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

PR::PR(const Priamka &P):Priamka(P)
{
    setKoeficienty();
}

void PR::setKoeficienty()
{
    koeficienty[0]=X.getX();
    koeficienty[1]=getSmerovy().getX();
    koeficienty[2]=X.getY();//x = a1 + s1*t   y= a2 + s2*t
    koeficienty[3] =getSmerovy().getY();
}
