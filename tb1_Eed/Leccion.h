#pragma once
#include <string>
#include "Lista.hpp"
#include "Cola.hpp" 
#include "Progreso.h"
#include "Error.h"

using namespace std;

class Leccion {

public:
    virtual ~Leccion();

    virtual void ordenarOracion(Progreso& progreso) = 0;
    virtual void completarOracion(Progreso& progreso) = 0;
    virtual void traduccionAvanzada(Progreso& progreso) = 0;

};

