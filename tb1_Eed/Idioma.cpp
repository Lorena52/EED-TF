#include "pch.h"
#include "Idioma.h"
#include <iostream> 
using namespace std;
//comentario 
Idioma::Idioma(string c, string n) : codigo(c), nombre(n), nivel(1) {}

Idioma::~Idioma() {
    //for (auto nodo = lecciones.inicio(); nodo != nullptr; nodo = nodo->sig) {
    //    delete nodo->elem; 
    //}
}


void Idioma::setNivel(int n) { nivel = n; }
int Idioma::getNivel() const { return nivel; }

void Idioma::repasoContinuo(Progreso& progreso) {
    if (vocabulario.estaVacia()) {
        cout << "No hay palabras cargadas." << endl;
        return;
    }
    auto aux = vocabulario.primero();
    for (unsigned int i = 0; i < vocabulario.tam(); i++) {
        cout << aux->elem.getTermino() << endl;
        aux = aux->sig; //La lista circular se usa para el vocabulario de cada idioma
    }
}

void Idioma::cargarVocabulario() {

}


void Idioma::diccionario() {
    if (vocabulario.estaVacia()) {
        cout << "Diccionario vacío. Cargue vocabulario primero." << endl;
        return;
    }

    cout << "\n=== Diccionario de " << nombre << " ===\n";
    auto aux = vocabulario.primero();
    unsigned int n = vocabulario.tam();

    for (unsigned int i = 0; i < n; i++) {
        aux->elem.mostrar();   
        aux = aux->sig;
    }
}