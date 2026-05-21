#pragma once
#include "Idioma.h"
#include "ListaCircular.hpp"
#include "Palabra.h"
#include "Progreso.h"
#include "LeccionItaliano.h"
#include <iostream>

using namespace std;

class Italiano : public Idioma {

private:
    ListaCircular<Palabra> vocabulario;

public:
    Italiano();

    void mostrarTeoria() override;

    void iniciarEjercicios(Progreso& progreso) override;

    void cargarVocabulario() override;

    void repasoContinuo(Progreso& progreso) override;

    void diccionario() override;
};