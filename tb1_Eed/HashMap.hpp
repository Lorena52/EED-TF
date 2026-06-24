#pragma once
#include <string>
#include <vector>
#include <functional>

using namespace std;

// ═══════════════════════════════════════════════════════════════
//  HASH MAP generico  <K, V>
//
//  - K : tipo de la clave (string, int, double, puntero, etc).
//  - V : tipo del valor (cualquier cosa).
//  - vector<Nodo*> buckets : cada casilla apunta al primer nodo
//    de su cadena (o nullptr si esta vacia).
//  - Colision -> cadena de nodos enlazados con 'siguiente'.
//  - Crece SOLO: cuando hay mas elementos que buckets, se hace
//    rehash (se dobla el tamaño y se reubica todo).
// ═══════════════════════════════════════════════════════════════
template <typename K, typename V>
class HashMap {
private:
    struct Nodo {
        K     clave;
        V     valor;
        Nodo* siguiente;
        Nodo(K clave, V valor) {
            this->clave = clave;
            this->valor = valor;
            this->siguiente = nullptr;
        }
    };

    vector<Nodo*> buckets;
    int           numElementos;

    int hash(K clave) {
        return std::hash<K>{}(clave) % buckets.size();
    }

    // REHASH: dobla el tamaño del vector y reubica todos los nodos.
    void rehash() {
        vector<Nodo*> viejos = buckets;                       // me guardo los buckets viejos
        buckets = vector<Nodo*>(viejos.size() * 2, nullptr);  // creo uno del doble, todo en nullptr

        for (int i = 0; i < (int)viejos.size(); i++) {        // recorro cada bucket viejo
            Nodo* actual = viejos[i];
            while (actual != nullptr) {
                Nodo* siguiente = actual->siguiente;          // me guardo el siguiente ANTES de tocar 'actual->siguiente'
                int j = hash(actual->clave);                  // recalculo el bucket con el nuevo tamaño
                actual->siguiente = buckets[j];               // engancho al inicio del bucket nuevo
                buckets[j] = actual;
                actual = siguiente;                           // sigo con el siguiente viejo
            }
        }
    }

public:
    HashMap() {
        buckets = vector<Nodo*>(1, nullptr);     // arranca con 1 bucket, va a crecer solo
        numElementos = 0;
    }

    ~HashMap() {
        for (int i = 0; i < (int)buckets.size(); i++) {
            Nodo* actual = buckets[i];
            while (actual != nullptr) {
                Nodo* aBorrar = actual;
                actual = actual->siguiente;
                delete aBorrar;
            }
        }
    }

    // INSERTAR: si la clave existe -> actualizo. Si no -> creo nodo nuevo.
    void insertar(K clave, V valor) {
        int i = hash(clave);                  // ¿en que bucket cae la clave?

        Nodo* actual = buckets[i];            // empiezo por el primer nodo del bucket
        while (actual != nullptr) {           // recorro la cadena
            if (actual->clave == clave) {     // ¿la clave ya estaba?
                actual->valor = valor;        // si -> actualizo el valor
                return;                       // y salgo (no creo nodo nuevo)
            }
            actual = actual->siguiente;       // avanzo al siguiente
        }

        Nodo* nuevo = new Nodo(clave, valor); // no estaba -> creo nodo en memoria dinamica
        nuevo->siguiente = buckets[i];        // el primero viejo pasa a ser segundo
        buckets[i] = nuevo;                   // el nuevo pasa a ser primero
        numElementos++;

        if (numElementos > (int)buckets.size()) rehash();   // ¿esta lleno? -> agrando
    }

    // BUSCAR: salto al bucket y recorro su cadena. El valor sale por 'salida'.
    bool buscar(K clave, V& salida) {
        int i = hash(clave);                  // salto directo al bucket
        Nodo* actual = buckets[i];            // empiezo por el primer nodo
        while (actual != nullptr) {           // recorro la cadena
            if (actual->clave == clave) {     // ¿es la clave exacta?
                salida = actual->valor;       // si -> saco el valor por referencia
                return true;                  // encontrado
            }
            actual = actual->siguiente;       // avanzo
        }
        return false;                         // recorri todo y no estaba
    }

    // ELIMINAR: necesito 'previo' para poder "saltar" sobre el nodo a borrar.
    bool eliminar(K clave) {
        int i = hash(clave);                              // bucket donde deberia estar
        Nodo* actual = buckets[i];                        // primer nodo del bucket
        Nodo* previo = nullptr;                           // nada antes del primero

        while (actual != nullptr) {                       // recorro la cadena
            if (actual->clave == clave) {                 // ENCONTRADO
                if (previo == nullptr)                    // caso A: era el primero
                    buckets[i] = actual->siguiente;       // el bucket apunta al segundo
                else                                      // caso B: estaba en medio/final
                    previo->siguiente = actual->siguiente;// previo "salta" sobre actual
                delete actual;                            // libero la memoria
                numElementos--;
                return true;
            }
            previo = actual;                              // avanzo: previo donde estaba actual
            actual = actual->siguiente;                   // actual avanza al siguiente
        }
        return false;                                     // no existia
    }

    // RECORRER: aplica una accion a cada par (clave, valor). Sirve para listar.
    void recorrer(function<void(K, V)> accion) {
        for (int i = 0; i < (int)buckets.size(); i++) {
            Nodo* actual = buckets[i];
            while (actual != nullptr) {
                accion(actual->clave, actual->valor);
                actual = actual->siguiente;
            }
        }
    }

    int  tam() { return numElementos; }
    bool estaVacia() { return numElementos == 0; }
};
