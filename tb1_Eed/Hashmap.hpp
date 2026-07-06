#pragma once
#include <string>
#include <vector>
#include <functional>
#include <type_traits>

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

    // ═══════════════════════════════════════════════════════════
    //  FUNCION HASH PROPIA (hecha por el equipo) - "hash posicional"
    //
    //  No es un algoritmo de libro (tipo djb2/FNV), sino uno pensado
    //  a partir de los datos reales de ESTA app:
    //    - Palabras del vocabulario (Ingles/Italiano/Portugues), que
    //      muchas veces comparten letras entre si (ej. "casa","caso").
    //    - Nombres de usuario generados en Sistema::generarDatasetAleatorio(),
    //      con el patron Nombre+Apellido+numero (ej. "CarlosVargas405"),
    //      donde es comun que muchos usuarios compartan el mismo Nombre
    //      o el mismo Apellido como sub-cadena.
    //
    //  Un hash que solo SUMA los caracteres (sin importar su posicion)
    //  generaria el mismo valor para "roper" y "perro", o colisionaria
    //  mucho entre nombres que comparten letras. Por eso, ademas de la
    //  longitud como semilla, cada caracter se multiplica por:
    //     (posicion + 1) * un numero primo (37)
    //  Asi el ORDEN de las letras si afecta el resultado final, y se
    //  reduce la probabilidad de colision entre palabras/nombres que
    //  comparten letras pero en distinto orden o posicion.
    //
    //  Complejidad: O(L), con L = longitud de la clave.
    // ═══════════════════════════════════════════════════════════
    unsigned long hashPropio(const string& texto) const {
        unsigned long h = static_cast<unsigned long>(texto.size()) * 101UL;
        for (size_t i = 0; i < texto.size(); i++) {
            unsigned char c = texto[i];
            h += static_cast<unsigned long>(c) * (i + 1) * 37UL;
        }
        return h;
    }

    // Convierte la clave a una representacion en texto para
    // pasarsela al hash propio. Si K ya es string, se usa tal cual;
    // si es un tipo numerico (int, long, etc.) se convierte con
    // to_string antes de aplicar djb2.
    int hash(K clave) {
        unsigned long h;
        if constexpr (is_same<K, string>::value) {
            h = hashPropio(clave);
        }
        else {
            h = hashPropio(to_string(clave));
        }
        return static_cast<int>(h % buckets.size());
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

    // Metodo de apoyo (NO modifica el HashMap): devuelve en que bucket
    // caeria una clave con la funcion hash propia. Sirve solo para
    // demostrar/depurar visualmente que el hash esta funcionando
    // (ej. imprimirlo en pantalla durante la sustentacion).
    int bucketDe(K clave) { return hash(clave); }
    int totalBuckets() const { return (int)buckets.size(); }

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