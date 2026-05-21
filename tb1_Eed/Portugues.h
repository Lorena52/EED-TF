#pragma once
#include "Idioma.h"
#include "ListaCircular.hpp"
#include "Palabra.h"
#include "Progreso.h"
#include "Leccion.h"
#include <iostream>
using namespace std;

class Portugues : public Idioma {
private:
    ListaCircular<Palabra> vocabulario;
public:
    Portugues();
    void mostrarTeoria() override;
    void iniciarEjercicios(Progreso& progreso) override;
    //actu para,metros
    void repasoContinuo(Progreso& progreso) override;
    void cargarVocabulario() override;
    void diccionario() override;
};
