#pragma once
#include <string>

using namespace std;

class Ranking {

private:

    string nombre;
    int mejorRacha;

public:

    Ranking();
    Ranking(string nombre, int mejorRacha);

    string getNombre();
    int getMejorRacha();

    void setNombre(string nombre);
    void setMejorRacha(int racha);



    string serializar() const;
};