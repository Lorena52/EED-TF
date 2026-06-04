#pragma once
#include <string>
#include "Progreso.h"

class Idioma; // fwd decl para no acoplar headers

class Usuario {
private:
    int         id;
    std::string nombre;
    std::string email;
    int         puntajeTotal;
    Progreso    progreso;

    int nivelIngles;
    int nivelPortugues;
    int nivelItaliano;

public:
    Usuario();
    Usuario(int id, const std::string& nombre, const std::string& email,
        int ni, int np, int ni2);

    // Getters
    int         getId()             const { return id; }
    std::string getNombre()         const { return nombre; }
    std::string getEmail()          const { return email; }
    int         getPuntajeTotal()   const { return puntajeTotal; }
    int         getNivelIngles()    const { return nivelIngles; }
    int         getNivelPortugues() const { return nivelPortugues; }
    int         getNivelItaliano()  const { return nivelItaliano; }

    // Setters
    void setNivelIngles(int n) { nivelIngles = n; }
    void setNivelPortugues(int n) { nivelPortugues = n; }
    void setNivelItaliano(int n) { nivelItaliano = n; }

    // Progreso
    Progreso* obtenerProgreso();
    void      agregarPuntaje(int n) { puntajeTotal += n; }

    // Persistencia
    std::string    serializar() const;
    static Usuario deserializar(const std::string& linea);
};