#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Banner.h"

using namespace std;

// ===============================================================
//  Tabla  -  Dibuja tablas/cuadros con bordes en consola.
//  Cada fila se arma como un string y se imprime CENTRADA sobre el
//  fondo blanco (usando Banner::lineaCentrada), para combinar con el
//  estilo del resto de la app. Usa bordes ASCII (+ - |) que se ven
//  en cualquier consola (los caracteres de caja Unicode salian '?').
// ===============================================================
namespace Tabla {

    // Colores de texto (paleta tipo Duolingo, oscuros para fondo blanco)
    const string T_VERDE = "\033[38;2;46;125;50m";
    const string T_GRIS = "\033[38;2;55;55;55m";

    inline string repetir(const string& s, int n) {
        string r;
        for (int i = 0; i < n; i++) r += s;
        return r;
    }

    inline string ajustar(const string& texto, int ancho) {
        string r = texto;
        while ((int)r.size() < ancho) r += " ";
        return r;
    }

    inline vector<int> calcularAnchos(const vector<string>& headers,
        const vector<vector<string>>& filas) {
        vector<int> anchos(headers.size(), 0);
        for (size_t c = 0; c < headers.size(); c++)
            anchos[c] = (int)headers[c].size();
        for (const auto& fila : filas)
            for (size_t c = 0; c < fila.size() && c < anchos.size(); c++)
                if ((int)fila[c].size() > anchos[c]) anchos[c] = (int)fila[c].size();
        return anchos;
    }

    // Borde horizontal: +-----+-----+  (ASCII)
    inline string bordeStr(const vector<int>& anchos) {
        string s = "+";
        for (size_t c = 0; c < anchos.size(); c++) {
            s += repetir("-", anchos[c] + 2);
            s += "+";
        }
        return s;
    }

    // Fila de contenido: | celda | celda |
    inline string filaStr(const vector<string>& celdas, const vector<int>& anchos) {
        string s = "|";
        for (size_t c = 0; c < anchos.size(); c++) {
            string contenido = (c < celdas.size()) ? celdas[c] : "";
            s += " " + ajustar(contenido, anchos[c]) + " |";
        }
        return s;
    }

    inline void imprimir(const string& titulo,
        const vector<string>& headers,
        const vector<vector<string>>& filas) {
        vector<int> anchos = calcularAnchos(headers, filas);

        Banner::lineaVacia();
        if (!titulo.empty())
            Banner::lineaCentrada(titulo, T_VERDE);

        // Todo centrado sobre el fondo blanco
        Banner::lineaCentrada(bordeStr(anchos), T_GRIS);
        Banner::lineaCentrada(filaStr(headers, anchos), T_VERDE);
        Banner::lineaCentrada(bordeStr(anchos), T_GRIS);

        if (filas.empty()) {
            vector<string> vacia(headers.size(), "");
            if (!vacia.empty()) vacia[0] = "(sin datos)";
            Banner::lineaCentrada(filaStr(vacia, anchos), T_GRIS);
        }
        else {
            for (const auto& fila : filas)
                Banner::lineaCentrada(filaStr(fila, anchos), T_GRIS);
        }
        Banner::lineaCentrada(bordeStr(anchos), T_GRIS);
    }
}