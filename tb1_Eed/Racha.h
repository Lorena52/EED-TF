#pragma once
#include <iostream>
#include <string>
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

    int getActual() const { return actual   ; }
    int getMaxima()   const { return maxima; }

    void mostrar() const { cout << "\n===== RACHA =====\n"; 
    cout << "Racha actual: " << actual << endl; 
    cout << "Mejor racha: " << maxima << endl; }

    void reiniciar() { actual = 0; }
    void setMejor(int valor) {
        maxima = valor;
    }
};