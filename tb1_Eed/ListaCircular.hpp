#pragma once
#include <functional>

typedef unsigned int uint;

// =====================================================================
//  ListaCircular<T>
//  Lista enlazada simple CIRCULAR: el ultimo nodo apunta de nuevo al
//  primero. Se guarda un unico puntero 'ult' (al ultimo), de modo que
//  ult->sig es siempre el primer nodo. Asi insertar al inicio y al
//  final son O(1).
//
//  Estructura totalmente independiente: define su propio Nodo anidado
//  y no depende de ningun otro header.
// =====================================================================
template <typename T>
class ListaCircular {
public:
    struct Nodo {
        T     elem;
        Nodo* sig;
        Nodo(T elem) : elem(elem), sig(nullptr) {}
    };

private:
    Nodo* ult;
    uint  lon;

public:
    // --- Constructor / Destructor ---
    ListaCircular() : ult(nullptr), lon(0) {}
    ~ListaCircular() { vaciar(); }

    // --- Consultas ---
    uint  tam()       const { return lon; }
    bool  estaVacia() const { return lon == 0; }
    Nodo* primero()   const { return ult ? ult->sig : nullptr; }
    Nodo* ultimo()    const { return ult; }

    // --- Insercion ---
    void insertarInicio(T elem) {
        Nodo* nuevo = new Nodo(elem);
        if (ult == nullptr) {
            nuevo->sig = nuevo;     // se apunta a si mismo
            ult = nuevo;
        }
        else {
            nuevo->sig = ult->sig;  // nuevo pasa a ser el primero
            ult->sig = nuevo;
        }
        lon++;
    }

    void insertarFinal(T elem) {
        insertarInicio(elem);
        ult = ult->sig;             // el "primero" recien puesto pasa a ser el ultimo
    }

    // --- Eliminacion ---
    void eliminarInicio() {
        if (lon == 0) return;
        Nodo* borrar = ult->sig;
        if (lon == 1) ult = nullptr;
        else ult->sig = borrar->sig;
        delete borrar;
        lon--;
    }

    // --- Acceso ---
    T obtener(uint pos) {
        Nodo* aux = ult->sig;
        for (uint i = 0; i < pos; i++) aux = aux->sig;
        return aux->elem;
    }

    Nodo* buscar(T elem) {
        if (ult == nullptr) return nullptr;
        Nodo* aux = ult->sig;
        for (uint i = 0; i < lon; i++) {
            if (aux->elem == elem) return aux;
            aux = aux->sig;
        }
        return nullptr;
    }

    // --- Utilidades ---

    // BUGFIX: antes estaba declarada como "void ListaCircular<T>::vaciar()"
    // DENTRO de la clase (sintaxis de definicion externa), lo cual es
    // codigo ill-formed. Aqui queda como un metodo normal de la clase.
    void vaciar() {
        if (ult == nullptr) return;     // lista vacia
        Nodo* ini = ult->sig;           // primer nodo
        ult->sig = nullptr;             // rompemos el ciclo para poder recorrer hasta null
        Nodo* aux;
        while (ini != nullptr) {
            aux = ini;
            ini = ini->sig;
            delete aux;
        }
        ult = nullptr;
        lon = 0;
    }

    // METODO NUEVO 1 (lambda): recorre la lista una vuelta completa
    // aplicando una accion a cada elemento, sin modificarla.
    void recorrerCon(std::function<void(const T&)> accion) const {
        if (ult == nullptr) return;
        Nodo* aux = ult->sig;
        for (uint i = 0; i < lon; i++) {
            accion(aux->elem);
            aux = aux->sig;
        }
    }

    // METODO NUEVO 2: cuenta cuantos elementos cumplen un criterio (lambda).
    uint contarSi(std::function<bool(const T&)> pred) const {
        uint total = 0;
        if (ult == nullptr) return 0;
        Nodo* aux = ult->sig;
        for (uint i = 0; i < lon; i++) {
            if (pred(aux->elem)) total++;
            aux = aux->sig;
        }
        return total;
    }

    //RECURSIVIDAD: recorre la lista de forma recursiva
    void recorrerRecursivo(std::function<void(const T&)> accion) const {
        if (ult == nullptr) return;
        recorrerRecursivoAux(ult->sig, lon, accion);
    }

private:
    void recorrerRecursivoAux(Nodo* nodo, uint restantes,
        std::function<void(const T&)> accion) const {
        if (nodo == nullptr || restantes == 0) return;     // caso base
        accion(nodo->elem);
        recorrerRecursivoAux(nodo->sig, restantes - 1, accion);
    }
};