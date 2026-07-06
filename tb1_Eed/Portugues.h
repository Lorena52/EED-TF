#pragma once

#include "Idioma.h"
#include "Palabra.h"

// =====================================================================
//  Portugues : public Idioma
//  Usa el 'vocabulario' heredado de Idioma (sin redeclararlo).
// ====================================================================

class Portugues : public Idioma {
public:
    Portugues();

    void mostrarTeoria() override;
    bool iniciarEjercicios(Progreso& progreso) override;
    void repasoContinuo(Progreso& progreso) override;
    void cargarVocabulario() override;
    void diccionario() override;
};
