#pragma once
#include <string>
using namespace std;

class NodoLeccion {
private:
    string idioma;         
    int    nivel;           
    string ejercicio;        
    int    minutosEstimado; 

public:
    NodoLeccion();
    NodoLeccion(string idioma, int nivel, string ejercicio, int minutosEstimado);

    string getIdioma()   const;
    int    getNivel()    const;
    string getEjercicio() const;
    int    getMinutos()  const;

    string detalle() const;   // texto listo para consola
};
