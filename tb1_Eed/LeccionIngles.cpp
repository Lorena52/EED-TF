#include "pch.h"
#include <limits>
#include "LeccionIngles.h"
#include "Ordenamiento.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sistema.h"
using namespace std;

// Colores (paleta tipo Duolingo, oscuros para leer sobre fondo blanco)
static const string V_T = "\033[38;2;46;125;50m";   // verde
static const string G_T = "\033[38;2;55;55;55m";    // gris
static const string R_T = "\033[38;2;200;40;40m";   // rojo

void LeccionIngles::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        srand(time(nullptr));

        Lista<string> correcta;
        int tipo = rand() % 4;

        if (tipo == 0) { correcta.insertarFinal("I"); correcta.insertarFinal("study"); correcta.insertarFinal("English"); }
        else if (tipo == 1) { correcta.insertarFinal("She"); correcta.insertarFinal("likes"); correcta.insertarFinal("music"); }
        else if (tipo == 2) { correcta.insertarFinal("We"); correcta.insertarFinal("play"); correcta.insertarFinal("soccer"); }
        else { correcta.insertarFinal("They"); correcta.insertarFinal("watch"); correcta.insertarFinal("movies"); }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) mezclada.insertarFinal(correcta.obtener(i));
        Ordenamiento<string>::mezclar(&mezclada);

        Banner::lineaVacia();
        Banner::lineaCentrada("Order the sentence:", G_T);
        for (unsigned int i = 0; i < mezclada.tam(); i++)
            Banner::lineaCentrada(to_string(i + 1) + ") " + mezclada.obtener(i), G_T);

        int respuestas[10];
        Banner::promptCentrado("Enter the correct order: ");
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

        Banner::promptCentrado("Continue? (y/n): ");
        cin >> continuar;
        cout << Banner::RESET;
    } while (continuar == 'y' || continuar == 'Y');
}








void LeccionIngles::completarOracion(Progreso& progreso) {
    Cola<string> opciones;
    opciones.encolar("study");
    opciones.encolar("eat");
    opciones.encolar("play");

    Banner::lineaVacia();
    Banner::lineaCentrada("Complete the sentence: I ___ English.", G_T);
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
}


void LeccionIngles::traduccionAvanzada(Progreso& progreso) {
    Banner::lineaVacia();
    Banner::lineaCentrada("=== Advanced Translation Exercise ===", V_T);

    struct Frase { string ingles; string espanol; };
    Frase frases[] = {
        {"Despite the rain, they continued playing football.", "A pesar de la lluvia, continuaron jugando futbol."},
        {"She has been working on this project for three months.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"If I had known, I would have helped you.", "Si lo hubiera sabido, te habria ayudado."}
    };

    int total = 3, correctas = 0;
    for (int i = 0; i < total; i++) {
        Banner::lineaVacia();
        Banner::lineaCentrada("Translate into Spanish:", G_T);
        Banner::lineaCentrada(frases[i].ingles, G_T);
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Banner::promptCentrado("Respuesta: ");
        getline(cin, respuesta);
        cout << Banner::RESET;

        if (respuesta == frases[i].espanol) {
            Banner::lineaCentrada("Correct!", V_T);
            progreso.registrarAcierto();
            correctas++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(correctas, total);
        }
        else {
            Banner::lineaCentrada("Incorrect. Correct answer:", R_T);
            Banner::lineaCentrada(frases[i].espanol, G_T);
            Error e(i + 1, "Wrong translation", "2026-05-10");
            progreso.registrarError(e);
        }
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("You got " + to_string(correctas) + " out of " + to_string(total) + ".", V_T);
    progreso.actualizar(correctas, total);
}