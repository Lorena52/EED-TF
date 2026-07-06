#include "pch.h"
#include "Idioma.h"
#include "Progreso.h"
#include <iostream>
using namespace std;

Idioma::Idioma(string codigo, string nombre)
    : codigo(codigo), nombre(nombre), nivel(1) {
}

Idioma::~Idioma() {
    // Liberar las lecciones creadas con 'new' en iniciarEjercicios().
    for (auto nodo = lecciones.inicio(); nodo != nullptr; nodo = nodo->sig) {
        delete nodo->elem;
    }
}

void   Idioma::setNivel(int n) { nivel = n; }
int    Idioma::getNivel() const { return nivel; }
string Idioma::getNombre() const { return nombre; }

// --- Repaso comun (recorrido simple del vocabulario) ---
void Idioma::repasoContinuo(Progreso& progreso) {
    if (vocabulario.estaVacia()) {
        cout << "No hay palabras cargadas." << endl;
        return;
    }
    vocabulario.recorrerCon([](const Palabra& p) {
        cout << p.getTermino() << endl;
        });
}

// --- Diccionario comun (recursivo sobre la lista circular) ---
void Idioma::diccionario() {
    if (vocabulario.estaVacia()) {
        cout << "Diccionario vacio. Cargue vocabulario primero." << endl;
        return;
    }
    cout << "\n=== Diccionario de " << nombre << " ===\n";
    vocabulario.recorrerRecursivo([](const Palabra& p) { p.mostrar(); });
}


