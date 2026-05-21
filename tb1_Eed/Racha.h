#pragma once
#include <iostream>
#include <string>
using namespace std;

class Racha {
private:
    int actual;   
    int maxima;     

public:
    Racha() : actual(0), maxima(0) {}     

    void registrarAcierto() {
        actual++;
        if (actual > maxima) maxima = actual;
    }

    void registrarError() {
        actual = 0; 
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