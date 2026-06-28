#pragma once
#include <iostream>
#include <string>
#include "Banner.h"
using namespace std;

class Racha {
private:
    int actual;
    int maxima;

    //RECURSIVIDAD: puntaje acumulado de la racha actual.
    int puntajeAux(int n) const {
        if (n <= 0) return 0;          // caso base
        return n + puntajeAux(n - 1);  // n + el puntaje de la racha anterior
    }

public:
    Racha() : actual(0), maxima(0) {}

    void registrarAcierto() {
        actual++;
        if (actual > maxima) maxima = actual;
    }

    void registrarError() {
        actual = 0;
    }

    int puntajeAcumulado() const {
        return puntajeAux(actual);
    }

    int getActual() const { return actual; }
    int getMaxima()   const { return maxima; }

    void mostrar() const {
        Banner::lineaCentrada("===== RACHA =====", "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Racha actual: " + to_string(actual), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Mejor racha: " + to_string(maxima), "\033[38;2;55;55;55m");
    }

    void reiniciar() { actual = 0; }
    void setMejor(int valor) {
        maxima = valor;
    }
};