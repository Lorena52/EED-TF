#include "pch.h"
#include "Ingles.h"
#include "Leccion.h"
#include "Progreso.h"
#include <iostream>
#include "LeccionIngles.h"
#include <cstdlib>   // rand, srand
#include <ctime>   // time

using namespace std;

Ingles::Ingles() : Idioma("EN", "Inglés") {
}

void Ingles::mostrarTeoria() {
    switch (nivel) {
    case 1:
        cout << "Teoría básica de Inglés: saludos y frases simples." << endl;
        break;
    case 2:
        cout << "Teoría intermedia: tiempos verbales y vocabulario." << endl;
        break;
    case 3:
        cout << "Teoría avanzada: estructuras complejas y modismos." << endl;
        break;
    default:
        cout << "Nivel no reconocido." << endl;
    }
}

void Ingles::iniciarEjercicios(Progreso& progreso) {
    Leccion* leccion = new LeccionIngles();
    lecciones.insertarFinal(leccion);
    switch (nivel) {
    case 1:
        leccion->ordenarOracion(progreso);
        break;
    case 2:
        leccion->completarOracion(progreso); 
        break;
    case 3:
        leccion->traduccionAvanzada(progreso);
        break;
    }

}

void Ingles::repasoContinuo(Progreso& progreso) {
    if (vocabulario.estaVacia()) {
        cout << "No hay palabras registradas." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr))); // evitar warning C4244
    auto* aux = vocabulario.primero();  // primer nodo de la lista circular
    char continuar;

    do {
        Palabra& p = aux->elem;

        if (p.getNivel() == nivel) {
            cout << "\nPalabra en inglés: " << p.getTermino() << endl;

            string opciones[4] = { p.getTraduccion(), "puerta", "perro", "cielo" };
            int correcta = 0;

            // Mezclar opciones
            for (int i = 0; i < 4; i++) {
                int j = rand() % 4;
                swap(opciones[i], opciones[j]);
                if (i == correcta) correcta = j;
                else if (j == correcta) correcta = i;
            }

            for (int i = 0; i < 4; i++) {
                cout << i + 1 << ". " << opciones[i] << endl;
            }

            int respuesta;
            cout << "Seleccione la opción correcta (1-4): ";
            cin >> respuesta;

            if (respuesta - 1 == correcta) {
                cout << "✅ Correcto!" << endl;
                p.incrementarRepaso();
                progreso.registrarAcierto();
            }
            else {
                cout << "❌ Incorrecto. La respuesta correcta era: " << opciones[correcta] << endl;
                Error e(0, "Error en repaso", "2026-05-07");
                progreso.registrarError(e);
            }

            if (progreso.getErroresSeguidos() >= 3) {
                cout << "\n⚠ Has cometido 3 errores seguidos." << endl;
                cout << "¿Desea continuar el repaso? (s/n): ";
                char op; cin >> op;
                if (op == 'n' || op == 'N') return;
                progreso.reiniciarErrores();
            }
        }

        cout << "¿Desea continuar? (s/n): ";
        cin >> continuar;

        aux = aux->sig;  // ✅ avanzar en la lista circular

    } while (continuar == 's' || continuar == 'S');
}

void Ingles::cargarVocabulario() {
    vocabulario.vaciar(); // limpiar lista antes de recargar

    if (nivel == 1) {

        vocabulario.insertarFinal(Palabra("apple", "manzana", 1));
        vocabulario.insertarFinal(Palabra("house", "casa", 1));
        vocabulario.insertarFinal(Palabra("dog", "perro", 1));
        vocabulario.insertarFinal(Palabra("cat", "gato", 1));
        vocabulario.insertarFinal(Palabra("book", "libro", 1));
        vocabulario.insertarFinal(Palabra("water", "agua", 1));
        vocabulario.insertarFinal(Palabra("food", "comida", 1));
        vocabulario.insertarFinal(Palabra("friend", "amigo", 1));
        vocabulario.insertarFinal(Palabra("school", "escuela", 1));
        vocabulario.insertarFinal(Palabra("sun", "sol", 1));
    }
    else if (nivel == 2) {
        vocabulario.insertarFinal(Palabra("car", "carro", 2));
        vocabulario.insertarFinal(Palabra("school", "escuela", 2));
        vocabulario.insertarFinal(Palabra("computer", "computadora", 2));
        vocabulario.insertarFinal(Palabra("teacher", "profesor", 2));
        vocabulario.insertarFinal(Palabra("window", "ventana", 2));
        vocabulario.insertarFinal(Palabra("street", "calle", 2));
        vocabulario.insertarFinal(Palabra("market", "mercado", 2));
        vocabulario.insertarFinal(Palabra("family", "familia", 2));
        vocabulario.insertarFinal(Palabra("language", "idioma", 2));
        vocabulario.insertarFinal(Palabra("travel", "viajar", 2));
        vocabulario.insertarFinal(Palabra("hospital", "hospital", 2));
        vocabulario.insertarFinal(Palabra("library", "biblioteca", 2));
    }
    else if (nivel == 3) {
        vocabulario.insertarFinal(Palabra("thought", "pensamiento", 3));
        vocabulario.insertarFinal(Palabra("achievement", "logro", 3));
        vocabulario.insertarFinal(Palabra("knowledge", "conocimiento", 3));
        vocabulario.insertarFinal(Palabra("responsibility", "responsabilidad", 3));
        vocabulario.insertarFinal(Palabra("environment", "medio ambiente", 3));
        vocabulario.insertarFinal(Palabra("development", "desarrollo", 3));
        vocabulario.insertarFinal(Palabra("opportunity", "oportunidad", 3));
        vocabulario.insertarFinal(Palabra("relationship", "relación", 3));
        vocabulario.insertarFinal(Palabra("experience", "experiencia", 3));
        vocabulario.insertarFinal(Palabra("communication", "comunicación", 3));
    }
}

void Ingles::mostrarDiccionarioRecursivo(ListaCircular<Palabra>::Nodo* nodo, unsigned int restantes) {
    if (nodo == nullptr || restantes == 0) return; // caso base

    nodo->elem.mostrar(); // mostrar palabra actual
    mostrarDiccionarioRecursivo(nodo->sig, restantes - 1); // llamada recursiva
}

void Ingles::diccionario() {
    if (vocabulario.estaVacia()) {
        cout << "Diccionario vacío. Cargue vocabulario primero." << endl;
        return;
    }

    cout << "\n=== Diccionario de Inglés (recursivo) ===\n";
    mostrarDiccionarioRecursivo(vocabulario.primero(), vocabulario.tam());
}
