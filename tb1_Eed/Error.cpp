#include "pch.h"
#include "Error.h"
Error::Error(int id, std::string d, std::string f)
    : idEjercicio(id), detalle(d), fecha(f) {
}

int Error::getIdEjercicio() const { return idEjercicio; }
string Error::getDetalle() const { return detalle; }
string Error::getFecha() const { return fecha; }