#pragma once
#include "Idioma.h"
#include <iostream>
#include "Progreso.h"
#include "Palabra.h"
#include "Lista.hpp"
class Ingles : public Idioma {
private:
    ListaCircular<Palabra>vocabulario;
public:
    Ingles();
    void mostrarTeoria() override;
    void iniciarEjercicios(Progreso& progreso) override;
    void repasoContinuo(Progreso& progreso) override;
    void cargarVocabulario();

    void diccionario() override;

    void mostrarDiccionarioRecursivo(ListaCircular<Palabra>::Nodo* nodo, unsigned int restantes);
};

