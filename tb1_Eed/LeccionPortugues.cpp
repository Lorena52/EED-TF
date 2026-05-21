#include "pch.h"
#include <limits>
#include "LeccionPortugues.h"
#include "Ordenamiento.h"
#include "Sistema.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void LeccionPortugues::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        srand(time(nullptr));

        Lista<string> correcta;
        int tipo = rand() % 3;

        if (tipo == 0) {
            correcta.insertarFinal("Eu");
            correcta.insertarFinal("estudo");
            correcta.insertarFinal("português");
        }
        else if (tipo == 1) {
            correcta.insertarFinal("Ela");
            correcta.insertarFinal("gosta");
            correcta.insertarFinal("de");
            correcta.insertarFinal("musica");
        }
        else {
            correcta.insertarFinal("Nós");
            correcta.insertarFinal("jogamos");
            correcta.insertarFinal("futebol");
        }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            mezclada.insertarFinal(correcta.obtener(i));
        }
        Ordenamiento<string>::mezclar(&mezclada);

        cout << "Ordene a frase:" << endl;
        for (unsigned int i = 0; i < mezclada.tam(); i++) {
            cout << i + 1 << ") " << mezclada.obtener(i) << endl;
        }

        int respuestas[10];
        cout << "Ingrese el orden correcto: ";
        for (unsigned int i = 0; i < correcta.tam(); i++) cin >> respuestas[i];

        bool correcto = true;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            if (mezclada.obtener(respuestas[i] - 1) != correcta.obtener(i)) correcto = false;
        }

        if (correcto) {
            cout << "Correcto!" << endl;
            progreso.registrarAcierto();
            progreso.actualizar(1, 1);

            //Avanza barra solo si es correcto
            contador++;
            Sistema sistema;
            sistema.mostrarBarraProgreso(contador, totalPreguntas);

            //Mostrar racha actual
            cout << "\n--- Racha actual ---" << endl;
            progreso.getRacha()->mostrar();
        }
        else {
            cout << "Incorrecto." << endl;
            Error e(1, "Orden incorrecto", "2026-05-09");
            progreso.registrarError(e);
            progreso.actualizar(0, 1);

            //Reiniciar racha si falla
            progreso.getRacha()->reiniciar();
            cout << "\n--- Racha reiniciada a 0 ---" << endl;
        }

        if (progreso.getErroresSeguidos() >= 3) {
            cout << "\nHas cometido 3 errores seguidos." << endl;
            cout << "¿Desea continuar la lección? (s/n): ";
            char op; cin >> op;
            if (op == 'n' || op == 'N') {
                cout << "Volviendo al menú..." << endl;
                return;
            }
            progreso.reiniciarErrores();
        }

        cout << "¿Desea continuar? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');
}

void LeccionPortugues::completarOracion(Progreso& progreso) {
    Cola<string> opcoes;
    int tipo = rand() % 5;

    if (tipo == 0) {
        cout << "Complete a frase: Eu ___ português." << endl;
        opcoes.encolar("estudo"); opcoes.encolar("como"); opcoes.encolar("jogo");
    }
    else if (tipo == 1) {
        cout << "Complete a frase: Ela ___ música." << endl;
        opcoes.encolar("gosta"); opcoes.encolar("corre"); opcoes.encolar("dorme");
    }
    else if (tipo == 2) {
        cout << "Complete a frase: Nós ___ futebol." << endl;
        opcoes.encolar("jogamos"); opcoes.encolar("cantamos"); opcoes.encolar("estudamos");
    }
    else if (tipo == 3) {
        cout << "Complete a frase: Eles ___ filmes." << endl;
        opcoes.encolar("assistem"); opcoes.encolar("bebem"); opcoes.encolar("escrevem");
    }
    else {
        cout << "Complete a frase: Você ___ muito rápido." << endl;
        opcoes.encolar("corre"); opcoes.encolar("lê"); opcoes.encolar("canta");
    }

    int i = 1;
    opcoes.mostrarCon([&](string palavra) { cout << i++ << ") " << palavra << endl; });

    int opcion; cin >> opcion;
    if (opcion == 1) {
        cout << "Correcto!" << endl;
        progreso.registrarAcierto();
        progreso.actualizar(1, 1);

        Sistema sistema;
        sistema.mostrarBarraProgreso(1, 1);

        cout << "\n--- Racha actual ---" << endl;
        progreso.getRacha()->mostrar();
    }
    else {
        cout << "Incorrecto." << endl;
        Error e(2, "Palabra incorrecta", "2026-05-08");
        progreso.registrarError(e);
        progreso.actualizar(0, 1);

        progreso.getRacha()->reiniciar();
        cout << "\n--- Racha reiniciada a 0 ---" << endl;
    }


    if (progreso.getErroresSeguidos() >= 3) {
        cout << "\nHas cometido 3 errores seguidos." << endl;
        cout << "¿Desea continuar la lección? (s/n): ";
        char op; cin >> op;
        if (op == 'n' || op == 'N') {
            cout << "Volviendo al menú..." << endl;
            return;
        }
        progreso.reiniciarErrores();
    }
}

void LeccionPortugues::traduccionAvanzada(Progreso& progreso) {
    cout << "\n=== Exercício de Tradução Avançada ===" << endl;

    struct Frase { string portugues; string espanhol; };
    Frase frases[] = {
        {"Apesar da chuva, eles continuaram jogando futebol.", "A pesar de la lluvia, continuaron jugando fútbol."},
        {"Ela está trabalhando neste projeto há três meses.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"Se eu soubesse, teria ajudado você.", "Si lo hubiera sabido, te habría ayudado."}
    };

    int total = 3, corretas = 0;
    for (int i = 0; i < total; i++) {
        cout << "\nTraduza a seguinte frase para o espanhol:\n" << frases[i].portugues << endl;
        string resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, resposta);

        if (resposta == frases[i].espanhol) {
            cout << "Correcto!" << endl;
            progreso.registrarAcierto();
            corretas++;

            // Barra solo si es correcto
            Sistema sistema;
            sistema.mostrarBarraProgreso(corretas, total);
        }
        else {
            cout << "Incorrecto. A tradução correta é:\n" << frases[i].espanhol << endl;
            Error e(i + 1, "Tradução incorreta", "2026-05-07");
            progreso.registrarError(e);
        }
    }

    cout << "\nVocê acertou " << corretas << " de " << total << " frases." << endl;
    progreso.actualizar(corretas, total);
}
