#pragma once
#include <functional>

using namespace std;

// ===================================================================
// === RUBRICA: IMPLEMENTACION DE ARBOL BINARIO (D) =================
// ArbolBinario<T>: ABB generico ordenado por un criterio (lambda).
// El recorrido inorden entrega los elementos ya ordenados. Se usa
// para el ranking de rachas.
// ===================================================================
template <typename T>
class ArbolBinario {
public:
    struct Nodo {
        T     elem;
        Nodo* izq;
        Nodo* der;
        Nodo(T elem) : elem(elem), izq(nullptr), der(nullptr) {}
    };

private:
    Nodo* raiz;
    unsigned int lon;
    function<bool(T, T)> menor;

    void destruir(Nodo* n) {
        if (n == nullptr) return;
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }

    Nodo* insertarRec(Nodo* n, T elem) {
        if (n == nullptr) { lon++; return new Nodo(elem); }
        if (menor(elem, n->elem)) n->izq = insertarRec(n->izq, elem);
        else                      n->der = insertarRec(n->der, elem);
        return n;
    }

    // Recorrido inorden (izq - nodo - der): entrega los elementos
    // en el orden definido por el criterio 'menor'.
    void inordenRec(Nodo* n, function<void(T)> accion) const {
        if (n == nullptr) return;
        inordenRec(n->izq, accion);
        accion(n->elem);
        inordenRec(n->der, accion);
    }

    int alturaRec(Nodo* n) const {
        if (n == nullptr) return 0;
        int hi = alturaRec(n->izq);
        int hd = alturaRec(n->der);
        return 1 + (hi > hd ? hi : hd);
    }

public:
    ArbolBinario(function<bool(T, T)> criterio)
        : raiz(nullptr), lon(0), menor(criterio) {
    }

    ~ArbolBinario() { destruir(raiz); }

    unsigned int tam()       const { return lon; }
    bool         estaVacio() const { return lon == 0; }
    int          altura()    const { return alturaRec(raiz); }

    void insertar(T elem) { raiz = insertarRec(raiz, elem); }

    bool buscar(T elem) const {
        Nodo* aux = raiz;
        while (aux != nullptr) {
            if (!menor(elem, aux->elem) && !menor(aux->elem, elem)) return true;
            aux = menor(elem, aux->elem) ? aux->izq : aux->der;
        }
        return false;
    }

    // Recorrido inorden ascendente (segun el criterio).
    void inorden(function<void(T)> accion) const {
        inordenRec(raiz, accion);
    }

    // Cuenta cuantos elementos cumplen un predicado (estilo Lista::contarSi).
    int contarSi(function<bool(T)> pred) const {
        int total = 0;
        inordenRec(raiz, [&](T e) { if (pred(e)) total++; });
        return total;
    }
};