#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ===============================================================
//  Tabla  -  Dibuja tablas/cuadros con bordes en consola.
//  Calcula el ancho de cada columna automaticamente y alinea todo.
//  No es estructura de datos: es solo presentacion visual.
// ===============================================================
namespace Tabla {

    const string T_RESET = "\033[0m";
    const string T_CYAN = "\033[36m";
    const string T_GREEN = "\033[32m";
    const string T_YELLOW = "\033[33m";
    const string T_BOLD = "\033[1m";

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

    inline void dibujarBorde(const vector<int>& anchos, char tipo) {
        string izq, mid, der, hor = "\u2500";
        if (tipo == 't') { izq = "\u250C"; mid = "\u252C"; der = "\u2510"; }
        else if (tipo == 'm') { izq = "\u251C"; mid = "\u253C"; der = "\u2524"; }
        else { izq = "\u2514"; mid = "\u2534"; der = "\u2518"; }

        cout << T_CYAN << izq;
        for (size_t c = 0; c < anchos.size(); c++) {
            cout << repetir(hor, anchos[c] + 2);
            cout << (c + 1 < anchos.size() ? mid : der);
        }
        cout << T_RESET << endl;
    }

    inline void dibujarFila(const vector<string>& celdas,
        const vector<int>& anchos,
        bool esHeader = false) {
        cout << T_CYAN << "\u2502" << T_RESET;
        for (size_t c = 0; c < anchos.size(); c++) {
            string contenido = (c < celdas.size()) ? celdas[c] : "";
            cout << " ";
            if (esHeader) cout << T_YELLOW << T_BOLD;
            else          cout << T_GREEN;
            cout << ajustar(contenido, anchos[c]) << T_RESET;
            cout << " " << T_CYAN << "\u2502" << T_RESET;
        }
        cout << endl;
    }

    inline void imprimir(const string& titulo,
        const vector<string>& headers,
        const vector<vector<string>>& filas) {
        vector<int> anchos = calcularAnchos(headers, filas);

        if (!titulo.empty())
            cout << "\n" << T_CYAN << T_BOLD << titulo << T_RESET << endl;

        dibujarBorde(anchos, 't');
        dibujarFila(headers, anchos, true);
        dibujarBorde(anchos, 'm');
        if (filas.empty()) {
            vector<string> vacia(headers.size(), "");
            if (!vacia.empty()) vacia[0] = "(sin datos)";
            dibujarFila(vacia, anchos, false);
        }
        else {
            for (const auto& fila : filas)
                dibujarFila(fila, anchos, false);
        }
        dibujarBorde(anchos, 'b');
    }
}