#pragma once
#include <iostream>
#include <string>
#include "Idioma.h"
#include "Progreso.h"
#include "Leccion.h"
#include "ListaDoble.hpp"

using namespace std;

class Usuario {
private:
    int id;
    string nombre;
    string email;
    int puntajeTotal;
    Progreso progreso;      // progreso del usuario

    int nivelIngles;
    int nivelPortugues;
    int nivelItaliano;

public:
    Usuario();
    Usuario(int i, const string& n, const string& e, int ni, int np, int ni2);
    ~Usuario();

    // getters
    string getNombre() const;
    string getEmail() const;
    int getPuntajeTotal() const;

    int getNivelIngles() const;
    int getNivelPortugues() const;
    int getNivelItaliano() const;

    void setNivelIngles(int n);
    void setNivelPortugues(int n);
    void setNivelItaliano(int n);


    // manejo de idioma
    void seleccionarIdioma(int opcion, int nivel);
    Idioma* getIdiomaActual();

    // progreso
    Progreso* obtenerProgreso();
    void agregarPuntaje(int n);


    string serializar() const;
    static Usuario deserializar(const string& linea);

    // LAMBDA 4: nivel global = promedio de los 3 idiomas
    int nivelGlobal() const {
        auto promedio = [](int a, int b, int c) {
            return (a + b + c) / 3;
            };
        return promedio(nivelIngles, nivelPortugues, nivelItaliano);
    }


};
