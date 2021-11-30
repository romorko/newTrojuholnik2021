//
// Created by roman on 10. 11. 2021.
//
#include "inout.h"
#include "trojuholnik.h"
#include <cmath>
#include <random>

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
    os << "[ " << std::setprecision(4) << other.x << "," << other.y << " ]";
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
    float uhol = std::acos((smerovy1 * smerovy2) / (smerovy1.getDistance() * smerovy2.getDistance()));
    return vrat == 'r' ? (float)uhol : (float)(180 / 3.14159265358) * uhol;
}

bool Priamka::operator==(const Priamka &other) const
{
    return ((jeRovnobezna(other)) && (leziNaPriamke(other.Y)));
}

bool Priamka::leziNaPriamke(const Bod & other) const
{
    VR vPriamka(*this);
    return vPriamka[0] * other.getX() + vPriamka[1] * other.getY() + vPriamka[2] == 0;
}

bool Priamka::jeRovnobezna(const Priamka &other) const
{
    return getSmerovy() * other.getNormalovy() == 0;
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
