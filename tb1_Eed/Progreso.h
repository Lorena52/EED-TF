#pragma once
#include <string>
#include "Pila.hpp"
#include "Error.h"
#include "Racha.h"
using namespace std;

class Progreso {
private:
    
    int leccionesComp;
    int puntosTotales;
    int ejerciciosTotales;

    float porcentaje;
    string fechaUltima;

    Pila<Error> errores;

    Racha* racha;
    int erroresSeguidos;

    int contarErroresAux(Pila<Error>::Nodo* nodo);


public:
    Progreso();
    ~Progreso();
    Progreso(const Progreso& otro);            
    Progreso& operator=(const Progreso& otro); 

    void actualizar(int puntos, int total);
    void reiniciar();
    void registrarAcierto();
    void registrarError(const Error& e);
    void mostrarHistorialErrores();
    void mostrarRacha();

    float getPorcentaje() const;
    int getLeccionesComp() const;
    int getErroresSeguidos() const;
    //agregacacion

    void setPuntosTotales(int v);
    int getPuntosTotales() const;


    Racha* getRacha() const;
    Pila<Error> verUltimosErrores() const;


    void setRachaActual(int valor);
    void setMejorRacha(int valor);


    void reiniciarErrores();

    int contarErrores();

    float calcularPorcentaje(int aciertos, int total) const;
    int contarErroresDeEjercicio(int idEjercicio);
};
