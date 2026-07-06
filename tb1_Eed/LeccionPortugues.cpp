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

bool LeccionPortugues::ordenarOracion(Progreso& progreso) {
    // Antes esto era un do-while con "Desea continuar? (s/n)" que dejaba
    // seguir respondiendo sin limite, por eso la barra de progreso podia
    // pasar de 100%. Ahora se hacen EXACTAMENTE totalPreguntas rondas.
    int totalPreguntas = 3;
    int aciertos = 0;

    for (int ronda = 1; ronda <= totalPreguntas; ronda++) {
        srand(time(nullptr) + ronda);

        system("cls");
        Banner::fondoForm();

        Lista<string> correcta;
        int tipo = rand() % 5;

        if (tipo == 0) {
            correcta.insertarFinal("Eu"); correcta.insertarFinal("estudo"); correcta.insertarFinal("portugues");
        }
        else if (tipo == 1) {
            correcta.insertarFinal("Ela"); correcta.insertarFinal("gosta"); correcta.insertarFinal("de"); correcta.insertarFinal("musica");
        }
        else if (tipo == 2) {
            correcta.insertarFinal("Nos"); correcta.insertarFinal("jogamos"); correcta.insertarFinal("futebol");
        }
        else if (tipo == 3) {
            correcta.insertarFinal("Ele"); correcta.insertarFinal("le"); correcta.insertarFinal("livros");
        }
        else {
            correcta.insertarFinal("Voce"); correcta.insertarFinal("fala"); correcta.insertarFinal("portugues");
        }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) mezclada.insertarFinal(correcta.obtener(i));
        Ordenamiento<string>::mezclar(&mezclada);

        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(ronda) + " de " + to_string(totalPreguntas), G_T);
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
            aciertos++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(ronda, totalPreguntas);

            Banner::lineaVacia();
            Banner::lineaCentrada("--- Racha actual ---", G_T);
            progreso.getRacha()->mostrar();
        }
        else {
            Banner::lineaCentrada("Incorrecto.", R_T);
            Error e(1, "Orden incorrecto", "2026-05-09");
            progreso.registrarError(e);
            progreso.actualizar(0, 1);

            Sistema sistema;
            sistema.mostrarBarraProgreso(ronda, totalPreguntas);

            progreso.getRacha()->reiniciar();
            Banner::lineaCentrada("--- Racha reiniciada a 0 ---", R_T);
        }

        Banner::lineaVacia();
        Banner::promptCentrado("Presione ENTER para continuar...");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        cout << Banner::RESET;
    }

    return aciertos == totalPreguntas;
}

bool LeccionPortugues::completarOracion(Progreso& progreso) {
    // Se pidio mas variedad: antes era 1 sola pregunta entre 5 posibles.
    // Ahora hay un banco de 10 frases y se hacen 5 rondas SIN REPETIR
    // frase dentro de la misma sesion.
    struct FraseCompletar { string enunciado; string opcionA, opcionB, opcionC; };
    FraseCompletar banco[] = {
        {"Complete a frase: Eu ___ portugues.",           "estudo",   "como",     "jogo"},
        {"Complete a frase: Ela ___ musica.",              "gosta",    "corre",    "dorme"},
        {"Complete a frase: Nos ___ futebol.",             "jogamos",  "cantamos", "estudamos"},
        {"Complete a frase: Eles ___ filmes.",             "assistem", "bebem",    "escrevem"},
        {"Complete a frase: Voce ___ muito rapido.",       "corre",    "le",       "canta"},
        {"Complete a frase: Ele ___ muitos livros.",       "le",       "come",     "nada"},
        {"Complete a frase: Eu ___ cafe toda manha.",      "bebo",     "visto",    "estudo"},
        {"Complete a frase: Ela ___ na academia todo dia.","vai",      "cozinha",  "pinta"},
        {"Complete a frase: Nos ___ o dever a noite.",     "fazemos",  "vendemos", "compramos"},
        {"Complete a frase: Eles ___ portugues muito bem.","falam",    "escalam",  "dirigem"}
    };
    int totalBanco = 10;
    int totalPreguntas = 5;

    srand(static_cast<unsigned int>(time(nullptr)));
    int usados[10] = { 0,0,0,0,0,0,0,0,0,0 };
    int orden[5];
    for (int k = 0; k < totalPreguntas; k++) {
        int idx;
        do { idx = rand() % totalBanco; } while (usados[idx]);
        usados[idx] = 1;
        orden[k] = idx;
    }

    int aciertos = 0;
    for (int ronda = 1; ronda <= totalPreguntas; ronda++) {
        system("cls");
        Banner::fondoForm();

        FraseCompletar& frase = banco[orden[ronda - 1]];

        Cola<string> opcoes;
        Lista<string> tresOpcoes;
        tresOpcoes.insertarFinal(frase.opcionA);
        tresOpcoes.insertarFinal(frase.opcionB);
        tresOpcoes.insertarFinal(frase.opcionC);
        Ordenamiento<string>::mezclar(&tresOpcoes);
        int posicionCorrecta = -1;
        for (unsigned int i = 0; i < tresOpcoes.tam(); i++) {
            opcoes.encolar(tresOpcoes.obtener(i));
            if (tresOpcoes.obtener(i) == frase.opcionA) posicionCorrecta = (int)i + 1;
        }

        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(ronda) + " de " + to_string(totalPreguntas), G_T);
        Banner::lineaCentrada(frase.enunciado, G_T);

        int i = 1;
        opcoes.mostrarCon([&](string palavra) {
            Banner::lineaCentrada(to_string(i++) + ") " + palavra, G_T);
            });

        int opcion;
        Banner::promptCentrado("Opcion: ");
        cin >> opcion;
        cout << Banner::RESET;
        if (opcion == posicionCorrecta) {
            Banner::lineaCentrada("Correcto!", V_T);
            progreso.registrarAcierto();
            progreso.actualizar(1, 1);
            aciertos++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(ronda, totalPreguntas);

            Banner::lineaVacia();
            Banner::lineaCentrada("--- Racha actual ---", G_T);
            progreso.getRacha()->mostrar();
        }
        else {
            Banner::lineaCentrada("Incorrecto.", R_T);
            Error e(2, "Palabra incorrecta", "2026-05-08");
            progreso.registrarError(e);
            progreso.actualizar(0, 1);

            Sistema sistema;
            sistema.mostrarBarraProgreso(ronda, totalPreguntas);

            progreso.getRacha()->reiniciar();
            Banner::lineaCentrada("--- Racha reiniciada a 0 ---", R_T);
        }

        Banner::lineaVacia();
        Banner::promptCentrado("Presione ENTER para continuar...");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        cout << Banner::RESET;
    }

    return aciertos == totalPreguntas;
}

bool LeccionPortugues::traduccionAvanzada(Progreso& progreso) {
    // Se agrego mas variedad: antes siempre eran las mismas 3 frases en el
    // mismo orden. Ahora hay 6 frases y se eligen 3 distintas al azar.
    struct Frase { string portugues; string espanhol; };
    Frase todas[] = {
        {"Apesar da chuva, eles continuaram jogando futebol.", "A pesar de la lluvia, continuaron jugando futbol."},
        {"Ela esta trabalhando neste projeto ha tres meses.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"Se eu soubesse, teria ajudado voce.", "Si lo hubiera sabido, te habria ayudado."},
        {"Quando chegamos, o filme ja tinha comecado.", "Para cuando llegamos, la pelicula ya habia empezado."},
        {"Ele preferiria estudar a noite do que de manha.", "El prefiere estudiar de noche que en la mañana."},
        {"Eles nunca estiveram tao animados com uma viagem.", "Ellos nunca han estado tan emocionados por un viaje."}
    };
    int totalDisponibles = 6;

    srand(static_cast<unsigned int>(time(nullptr)));
    int usados[6] = { 0,0,0,0,0,0 };
    int orden[3];
    for (int k = 0; k < 3; k++) {
        int idx;
        do { idx = rand() % totalDisponibles; } while (usados[idx]);
        usados[idx] = 1;
        orden[k] = idx;
    }

    int total = 3, corretas = 0;
    for (int i = 0; i < total; i++) {
        system("cls");
        Banner::fondoForm();

        Frase& frase = todas[orden[i]];
        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(i + 1) + " de " + to_string(total), G_T);
        Banner::lineaCentrada("=== Exercicio de Traducao Avancada ===", V_T);
        Banner::lineaCentrada("Traduza a seguinte frase para o espanhol:", G_T);
        Banner::lineaCentrada(frase.portugues, G_T);
        string resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Banner::promptCentrado("Respuesta: ");
        getline(cin, resposta);
        cout << Banner::RESET;

        if (resposta == frase.espanhol) {
            Banner::lineaCentrada("Correcto!", V_T);
            progreso.registrarAcierto();
            corretas++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(i + 1, total);
        }
        else {
            Banner::lineaCentrada("Incorrecto. A traducao correta e:", R_T);
            Banner::lineaCentrada(frase.espanhol, G_T);
            Error e(i + 1, "Traducao incorreta", "2026-05-07");
            progreso.registrarError(e);

            Sistema sistema;
            sistema.mostrarBarraProgreso(i + 1, total);
        }

        Banner::lineaVacia();
        Banner::promptCentrado("Presione ENTER para continuar...");
        cin.get();
        cout << Banner::RESET;
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("Voce acertou " + to_string(corretas) + " de " + to_string(total) + " frases.", V_T);
    progreso.actualizar(corretas, total);
    return corretas == total;
}
