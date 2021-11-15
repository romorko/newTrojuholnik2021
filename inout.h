//
// Created by roman on 10. 11. 2021.
//

#ifndef TROJUHOLNIK_INOUT_H
#define TROJUHOLNIK_INOUT_H

#include <iostream>
#include <fstream>
#include <iomanip>
namespace inout
{
    using std::cout;
    using std::cin;
    using std::setfill; //nastavi vyplnovy znak  napr. setfill('-')
    using std::setw;	//nastavi sirku vystupu  napr. setw(15), treba pouzit pred kazdym vypisom
    using std::setprecision; //nastavi pocet desatinnych miest napr. setprecision(5)
    using std::endl;
    using std::left;    //zarovnanie vystupu vlavo
    using std::right;	//zarovnanie vystupu vpravo
    using std::showpos; //vypisovanie znamienka napr. cislo 10 vypise ako +10
    using std::noshowpos; //nevypisovanie znamienka
}

#endif //TROJUHOLNIK_INOUT_H
