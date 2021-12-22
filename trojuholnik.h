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
    float operator*(const Bod & other) const;//skalarny sucin vektorov
    bool operator<(const Bod & other);
    bool operator>(const Bod & other);
    bool operator==(const Bod & other);
    Bod operator^(const Bod & other) const; //pretazeny operator strieska na vypocet stredu usecky
    explicit operator float() const;  //pretazeny operator konverzie na float, ktory vrati vzdialenost od [0,0]
    friend Bod operator*(float k, const Bod &other);
    friend std::ostream & operator<<(std::ostream & os,const Bod &other);
    //getery a setery
    float getX() const{return x;}
    float getY() const{return y;}
    Bod getJednotkovy() const;
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

    class Priesecnik
    {
    private:
        Bod P;
        char popis[11];
    public:
        Priesecnik():P({0,0}),popis(" "){};
        Priesecnik(const Bod &R,const char * msg);
        Bod getBodPriesecnika()const{return P;} ;
        char * getpopisPriesecnika() const;
        friend std::ostream & operator<<(std::ostream & os,const Priesecnik  &other);
    };

    Priamka(){X ={0,0},Y ={1,0};}; //vytvorime implicitnu priamku, ktora je osou x
    explicit Priamka(Bod A); //vytvorime implicitnu priamku iducu bodom A rovnobeznu s osou x
    Priamka(Bod A, Bod B);
    friend std::ostream & operator<<(std::ostream &os, const Priamka & other);
    Bod getStred() const;
    float getDlzka() const;
    bool leziNaPriamke(const Bod & other) const;
    bool jeRovnobezna(const Priamka & other) const;
    bool operator==(const Priamka & other) const;
    virtual Vektor getSmerovy() const;
    virtual Vektor getNormalovy() const;
    Priamka getOsStrany() const;
    Priesecnik getPoloha(const Priamka & other) const;
    Priamka getOsUhla(const Priamka & other)const;
    float getUhol(const Priamka & other,char vrat='s') const; //vrati velkost uhla priamok bud v stupnoch(s) alebo radianoch (r)
};

class PR: public Priamka
{
private:
    float koeficienty[4]; //koeficienty a1,s1,a2,s2 v rovniciach:  x = a1 + s1*t   y= a2 + s2*t
public:
    PR():koeficienty{0,0,0,0}{};
    PR(Bod A, Bod B);  //parametricka priamka urcena dvoma bodmi
    explicit PR(const Priamka & P); //vyrobi z objektu priamka parametricku rovnicu
    float &operator [](int index) {return koeficienty[index];} //pretazeny operator [] pre nekonstanty pristup
    const float & operator [](int index) const {return koeficienty[index];} //pretazeny operator [] pre konstanty pristup
    friend std::ostream & operator<<(std::ostream & os,const PR & other);
    float * getKoeficienty();  //vrati pole koeficientov
    Vektor getSmerovy()  const override;
    void setKoeficienty(); //nastavi koeficienty v parametrickej rovnici na spravne hodnoty
};

class VR:public Priamka
{
private:
    float koeficienty[3]; //koeficienty a,b,c z rovnice ax+by+c=0
    static int p;
public:
    VR();
    VR(Bod A, Bod B);  //vseobecna priamka urcena dvoma bodmi
    VR(float a,float b,float c);
    explicit VR(const Priamka & P); //vyrobi z objektu priamka vseobecnu rovnicu
    float &operator [](int index) {return koeficienty[index];} //pretazeny operator [] pre nekonstanty pristup
    const float & operator [](int index) const {return koeficienty[index];} //pretazeny operator [] pre konstanty pristup
    friend std::ostream & operator<<(std::ostream & os,const VR & other);
    float * getKoeficienty();  //vrati pole koeficientov
    Vektor getNormalovy() const override;
    void setKoeficienty(); //nastavi koeficienty vo vseobecnej rovnici na spravne hodnoty vypocitane podla bodov
    Bod vypocitajBod(float a, float b,float c) const; //na zaklade zadanych koeficientov a.b.priamkyc vypocita body

};


class Trojuholnik
{


};

#endif //TROJUHOLNIK_TROJUHOLNIK_H
