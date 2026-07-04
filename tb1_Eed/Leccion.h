#pragma once
#include <string>
#include "Ejercicio.h"
#include "Lista.hpp"
#include "Cola.hpp" 
#include "Progreso.h"
#include "Error.h"

using namespace std;

class Leccion {

public:
    virtual ~Leccion();

    // Métodos comunes que cada idioma debe implementar
    virtual void ordenarOracion(Progreso& progreso) = 0;
    virtual void completarOracion(Progreso& progreso) = 0;
    virtual void traduccionAvanzada(Progreso& progreso) = 0;
};

