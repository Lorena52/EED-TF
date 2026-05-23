#include "pch.h"
#include "Italiano.h"
#include "LeccionItaliano.h"
#include "Ordenamiento.h"
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
}
void Italiano::repasoContinuo(Progreso& progreso) {

    if (vocabulario.estaVacia()) {
        cout << "No hay palabras registradas." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    auto* aux = vocabulario.primero();

    char continuar;

    do {

        Palabra& p = aux->elem;

        if (p.getNivel() == nivel) {

            cout << "\n====================================" << endl;
            cout << "Parola in italiano: "
                << p.getTermino() << endl;
            cout << "====================================" << endl;

            // LISTA DE OPCIONES
            Lista<string> opciones;

            string correcta = p.getTraduccion();

            opciones.insertarFinal(correcta);
            opciones.insertarFinal("puerta");
            opciones.insertarFinal("perro");
            opciones.insertarFinal("cielo");

            // MEZCLAR OPCIONES
            Ordenamiento<string>::mezclar(&opciones);

            // MOSTRAR OPCIONES
            auto* nodo = opciones.inicio();

            int indice = 1;

            while (nodo != nullptr) {

                cout << indice << ". "
                    << nodo->elem << endl;

                nodo = nodo->sig;
                indice++;
            }

            int respuesta;

            cout << "\nSeleccione la opcion correcta (1-4): ";
            cin >> respuesta;

            // VALIDAR OPCION
            if (respuesta < 1 || respuesta > 4) {

                cout << "Opcion invalida." << endl;
            }
            else {

                // COMPARAR RESPUESTA
                if (opciones.obtener(respuesta - 1) == correcta) {

                    cout << "\nCorrecto! :) " << endl;

                    p.incrementarRepaso();

                    progreso.registrarAcierto();

                    cout << "\n--- Racha actual ---" << endl;

                    progreso.getRacha()->mostrar();

                    cout << "Veces repasada: "
                        << p.getVeces() << endl;
                }
                else {

                    cout << "\nIncorrecto." << endl;

                    cout << "La respuesta correcta era: "
                        << correcta << endl;

                    Error e(
                        0,
                        "Error en repaso Italiano",
                        "2026-05-07"
                    );

                    progreso.registrarError(e);

                    // REINICIAR RACHA
                    progreso.getRacha()->reiniciar();

                    cout << "\n--- Racha reiniciada ---" << endl;
                }
            }

            // CONTROL DE ERRORES SEGUIDOS
            if (progreso.getErroresSeguidos() >= 3) {

                cout << "\nHas cometido 3 errores seguidos." << endl;

                cout << "¿Desea continuar el repaso? (s/n): ";

                char op;

                cin >> op;

                if (op == 'n' || op == 'N') {

                    cout << "Volviendo al menu..." << endl;

                    return;
                }

                progreso.reiniciarErrores();
            }
        }

        cout << "\n¿Desea continuar? (s/n): ";
        cin >> continuar;

        aux = aux->sig;

    } while (continuar == 's' || continuar == 'S');
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