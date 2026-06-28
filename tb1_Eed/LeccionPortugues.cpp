#include "pch.h"
#include <limits>
#include "LeccionPortugues.h"
#include "Ordenamiento.h"
#include "Sistema.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

static const string V_T = "\033[38;2;46;125;50m";
static const string G_T = "\033[38;2;55;55;55m";
static const string R_T = "\033[38;2;200;40;40m";

void LeccionPortugues::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        srand(time(nullptr));

        Lista<string> correcta;
        int tipo = rand() % 3;

        if (tipo == 0) {
            correcta.insertarFinal("Eu"); correcta.insertarFinal("estudo"); correcta.insertarFinal("portugues");
        }
        else if (tipo == 1) {
            correcta.insertarFinal("Ela"); correcta.insertarFinal("gosta"); correcta.insertarFinal("de"); correcta.insertarFinal("musica");
        }
        else {
            correcta.insertarFinal("Nos"); correcta.insertarFinal("jogamos"); correcta.insertarFinal("futebol");
        }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) mezclada.insertarFinal(correcta.obtener(i));
        Ordenamiento<string>::mezclar(&mezclada);

        Banner::lineaVacia();
        Banner::lineaCentrada("Ordene a frase:", G_T);
        for (unsigned int i = 0; i < mezclada.tam(); i++)
            Banner::lineaCentrada(to_string(i + 1) + ") " + mezclada.obtener(i), G_T);

        int respuestas[10];
        Banner::promptCentrado("Ingrese el orden correcto: ");
        for (unsigned int i = 0; i < correcta.tam(); i++) cin >> respuestas[i];
        cout << Banner::RESET;

        bool correcto = true;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            if (mezclada.obtener(respuestas[i] - 1) != correcta.obtener(i)) correcto = false;
        }

        if (correcto) {
            Banner::lineaCentrada("Correcto!", V_T);
            progreso.registrarAcierto();
            progreso.actualizar(1, 1);

            contador++;
            Sistema sistema;
            sistema.mostrarBarraProgreso(contador, totalPreguntas);

            Banner::lineaVacia();
            Banner::lineaCentrada("--- Racha actual ---", G_T);
            progreso.getRacha()->mostrar();
        }
        else {
            Banner::lineaCentrada("Incorrecto.", R_T);
            Error e(1, "Orden incorrecto", "2026-05-09");
            progreso.registrarError(e);
            progreso.actualizar(0, 1);

            progreso.getRacha()->reiniciar();
            Banner::lineaCentrada("--- Racha reiniciada a 0 ---", R_T);
        }

        if (progreso.getErroresSeguidos() >= 3) {
            Banner::lineaVacia();
            Banner::lineaCentrada("Has cometido 3 errores seguidos.", R_T);
            Banner::promptCentrado("Desea continuar la leccion? (s/n): ");
            char op; cin >> op;
            cout << Banner::RESET;
            if (op == 'n' || op == 'N') {
                Banner::lineaCentrada("Volviendo al menu...", G_T);
                return;
            }
            progreso.reiniciarErrores();
        }

        Banner::promptCentrado("Desea continuar? (s/n): ");
        cin >> continuar;
        cout << Banner::RESET;

    } while (continuar == 's' || continuar == 'S');
}

void LeccionPortugues::completarOracion(Progreso& progreso) {
    Cola<string> opcoes;
    int tipo = rand() % 5;

    Banner::lineaVacia();
    if (tipo == 0) {
        Banner::lineaCentrada("Complete a frase: Eu ___ portugues.", G_T);
        opcoes.encolar("estudo"); opcoes.encolar("como"); opcoes.encolar("jogo");
    }
    else if (tipo == 1) {
        Banner::lineaCentrada("Complete a frase: Ela ___ musica.", G_T);
        opcoes.encolar("gosta"); opcoes.encolar("corre"); opcoes.encolar("dorme");
    }
    else if (tipo == 2) {
        Banner::lineaCentrada("Complete a frase: Nos ___ futebol.", G_T);
        opcoes.encolar("jogamos"); opcoes.encolar("cantamos"); opcoes.encolar("estudamos");
    }
    else if (tipo == 3) {
        Banner::lineaCentrada("Complete a frase: Eles ___ filmes.", G_T);
        opcoes.encolar("assistem"); opcoes.encolar("bebem"); opcoes.encolar("escrevem");
    }
    else {
        Banner::lineaCentrada("Complete a frase: Voce ___ muito rapido.", G_T);
        opcoes.encolar("corre"); opcoes.encolar("le"); opcoes.encolar("canta");
    }

    int i = 1;
    opcoes.mostrarCon([&](string palavra) {
        Banner::lineaCentrada(to_string(i++) + ") " + palavra, G_T);
        });

    int opcion;
    Banner::promptCentrado("Opcion: ");
    cin >> opcion;
    cout << Banner::RESET;
    if (opcion == 1) {
        Banner::lineaCentrada("Correcto!", V_T);
        progreso.registrarAcierto();
        progreso.actualizar(1, 1);

        Sistema sistema;
        sistema.mostrarBarraProgreso(1, 1);

        Banner::lineaVacia();
        Banner::lineaCentrada("--- Racha actual ---", G_T);
        progreso.getRacha()->mostrar();
    }
    else {
        Banner::lineaCentrada("Incorrecto.", R_T);
        Error e(2, "Palabra incorrecta", "2026-05-08");
        progreso.registrarError(e);
        progreso.actualizar(0, 1);

        progreso.getRacha()->reiniciar();
        Banner::lineaCentrada("--- Racha reiniciada a 0 ---", R_T);
    }

    if (progreso.getErroresSeguidos() >= 3) {
        Banner::lineaVacia();
        Banner::lineaCentrada("Has cometido 3 errores seguidos.", R_T);
        Banner::promptCentrado("Desea continuar la leccion? (s/n): ");
        char op; cin >> op;
        cout << Banner::RESET;
        if (op == 'n' || op == 'N') {
            Banner::lineaCentrada("Volviendo al menu...", G_T);
            return;
        }
        progreso.reiniciarErrores();
    }
}

void LeccionPortugues::traduccionAvanzada(Progreso& progreso) {
    Banner::lineaVacia();
    Banner::lineaCentrada("=== Exercicio de Traducao Avancada ===", V_T);

    struct Frase { string portugues; string espanhol; };
    Frase frases[] = {
        {"Apesar da chuva, eles continuaram jogando futebol.", "A pesar de la lluvia, continuaron jugando futbol."},
        {"Ela esta trabalhando neste projeto ha tres meses.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"Se eu soubesse, teria ajudado voce.", "Si lo hubiera sabido, te habria ayudado."}
    };

    int total = 3, corretas = 0;
    for (int i = 0; i < total; i++) {
        Banner::lineaVacia();
        Banner::lineaCentrada("Traduza a seguinte frase para o espanhol:", G_T);
        Banner::lineaCentrada(frases[i].portugues, G_T);
        string resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Banner::promptCentrado("Respuesta: ");
        getline(cin, resposta);
        cout << Banner::RESET;

        if (resposta == frases[i].espanhol) {
            Banner::lineaCentrada("Correcto!", V_T);
            progreso.registrarAcierto();
            corretas++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(corretas, total);
        }
        else {
            Banner::lineaCentrada("Incorrecto. A traducao correta e:", R_T);
            Banner::lineaCentrada(frases[i].espanhol, G_T);
            Error e(i + 1, "Traducao incorreta", "2026-05-07");
            progreso.registrarError(e);
        }
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("Voce acertou " + to_string(corretas) + " de " + to_string(total) + " frases.", V_T);
    progreso.actualizar(corretas, total);
}