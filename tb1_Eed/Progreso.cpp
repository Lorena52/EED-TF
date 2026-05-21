#include "pch.h"
#include "Progreso.h"

Progreso::Progreso()
    : leccionesComp(0), puntosTotales(0), ejerciciosTotales(0),
    porcentaje(0.0f), fechaUltima(""), erroresSeguidos(0) {
    racha = new Racha(); 
}

Progreso::~Progreso() {
    delete racha;          
}

Progreso::Progreso(const Progreso& otro)
    : leccionesComp(otro.leccionesComp),
    puntosTotales(otro.puntosTotales),
    ejerciciosTotales(otro.ejerciciosTotales),
    porcentaje(otro.porcentaje),
    fechaUltima(otro.fechaUltima),
    erroresSeguidos(otro.erroresSeguidos) {
    racha = new Racha(*otro.racha);
}

Progreso& Progreso::operator=(const Progreso& otro) {
    if (this == &otro) return *this;
    leccionesComp = otro.leccionesComp;
    puntosTotales = otro.puntosTotales;
    ejerciciosTotales = otro.ejerciciosTotales;
    porcentaje = otro.porcentaje;
    fechaUltima = otro.fechaUltima;
    erroresSeguidos = otro.erroresSeguidos;
    delete racha;
    racha = new Racha(*otro.racha);
    return *this;
}

void Progreso::actualizar(int aciertos, int total) {
    ejerciciosTotales += total;
    puntosTotales += aciertos;
    leccionesComp++;
    porcentaje = (ejerciciosTotales > 0)
        ? (float)puntosTotales / ejerciciosTotales * 100.0f
        : 0.0f;
}

void Progreso::reiniciar() {
    leccionesComp = 0;
    puntosTotales = 0;
    ejerciciosTotales = 0;
    porcentaje = 0.0f;
    erroresSeguidos = 0;
    racha->reiniciar();
}

void Progreso::registrarAcierto() {
    racha->registrarAcierto();
    erroresSeguidos = 0;
}

void Progreso::registrarError(const Error& e) {
    errores.apilar(e); //La pila se usa para guardar el historial de errores del usuario
    erroresSeguidos++;
    racha->registrarError();
}

void Progreso::mostrarHistorialErrores() {
    cout << "\n===== ERRORES =====\n";
    auto aux = errores.inicio();
    while (aux != nullptr) {
        cout << "Error en ejercicio " << aux->elem.getIdEjercicio()
            << ": " << aux->elem.getDetalle()
            << " (" << aux->elem.getFecha() << ")" << endl;
        aux = aux->sig;
    }
}

void Progreso::mostrarRacha() {
    racha->mostrar();
}

// Getters
float Progreso::getPorcentaje() const { return porcentaje; }
int Progreso::getLeccionesComp() const { return leccionesComp; }
int Progreso::getErroresSeguidos() const { return erroresSeguidos; }
Racha* Progreso::getRacha() const { return racha; }
Pila<Error> Progreso::verUltimosErrores() const { return errores; }

void Progreso::reiniciarErrores() {
    erroresSeguidos = 0;
}

void Progreso::setRachaActual(int valor) {
    racha->reiniciar();
    for (int i = 0; i < valor; i++) racha->registrarAcierto();
}

void Progreso::setMejorRacha(int valor) {
    racha->setMejor(valor);   // ⚠️ necesitas implementar este método en Racha
    racha->reiniciar();
}
