#pragma once
#include "Leccion.h"
#include <string>
using namespace std;

class LeccionItaliano : public Leccion {
public:
    bool ordenarOracion(Progreso& progreso) override;
    bool completarOracion(Progreso& progreso) override;
    bool traduccionAvanzada(Progreso& progreso) override;
};
