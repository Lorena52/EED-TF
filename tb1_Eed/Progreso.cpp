#include "pch.h"
#include "Progreso.h"
#include "Banner.h"

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

void Progreso::actualizar(int puntos, int total) {
    ejerciciosTotales += total;
    puntosTotales += puntos;
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
    Banner::lineaCentrada("===== ERRORES =====", "\033[38;2;55;55;55m");

    // LAMBDA 3: define como se imprime un error (formato en un solo lugar)
    auto formatearError = [](const Error& e) {
        Banner::lineaCentrada("Error en ejercicio " + to_string(e.getIdEjercicio())
            + ": " + e.getDetalle()
            + " (" + e.getFecha() + ")", "\033[38;2;200;40;40m");
        };

    auto aux = errores.inicio();
    while (aux != nullptr) {
        formatearError(aux->elem);   // se usa la lambda
        aux = aux->sig;
    }

    if (errores.inicio() == nullptr) {
        Banner::lineaCentrada("Sin errores registrados. Buen trabajo!", "\033[38;2;46;125;50m");
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
    racha->setMejor(valor);
    racha->reiniciar();
}

// RECURSIVIDAD 1: cuenta los errores recorriendo la pila nodo a nodo.
int Progreso::contarErrores() {
    return contarErroresAux(errores.inicio());
}
int Progreso::contarErroresAux(Pila<Error>::Nodo* nodo) {
    if (nodo == nullptr) return 0;              // caso base
    return 1 + contarErroresAux(nodo->sig);     // 1 + el resto de la pila
}

float Progreso::calcularPorcentaje(int aciertos, int total) const {
    // LAMBDA 8: calcula el porcentaje evitando division por cero
    auto porcentaje = [](int a, int t) -> float {
        return (t == 0) ? 0.0f : (float)a / t * 100.0f;
        };
    return porcentaje(aciertos, total);
}

int Progreso::contarErroresDeEjercicio(int idEjercicio) {
    // LAMBDA 9 : predicado que filtra errores por id de ejercicio
    auto esDelEjercicio = [idEjercicio](const Error& e) {
        return e.getIdEjercicio() == idEjercicio;
        };
    int total = 0;
    auto* aux = errores.inicio();   // recorre la pila REAL (sin copiar)
    while (aux != nullptr) {
        if (esDelEjercicio(aux->elem)) total++;
        aux = aux->sig;
    }
    return total;
}
int Progreso::getPuntosTotales() const {
    return puntosTotales;
}

void Progreso::setPuntosTotales(int v) { puntosTotales = v; }