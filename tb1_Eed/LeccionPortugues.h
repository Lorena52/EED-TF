#pragma once
#include "Leccion.h"
#include "Progreso.h"
#include "Error.h"
#include "Lista.hpp"
#include "Cola.hpp"
#include <string>
using namespace std;

class LeccionPortugues : public Leccion {
public:
    void ordenarOracion(Progreso& progreso) override;
    void completarOracion(Progreso& progreso) override;
    void traduccionAvanzada(Progreso& progreso) override;
};
