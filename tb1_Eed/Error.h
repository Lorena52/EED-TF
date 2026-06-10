#pragma once
#include <string>
#include <iostream>

using namespace std;

class Error {
private:
    int idEjercicio;
    string detalle;
    string fecha;

public:
    Error(int id, string d, string f);
    int getIdEjercicio() const;
    string getDetalle() const;
    string getFecha() const;
};


