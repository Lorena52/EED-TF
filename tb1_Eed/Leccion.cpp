#include "pch.h"
#include "Leccion.h"

// Como Leccion es abstracta (tiene métodos virtuales puros),
// no necesita implementar nada en el .cpp
// Solo definimos el destructor virtual si queremos dejarlo explícito.

Leccion::~Leccion() {
    // Destructor virtual vacío
}

