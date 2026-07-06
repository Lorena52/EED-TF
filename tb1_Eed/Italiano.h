#pragma once
#include "Idioma.h"
#include "Palabra.h"

// =====================================================================
//  Italiano : public Idioma
//  Usa el 'vocabulario' heredado de Idioma (sin redeclararlo).
// =====================================================================

class Italiano : public Idioma {

public:
    Italiano();

    void mostrarTeoria() override;
    bool iniciarEjercicios(Progreso& progreso) override;
    void cargarVocabulario() override;
    void repasoContinuo(Progreso& progreso) override;
    void diccionario() override;
};