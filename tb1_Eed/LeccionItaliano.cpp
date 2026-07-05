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

void LeccionItaliano::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        srand(time(nullptr));

        Lista<string> correcta;
        int tipo = rand() % 6;

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


void LeccionItaliano::completarOracion(Progreso& progreso) {
    // Se agregaron mas ejercicios: antes solo existia "Io ___ italiano." fijo.
    Cola<string> opciones;
    srand(static_cast<unsigned int>(time(nullptr)));
    int tipo = rand() % 5;

    Banner::lineaVacia();
    if (tipo == 0) {
        Banner::lineaCentrada("Completa la frase: Io ___ italiano.", G_T);
        opciones.encolar("studio"); opciones.encolar("mangio"); opciones.encolar("gioco");
    }
    else if (tipo == 1) {
        Banner::lineaCentrada("Completa la frase: Lei ___ la musica.", G_T);
        opciones.encolar("ama"); opciones.encolar("corre"); opciones.encolar("dorme");
    }
    else if (tipo == 2) {
        Banner::lineaCentrada("Completa la frase: Noi ___ a calcio.", G_T);
        opciones.encolar("giochiamo"); opciones.encolar("cantiamo"); opciones.encolar("studiamo");
    }
    else if (tipo == 3) {
        Banner::lineaCentrada("Completa la frase: Loro ___ film.", G_T);
        opciones.encolar("guardano"); opciones.encolar("bevono"); opciones.encolar("scrivono");
    }
    else {
        Banner::lineaCentrada("Completa la frase: Tu ___ molto veloce.", G_T);
        opciones.encolar("corri"); opciones.encolar("leggi"); opciones.encolar("canti");
    }

    int i = 1;
    opciones.mostrarCon([&](string palabra) {
        Banner::lineaCentrada(to_string(i++) + ") " + palabra, G_T);
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


void LeccionItaliano::traduccionAvanzada(Progreso& progreso) {
    Banner::lineaVacia();
    Banner::lineaCentrada("=== Esercizio di Traduzione Avanzata ===", V_T);

   
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
        Frase& frase = todas[orden[i]];
        Banner::lineaVacia();
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
            sistema.mostrarBarraProgreso(correctas, total);
        }
        else {
            Banner::lineaCentrada("Incorrecto. La traduccion correcta era:", R_T);
            Banner::lineaCentrada(frase.espanol, G_T);
            Error e(i + 1, "Traduccion incorrecta", "2026-05-08");
            progreso.registrarError(e);
        }
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("Has acertado " + to_string(correctas) + " de " + to_string(total) + " frases.", V_T);
    progreso.actualizar(correctas, total);
}