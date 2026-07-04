#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

// ============================================================
//  Grafo<T,P>  (estructura genérica, template)
//  - Cada nodo guarda un DATO de cualquier tipo T:  valores[i]
//  - El PESO de la conexion es de tipo P (int por defecto):
//    ady[i][j]   (0 = no hay conexion)
//
//  Usado en AprendeGo! para modelar la MALLA DE TEMAS de un
//  idioma: cada nodo es un tema gramatical/vocabulario y cada
//  conexion dirigida A->B significa "A es prerrequisito de B".
// ============================================================
template <typename T, typename P = int>
class Grafo {
public:
    int n;                       // cuantos nodos hay
    vector<T> valores;           // el DATO de cada nodo (tipo T)
    vector<vector<P>> ady;       // tabla de conexiones (peso tipo P)

    Grafo(int n) {
        this->n = n;
        valores.resize(n);
        ady.assign(n, vector<P>(n, 0));
    }

    void asignar(int i, T valor) { valores[i] = valor; }
    T    obtener(int i) { return valores[i]; }

    // conexion en doble sentido (ej. red de amigos)
    void conectar(int a, int b, P peso = 1) {
        ady[a][b] = peso;
        ady[b][a] = peso;
    }

    // conexion en un solo sentido (ej. prerrequisitos, "a antes que b")
    void conectarDirigido(int a, int b, P peso = 1) {
        ady[a][b] = peso;
    }

    // BFS: recorre por niveles (lo mas cercano primero)
    vector<int> bfs(int inicio) {
        vector<bool> visitado(n, false);
        vector<int> orden;
        queue<int> cola;
        visitado[inicio] = true;
        cola.push(inicio);
        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();
            orden.push_back(actual);
            for (int vecino = 0; vecino < n; vecino++) {
                if (ady[actual][vecino] != 0 && !visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }
        return orden;
    }

    // DFS: recorre un camino completo antes de cambiar de rama
    vector<int> dfs(int inicio) {
        vector<bool> visitado(n, false);
        vector<int> orden;
        stack<int> pila;
        pila.push(inicio);
        while (!pila.empty()) {
            int actual = pila.top();
            pila.pop();
            if (visitado[actual]) continue;
            visitado[actual] = true;
            orden.push_back(actual);
            for (int vecino = n - 1; vecino >= 0; vecino--)
                if (ady[actual][vecino] != 0 && !visitado[vecino])
                    pila.push(vecino);
        }
        return orden;
    }

    // DIJKSTRA: costo minimo desde 'origen' a cada nodo
    vector<P> rutaMasCorta(int origen) {
        const P INF = numeric_limits<P>::max();
        vector<P> dist(n, INF);
        vector<bool> listo(n, false);
        dist[origen] = 0;
        for (int paso = 0; paso < n; paso++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!listo[i] && (u == -1 || dist[i] < dist[u])) u = i;
            if (u == -1 || dist[u] == INF) break;
            listo[u] = true;
            for (int v = 0; v < n; v++)
                if (ady[u][v] != 0 && dist[u] + ady[u][v] < dist[v])
                    dist[v] = dist[u] + ady[u][v];
        }
        return dist;
    }

    
    vector<int> ordenarPorRequisitos() {
        vector<int> entran(n, 0);                           // (1) O(V)
        for (int i = 0; i < n; i++)                         // (2) O(V²)
            for (int j = 0; j < n; j++)
                if (ady[i][j] != 0) entran[j]++;

        queue<int> cola;
        for (int i = 0; i < n; i++)                          // (3) O(V)
            if (entran[i] == 0) cola.push(i);

        vector<int> orden;
        while (!cola.empty()) {                            // (4) O(V²)
            int actual = cola.front();
            cola.pop();
            orden.push_back(actual);
            for (int v = 0; v < n; v++)                      //     recorre TODA la fila por cada nodo
                if (ady[actual][v] != 0 && --entran[v] == 0)
                    cola.push(v);
        }
        return orden;
    }
};
