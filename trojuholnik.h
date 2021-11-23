//
// Created by roman on 10. 11. 2021.
//

#ifndef TROJUHOLNIK_TROJUHOLNIK_H
#define TROJUHOLNIK_TROJUHOLNIK_H

class Bod
{
private:
    float x;
    float y;
public:
    Bod():x(0),y(0){};
    explicit Bod(float a):x(a),y(a){};
    Bod(float a,float b):x(a),y(b){};
    float getDistance(const Bod & other = Bod(0,0) ) const;
    Bod getCenter(const Bod & other) const;
    Bod operator+(const Bod & other) const;
    Bod operator-(const Bod & other) const;
    Bod operator/(float k) const;
    Bod operator*(float k) const;
    bool operator<(const Bod & other);
    bool operator>(const Bod & other);
    Bod operator^(const Bod & other) const; //pretazeny operator strieska na vypocet stredu usecky
    explicit operator float() const;  //pretazeny operator konverzie na float, ktory vrati vzdialenost od [0,0]
    //inicializacia generatorov cisel
    friend Bod operator*(float k, const Bod &other);
    friend std::ostream & operator<<(std::ostream & os,const Bod &other);
    //getery a setery
    float getX() const{return x;}
    float getY() const{return y;}
    void setX(float mojX){x = mojX;}
    void setY(float mojY){y = mojY;}
    //staticka metoda ktora vygeneruje pole bodov zadaneho poctu a utriedi ho podla vzdialenosti bodu od pociatku
    static Bod * generujPoleBodov(int pocetBodov);
    static void vypisPoleBodov(int pocetBodov,Bod *poleBodov);
    static int cmp(const void *prvy,const void *druhy);
    static int generujInt(int min, int max);
    static float generujFloat(float min, float max);
};

using Vektor = Bod; //aby sme mohli pouzivat vektor namiesto bodu vtedy, ked to je vhodne a bolo vidiet co presne robime

class Priamka
{
protected:
    Bod X;
    Bod Y;
public:
    Priamka(){};
    explicit Priamka(Bod A):X(A),Y(A){};
    Priamka(Bod A, Bod B):X(A),Y(B){};
    friend std::ostream & operator<<(std::ostream &os, const Priamka & other);
    Bod getCenter() const;
    float getDlzka() const;
    Vektor getSmerovy() const;
    Vektor getNormalovy() const;
    Priamka getOsStrany() const;
};

class PR: public Priamka
{
private:
    float koeficienty[4]; //koeficienty a1,s1,a2,s2 v rovniciach:  x = a1 + s1*t   y= a2 + s2*t
public:
    PR():koeficienty{0,0,0,0}{};
    PR(Bod A, Bod B);
    PR(const Priamka & P);
    float &operator [](int index) {return koeficienty[index];}
    const float & operator [](int index) const {return koeficienty[index];}
    friend std::ostream & operator<<(std::ostream & os,const PR & other);
    float * getKoeficienty();
    void setKoeficienty();
};


#endif //TROJUHOLNIK_TROJUHOLNIK_H
