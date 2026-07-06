#include "pch.h"
#include "MallaLecciones.h"
#include "Banner.h"
#include <iostream>
#include <limits>
using namespace std;

MallaLecciones::MallaLecciones() {
    g = new Grafo<NodoLeccion, int>(IDIOMAS * NIVELES);
}

MallaLecciones::~MallaLecciones() {
    delete g;
}

int MallaLecciones::cantidadNodos() const { return g->n; }

int MallaLecciones::indice(int idiomaIdx, int nivel) const {
    return idiomaIdx * NIVELES + (nivel - 1);
}


void MallaLecciones::cargarDatos() {
    string ejercicios[NIVELES] = { "ordenarOracion", "completarOracion", "traduccionAvanzada" };
    int minutosPorNivel[NIVELES] = { 15, 20, 30 };

    for (int i = 0; i < IDIOMAS; i++) {
        for (int niv = 1; niv <= NIVELES; niv++) {
            g->asignar(indice(i, niv),
                NodoLeccion(nombresIdioma[i], niv, ejercicios[niv - 1], minutosPorNivel[niv - 1]));
        }
        // Prerrequisitos aqui es el pre
        g->conectarDirigido(indice(i, 1), indice(i, 2), minutosPorNivel[1]);
        g->conectarDirigido(indice(i, 2), indice(i, 3), minutosPorNivel[2]);
    }
}

void MallaLecciones::listarLecciones() {
    Banner::lineaCentrada("--- Lecciones (nodos del grafo) ---", "\033[38;2;46;125;50m");
    for (int i = 0; i < g->n; i++)
        Banner::lineaCentrada(to_string(i) + " = " + g->obtener(i).detalle(),
            "\033[38;2;55;55;55m");
}

void MallaLecciones::mostrarMenuIdiomas() {
    for (int i = 0; i < IDIOMAS; i++)
        Banner::lineaCentrada(to_string(i) + " = " + nombresIdioma[i], "\033[38;2;55;55;55m");
}

// ORDEN TOPOLOGICO sobre las 9 lecciones: nunca muestra un nivel 2
// antes que su nivel 1, ni un nivel 3 antes que su nivel 2.
void MallaLecciones::ordenSugerido() {
    vector<int> orden = g->ordenarPorRequisitos();
    Banner::lineaCentrada("--- Orden sugerido (orden topologico) ---", "\033[38;2;46;125;50m");
    for (int i = 0; i < (int)orden.size(); i++)
        Banner::lineaCentrada(to_string(i + 1) + ". " + g->obtener(orden[i]).detalle(),
            "\033[38;2;55;55;55m");
}

// DFS: recorre a fondo la cadena nivel1 -> nivel2 -> nivel3 de UN idioma.
//void MallaLecciones::recorrerIdioma(int idiomaIdx) {
//    if (idiomaIdx < 0 || idiomaIdx >= IDIOMAS) {
//        cout << "   Idioma invalido.\n";
//        return;
//    }
//    int inicio = indice(idiomaIdx, 1);
//    vector<int> orden = g->dfs(inicio);
//    cout << "\n--- Recorrido DFS de " << nombresIdioma[idiomaIdx] << " ---\n";
//    for (int i = 0; i < (int)orden.size(); i++)
//        cout << "   " << (i + 1) << ". " << g->obtener(orden[i]).detalle() << endl;
//}

// DIJKSTRA: minutos minimos desde 'origen' a cada leccion alcanzable.
//void MallaLecciones::rutaMasRapida(int origen) {
//    vector<int> dist = g->rutaMasCorta(origen);
//    cout << "\n--- Ruta mas rapida desde '" << g->obtener(origen).detalle() << "' ---\n";
//    for (int i = 0; i < g->n; i++) {
//        if (i == origen) continue;
//        if (dist[i] == numeric_limits<int>::max())
//            cout << "   " << g->obtener(i).detalle() << ": no alcanzable desde aqui\n";
//        else
//            cout << "   " << g->obtener(i).detalle() << ": " << dist[i] << " min\n";
//    }
//}

void MallaLecciones::prerrequisitosDe(int nodo) {
    Banner::lineaCentrada("--- Prerrequisitos de: " + g->obtener(nodo).detalle() + " ---",
        "\033[38;2;46;125;50m");
    bool alguno = false;
    for (int i = 0; i < g->n; i++) {
        if (g->ady[i][nodo] != 0) {
            Banner::lineaCentrada("- " + g->obtener(i).detalle(), "\033[38;2;55;55;55m");
            alguno = true;
        }
    }
    if (!alguno)
        Banner::lineaCentrada("(no tiene prerrequisitos, es nivel inicial de su idioma)",
            "\033[38;2;55;55;55m");
}

int MallaLecciones::idiomaIdxPorNombre(const string& nombre) const {
    for (int i = 0; i < IDIOMAS; i++)
        if (nombresIdioma[i] == nombre) return i;
    return -1;
}

bool MallaLecciones::esNivelDesbloqueado(int idiomaIdx, int nivelActual, int nivelDeseado) {
    if (idiomaIdx < 0 || idiomaIdx >= IDIOMAS) return false;        // (1) O(1)
    if (nivelDeseado <= nivelActual) return true;                   // (2) O(1)

    int origen = indice(idiomaIdx, nivelActual);                     // (3) O(1)
    int destino = indice(idiomaIdx, nivelDeseado);                   // (4) O(1)
    return g->ady[origen][destino] != 0;                            // (5) O(1)
}

string MallaLecciones::mensajeBloqueo(int idiomaIdx, int nivelActual, int nivelDeseado) {
    int destino = indice(idiomaIdx, nivelDeseado);                                       // (1) O(1)    
    string msg = "No puedes pasar directo a '" + g->obtener(destino).detalle() +         // (2) O(1)
        "'. Segun la malla de lecciones, primero debes completar:\n";
    for (int i = 0; i < g->n; i++)                                                       // (3) O(V)
        if (g->ady[i][destino] != 0)                                                    // (4) O(1)
            msg += "      - " + g->obtener(i).detalle() + "\n";                          // (5) O(1)
    return msg;
}