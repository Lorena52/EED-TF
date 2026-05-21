#pragma once
#include "Leccion.h"
#include <string>
using namespace std;

class LeccionIngles : public Leccion {
public:
    void ordenarOracion(Progreso& progreso) override;
    void completarOracion(Progreso& progreso) override;
    void traduccionAvanzada(Progreso& progreso) override;
};
