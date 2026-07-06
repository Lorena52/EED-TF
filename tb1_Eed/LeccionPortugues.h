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
    bool ordenarOracion(Progreso& progreso) override;
    bool completarOracion(Progreso& progreso) override;
    bool traduccionAvanzada(Progreso& progreso) override;
};
