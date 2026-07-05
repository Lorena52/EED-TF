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
        Banner::lineaCentrada("Teoria básica de Português: cumprimentos e frases simples.", "\033[38;2;55;55;55m");
        break;
    case 2:
        Banner::lineaCentrada("Teoria intermediária: tempos verbais e vocabulário.", "\033[38;2;55;55;55m");
        break;
    case 3:
        Banner::lineaCentrada("Teoria avançada: estruturas complexas e expressões idiomáticas.", "\033[38;2;55;55;55m");
        break;
    default:
        Banner::lineaCentrada("Nível não reconhecido.", "\033[38;2;55;55;55m");
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
        Banner::lineaCentrada("Nao ha palavras registradas.", "\033[38;2;200;40;40m");
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
        Banner::lineaCentrada("Nao ha palavras para este nivel.", "\033[38;2;200;40;40m");
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
        Banner::lineaCentrada("Palavra em portugues: " + p->getTermino(), VERDE_T);
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
        string respaldo[] = { "porta", "cachorro", "ceu", "mesa", "arvore", "rio" };
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

        int resposta;
        Banner::lineaVacia();
        Banner::promptCentrado("Selecione a opcao correta (1-4): ");
        cin >> resposta;
        cout << Banner::RESET;

        if (resposta < 1 || resposta > 4) {
            Banner::lineaCentrada("Opcao invalida. A palavra voltara ao final.", ROJO_T);
            ronda.encolar(p);
        }
        else if (opciones.obtener(resposta - 1) == correcta) {
            Banner::lineaCentrada("Correto! :)", VERDE_T);
            p->incrementarRepaso();
            progreso.registrarAcierto();
            aciertos++;
        }
        else {
            Banner::lineaCentrada("Incorreto. A resposta correta era: " + correcta, ROJO_T);
            Error e(0, "Error en repaso Portugues", "2026-06-10");
            progreso.registrarError(e);
            progreso.getRacha()->reiniciar();
            ronda.encolar(p);
        }

        Banner::lineaVacia();
        Banner::lineaCentrada("Progreso do repaso:", GRIS_T);
        Sistema::mostrarBarraProgreso(aciertos, cuantas);
        Banner::lineaCentrada("Exercicios: " + to_string(aciertos) + "/" + to_string(cuantas), GRIS_T);
        Banner::lineaCentrada("Sequencia atual: " + to_string(progreso.getRacha()->getActual()), GRIS_T);
    }

    Banner::lineaCentrada("=== Repaso continuo completado! Acertaste as "
        + to_string(cuantas) + " palavras. ===", "\033[38;2;46;125;50m");
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
        Banner::lineaCentrada("Diccionario vacío. Cargue vocabulario primero.", "\033[38;2;55;55;55m");
        return;
    }

    Banner::lineaCentrada("=== Diccionario de Português ===", "\033[38;2;55;55;55m");
    auto aux = vocabulario.primero();
    unsigned int n = vocabulario.tam();

    for (unsigned int i = 0; i < n; i++) {
        aux->elem.mostrar();
        aux = aux->sig;
    }
}