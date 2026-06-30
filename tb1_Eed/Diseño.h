#pragma once
#include <iostream>
#include <string>

using namespace std;

class Diseño {
public:

    static string color(int v) {
        switch (v) {
        case 3: return "\033[42m"; // verde
        //case 2: return "\033[48;2;55;55;55m";    // gris oscuro
        case 6: return "\033[48;2;55;55;55m"; // gris
        case 7: return "\033[48;2;255;182;193m"; // rosa claro
        default: return "\033[107m"; // blanco
        }
    }

    static void mostrar() {

        int logo[12][12] =
        {{0,0,0,0,3,0,0,0,0,0,0,0},
         {0,0,0,0,0,6,0,0,0,0,0,0},
         {0,0,0,0,6,6,6,6,0,0,0,0},
         {0,0,6,6,3,6,3,3,6,6,0,0},
         {0,6,3,3,3,6,6,3,3,3,6,0},
         {0,6,3,3,3,3,3,3,3,3,6,0},
         {0,6,3,3,3,3,3,3,3,3,6,0},
         {0,6,3,3,6,3,3,6,3,3,6,0},
         {0,6,3,7,3,3,3,3,7,3,6,0},
         {6,0,6,6,3,3,3,3,6,6,0,6},
         {6,0,0,0,6,6,6,6,0,0,0,6},
         {0,0,0,6,6,0,0,6,6,0,0,0}
        };

        cout << "\033[107m"; // fondo blanco fijo

        for (int f = 0; f < 12; f++) {

            // 🔥 IMPORTANTE: rellenar toda la línea primero
            cout << "   ";

            for (int c = 0; c < 12; c++) {
                cout << color(logo[f][c]) << "  ";
            }

            // 🔥 relleno hasta final de línea (EVITA LÍNEA NEGRA)
            cout << "\033[107m";
            cout << string(60, ' ');
            cout << "\n";
        }

        cout << "\033[0m";
    }
};