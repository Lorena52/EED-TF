#pragma once
#include <string>
#include "Leccion.h"
#include "Palabra.h"
#include "ListaDoble.hpp"
#include "ListaCircular.hpp"

using namespace std;

class Progreso; 

// =====================================================================
//  Idioma  (clase ABSTRACTA)
//  Representa un idioma que el usuario puede aprender. Define el
//  comportamiento comun y obliga a las subclases (Ingles, Portugues,
//  Italiano) a implementar la teoria, los ejercicios y el vocabulario.
//
//  IMPORTANTE (correccion de diseno):
//  El vocabulario y las lecciones se declaran UNA sola vez aqui, en la
//  clase base. Antes cada subclase volvia a declarar su propio
//  'vocabulario', lo que ocultaba (shadowing) al de la base y generaba
//  confusion. Ahora las hijas comparten estos contenedores 'protected'.
//
//  Estructuras usadas:
//    - ListaDoble<Leccion*>   -> historial de lecciones realizadas
//    - ListaCircular<Palabra> -> vocabulario (se repasa en ciclo)
// =====================================================================

class Idioma {
protected:
    string codigo; // "EN", "PT", "IT"
    string nombre; // "Ingles", "Portugues"
	int nivel; //1=Principiante, 2=Intermedio, 3=Avanzado

    ListaDoble<Leccion*> lecciones;
    ListaCircular<Palabra> vocabulario;
public:
    Idioma(string c, string n);
    virtual ~Idioma();

    void setNivel(int n);
    int getNivel() const;
    string getNombre() const;

    //Comportamiento que CADA idioma debe definir
    virtual void mostrarTeoria() = 0;
    virtual void iniciarEjercicios(Progreso& progreso) = 0;
    virtual void cargarVocabulario() = 0;

    // Comportamiento comun (puede sobreescribirse) 
    virtual void repasoContinuo(Progreso& progreso);
    virtual void diccionario();
};
