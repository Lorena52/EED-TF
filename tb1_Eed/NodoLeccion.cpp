#include "pch.h"
#include "NodoLeccion.h"

NodoLeccion::NodoLeccion()
    : idioma(""), nivel(1), ejercicio(""), minutosEstimado(0) {
}

NodoLeccion::NodoLeccion(string idioma, int nivel, string ejercicio, int minutosEstimado)
    : idioma(idioma), nivel(nivel), ejercicio(ejercicio), minutosEstimado(minutosEstimado) {
}

string NodoLeccion::getIdioma()    const { return idioma; }
int    NodoLeccion::getNivel()     const { return nivel; }
string NodoLeccion::getEjercicio() const { return ejercicio; }
int    NodoLeccion::getMinutos()   const { return minutosEstimado; }

string NodoLeccion::detalle() const {
    return idioma + " - Nivel " + to_string(nivel) + " (" + ejercicio + ")  ~" +
        to_string(minutosEstimado) + " min";
}
