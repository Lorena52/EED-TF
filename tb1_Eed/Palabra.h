#pragma once
#include <string>
#include <iostream>
using namespace std;

class Palabra {
private:
    string termino;
    string traduccion;
	string categoria;
    int nivel;
    int vecesRepasada;

public:
    Palabra();
    Palabra(string t, string tr, int n);


    string getTermino();
    string getTraduccion();
    string getCategoria();
    int getNivel();
    int getVeces();

    void incrementarRepaso();
    bool esDificil();

    void mostrar();
};