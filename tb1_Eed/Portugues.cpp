#include "pch.h"
#include "Portugues.h"
#include "Error.h"
#include "LeccionPortugues.h"
#include "Ordenamiento.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Portugues::Portugues() : Idioma("PT", "Portugués") {
    cargarVocabulario();
}

void Portugues::mostrarTeoria() {
    switch (nivel) {
    case 1:
        cout << "Teoria básica de Português: cumprimentos e frases simples." << endl;
        break;
    case 2:
        cout << "Teoria intermediária: tempos verbais e vocabulário." << endl;
        break;
    case 3:
        cout << "Teoria avançada: estruturas complexas e expressões idiomáticas." << endl;
        break;
    default:
        cout << "Nível não reconhecido." << endl;
    }
}

void Portugues::iniciarEjercicios(Progreso& progreso) {
    Leccion* leccion = new LeccionPortugues();
    lecciones.insertarFinal(leccion);
    switch (nivel) {
    case 1: leccion->ordenarOracion(progreso); break;
    case 2: leccion->completarOracion(progreso); break;
    case 3: leccion->traduccionAvanzada(progreso); break;
    }
}

void Portugues::repasoContinuo(Progreso& progreso) {

    if (vocabulario.estaVacia()) {
        cout << "Não há palavras registradas." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    auto* aux = vocabulario.primero();

    char continuar;

    do {

        Palabra& p = aux->elem;

        if (p.getNivel() == nivel) {

            cout << "\n====================================" << endl;
            cout << "Palavra em português: "
                << p.getTermino() << endl;
            cout << "====================================" << endl;

            // LISTA DE OPCIONES
            Lista<string> opciones;

            string correcta = p.getTraduccion();

            opciones.insertarFinal(correcta);
            opciones.insertarFinal("porta");
            opciones.insertarFinal("cachorro");
            opciones.insertarFinal("céu");

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

            int resposta;

            cout << "\nSelecione a opção correta (1-4): ";
            cin >> resposta;

            // VALIDAR OPCION
            if (resposta < 1 || resposta > 4) {

                cout << "Opção inválida." << endl;
            }
            else {

                // COMPARAR RESPUESTA
                if (opciones.obtener(resposta - 1) == correcta) {

                    cout << "\nCorreto! :) " << endl;

                    p.incrementarRepaso();

                    progreso.registrarAcierto();

                    cout << "\n--- Racha atual ---" << endl;

                    progreso.getRacha()->mostrar();

                    cout << "Vezes repasada: "
                        << p.getVeces() << endl;
                }
                else {

                    cout << "\nIncorreto." << endl;

                    cout << "A resposta correta era: "
                        << correcta << endl;

                    Error e(
                        0,
                        "Error en repaso Portugues",
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

        cout << "\nDeseja continuar? (s/n): ";
        cin >> continuar;

        aux = aux->sig;

    } while (continuar == 's' || continuar == 'S');
}


void Portugues::cargarVocabulario() {
    vocabulario.vaciar();
    if (nivel == 1) {
        vocabulario.insertarFinal(Palabra("ola", "hola", 1));
        vocabulario.insertarFinal(Palabra("adeus", "adiós", 1));
        vocabulario.insertarFinal(Palabra("casa", "casa", 1));
        vocabulario.insertarFinal(Palabra("gato", "gato", 1));
        vocabulario.insertarFinal(Palabra("cao", "perro", 1));
        vocabulario.insertarFinal(Palabra("agua", "agua", 1));
        vocabulario.insertarFinal(Palabra("livro", "libro", 1));
        vocabulario.insertarFinal(Palabra("sol", "sol", 1));
        vocabulario.insertarFinal(Palabra("mesa", "mesa", 1));
        vocabulario.insertarFinal(Palabra("amigo", "amigo", 1));
    }
    else if (nivel == 2) {
        vocabulario.insertarFinal(Palabra("livro", "libro", 2));
        vocabulario.insertarFinal(Palabra("escola", "escuela", 2));
        vocabulario.insertarFinal(Palabra("trabalho", "trabajo", 2));
        vocabulario.insertarFinal(Palabra("cidade", "ciudad", 2));
        vocabulario.insertarFinal(Palabra("janela", "ventana", 2));
        vocabulario.insertarFinal(Palabra("porta", "puerta", 2));
        vocabulario.insertarFinal(Palabra("familia", "familia", 2));
        vocabulario.insertarFinal(Palabra("professor", "profesor", 2));
        vocabulario.insertarFinal(Palabra("comida", "comida", 2));
        vocabulario.insertarFinal(Palabra("rua", "calle", 2));
    }
    else if (nivel == 3) {
        vocabulario.insertarFinal(Palabra("responsabilidade", "responsabilidad", 3));
        vocabulario.insertarFinal(Palabra("conhecimento", "conocimiento", 3));
        vocabulario.insertarFinal(Palabra("desenvolvimento", "desarrollo", 3));
        vocabulario.insertarFinal(Palabra("aprendizagem", "aprendizaje", 3));
        vocabulario.insertarFinal(Palabra("experiencia", "experiencia", 3));
        vocabulario.insertarFinal(Palabra("traduccion", "traducción", 3));
        vocabulario.insertarFinal(Palabra("comunicacao", "comunicación", 3));
        vocabulario.insertarFinal(Palabra("tecnologia", "tecnología", 3));
        vocabulario.insertarFinal(Palabra("inteligencia", "inteligencia", 3));
        vocabulario.insertarFinal(Palabra("universidade", "universidad", 3));
    }
}

void Portugues::diccionario() {
    if (vocabulario.estaVacia()) {
        cout << "Diccionario vacío. Cargue vocabulario primero." << endl;
        return;
    }

    cout << "\n=== Diccionario de Português ===\n";
    auto aux = vocabulario.primero();
    unsigned int n = vocabulario.tam();

    for (unsigned int i = 0; i < n; i++) {
        aux->elem.mostrar();
        aux = aux->sig;
    }
}
