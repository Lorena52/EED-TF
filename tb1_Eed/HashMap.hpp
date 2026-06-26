#pragma once
#include <string>
#include <vector>
#include <functional>

using namespace std;

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

    void rehash() {
        vector<Nodo*> viejos = buckets;
        buckets = vector<Nodo*>(viejos.size() * 2, nullptr);

        for (int i = 0; i < (int)viejos.size(); i++) {
            Nodo* actual = viejos[i];
            while (actual != nullptr) {
                Nodo* siguiente = actual->siguiente;
                int j = hash(actual->clave);
                actual->siguiente = buckets[j];
                buckets[j] = actual;
                actual = siguiente;
            }
        }
    }

public:
    HashMap() {
        buckets = vector<Nodo*>(1, nullptr);
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

    void insertar(K clave, V valor) {
        int i = hash(clave);
        Nodo* actual = buckets[i];
        while (actual != nullptr) {
            if (actual->clave == clave) {
                actual->valor = valor;
                return;
            }
            actual = actual->siguiente;
        }
        Nodo* nuevo = new Nodo(clave, valor);
        nuevo->siguiente = buckets[i];
        buckets[i] = nuevo;
        numElementos++;
        if (numElementos > (int)buckets.size()) rehash();
    }

    bool buscar(K clave, V& salida) {
        int i = hash(clave);
        Nodo* actual = buckets[i];
        while (actual != nullptr) {
            if (actual->clave == clave) {
                salida = actual->valor;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    bool eliminar(K clave) {
        int i = hash(clave);
        Nodo* actual = buckets[i];
        Nodo* previo = nullptr;
        while (actual != nullptr) {
            if (actual->clave == clave) {
                if (previo == nullptr)
                    buckets[i] = actual->siguiente;
                else
                    previo->siguiente = actual->siguiente;
                delete actual;
                numElementos--;
                return true;
            }
            previo = actual;
            actual = actual->siguiente;
        }
        return false;
    }

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