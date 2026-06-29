#pragma once
#include <iostream>
#include <string>

using namespace std;

// ═══════════════════════════════════════════════════════════════
//  Banner  -  Dibujo por MATRIZ de colores (estilo pixel-art),
//  inspirado en DibujarMatriz del proyecto "Juego Splash".
//
//  - Cada celda de la matriz es un color; el "pixel" se pinta como un
//    BLOQUE DE COLOR DE FONDO, por lo que se ve como un cuadrado solido
//    real, sin depender de la fuente de la consola.
//  - Toda la pantalla se pinta con FONDO BLANCO (simula un Windows Form).
//  - El logo dice "APRENDE GO" (palabras separadas), centrado, con una
//    paleta tipo Duolingo en tonos OSCUROS para contrastar con el blanco.
//
//  Paleta (colores de FONDO de cada bloque, ANSI 24-bit):
//    1 = verde fuerte  (#58CC02)
//    2 = verde lima    (#89E219)
//    3 = gris oscuro   (#4B4B4B)
//    5 = verde fuerte  (borde del logo, #58CC02)
// ═══════════════════════════════════════════════════════════════
namespace Banner {

    const int FILAS = 9;
    const int COLUMNAS = 65;

    const string RESET = "\033[0m";
    const string FONDO_FORM = "\033[107m";  // fondo BLANCO brillante (el "Form")
    const string TXT_OSCURO = "\033[38;2;75;75;75m"; // gris oscuro para texto

    // Color de FONDO de cada pixel del logo (ANSI verdad RGB: 48;2;R;G;B).
    inline string bgPixel(int v) {
        switch (v) {
        case 1: return "\033[48;2;46;125;50m";  // verde oscuro
        case 2: return "\033[48;2;85;160;30m";  // verde medio
        case 3: return "\033[48;2;55;55;55m";   // gris oscuro
        case 5: return "\033[48;2;46;125;50m";  // borde: verde oscuro
        default: return FONDO_FORM;             // fondo del form (blanco)
        }
    }

    // MATRIZ del logo "APRENDE GO!". Cada valor es un color.
    const int LOGO[FILAS][COLUMNAS] = {
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,1,1,1,0,0,2,2,2,2,0,0,3,3,3,3,0,0,1,1,1,1,1,0,2,0,0,0,2,0,3,3,3,3,0,0,1,1,1,1,1,0,0,0,0,0,2,2,2,2,0,0,3,3,3,0,0,0,0,4,4,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,2,0,3,0,0,0,3,0,1,0,0,0,0,0,2,2,0,0,2,0,3,0,0,0,3,0,1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3,0,0,0,3,0,0,0,4,4,0,5},
        {5,0,1,1,1,1,1,0,2,2,2,2,0,0,3,3,3,3,0,0,1,1,1,1,0,0,2,0,2,0,2,0,3,0,0,0,3,0,1,1,1,1,0,0,0,0,0,2,0,2,2,2,0,3,0,0,0,3,0,0,0,4,4,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,0,0,3,0,0,3,0,0,1,0,0,0,0,0,2,0,0,2,2,0,3,0,0,0,3,0,1,0,0,0,0,0,0,0,0,2,0,0,0,2,0,3,0,0,0,3,0,0,0,0,0,0,5},
        {5,0,1,0,0,0,1,0,2,0,0,0,0,0,3,0,0,0,3,0,1,1,1,1,1,0,2,0,0,0,2,0,3,3,3,3,0,0,1,1,1,1,1,0,0,0,0,0,2,2,2,0,0,0,3,3,3,0,0,0,0,4,4,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
    };

    // --- Dimensiones reales de la ventana (implementadas en Banner.cpp,
    //     donde se incluye <Windows.h> aislado) ---
    int anchoConsola();
    int altoConsola();

    // Linea de texto CENTRADA sobre el fondo blanco del form.
    inline void lineaCentrada(const string& texto, const string& colorTexto) {
        int ancho = anchoConsola();
        int izq = (ancho - (int)texto.size()) / 2;
        if (izq < 0) izq = 0;
        int der = ancho - (int)texto.size() - izq;
        if (der < 0) der = 0;
        cout << FONDO_FORM;
        for (int i = 0; i < izq; i++) cout << " ";
        cout << colorTexto << texto << TXT_OSCURO;
        for (int i = 0; i < der; i++) cout << " ";
        cout << RESET << "\n";
    }

    // Linea totalmente blanca (fondo del form), a todo el ancho.
    inline void lineaVacia() {
        int ancho = anchoConsola();
        cout << FONDO_FORM;
        for (int i = 0; i < ancho; i++) cout << " ";
        cout << RESET << "\n";
    }

    // Dibuja el LOGO (matriz) centrado. Cada pixel es un bloque de color
    // de fondo. Se usa 1 espacio por pixel para que el logo quepa completo
    // en el ancho de la ventana sin partirse.
    inline void dibujarLogo() {
        int ancho = anchoConsola();
        int anchoLogo = COLUMNAS;          // 1 caracter por pixel
        int izq = (ancho - anchoLogo) / 2;
        if (izq < 0) izq = 0;
        int der = ancho - anchoLogo - izq;
        if (der < 0) der = 0;

        for (int f = 0; f < FILAS; f++) {
            cout << FONDO_FORM;
            for (int i = 0; i < izq; i++) cout << " ";
            for (int c = 0; c < COLUMNAS; c++) {
                cout << bgPixel(LOGO[f][c]) << " ";   // 1 espacio por pixel
            }
            cout << FONDO_FORM;
            for (int i = 0; i < der; i++) cout << " ";
            cout << RESET << "\n";
        }
    }

    // Muestra un texto (prompt) centrado sobre el fondo blanco y deja el
    // cursor en una linea centrada, manteniendo fondo blanco/texto oscuro
    // mientras el usuario escribe. Usar antes de un cin.
    inline void promptCentrado(const string& texto) {
        int ancho = anchoConsola();
        int izq = (ancho - (int)texto.size()) / 2;
        if (izq < 0) izq = 0;
        cout << FONDO_FORM;
        for (int i = 0; i < izq; i++) cout << " ";
        cout << TXT_OSCURO << texto;
        // se deja el fondo/texto activos para que lo escrito se vea oscuro
        cout << "\033[107m\033[38;2;55;55;55m";
    }

    // Pinta SOLO el fondo blanco del "Form" en toda la pantalla y deja el
    // cursor arriba con color de texto oscuro. Se usa en las demas pantallas
    // (sin logo): da el mismo fondo blanco uniforme en toda la app.
    inline void fondoForm() {
        cout << FONDO_FORM;
        int alto = altoConsola();
        for (int i = 0; i < alto; i++) lineaVacia();
        cout << "\033[H";                  // cursor arriba a la izquierda
        cout << FONDO_FORM << TXT_OSCURO;  // fondo blanco + texto oscuro
    }

    // Pinta el "Windows Form": fondo blanco en toda la pantalla + logo arriba.
    inline void dibujar() {
        cout << FONDO_FORM;
        int alto = altoConsola();
        for (int i = 0; i < alto; i++) lineaVacia();
        cout << "\033[H"; // cursor arriba a la izquierda
        lineaVacia();
        dibujarLogo();
        lineaVacia();
    }
}