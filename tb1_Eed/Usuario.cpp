#include "pch.h"
#include "Usuario.h"
#include <sstream>
#include <stdexcept>

using namespace std;

Usuario::Usuario()
    : id(0), nombre(""), email(""), puntajeTotal(0),
    nivelIngles(1), nivelPortugues(1), nivelItaliano(1) {
}

Usuario::Usuario(int i, const string& n, const string& e, int ni, int np, int ni2)
    : id(i), nombre(n), email(e), puntajeTotal(0),
    nivelIngles(ni), nivelPortugues(np), nivelItaliano(ni2) {
}

Progreso* Usuario::obtenerProgreso() { return &progreso; }

string Usuario::serializar() const {
    return to_string(id) + ";" + nombre + ";" + email + ";" +
        to_string(nivelIngles) + ";" +
        to_string(nivelPortugues) + ";" +
        to_string(nivelItaliano) + ";" +
        to_string(progreso.getRacha()->getActual()) + ";" +
        to_string(progreso.getRacha()->getMaxima());
}

Usuario Usuario::deserializar(const string& linea) {
    stringstream ss(linea);
    string idTxt, nom, mail, ni, np, ni2, rActual, rMejor;
    getline(ss, idTxt, ';');
    getline(ss, nom, ';');
    getline(ss, mail, ';');
    getline(ss, ni, ';');
    getline(ss, np, ';');
    getline(ss, ni2, ';');
    getline(ss, rActual, ';');
    getline(ss, rMejor, ';');

    if (idTxt.empty() || nom.empty() || ni.empty() || np.empty() || ni2.empty())
        throw runtime_error("Linea invalida en usuarios.txt: " + linea);

    Usuario u(stoi(idTxt), nom, mail, stoi(ni), stoi(np), stoi(ni2));
    if (!rMejor.empty())  u.obtenerProgreso()->setMejorRacha(stoi(rMejor));
    if (!rActual.empty()) u.obtenerProgreso()->setRachaActual(stoi(rActual));
    return u;
}