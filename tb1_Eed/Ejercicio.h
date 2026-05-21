#pragma once
#include <string>
using namespace std;

class Ejercicio {
private:
    int id;
    string enunciado;
    Ejercicio* tipo;
    int puntaje;
    string respuestaCorrecta;
public:
    bool validarRespuesta(string r);
	int getPuntaje();
	string getEnunciado();
};
