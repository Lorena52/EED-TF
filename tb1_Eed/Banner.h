#pragma once
#include <iostream>
#include <string>

using namespace std;

// ===============================================================
//  Banner  -  Dibujo por MATRIZ de colores (estilo pixel-art).
//  Mismo concepto del proyecto "Juego Splash": matriz int[FILAS][COLUMNAS]
//  donde cada numero es un color, recorrida con doble for y pintada con
//  bloques solidos. Aqui se usan colores ANSI (igual que Sistema.cpp).
//  La matriz deletrea el logo "APRENDEGO" en letras grandes.
//    0 = vacio   1 = cyan   2 = amarillo   3 = verde   4 = magenta   5 = borde
// ===============================================================
namespace Banner {

    const int FILAS = 9;
    const int COLUMNAS = 58;

    // Bloque solido (un "pixel"). Equivalente al (char)219 del Splash.
    const string BLOQUE = "\u2588";

    // Devuelve el codigo ANSI segun el numero de color de la celda.
    inline string colorDe(int v) {
        switch (v) {
        case 1: return "\033[36m"; // cyan
        case 2: return "\033[33m"; // amarillo
        case 3: return "\033[32m"; // verde
        case 4: return "\033[35m"; // magenta
        case 5: return "\033[37m"; // blanco (borde)
        default: return "\033[0m";
        }
    }

    // MATRIZ del logo "APRENDEGO". Cada valor es un color.
    const int LOGO[FILAS][COLUMNAS] = {
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,1,1,1,0,0,2,2,2,2,0,0,3,3,3,3,0,0,4,4,4,4,4,0,1,0,0,0,1,0,2,2,2,2,0,0,3,3,3,3,3,0,0,4,4,4,4,0,0,1,1,1,0,0,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,2,0,3,0,0,0,3,0,4,0,0,0,0,0,1,1,0,0,1,0,2,0,0,0,2,0,3,0,0,0,0,0,4,0,0,0,0,0,1,0,0,0,1,0,0,5},
        {5,0,1,1,1,1,1,0,2,2,2,2,0,0,3,3,3,3,0,0,4,4,4,4,0,0,1,0,1,0,1,0,2,0,0,0,2,0,3,3,3,3,0,0,4,0,4,4,4,0,1,0,0,0,1,0,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,0,0,3,0,0,3,0,0,4,0,0,0,0,0,1,0,0,1,1,0,2,0,0,0,2,0,3,0,0,0,0,0,4,0,0,0,4,0,1,0,0,0,1,0,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,0,0,3,0,0,0,3,0,4,4,4,4,4,0,1,0,0,0,1,0,2,2,2,2,0,0,3,3,3,3,3,0,0,4,4,4,0,0,0,1,1,1,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
    };

    // Recorre la matriz con doble for y pinta cada celda (como DibujarMatriz del Splash).
    inline void dibujar() {
        for (int f = 0; f < FILAS; f++) {
            for (int c = 0; c < COLUMNAS; c++) {
                int v = LOGO[f][c];
                if (v == 0) cout << " ";
                else        cout << colorDe(v) << BLOQUE;
            }
            cout << "\033[0m" << endl;
        }
    }
}