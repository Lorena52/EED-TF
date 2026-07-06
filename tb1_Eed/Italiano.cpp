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
        Banner::lineaCentrada("Teoria basica de Italiano: saludos y frases simples.", "\033[38;2;55;55;55m");
        break;

    case 2:
        Banner::lineaCentrada("Teoria intermedia: verbos y vocabulario cotidiano.", "\033[38;2;55;55;55m");
        break;

    case 3:
        Banner::lineaCentrada("Teoria avanzada: expresiones complejas y conversacion.", "\033[38;2;55;55;55m");
        break;

    default:
        Banner::lineaCentrada("Nivel no reconocido.", "\033[38;2;55;55;55m");
    }
}

bool Italiano::iniciarEjercicios(Progreso& progreso) {

    Leccion* leccion = new LeccionItaliano();
    lecciones.insertarFinal(leccion);

    switch (nivel) {

    case 1:
        return leccion->ordenarOracion(progreso);

    case 2:
        return leccion->completarOracion(progreso);

    case 3:
        return leccion->traduccionAvanzada(progreso);
    }
    return false;
}

void Italiano::repasoContinuo(Progreso& progreso) {
    const int META = 10;

    if (vocabulario.estaVacia()) {
        Banner::lineaCentrada("Non ci sono parole registrate.", "\033[38;2;200;40;40m");
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
        Banner::lineaCentrada("Non ci sono parole per questo livello.", "\033[38;2;200;40;40m");
        return;
    }

    Ordenamiento<Palabra*>::mezclar(&delNivel);
    Cola<Palabra*> ronda;
    int cuantas = (delNivel.tam() < (unsigned)META) ? (int)delNivel.tam() : META;
    for (int i = 0; i < cuantas; i++) ronda.encolar(delNivel.obtener(i));

    int aciertos = 0;
    const string VERDE_T = "\033[38;2;46;125;50m";
    const string GRIS_T = "\033[38;2;55;55;55m";
    const string ROJO_T = "\033[38;2;200;40;40m";
    while (aciertos < cuantas && !ronda.estaVacia()) {
        Palabra* p = ronda.frente();
        ronda.desencolar();

        Banner::lineaVacia();
        Banner::lineaCentrada("====================================", GRIS_T);
        Banner::lineaCentrada("Parola in italiano: " + p->getTermino(), VERDE_T);
        Banner::lineaCentrada("====================================", GRIS_T);


        Lista<string> opciones;
        string correcta = p->getTraduccion();
        opciones.insertarFinal(correcta);

        Lista<string> candidatas;
        for (unsigned int i = 0; i < delNivel.tam(); i++) {
            string trad = delNivel.obtener(i)->getTraduccion();
            if (trad == correcta) continue;
            bool yaEsta = false;
            for (unsigned int j = 0; j < candidatas.tam(); j++)
                if (candidatas.obtener(j) == trad) { yaEsta = true; break; }
            if (!yaEsta) candidatas.insertarFinal(trad);
        }
        string respaldo[] = { "porta", "cane", "cielo", "tavolo", "albero", "fiume" };
        for (int r = 0; r < 6; r++) {
            if (respaldo[r] == correcta) continue;
            bool yaEsta = false;
            for (unsigned int j = 0; j < candidatas.tam(); j++)
                if (candidatas.obtener(j) == respaldo[r]) { yaEsta = true; break; }
            if (!yaEsta) candidatas.insertarFinal(respaldo[r]);
        }
        Ordenamiento<string>::mezclar(&candidatas);
        for (unsigned int i = 0; i < candidatas.tam() && opciones.tam() < 4; i++)
            opciones.insertarFinal(candidatas.obtener(i));
        Ordenamiento<string>::mezclar(&opciones);

        auto* on = opciones.inicio();
        int indice = 1;
        while (on != nullptr) {
            Banner::lineaCentrada(to_string(indice) + ". " + on->elem, GRIS_T);
            on = on->sig;
            indice++;
        }

        int risposta;
        Banner::lineaVacia();
        Banner::promptCentrado("Seleziona l'opzione corretta (1-4): ");
        cin >> risposta;
        cout << Banner::RESET;

        if (risposta < 1 || risposta > 4) {
            Banner::lineaCentrada("Opzione non valida. La parola tornera alla fine.", ROJO_T);
            ronda.encolar(p);
        }
        else if (opciones.obtener(risposta - 1) == correcta) {
            Banner::lineaCentrada("Corretto! :)", VERDE_T);
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;
        }
        else {
            Banner::lineaCentrada("Sbagliato. La risposta corretta era: " + correcta, ROJO_T);
            Error e(0, "Error en repaso Italiano", "2026-06-10");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();
            ronda.encolar(p);
        }

        Banner::lineaVacia();
        Banner::lineaCentrada("Progresso del ripasso:", GRIS_T);
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        Banner::lineaCentrada("Esercizi: " + to_string(aciertos) + "/" + to_string(cuantas), GRIS_T);
        Banner::lineaCentrada("Serie attuale: " + to_string(progreso.getRacha()->getActual()), GRIS_T);
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("=== Ripasso completato! Hai indovinato le "
        + to_string(cuantas) + " parole. ===", VERDE_T);
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

        Banner::lineaCentrada("Diccionario vacio.", "\033[38;2;200;40;40m");
        return;
    }

    Banner::lineaCentrada("=== Diccionario Italiano ===", "\033[38;2;55;55;55m");

    auto aux = vocabulario.primero();

    unsigned int n = vocabulario.tam();

    for (unsigned int i = 0; i < n; i++) {

        aux->elem.mostrar();

        aux = aux->sig;
    }
}