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
    //staticka metoda ktora vygeneruje pole bodov zadaneho poctu a utriedi ho podla vzdialenosti bodu od pociatku
    static Bod * generujPoleBodov(int pocetBodov);
    static void vypisPoleBodov(int pocetBodov,Bod *poleBodov);
    static int cmp(const void *prvy,const void *druhy);
    static int generujInt(int min, int max);
    static float generujFloat(float min, float max);
};



#endif //TROJUHOLNIK_TROJUHOLNIK_H
