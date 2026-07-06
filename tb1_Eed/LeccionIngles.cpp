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

bool LeccionIngles::ordenarOracion(Progreso& progreso) {
  
    int totalPreguntas = 3;
    int aciertos = 0;

    for (int ronda = 1; ronda <= totalPreguntas; ronda++) {
        srand(time(nullptr) + ronda);

        system("cls");
        Banner::fondoForm();

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
        Banner::lineaCentrada("Pregunta " + to_string(ronda) + " de " + to_string(totalPreguntas), G_T);
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

    return aciertos == totalPreguntas;   // true solo si acerto TODAS las preguntas
}


bool LeccionIngles::completarOracion(Progreso& progreso) {
  
    struct FraseCompletar { string enunciado; string opcionA, opcionB, opcionC; };
    FraseCompletar banco[] = {
        {"Complete the sentence: I ___ English.",            "study", "eat",   "play"},
        {"Complete the sentence: She ___ music.",             "likes", "runs",  "sleeps"},
        {"Complete the sentence: We ___ soccer.",             "play",  "sing",  "study"},
        {"Complete the sentence: They ___ movies.",           "watch", "drink", "write"},
        {"Complete the sentence: You ___ very fast.",         "run",   "read",  "sing"},
        {"Complete the sentence: He ___ a lot of books.",     "reads", "eats",  "swims"},
        {"Complete the sentence: I ___ coffee every morning.","drink", "wear",  "study"},
        {"Complete the sentence: She ___ to the gym daily.",  "goes",  "cooks", "paints"},
        {"Complete the sentence: We ___ our homework at night.", "do", "sell", "buy"},
        {"Complete the sentence: They ___ English very well.","speak", "climb","drive"}
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

        // Mezclar cual opcion (A, B o C) es la correcta para que no
        // siempre aparezca en el mismo puesto.
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


bool LeccionIngles::traduccionAvanzada(Progreso& progreso) {
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
        system("cls");
        Banner::fondoForm();

        Frase& frase = todas[orden[i]];
        Banner::lineaVacia();
        Banner::lineaCentrada("Pregunta " + to_string(i + 1) + " de " + to_string(total), G_T);
        Banner::lineaCentrada("=== Advanced Translation Exercise ===", V_T);
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
            sistema.mostrarBarraProgreso(i + 1, total);
        }
        else {
            Banner::lineaCentrada("Incorrect. Correct answer:", R_T);
            Banner::lineaCentrada(frase.espanol, G_T);
            Error e(i + 1, "Wrong translation", "2026-05-10");
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
    Banner::lineaCentrada("You got " + to_string(correctas) + " out of " + to_string(total) + ".", V_T);
    progreso.actualizar(correctas, total);
    return correctas == total;
}
