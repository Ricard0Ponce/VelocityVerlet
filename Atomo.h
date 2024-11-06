//
// Created by rich on 25/10/24.
//

#ifndef ATOMO_H
#define ATOMO_H
#include <vector>
#include <iostream>

using namespace std;

class Atomo {
public:
    Atomo(); // Declaración del constructor

    //std::vector<double> p; // Posiciones
    //std::vector<double> v; // Velocidades
    virtual ~Atomo();

    vector <double>p,v,a;

    protected:

    private:


};



#endif //ATOMO_H
