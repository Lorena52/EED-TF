#include "pch.h"
#include "Ranking.h"

Ranking::Ranking() {

    nombre = "";
    mejorRacha = 0;
}

Ranking::Ranking(string nombre, int mejorRacha) {

    this->nombre = nombre;
    this->mejorRacha = mejorRacha;
}

string Ranking::getNombre() {

    return nombre;
}

int Ranking::getMejorRacha() {

    return mejorRacha;
}

void Ranking::setNombre(string nombre) {

    this->nombre = nombre;
}

void Ranking::setMejorRacha(int racha) {

    mejorRacha = racha;
}

string Ranking::serializar() const {

    return nombre + ";" + to_string(mejorRacha);
}