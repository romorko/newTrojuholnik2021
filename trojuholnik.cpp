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
    os<<"[ "<<std::setprecision(4)<<other.x<<","<<other.y<<" ]"<<(float)other<<std::endl;
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
    srand(time(nullptr));
    Bod *poleBodov;
    try
    {
        poleBodov= new Bod[pocetBodov];
        for(int i=0;i<pocetBodov;++i)
        {
            (poleBodov+i)->x=(float)(rand()%50);
            (poleBodov+i)->y=(float)(rand()%50);
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
    std::random_device rd; // ziska trandom cislo z hardveru pocitaca
    std::mt19937 eng(rd()); // "osoli" generator
    std::uniform_int_distribution<> distr(min, max); // definuje interval z ktoreho sa generuju cisla
    return distr(eng); //generuje cislo
}

float Bod::generujFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min,max);
    return dis(gen) ;
}
