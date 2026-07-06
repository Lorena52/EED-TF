#pragma once
#include <functional>

using namespace std;

// ═══════════════════════════════════════════════════════════════
//  ArbolAVL<T>  (Arbol Binario de Busqueda BALANCEADO - AVL)
//
//  Extiende la idea del ArbolBinario<T> (ABB) del proyecto pero
//  garantizando que el arbol se mantenga BALANCEADO: para todo
//  nodo, la diferencia de alturas entre su subarbol izquierdo y
//  derecho (factor de equilibrio) es a lo sumo 1.
//
//  ¿Por que balancear?
//    - En un ABB comun, si los datos llegan ya ordenados el arbol
//      degenera en una "lista" y las operaciones caen a O(n).
//    - El AVL aplica ROTACIONES (simples y dobles) tras cada
//      insercion para restaurar el equilibrio, garantizando
//      altura O(log n) y por lo tanto insercion y busqueda en
//      O(log n) SIEMPRE (peor caso incluido).
//
//  Mismo enfoque generico del proyecto: criterio de orden por
//  function<bool(T,T)> (lambda o puntero a funcion), igual que
//  Ordenamiento<T> y ArbolBinario<T>.
//
//  Uso en el proyecto: ranking de rachas balanceado. Como el
//  ranking se inserta ya ordenado (peor caso del ABB), el AVL
//  demuestra su ventaja: altura minima garantizada.
// ═══════════════════════════════════════════════════════════════
template <typename T>
class ArbolAVL {
public:
    struct Nodo {
        T     elem;
        Nodo* izq;
        Nodo* der;
        int   altura;   // altura del subarbol con raiz en este nodo
        Nodo(T elem) : elem(elem), izq(nullptr), der(nullptr), altura(1) {}
    };

private:
    Nodo* raiz;
    unsigned int lon;
    unsigned int rotaciones;              // contador de rotaciones realizadas
    function<bool(T, T)> menor;           // criterio de orden

    // --- Auxiliares de altura y balance ---
    int alturaDe(Nodo* n) const { return (n == nullptr) ? 0 : n->altura; }

    int factorEquilibrio(Nodo* n) const {
        return (n == nullptr) ? 0 : alturaDe(n->izq) - alturaDe(n->der);
    }

    void actualizarAltura(Nodo* n) {
        int hi = alturaDe(n->izq);
        int hd = alturaDe(n->der);
        n->altura = 1 + (hi > hd ? hi : hd);
    }

    // --- ROTACIONES ---
    // Rotacion simple a la DERECHA (caso Izquierda-Izquierda):
    //        y                x
    //       / \              / \.
    //      x   C    ->      A   y
    //     / \                  / \.
    //    A   B                B   C
    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        Nodo* B = x->der;
        x->der = y;
        y->izq = B;
        actualizarAltura(y);
        actualizarAltura(x);
        rotaciones++;
        return x;   // nueva raiz del subarbol
    }

    // Rotacion simple a la IZQUIERDA (caso Derecha-Derecha):
    //      x                    y
    //     / \                  / \.
    //    A   y      ->        x   C
    //       / \              / \.
    //      B   C            A   B
    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        Nodo* B = y->izq;
        y->izq = x;
        x->der = B;
        actualizarAltura(x);
        actualizarAltura(y);
        rotaciones++;
        return y;   // nueva raiz del subarbol
    }

    // --- Insercion con rebalanceo: O(log n) garantizado ---
    Nodo* insertarRec(Nodo* n, T elem) {
        // 1) Insercion normal de ABB
        if (n == nullptr) { lon++; return new Nodo(elem); }
        if (menor(elem, n->elem)) n->izq = insertarRec(n->izq, elem);
        else                      n->der = insertarRec(n->der, elem);

        // 2) Actualizar altura del nodo actual
        actualizarAltura(n);

        // 3) Calcular factor de equilibrio y aplicar rotaciones
        int fe = factorEquilibrio(n);

        // Caso Izquierda-Izquierda -> rotacion simple derecha
        if (fe > 1 && menor(elem, n->izq->elem))
            return rotarDerecha(n);

        // Caso Derecha-Derecha -> rotacion simple izquierda
        if (fe < -1 && !menor(elem, n->der->elem))
            return rotarIzquierda(n);

        // Caso Izquierda-Derecha -> rotacion doble (izq + der)
        if (fe > 1 && !menor(elem, n->izq->elem)) {
            n->izq = rotarIzquierda(n->izq);
            return rotarDerecha(n);
        }

        // Caso Derecha-Izquierda -> rotacion doble (der + izq)
        if (fe < -1 && menor(elem, n->der->elem)) {
            n->der = rotarDerecha(n->der);
            return rotarIzquierda(n);
        }

        return n;   // ya estaba balanceado
    }

    void inordenRec(Nodo* n, function<void(T)> accion) const {
        if (n == nullptr) return;
        inordenRec(n->izq, accion);
        accion(n->elem);
        inordenRec(n->der, accion);
    }

    void destruir(Nodo* n) {
        if (n == nullptr) return;
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }

    bool balanceadoRec(Nodo* n) const {
        if (n == nullptr) return true;
        int fe = factorEquilibrio(n);
        if (fe > 1 || fe < -1) return false;
        return balanceadoRec(n->izq) && balanceadoRec(n->der);
    }

public:
    // Constructor: recibe el criterio de orden (lambda o puntero a funcion).
    ArbolAVL(function<bool(T, T)> criterio)
        : raiz(nullptr), lon(0), rotaciones(0), menor(criterio) {
    }

    ~ArbolAVL() { destruir(raiz); }

    // --- Consultas ---
    unsigned int tam()            const { return lon; }
    bool         estaVacio()      const { return lon == 0; }
    int          altura()         const { return alturaDe(raiz); }
    unsigned int getRotaciones()  const { return rotaciones; }
    bool         estaBalanceado() const { return balanceadoRec(raiz); }

    // --- Operaciones ---
    // Insercion: O(log n) garantizado gracias al rebalanceo AVL.
    void insertar(T elem) { raiz = insertarRec(raiz, elem); }

    // Busqueda: O(log n) garantizado (altura acotada por el balanceo).
    bool buscar(T elem) const {
        Nodo* aux = raiz;
        while (aux != nullptr) {
            if (!menor(elem, aux->elem) && !menor(aux->elem, elem)) return true;
            aux = menor(elem, aux->elem) ? aux->izq : aux->der;
        }
        return false;
    }

    // Recorrido inorden ascendente (segun el criterio): O(n).
    void inorden(function<void(T)> accion) const {
        inordenRec(raiz, accion);
    }

    // Cuenta cuantos elementos cumplen un predicado: O(n).
    int contarSi(function<bool(T)> pred) const {
        int total = 0;
        inordenRec(raiz, [&](T e) { if (pred(e)) total++; });
        return total;
    }
};