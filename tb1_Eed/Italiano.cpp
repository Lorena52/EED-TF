#include "pch.h"
#include "Italiano.h"
#include "LeccionItaliano.h"
#include "Sistema.h" 
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Italiano::Italiano() : Idioma("IT", "Italiano") {
    cargarVocabulario();
}

void Italiano::mostrarTeoria() {
    switch (nivel) {
    case 1:
        cout << "Teoria basica de Italiano: saludos y frases simples." << endl;
        break;

    case 2:
        cout << "Teoria intermedia: verbos y vocabulario cotidiano." << endl;
        break;

    case 3:
        cout << "Teoria avanzada: expresiones complejas y conversacion." << endl;
        break;

    default:
        cout << "Nivel no reconocido." << endl;
    }
}

void Italiano::iniciarEjercicios(Progreso& progreso) {

    Leccion* leccion = new LeccionItaliano();
    lecciones.insertarFinal(leccion);

    switch (nivel) {

    case 1:
        leccion-> ordenarOracion(progreso);
        break;

    case 2:
        leccion->completarOracion(progreso);
        break;

    case 3:
        leccion->traduccionAvanzada(progreso);
        break;
    }
    progreso.actualizar(nivel * 10, nivel * 10);
}

void Italiano::repasoContinuo(Progreso& progreso) {
    const int META = 10;

    if (vocabulario.estaVacia()) {
        cout << "Non ci sono parole registrate." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    Lista<Palabra*> delNivel;
    auto* nodo = vocabulario.primero();
    for (unsigned int i = 0; i < vocabulario.tam(); i++) {
        if (nodo->elem.getNivel() == nivel) delNivel.insertarFinal(&nodo->elem);
        nodo = nodo->sig;
    }
    if (delNivel.estaVacia()) {
        cout << "Non ci sono parole per questo livello." << endl;
        return;
    }

    Ordenamiento<Palabra*>::mezclar(&delNivel);
    Cola<Palabra*> ronda;
    int cuantas = (delNivel.tam() < (unsigned)META) ? (int)delNivel.tam() : META;
    for (int i = 0; i < cuantas; i++) ronda.encolar(delNivel.obtener(i));

    int aciertos = 0;
    //hito 1 
    int xpGanado = 0;
    while (aciertos < cuantas && !ronda.estaVacia()) {
        Palabra* p = ronda.frente();
        ronda.desencolar();

        cout << "\n====================================" << endl;
        cout << "Parola in italiano: " << p->getTermino() << endl;
        cout << "====================================" << endl;

        Lista<string> opciones;
        string correcta = p->getTraduccion();
        opciones.insertarFinal(correcta);
        opciones.insertarFinal("porta");
        opciones.insertarFinal("cane");
        opciones.insertarFinal("cielo");
        Ordenamiento<string>::mezclar(&opciones);

        auto* on = opciones.inicio();
        int indice = 1;
        while (on != nullptr) {
            cout << indice << ". " << on->elem << endl;
            on = on->sig;
            indice++;
        }

        int risposta;
        cout << "\nSeleziona l'opzione corretta (1-4): ";
        cin >> risposta;

        if (risposta < 1 || risposta > 4) {
            cout << "Opzione non valida. La parola tornera alla fine." << endl;
            ronda.encolar(p);
        }
        else if (opciones.obtener(risposta - 1) == correcta) {
            cout << "\nCorretto! :)" << endl;
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;
            xpGanado += 10;
        }
        else {
            cout << "\nSbagliato. La risposta corretta era: " << correcta << endl;
            Error e(0, "Error en repaso Italiano", "2026-06-10");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();
            xpGanado -= 2;
            ronda.encolar(p);
        }

        cout << "\nProgresso del ripasso:" << endl;
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        cout << "Esercizi: " << aciertos << "/" << cuantas << endl;
        cout << "Serie attuale: " << progreso.getRacha()->getActual() << endl;
    }
    if (xpGanado < 0) xpGanado = 0;
    cout << "\n=== Ripasso completato! Hai indovinato le "
        << cuantas << " parole. ===" << endl;
    progreso.actualizar(xpGanado, cuantas);
}

void Italiano::cargarVocabulario() {

    vocabulario.vaciar();

    if (nivel == 1) {

        vocabulario.insertarFinal(
            Palabra("ciao", "hola", 1));

        vocabulario.insertarFinal(
            Palabra("grazie", "gracias", 1));

        vocabulario.insertarFinal(
            Palabra("amico", "amigo", 1));

        vocabulario.insertarFinal(
            Palabra("sole", "sol", 1));

        vocabulario.insertarFinal(
            Palabra("acqua", "agua", 1));

        vocabulario.insertarFinal(
            Palabra("casa", "casa", 1));

        vocabulario.insertarFinal(
            Palabra("libro", "libro", 1));

        vocabulario.insertarFinal(
            Palabra("gatto", "gato", 1));

        vocabulario.insertarFinal(
            Palabra("cane", "perro", 1));

        vocabulario.insertarFinal(
            Palabra("scuola", "escuela", 1));
    }

    else if (nivel == 2) {

        vocabulario.insertarFinal(
            Palabra("scuola", "escuela", 2));

        vocabulario.insertarFinal(
            Palabra("libro", "libro", 2));

        vocabulario.insertarFinal(
            Palabra("finestra", "ventana", 2));

        vocabulario.insertarFinal(
            Palabra("strada", "calle", 2));

        vocabulario.insertarFinal(
            Palabra("insegnante", "profesor", 2));

        vocabulario.insertarFinal(
            Palabra("studente", "estudiante", 2));

        vocabulario.insertarFinal(
            Palabra("famiglia", "familia", 2));

        vocabulario.insertarFinal(
            Palabra("ospedale", "hospital", 2));

        vocabulario.insertarFinal(
            Palabra("telefono", "telefono", 2));

        vocabulario.insertarFinal(
            Palabra("computer", "computadora", 2));
    }

    else if (nivel == 3) {

        vocabulario.insertarFinal(
            Palabra("conoscenza", "conocimiento", 3));

        vocabulario.insertarFinal(
            Palabra("responsabilita", "responsabilidad", 3));

        vocabulario.insertarFinal(
            Palabra("consapevolezza", "conciencia", 3));

        vocabulario.insertarFinal(
            Palabra("sviluppo", "desarrollo", 3));

        vocabulario.insertarFinal(
            Palabra("apprendimento", "aprendizaje", 3));

        vocabulario.insertarFinal(
            Palabra("comunicazione", "comunicacion", 3));

        vocabulario.insertarFinal(
            Palabra("esperienza", "experiencia", 3));

        vocabulario.insertarFinal(
            Palabra("collaborazione", "colaboracion", 3));

        vocabulario.insertarFinal(
            Palabra("motivazione", "motivacion", 3));

        vocabulario.insertarFinal(
            Palabra("organizzazione", "organizacion", 3));
    }
}

void Italiano::diccionario() {

    if (vocabulario.estaVacia()) {

        cout << "Diccionario vacio." << endl;
        return;
    }

    cout << "\n=== Diccionario Italiano ===\n";

    auto aux = vocabulario.primero();

    unsigned int n = vocabulario.tam();

    for (unsigned int i = 0; i < n; i++) {

        aux->elem.mostrar();

        aux = aux->sig;
    }
}