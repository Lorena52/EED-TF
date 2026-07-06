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
#include "Hashmap.hpp"

using namespace std;

Ingles::Ingles() : Idioma("EN", "Ingles") {
    cargarVocabulario();
}

bool cmpPalabraAZ(Palabra* a, Palabra* b) {
    return a->getTermino() < b->getTermino();
}

void Ingles::mostrarTeoria() {
    switch (nivel) {
    case 1: Banner::lineaCentrada("Teoria basica de Ingles: saludos y frases simples.", "\033[38;2;55;55;55m"); break;
    case 2: Banner::lineaCentrada("Teoria intermedia: tiempos verbales y vocabulario.", "\033[38;2;55;55;55m"); break;
    case 3: Banner::lineaCentrada("Teoria avanzada: estructuras complejas y modismos.", "\033[38;2;55;55;55m"); break;
    default: Banner::lineaCentrada("Nivel no reconocido.", "\033[38;2;55;55;55m");
    }
}

bool Ingles::iniciarEjercicios(Progreso& progreso) {
    Leccion* leccion = new LeccionIngles();
    lecciones.insertarFinal(leccion);
    switch (nivel) {
    case 1: return leccion->ordenarOracion(progreso);
    case 2: return leccion->completarOracion(progreso);
    case 3: return leccion->traduccionAvanzada(progreso);
    }
    return false;
}
//INGLES
void Ingles::repasoContinuo(Progreso& progreso) {
    const int META = 10;

    if (vocabulario.estaVacia()) {
        Banner::lineaCentrada("No hay palabras registradas.", "\033[38;2;200;40;40m");
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
        Banner::lineaCentrada("No hay palabras para este nivel.", "\033[38;2;200;40;40m");
        return;
    }


    Ordenamiento<Palabra*>::mezclar(&delNivel);
    Cola<Palabra*> ronda;
    int cuantas = (delNivel.tam() < (unsigned)META) ? (int)delNivel.tam() : META;
    for (int i = 0; i < cuantas; i++) ronda.encolar(delNivel.obtener(i));

    const string VERDE_T = "\033[38;2;46;125;50m";
    const string GRIS_T = "\033[38;2;55;55;55m";
    const string ROJO_T = "\033[38;2;200;40;40m";


    HashMap<string, int> fallosPorPalabra;

    int aciertos = 0;
    while (aciertos < cuantas && !ronda.estaVacia()) {
        Palabra* p = ronda.frente();
        ronda.desencolar();

        Banner::lineaVacia();
        Banner::lineaCentrada("====================================", GRIS_T);
        Banner::lineaCentrada("Palabra en ingles: " + p->getTermino(), VERDE_T);
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

        string respaldo[] = { "puerta", "perro", "cielo", "mesa", "arbol", "rio" };
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

        int respuesta;
        Banner::lineaVacia();
        Banner::promptCentrado("Seleccione la opcion correcta (1-4): ");
        cin >> respuesta;
        cout << Banner::RESET;

        if (respuesta < 1 || respuesta > 4) {
            Banner::lineaCentrada("Opcion invalida. La palabra se repetira al final.", ROJO_T);
            ronda.encolar(p);
        }
        else if (opciones.obtener(respuesta - 1) == correcta) {
            Banner::lineaCentrada("Correcto! :)", VERDE_T);
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;
        }
        else {
            Banner::lineaCentrada("Incorrecto. La respuesta correcta era: " + correcta, ROJO_T);
            Error e(0, "Error en repaso Ingles", "2026-05-09");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();


            int vecesFallada = 0;
            fallosPorPalabra.buscar(p->getTermino(), vecesFallada);
            fallosPorPalabra.insertar(p->getTermino(), vecesFallada + 1);

            ronda.encolar(p);
        }


        Banner::lineaVacia();
        Banner::lineaCentrada("Progreso del repaso:", GRIS_T);
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        Banner::lineaCentrada("Ejercicios: " + to_string(aciertos) + "/" + to_string(cuantas), GRIS_T);
        Banner::lineaCentrada("Racha actual: " + to_string(progreso.getRacha()->getActual()), GRIS_T);
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("=== Repaso continuo completado! Acertaste las "
        + to_string(cuantas) + " palabras. ===", VERDE_T);


    if (fallosPorPalabra.tam() > 0) {
        Banner::lineaVacia();
        Banner::lineaCentrada("===== PALABRAS QUE DEBES REPASAR =====", GRIS_T);

        // Busca la palabra con mayor numero de fallos recorriendo el HashMap.
        string peorPalabra = "";
        int maxFallos = 0;

        fallosPorPalabra.recorrer([&](string palabra, int fallos) {
            Banner::lineaCentrada(palabra + " -> fallada " + to_string(fallos)
                + " vez(ces)", ROJO_T);
            if (fallos > maxFallos) {
                maxFallos = fallos;
                peorPalabra = palabra;
            }
            });

        if (peorPalabra != "") {
            Banner::lineaVacia();
            Banner::lineaCentrada("La que mas te costo fue: \"" + peorPalabra
                + "\". Te recomendamos repasarla primero.", VERDE_T);
        }
    }
    else {
        Banner::lineaVacia();
        Banner::lineaCentrada("No fallaste ninguna palabra. Excelente!", VERDE_T);
    }
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


void Ingles::mostrarDiccionarioRecursivo(ListaCircular<Palabra>::Nodo* nodo,
    unsigned int restantes) {
    if (nodo == nullptr || restantes == 0) return;
    nodo->elem.mostrar();
    mostrarDiccionarioRecursivo(nodo->sig, restantes - 1);
}

void Ingles::diccionario() {
    if (vocabulario.estaVacia()) {
        Banner::lineaCentrada("Diccionario vacio. Cargue vocabulario primero.", "\033[38;2;200;40;40m");
        return;
    }


    Lista<Palabra*> ordenado;
    auto* nodo = vocabulario.primero();
    for (unsigned int i = 0; i < vocabulario.tam(); i++) {
        ordenado.insertarFinal(&nodo->elem);
        nodo = nodo->sig;
    }


    Ordenamiento<Palabra*>::insertion(&ordenado, cmpPalabraAZ);

    Banner::lineaCentrada("=== Diccionario de Ingles (orden alfabetico) ===", "\033[38;2;55;55;55m");
    for (unsigned int i = 0; i < ordenado.tam(); i++) {
        ordenado.obtener(i)->mostrar();
    }
}