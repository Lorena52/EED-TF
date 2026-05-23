//Aqui utilizamos 
//- listas - colas - Ordemamiendto (mezclar )
//guia pa los demas lecciones quitar nulltpr ya esta en el main 
#include "pch.h"
#include "LeccionIngles.h"
#include "Ordenamiento.h"
//::::::::::::::::
#include <limits>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sistema.h"
using namespace std;

void LeccionIngles::ordenarOracion(Progreso& progreso) {
    char continuar;
    int contador = 0;
    int totalPreguntas = 3;

    do {
        Lista<string> correcta;// aplicamos lista para la oracion correcta , luego se mescla y se ordena luego  se compara 
        int tipo = rand() % 4; 

        if (tipo == 0)
        { correcta.insertarFinal("I"); correcta.insertarFinal("study"); correcta.insertarFinal("English"); }

        else if (tipo == 1) 
        { correcta.insertarFinal("She"); correcta.insertarFinal("likes"); correcta.insertarFinal("music"); }

        else if (tipo == 2) 
        { correcta.insertarFinal("We"); correcta.insertarFinal("play"); correcta.insertarFinal("soccer"); }

        else { correcta.insertarFinal("They"); correcta.insertarFinal("watch"); correcta.insertarFinal("movies"); }

        Lista<string> mezclada;// se crea una lista nueva pero mezclada 

        for (unsigned int i = 0; i < correcta.tam(); i++)  mezclada.insertarFinal(correcta.obtener(i));

        Ordenamiento<string>::mezclar(&mezclada);

        cout << "Order the sentence:" << endl;
        for (unsigned int i = 0; i < mezclada.tam(); i++) cout << i + 1 << ") " << mezclada.obtener(i) << endl;

        int respuestas[10];
        cout << "Enter the correct order: ";

        for (unsigned int i = 0; i < correcta.tam(); i++)
            cin >> respuestas[i];

        bool correcto = true;
        for (unsigned int i = 0; i < correcta.tam(); i++) {
            if (mezclada.obtener(respuestas[i] - 1) != correcta.obtener(i)) correcto = false;// comparando las respuestas de listas 
        }

        if (correcto) {
            cout << "Correcto!" << endl;
            progreso.registrarAcierto();
            progreso.actualizar(1, 1);

            //Avanza barra solo si es correcto
            contador++;
        //aqui se muestra con statci 
            Sistema::mostrarBarraProgreso(contador, totalPreguntas);

            //Mostrar racha actual
            cout << "\n--- Racha actual :) ---" << endl;
            progreso.getRacha()->mostrar();//mostar de racha actual 
        }


        else {
            cout << "Incorrecto." << endl;
            Error e(1, "Orden incorrecto", "2026-05-09");//deriva de clase error (esta registrando )
            progreso.registrarError(e);
            progreso.actualizar(0, 1);

          
            progreso.getRacha()->reiniciar();//esta reiniciando la racha a 0 
            cout << "\n--- Perdio su Racha  :(  ---" << endl;
        }

        cout << "Desea Continuar  (y/n): ";
        cin >> continuar;
        // COMPLEJIDAD:::::::::::::::::::::::::::::::::::::::::::::
//
// - Copiar elementos a la lista mezclada -> O(n)
// - Mezclar palabras -> O(n)
// - Mostrar palabras -> O(n)
// - Verificar respuestas -> O(n)
//
// COMPLEJIDAD TOTAL:
// O(n)
//
// ESPACIO:
// O(n)

    } while (continuar == 'y' || continuar == 'Y');
}


void LeccionIngles::completarOracion(Progreso& progreso) {
    //creamos cola de opciones para completar la oracion 
    Cola<string> opciones;
    opciones.encolar("study");
    opciones.encolar("eat");
    opciones.encolar("play");

    cout << "Complete the sentence: I ___ English." << endl;
    int i = 1;
    //landa para mostarr 
    opciones.mostrarCon([&](string palabra) { cout << i++ << ") " << palabra << endl; });

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        cout << "Correcto!" << endl;
        progreso.registrarAcierto();
        progreso.actualizar(1, 1);

        Sistema::mostrarBarraProgreso(1, 1);


        cout << "\n--- Racha actual ---" << endl;
        progreso.getRacha()->mostrar();
    }
    else {
        cout << "Incorrecto." << endl;
        Error e(2, "Palabra incorrecta", "2026-05-08");
        progreso.registrarError(e);
        progreso.actualizar(0, 1);

        progreso.getRacha()->reiniciar();
        cout << "\n--- Perdio su Racha :( ---" << endl;
    }

}


void LeccionIngles::traduccionAvanzada(Progreso& progreso) {
    cout << "\n=== Advanced Translation Exercise ===" << endl;

    struct Frase { string ingles; string espanol; };
    Frase frases[] = {
        {"Despite the rain, they continued playing football.", "A pesar de la lluvia, continuaron jugando fútbol."},
        {"She has been working on this project for three months.", "Ella ha estado trabajando en este proyecto por tres meses."},
        {"If I had known, I would have helped you.", "Si lo hubiera sabido, te habría ayudado."}
    };

    int total = 3, correctas = 0;
    for (int i = 0; i < total; i++) {
        cout << "\nTranslate into Spanish:\n" << frases[i].ingles << endl;
        string respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, respuesta);

        if (respuesta == frases[i].espanol) {
            cout << "Correct!" << endl;
            progreso.registrarAcierto();
            correctas++;

            // Barra solo si es correcto
            Sistema sistema;
            sistema.mostrarBarraProgreso(correctas, total);
        }
        else {
            cout << "Incorrect. Correct answer:\n" << frases[i].espanol << endl;
            Error e(i + 1, "Wrong translation", "2026-05-10");
            progreso.registrarError(e);
        }
    }

    cout << "\nYou got " << correctas << " out of " << total << "." << endl;
    progreso.actualizar(correctas, total);
}
