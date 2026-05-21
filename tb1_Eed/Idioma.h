#pragma once
#include <string>
#include "Leccion.h"
#include "Palabra.h"
#include "ListaDoble.hpp"
#include "ListaCircular.hpp"

using namespace std;

class Progreso; 

class Idioma {
protected:
    string codigo;
    string nombre;
	int nivel; //1=Principiante, 2=Intermedio, 3=Avanzado
    ListaDoble<Leccion*> lecciones;
    ListaCircular<Palabra> vocabulario;
public:
    Idioma(string c, string n);
    virtual ~Idioma();

    void setNivel(int n);
    int getNivel() const;

    virtual void mostrarTeoria() = 0;
    virtual void iniciarEjercicios(class Progreso& progreso) = 0;
    
    virtual void repasoContinuo(Progreso& progreso);
    virtual void cargarVocabulario() = 0;
    
    virtual void diccionario();
};
