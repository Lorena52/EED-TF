#include "pch.h"
#include <limits>
#include "LeccionItaliano.h"
#include "Ordenamiento.h"
#include "Sistema.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

static const string V_T = "\033[38;2;46;125;50m";
static const string G_T = "\033[38;2;55;55;55m";
static const string R_T = "\033[38;2;200;40;40m";

bool LeccionItaliano::ordenarOracion(Progreso& progreso) {
    // Antes esto era un do-while con "Desea continuar? (s/n)" que dejaba
    // seguir respondiendo sin limite, por eso la barra de progreso podia
    // pasar de 100%. Ahora se hacen EXACTAMENTE totalPreguntas rondas.
    int totalPreguntas = 6;
    int aciertos = 0;

    for (int ronda = 1; ronda <= totalPreguntas; ronda++) {
        srand(time(nullptr) + ronda);

        system("cls");
        Banner::fondoForm();

        Lista<string> correcta;
        int tipo = ronda-1;

        if (tipo == 0) {
            correcta.insertarFinal("Io"); correcta.insertarFinal("studio"); correcta.insertarFinal("italiano");
        }
        else if (tipo == 1) {
            correcta.insertarFinal("Lei"); correcta.insertarFinal("ama"); correcta.insertarFinal("la"); correcta.insertarFinal("musica");
        }
        else if (tipo == 2) {
            correcta.insertarFinal("Noi"); correcta.insertarFinal("giochiamo"); correcta.insertarFinal("a"); correcta.insertarFinal("calcio");
        }
        else if (tipo == 3) {
            correcta.insertarFinal("Loro"); correcta.insertarFinal("guardano"); correcta.insertarFinal("film");
        }
        else if (tipo == 4) {
            correcta.insertarFinal("Lui"); correcta.insertarFinal("legge"); correcta.insertarFinal("libri");
        }
        else {
            correcta.insertarFinal("Tu"); correcta.insertarFinal("parli"); correcta.insertarFinal("italiano");
        }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) mezclada.insertarFinal(correcta.obtener(i));
        Ordenamiento<string>::mezclar(&mezclada);

        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(ronda) + " de " + to_string(totalPreguntas), G_T);
        Banner::lineaCentrada("Ordina la frase:", G_T);
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


bool LeccionItaliano::completarOracion(Progreso& progreso) {
    // Se pidio mas variedad: antes era 1 sola pregunta entre 5 posibles.
    // Ahora hay un banco de 10 frases y se hacen 5 rondas SIN REPETIR
    // frase dentro de la misma sesion.
    struct FraseCompletar { string enunciado; string opcionA, opcionB, opcionC; };
    FraseCompletar banco[] = {
        {"Completa la frase: Io ___ italiano.",            "studio",    "mangio",  "gioco"},
        {"Completa la frase: Lei ___ la musica.",          "ama",       "corre",   "dorme"},
        {"Completa la frase: Noi ___ a calcio.",           "giochiamo", "cantiamo","studiamo"},
        {"Completa la frase: Loro ___ film.",               "guardano",  "bevono",  "scrivono"},
        {"Completa la frase: Tu ___ molto veloce.",        "corri",     "leggi",   "canti"},
        {"Completa la frase: Lui ___ molti libri.",        "legge",     "mangia",  "nuota"},
        {"Completa la frase: Io ___ caffe ogni mattina.",  "bevo",      "indosso", "studio"},
        {"Completa la frase: Lei ___ in palestra ogni giorno.", "va",   "cucina",  "dipinge"},
        {"Completa la frase: Noi ___ i compiti di sera.",  "facciamo",  "vendiamo","compriamo"},
        {"Completa la frase: Loro ___ italiano molto bene.","parlano",  "scalano", "guidano"}
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

        Cola<string> opciones;
        Lista<string> tresOpciones;
        tresOpciones.insertarFinal(frase.opcionA);
        tresOpciones.insertarFinal(frase.opcionB);
        tresOpciones.insertarFinal(frase.opcionC);
        Ordenamiento<string>::mezclar(&tresOpciones);
        int posicionCorrecta = -1;
        for (unsigned int i = 0; i < tresOpciones.tam(); i++) {
            opciones.encolar(tresOpciones.obtener(i));
            if (tresOpciones.obtener(i) == frase.opcionA) posicionCorrecta = (int)i + 1;
        }

        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(ronda) + " de " + to_string(totalPreguntas), G_T);
        Banner::lineaCentrada(frase.enunciado, G_T);

        int i = 1;
        opciones.mostrarCon([&](string palabra) {
            Banner::lineaCentrada(to_string(i++) + ") " + palabra, G_T);
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


bool LeccionItaliano::traduccionAvanzada(Progreso& progreso) {
    // Se agrego mas variedad: antes siempre eran las mismas 3 frases en el
    // mismo orden. Ahora hay 6 frases y se eligen 3 distintas al azar.
    struct Frase { string italiano; string espanol; };
    Frase todas[] = {
        {"Nonostante la pioggia, hanno continuato a giocare a calcio.", "A pesar de la lluvia, continuaron jugando futbol."},
        {"Lei lavora a questo progetto da tre mesi.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"Se lo avessi saputo, ti avrei aiutato.", "Si lo hubiera sabido, te habria ayudado."},
        {"Quando siamo arrivati, il film era gia iniziato.", "Para cuando llegamos, la pelicula ya habia empezado."},
        {"Preferirebbe studiare di notte piuttosto che al mattino.", "El prefiere estudiar de noche que en la mañana."},
        {"Non sono mai stati cosi entusiasti per un viaggio.", "Ellos nunca han estado tan emocionados por un viaje."}
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

    int total = 3, correctas = 0;
    for (int i = 0; i < total; i++) {
        system("cls");
        Banner::fondoForm();

        Frase& frase = todas[orden[i]];
        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(i + 1) + " de " + to_string(total), G_T);
        Banner::lineaCentrada("=== Esercizio di Traduzione Avanzata ===", V_T);
        Banner::lineaCentrada("Traduci in spagnolo:", G_T);
        Banner::lineaCentrada(frase.italiano, G_T);
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Banner::promptCentrado("Respuesta: ");
        getline(cin, respuesta);
        cout << Banner::RESET;

        if (respuesta == frase.espanol) {
            Banner::lineaCentrada("Correcto", V_T);
            progreso.registrarAcierto();
            correctas++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(i + 1, total);
        }
        else {
            Banner::lineaCentrada("Incorrecto. La traduccion correcta era:", R_T);
            Banner::lineaCentrada(frase.espanol, G_T);
            Error e(i + 1, "Traduccion incorrecta", "2026-05-08");
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
    Banner::lineaCentrada("Has acertado " + to_string(correctas) + " de " + to_string(total) + " frases.", V_T);
    progreso.actualizar(correctas, total);
    return correctas == total;
}
