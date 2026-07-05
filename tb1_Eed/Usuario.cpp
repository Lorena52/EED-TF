#include "pch.h"
#include "Usuario.h"
#include <sstream>

using namespace std;

Usuario::Usuario()
    : id(0), nombre(""), email(""),
    nivelIngles(1), nivelPortugues(1), nivelItaliano(1),
    puntajeTotal(0) {
}

Usuario::Usuario(int i, const string& n, const string& e,
    int ni, int np, int ni2)
    : id(i), nombre(n), email(e),
    nivelIngles(ni), nivelPortugues(np), nivelItaliano(ni2),
    puntajeTotal(0) {
}

Usuario::~Usuario() {
    // ya no se libera idiomaActual, porque Sistema maneja los idiomas
}

string Usuario::getNombre() const { return nombre; }
string Usuario::getEmail() const { return email; }
int Usuario::getId() const { return id; }
int Usuario::getPuntajeTotal() const { return puntajeTotal; }

Progreso* Usuario::obtenerProgreso() {
    return &progreso;
}

void Usuario::agregarPuntaje(int n) {
    puntajeTotal += n;
}

int Usuario::getNivelIngles() const { return nivelIngles; }
int Usuario::getNivelPortugues() const { return nivelPortugues; }
int Usuario::getNivelItaliano() const { return nivelItaliano; }

void Usuario::setNivelIngles(int n) { nivelIngles = n; }
void Usuario::setNivelPortugues(int n) { nivelPortugues = n; }
void Usuario::setNivelItaliano(int n) { nivelItaliano = n; }

string Usuario::serializar() const {
    return to_string(id) + ";" +
        nombre + ";" +
        email + ";" +
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

    if (idTxt.empty() || ni.empty() || np.empty() || ni2.empty()) {
        throw runtime_error("Linea invalida en archivo");
    }

    Usuario u(stoi(idTxt), nom, mail,
        stoi(ni), stoi(np), stoi(ni2));

    if (!rActual.empty()) u.obtenerProgreso()->setRachaActual(stoi(rActual));
    if (!rMejor.empty())  u.obtenerProgreso()->setMejorRacha(stoi(rMejor));

    return u;
}
