#include "pch.h"
#include "Ejercicio.h"

bool Ejercicio::validarRespuesta(string r) {
    return r == respuestaCorrecta;
}
string Ejercicio::getEnunciado() {
    return enunciado; 
}
int Ejercicio::getPuntaje() {
	return puntaje;
}