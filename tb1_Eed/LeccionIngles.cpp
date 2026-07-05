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
        int tipo = rand() % 6;

        if (tipo == 0) { correcta.insertarFinal("I"); correcta.insertarFinal("study"); correcta.insertarFinal("English"); }
        else if (tipo == 1) { correcta.insertarFinal("She"); correcta.insertarFinal("likes"); correcta.insertarFinal("music"); }
        else if (tipo == 2) { correcta.insertarFinal("We"); correcta.insertarFinal("play"); correcta.insertarFinal("soccer"); }
        else if (tipo == 3) { correcta.insertarFinal("They"); correcta.insertarFinal("watch"); correcta.insertarFinal("movies"); }
        else if (tipo == 4) { correcta.insertarFinal("He"); correcta.insertarFinal("reads"); correcta.insertarFinal("books"); }
        else { correcta.insertarFinal("You"); correcta.insertarFinal("speak"); correcta.insertarFinal("English"); }

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
    srand(static_cast<unsigned int>(time(nullptr)));
    int tipo = rand() % 5;

    Banner::lineaVacia();
    if (tipo == 0) {
        Banner::lineaCentrada("Complete the sentence: I ___ English.", G_T);
        opciones.encolar("study"); opciones.encolar("eat"); opciones.encolar("play");
    }
    else if (tipo == 1) {
        Banner::lineaCentrada("Complete the sentence: She ___ music.", G_T);
        opciones.encolar("likes"); opciones.encolar("runs"); opciones.encolar("sleeps");
    }
    else if (tipo == 2) {
        Banner::lineaCentrada("Complete the sentence: We ___ soccer.", G_T);
        opciones.encolar("play"); opciones.encolar("sing"); opciones.encolar("study");
    }
    else if (tipo == 3) {
        Banner::lineaCentrada("Complete the sentence: They ___ movies.", G_T);
        opciones.encolar("watch"); opciones.encolar("drink"); opciones.encolar("write");
    }
    else {
        Banner::lineaCentrada("Complete the sentence: You ___ very fast.", G_T);
        opciones.encolar("run"); opciones.encolar("read"); opciones.encolar("sing");
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
}


void LeccionIngles::traduccionAvanzada(Progreso& progreso) {
    Banner::lineaVacia();
    Banner::lineaCentrada("=== Advanced Translation Exercise ===", V_T);

    // Se agrego mas variedad: antes siempre eran las mismas 3 frases en el
    // mismo orden. Ahora hay 6 frases y se eligen 3 distintas al azar.
    struct Frase { string ingles; string espanol; };
    Frase todas[] = {
        {"Despite the rain, they continued playing football.", "A pesar de la lluvia, continuaron jugando futbol."},
        {"She has been working on this project for three months.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"If I had known, I would have helped you.", "Si lo hubiera sabido, te habria ayudado."},
        {"By the time we arrived, the movie had already started.", "Para cuando llegamos, la pelicula ya habia empezado."},
        {"He would rather study at night than in the morning.", "El prefiere estudiar de noche que en la mañana."},
        {"They have never been so excited about a trip.", "Ellos nunca han estado tan emocionados por un viaje."}
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
        Banner::lineaCentrada("Translate into Spanish:", G_T);
        Banner::lineaCentrada(frase.ingles, G_T);
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Banner::promptCentrado("Respuesta: ");
        getline(cin, respuesta);
        cout << Banner::RESET;

        if (respuesta == frase.espanol) {
            Banner::lineaCentrada("Correct!", V_T);
            progreso.registrarAcierto();
            correctas++;

            Sistema sistema;
            sistema.mostrarBarraProgreso(correctas, total);
        }
        else {
            Banner::lineaCentrada("Incorrect. Correct answer:", R_T);
            Banner::lineaCentrada(frase.espanol, G_T);
            Error e(i + 1, "Wrong translation", "2026-05-10");
            progreso.registrarError(e);
        }
    }

    Banner::lineaVacia();
    Banner::lineaCentrada("You got " + to_string(correctas) + " out of " + to_string(total) + ".", V_T);
    progreso.actualizar(correctas, total);
}