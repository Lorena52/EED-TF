#include "pch.h"
#include <limits>
#include "LeccionItaliano.h"
#include "Ordenamiento.h"
#include "Sistema.h" 
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void LeccionItaliano::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        srand(time(nullptr));

        Lista<string> correcta;
        int tipo = rand() % 4;

        if (tipo == 0) {
            correcta.insertarFinal("Io");
            correcta.insertarFinal("studio");
            correcta.insertarFinal("italiano");
        }
        else if (tipo == 1) {
            correcta.insertarFinal("Lei");
            correcta.insertarFinal("ama");
            correcta.insertarFinal("la");
            correcta.insertarFinal("musica");
        }
        else if (tipo == 2) {
            correcta.insertarFinal("Noi");
            correcta.insertarFinal("giochiamo");
            correcta.insertarFinal("a");
            correcta.insertarFinal("calcio");
        }
        else {
            correcta.insertarFinal("Loro");
            correcta.insertarFinal("guardano");
            correcta.insertarFinal("film");
        }

        Lista<string> mezclada;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            mezclada.insertarFinal(correcta.obtener(i));
        }
        Ordenamiento<string>::mezclar(&mezclada);

        cout << "Ordina la frase:" << endl;
        for (unsigned int i = 0; i < mezclada.tam(); i++) {
            cout << i + 1 << ") " << mezclada.obtener(i) << endl;
        }

        int respuestas[10];
        cout << "Ingrese el orden correcto: ";
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            cin >> respuestas[i];
        }

        bool correcto = true;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            if (mezclada.obtener(respuestas[i] - 1) != correcta.obtener(i)) {
                correcto = false;
            }
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


void LeccionItaliano::completarOracion(Progreso& progreso) {
    Cola<string> opciones;
    opciones.encolar("studio");
    opciones.encolar("mangio");
    opciones.encolar("gioco");

    cout << "Completa la frase: Io ___ italiano." << endl;
    int i = 1;
    opciones.mostrarCon([&](string palabra) { cout << i++ << ") " << palabra << endl; });

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


void LeccionItaliano::traduccionAvanzada(Progreso& progreso) {
    cout << "\n=== Esercizio di Traduzione Avanzata ===" << endl;

    struct Frase { string italiano; string espanol; };
    Frase frases[] = {
        {"Nonostante la pioggia, hanno continuato a giocare a calcio.", "A pesar de la lluvia, continuaron jugando fútbol."},
        {"Lei lavora a questo progetto da tre mesi.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"Se lo avessi saputo, ti avrei aiutato.", "Si lo hubiera sabido, te habría ayudado."}
    };

    int total = 3, correctas = 0;
    for (int i = 0; i < total; i++) {
        cout << "\nTraduci in spagnolo:\n" << frases[i].italiano << endl;
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, respuesta);

        if (respuesta == frases[i].espanol) {
            cout << "Correcto" << endl;
            progreso.registrarAcierto();
            correctas++;

            //Barra solo si es correcto
            Sistema sistema;
            sistema.mostrarBarraProgreso(correctas, total);
        }
        else {
            cout << "Incorrecto. La traducción correcta era:\n" << frases[i].espanol << endl;
            Error e(i + 1, "Traducción incorrecta", "2026-05-08");
            progreso.registrarError(e);
        }
    }

    cout << "\nHas acertado " << correctas << " de " << total << " frases." << endl;
    progreso.actualizar(correctas, total);
}
