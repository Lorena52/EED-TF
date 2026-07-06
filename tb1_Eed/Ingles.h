#pragma once
#include <iostream>
#include "Idioma.h"
#include "Palabra.h"

// =====================================================================
//  Ingles : public Idioma
//  Idioma concreto. NO redeclara 'vocabulario': usa el que hereda de
//  Idioma (protected). Asi se evita el shadowing que habia antes.
// =====================================================================

class Ingles : public Idioma {
private:
    // Recursividad propia de Ingles: muestra el diccionario nodo a nodo.
    void mostrarDiccionarioRecursivo(ListaCircular<Palabra>::Nodo* nodo,
        unsigned int restantes);

public:
    Ingles();

    void mostrarTeoria() override;
    bool iniciarEjercicios(Progreso& progreso) override;
    void repasoContinuo(Progreso& progreso) override;
    void cargarVocabulario()override;
    void diccionario() override;

};

