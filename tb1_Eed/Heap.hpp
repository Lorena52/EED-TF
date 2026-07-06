#pragma once
#pragma once
#include <vector>
#include <utility>   // swap

using namespace std;

// ═══════════════════════════════════════════════════════════════
template <typename T>
class Heap {
private:
    vector<T>   datos;
    bool      (*compara)(T, T);


    // Sube el elemento de la posicion i mientras tenga MAS prioridad
    // que su padre. Se usa al insertar (insertamos al final y subimos).
    void subir(int i) {
        while (i > 0) {
            int padre = (i - 1) / 2;
            if (compara(datos[i], datos[padre])) {     // tengo mas prioridad que mi padre
                swap(datos[i], datos[padre]);
                i = padre;                              // ahora soy el padre, sigo subiendo
            }
            else {
                break;                                  // ya estoy bien ubicado
            }
        }
    }


    // Baja el elemento de la posicion i mientras algun hijo tenga
    // MAS prioridad que el. Se usa al extraer (movemos el ultimo a
    // la raiz y lo bajamos a su sitio).
    void bajar(int i) {
        int n = (int)datos.size();
        while (true) {
            int izq = 2 * i + 1;
            int der = 2 * i + 2;
            int mejor = i;

            if (izq < n && compara(datos[izq], datos[mejor])) mejor = izq;
            if (der < n && compara(datos[der], datos[mejor])) mejor = der;

            if (mejor == i) break;                      // yo soy el de mas prioridad, listo

            swap(datos[i], datos[mejor]);
            i = mejor;                                  // sigo bajando
        }
    }


public:
    // Crea un heap vacio. El comparador define la prioridad.
    Heap(bool (*compara)(T, T)) : compara(compara) {}


    // Cuantos elementos hay.
    int tam() { return (int)datos.size(); }

    // True si esta vacio.
    bool estaVacia() { return datos.empty(); }


    // Devuelve el elemento de la raiz (el de mas prioridad) SIN sacarlo.
    // Precondicion: el heap no debe estar vacio.
    T verTope() { return datos[0]; }


    // Inserta un elemento nuevo. Lo agrega al final y lo sube hasta
    // que se cumpla la regla del heap.
    void insertar(T elem) {
        datos.push_back(elem);
        subir((int)datos.size() - 1);
    }


    // Saca y devuelve el elemento de la raiz (el de mas prioridad).
    // Para mantener la forma de arbol completo: mueve el ultimo
    // elemento a la raiz y lo baja hasta su lugar.
    T extraer() {
        T tope = datos[0];
        datos[0] = datos.back();             // el ultimo a la raiz
        datos.pop_back();
        if (!datos.empty()) bajar(0);        // y lo bajo
        return tope;
    }
};
