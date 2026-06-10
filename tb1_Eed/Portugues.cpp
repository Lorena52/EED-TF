#include "pch.h"
#include "Portugues.h"
#include "Error.h"
#include "LeccionPortugues.h"
#include <iostream>
#include "Sistema.h" 
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
    const int META = 10;

    if (vocabulario.estaVacia()) {
        cout << "Nao ha palavras registradas." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    // 1) Recolectar palabras del nivel actual.
    Lista<Palabra*> delNivel;
    auto* nodo = vocabulario.primero();
    for (unsigned int i = 0; i < vocabulario.tam(); i++) {
        if (nodo->elem.getNivel() == nivel) delNivel.insertarFinal(&nodo->elem);
        nodo = nodo->sig;
    }
    if (delNivel.estaVacia()) {
        cout << "Nao ha palavras para este nivel." << endl;
        return;
    }

    // 2) Mezclar y meter hasta 10 en una COLA.
    Ordenamiento<Palabra*>::mezclar(&delNivel);
    Cola<Palabra*> ronda;
    int cuantas = (delNivel.tam() < (unsigned)META) ? (int)delNivel.tam() : META;
    for (int i = 0; i < cuantas; i++) ronda.encolar(delNivel.obtener(i));

    // 3) Procesar: acierto avanza barra; fallo se re-encola al final.
    int aciertos = 0;
    while (aciertos < cuantas && !ronda.estaVacia()) {
        Palabra* p = ronda.frente();
        ronda.desencolar();

        cout << "\n====================================" << endl;
        cout << "Palavra em portugues: " << p->getTermino() << endl;
        cout << "====================================" << endl;

        Lista<string> opciones;
        string correcta = p->getTraduccion();
        opciones.insertarFinal(correcta);
        opciones.insertarFinal("porta");
        opciones.insertarFinal("cachorro");
        opciones.insertarFinal("ceu");
        Ordenamiento<string>::mezclar(&opciones);

        auto* on = opciones.inicio();
        int indice = 1;
        while (on != nullptr) {
            cout << indice << ". " << on->elem << endl;
            on = on->sig;
            indice++;
        }

        int resposta;
        cout << "\nSelecione a opcao correta (1-4): ";
        cin >> resposta;

        if (resposta < 1 || resposta > 4) {
            cout << "Opcao invalida. A palavra voltara ao final." << endl;
            ronda.encolar(p);
        }
        else if (opciones.obtener(resposta - 1) == correcta) {
            cout << "\nCorreto! :)" << endl;
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;
        }
        else {
            cout << "\nIncorreto. A resposta correta era: " << correcta << endl;
            Error e(0, "Error en repaso Portugues", "2026-06-10");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();
            ronda.encolar(p);
        }

        cout << "\nProgreso do repaso:" << endl;
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        cout << "Exercicios: " << aciertos << "/" << cuantas << endl;
        cout << "Sequencia atual: " << progreso.getRacha()->getActual() << endl;
    }

    cout << "\n=== Repaso continuo completado! Acertaste as "
        << cuantas << " palavras. ===" << endl;
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
