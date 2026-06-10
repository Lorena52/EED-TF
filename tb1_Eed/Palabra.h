#pragma once
#include <string>
#include <iostream>
using namespace std;

// =====================================================================
//  Palabra
//  Entidad que representa una palabra del vocabulario de un idioma.
//  Responsabilidad UNICA: guardar los datos de una palabra y la
//  logica minima asociada a ella (repaso y dificultad).
//
//  Atributos:
//    termino       -> palabra en el idioma extranjero
//    traduccion    -> equivalente en espaniol
//    categoria     -> tipo de palabra (sustantivo, verbo, etc.)
//    nivel         -> 1=Basico, 2=Intermedio, 3=Avanzado
//    vecesRepasada -> cuantas veces el usuario la acerto en repaso
// =====================================================================
class Palabra {
private:
    string termino;
    string traduccion;
    string categoria;
    int    nivel;
    int    vecesRepasada;

public:
    // --- Constructores ---
    Palabra();
    Palabra(string termino, string traduccion, int nivel);
    Palabra(string termino, string traduccion, string categoria, int nivel);

    // --- Getters ---
    string getTermino()    const;
    string getTraduccion() const;
    string getCategoria()  const;
    int    getNivel()      const;
    int    getVeces()      const;

    // --- Setters ---
    void setCategoria(string categoria);

    // --- Logica propia ---
    void incrementarRepaso();
    bool esDificil() const;     // true si aun no se ha repasado lo suficiente

    // --- Presentacion ---
    void mostrar() const;
};