#pragma once
#include <cstdlib>   // rand, srand
#include <ctime>     // time


// ═══════════════════════════════════════════════════════════════
//  Ordenamiento.h
//  Los 5 algoritmos clasicos de ordenamiento + Fisher-Yates
//  (mezcla aleatoria) aplicados a Lista<T>.
//
//  Patron interno: cada metodo publico
//      1) extrae los valores de los nodos a un arreglo temporal,
//      2) opera sobre el arreglo (ordena o mezcla),
//      3) reinyecta los valores en los nodos.
//
//  Las versiones clasicas (sobre T*) viven como metodos privados
//  de esta misma clase: NO se incluye ningun otro archivo.
//
//  Uso:
//      Ordenamiento<Empleado>::bubble    (lista, cmpSalario);
//      Ordenamiento<Empleado>::bubbleMod (lista, cmpSalario);
//      Ordenamiento<Empleado>::insertion (lista, cmpSalario);
//      Ordenamiento<Empleado>::selection (lista, cmpSalario);
//      Ordenamiento<Empleado>::shell     (lista, cmpSalario);
//      Ordenamiento<Empleado>::mezclar   (lista);   // sin comparador
// ═══════════════════════════════════════════════════════════════


template <typename T>
class Ordenamiento {

private:

    // ─── HELPERS: extraer / reinyectar ───────────────────────────

    // Copia los valores de los nodos a un arreglo nuevo en heap.
    static T* extraer(Lista<T>* lista, int& n) {
        n = (int)lista->tam();
        if (n == 0) return nullptr;
        T* arr = new T[n];
        auto* aux = lista->inicio();
        for (int i = 0; i < n; i++) { arr[i] = aux->elem; aux = aux->sig; }
        return arr;
    }

    // Sobrescribe los valores de los nodos con los del arreglo y libera el arreglo.
    static void reinyectar(Lista<T>* lista, T* arr, int n) {
        auto* aux = lista->inicio();
        for (int i = 0; i < n; i++) { aux->elem = arr[i]; aux = aux->sig; }
        delete[] arr;
    }


    // ─── ALGORITMOS CLASICOS SOBRE ARREGLO (privados) ────────────

    static void bubbleArr(T* arr, int n, bool (*comp)(T, T)) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (comp(arr[j + 1], arr[j])) {
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }

    static void bubbleModArr(T* arr, int n, bool (*comp)(T, T)) {
        bool intercambio;
        for (int i = 0; i < n - 1; i++) {
            intercambio = false;
            for (int j = 0; j < n - 1 - i; j++) {
                if (comp(arr[j + 1], arr[j])) {
                    T tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    intercambio = true;
                }
            }
            if (!intercambio) break;
        }
    }

    static void insertionArr(T* arr, int n, bool (*comp)(T, T)) {
        for (int i = 1; i < n; i++) {
            T   aux = arr[i];
            int k = i - 1;
            while (k >= 0 && comp(aux, arr[k])) {
                arr[k + 1] = arr[k];
                k--;
            }
            arr[k + 1] = aux;
        }
    }

    static void selectionArr(T* arr, int n, bool (*comp)(T, T)) {
        for (int i = 0; i < n - 1; i++) {
            int k = i;
            for (int j = i + 1; j < n; j++) {
                if (comp(arr[j], arr[k])) k = j;
            }
            T tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
        }
    }

    static void shellArr(T* arr, int n, bool (*comp)(T, T)) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T   temp = arr[i];
                int j = i;
                while (j >= gap && comp(temp, arr[j - gap])) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }

    // Fisher-Yates: mezcla aleatoria del arreglo (no necesita comparador).
    static void fisherYatesArr(T* arr, int n) {
        srand((unsigned)time(nullptr));
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            T tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }


public:

    // ─── METODOS PUBLICOS PARA LISTA ─────────────────────────────

    static void bubble(Lista<T>* lista, bool (*comp)(T, T)) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        bubbleArr(arr, n, comp);
        reinyectar(lista, arr, n);
    }

    static void bubbleMod(Lista<T>* lista, bool (*comp)(T, T)) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        bubbleModArr(arr, n, comp);
        reinyectar(lista, arr, n);
    }

    static void insertion(Lista<T>* lista, bool (*comp)(T, T)) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        insertionArr(arr, n, comp);
        reinyectar(lista, arr, n);
    }

    static void selection(Lista<T>* lista, bool (*comp)(T, T)) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        selectionArr(arr, n, comp);
        reinyectar(lista, arr, n);
    }

    static void shell(Lista<T>* lista, bool (*comp)(T, T)) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        shellArr(arr, n, comp);
        reinyectar(lista, arr, n);
    }

    // Fisher-Yates: deja la lista en orden aleatorio. Sin comparador.
    static void mezclar(Lista<T>* lista) {
        int n; T* arr = extraer(lista, n);
        if (n == 0) return;
        fisherYatesArr(arr, n);
        reinyectar(lista, arr, n);
    }
};
