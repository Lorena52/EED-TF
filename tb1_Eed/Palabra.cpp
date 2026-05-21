#include "pch.h"
#include "Palabra.h"
#include <iostream>
#include <string>

using namespace std;

Palabra::Palabra()
    : termino(""), traduccion(""), categoria(""), nivel(1), vecesRepasada(0) {
}

Palabra::Palabra(string t, string tr, int n)
    : termino(t), traduccion(tr), nivel(n), vecesRepasada(0) {
}

string Palabra::getTermino() { return termino; }
string Palabra::getTraduccion() { return traduccion; }
string Palabra:: getCategoria() { return categoria; }
int Palabra::   getNivel() { return nivel; }
int Palabra::   getVeces() { return vecesRepasada; }

void Palabra::incrementarRepaso() { vecesRepasada++; }
bool Palabra::esDificil() { return vecesRepasada < 3; }

void Palabra::mostrar() {
    std::cout << "  [ " << termino << " ]  -->  "
        << traduccion << "  (" << categoria << ")\n";
}