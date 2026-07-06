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

  
    virtual bool ordenarOracion(Progreso& progreso) = 0;
    virtual bool completarOracion(Progreso& progreso) = 0;
    virtual bool traduccionAvanzada(Progreso& progreso) = 0;
};

