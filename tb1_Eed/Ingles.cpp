// Ingles usa: ListaCircular<Palabra> (vocabulario heredado de Idioma),
// Lista<string> (opciones de repaso) y Ordenamiento::mezclar.
#include "pch.h"
#include "Ingles.h"
#include "Sistema.h"
#include "Ordenamiento.h"
#include "Lista.hpp"
#include "LeccionIngles.h"
#include "Cola.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Ingles::Ingles() : Idioma("EN", "Ingles") {
    cargarVocabulario();
}

void Ingles::mostrarTeoria() {
    switch (nivel) {
    case 1: cout << "Teoria basica de Ingles: saludos y frases simples." << endl; break;
    case 2: cout << "Teoria intermedia: tiempos verbales y vocabulario." << endl; break;
    case 3: cout << "Teoria avanzada: estructuras complejas y modismos." << endl; break;
    default: cout << "Nivel no reconocido." << endl;
    }
}

void Ingles::iniciarEjercicios(Progreso& progreso) {
    Leccion* leccion = new LeccionIngles();
    lecciones.insertarFinal(leccion);   // historial en la lista doble heredada
    switch (nivel) {
    case 1: leccion->ordenarOracion(progreso); break;
    case 2: leccion->completarOracion(progreso); break;
    case 3: leccion->traduccionAvanzada(progreso); break;
    }
}
//INGLES
void Ingles::repasoContinuo(Progreso& progreso) {
    const int META = 10;   // 10 palabras por ronda

    if (vocabulario.estaVacia()) {
        cout << "No hay palabras registradas." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    // 1) Recolectar las palabras del nivel actual en una Lista.
    Lista<Palabra*> delNivel;
    auto* nodo = vocabulario.primero();
    for (unsigned int i = 0; i < vocabulario.tam(); i++) {
        if (nodo->elem.getNivel() == nivel) delNivel.insertarFinal(&nodo->elem);
        nodo = nodo->sig;
    }
    if (delNivel.estaVacia()) {
        cout << "No hay palabras para este nivel." << endl;
        return;
    }

    // 2) Mezclar al azar y meter hasta 10 en una COLA.
    //    La cola permite que una palabra fallada vuelva al final de la ronda.
    Ordenamiento<Palabra*>::mezclar(&delNivel);
    Cola<Palabra*> ronda;
    int cuantas = (delNivel.tam() < (unsigned)META) ? (int)delNivel.tam() : META;
    for (int i = 0; i < cuantas; i++) ronda.encolar(delNivel.obtener(i));

    // 3) Procesar la cola: acierto -> avanza barra; fallo -> se re-encola al final.
    int aciertos = 0;
    while (aciertos < cuantas && !ronda.estaVacia()) {
        Palabra* p = ronda.frente();
        ronda.desencolar();

        cout << "\n====================================" << endl;
        cout << "Palabra en ingles: " << p->getTermino() << endl;
        cout << "====================================" << endl;

        // Armar 4 opciones (1 correcta + 3 distractores) y mezclarlas.
        Lista<string> opciones;
        string correcta = p->getTraduccion();
        opciones.insertarFinal(correcta);
        opciones.insertarFinal("puerta");
        opciones.insertarFinal("perro");
        opciones.insertarFinal("cielo");
        Ordenamiento<string>::mezclar(&opciones);

        auto* on = opciones.inicio();
        int indice = 1;
        while (on != nullptr) {
            cout << indice << ". " << on->elem << endl;
            on = on->sig;
            indice++;
        }

        int respuesta;
        cout << "\nSeleccione la opcion correcta (1-4): ";
        cin >> respuesta;

        if (respuesta < 1 || respuesta > 4) {
            cout << "Opcion invalida. La palabra se repetira al final." << endl;
            ronda.encolar(p);   // vuelve al final
        }
        else if (opciones.obtener(respuesta - 1) == correcta) {
            cout << "\nCorrecto! :)" << endl;
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;   // SOLO aqui avanza la barra
        }
        else {
            cout << "\nIncorrecto. La respuesta correcta era: " << correcta << endl;
            Error e(0, "Error en repaso Ingles", "2026-05-09");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();
            ronda.encolar(p);   // la fallada reaparece al final de la ronda
        }

        // Barra de progreso + contador + racha (igual que en iniciar leccion).
        cout << "\nProgreso del repaso:" << endl;
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        cout << "Ejercicios: " << aciertos << "/" << cuantas << endl;
        cout << "Racha actual: " << progreso.getRacha()->getActual() << endl;
    }

    cout << "\n" << "=== Repaso continuo completado! Acertaste las "
        << cuantas << " palabras. ===" << endl;
}

void Ingles::cargarVocabulario() {
    vocabulario.vaciar();
    if (nivel == 1) {
        vocabulario.insertarFinal(Palabra("apple", "manzana", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("house", "casa", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("dog", "perro", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("cat", "gato", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("book", "libro", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("water", "agua", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("food", "comida", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("friend", "amigo", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("school", "escuela", "sustantivo", 1));
        vocabulario.insertarFinal(Palabra("sun", "sol", "sustantivo", 1));
    }
    else if (nivel == 2) {
        vocabulario.insertarFinal(Palabra("car", "carro", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("computer", "computadora", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("teacher", "profesor", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("window", "ventana", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("street", "calle", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("market", "mercado", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("family", "familia", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("language", "idioma", "sustantivo", 2));
        vocabulario.insertarFinal(Palabra("travel", "viajar", "verbo", 2));
        vocabulario.insertarFinal(Palabra("library", "biblioteca", "sustantivo", 2));
    }
    else if (nivel == 3) {
        vocabulario.insertarFinal(Palabra("thought", "pensamiento", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("achievement", "logro", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("knowledge", "conocimiento", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("responsibility", "responsabilidad", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("environment", "medio ambiente", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("development", "desarrollo", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("opportunity", "oportunidad", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("relationship", "relacion", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("experience", "experiencia", "sustantivo", 3));
        vocabulario.insertarFinal(Palabra("communication", "comunicacion", "sustantivo", 3));
    }
}

// RECURSIVIDAD: recorre el vocabulario nodo a nodo sin bucles.
void Ingles::mostrarDiccionarioRecursivo(ListaCircular<Palabra>::Nodo* nodo,
    unsigned int restantes) {
    if (nodo == nullptr || restantes == 0) return;   // caso base
    nodo->elem.mostrar();
    mostrarDiccionarioRecursivo(nodo->sig, restantes - 1);
}

void Ingles::diccionario() {
    if (vocabulario.estaVacia()) {
        cout << "Diccionario vacio. Cargue vocabulario primero." << endl;
        return;
    }
    cout << "\n=== Diccionario de Ingles (recursivo) ===\n";
    mostrarDiccionarioRecursivo(vocabulario.primero(), vocabulario.tam());
}