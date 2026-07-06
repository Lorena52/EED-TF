#include "pch.h"
#include "ArchivoManager.h"
#include "Util.h"
#include <iostream>
using namespace std;

ArchivoManager::ArchivoManager()
    : rutaUsuarios("usuarios.txt"), rutaRanking("ranking.txt"), rutaIngles("ingles.txt"), rutaItaliano("Italiano.txt"), rutaPortugues("Portugues.txt"), rutaRacha("Racha.txt") {
}

ArchivoManager::~ArchivoManager() {
}

// ---------------------------------------------------------------------
//  Usuarios
// ---------------------------------------------------------------------

// Lee usuarios.txt linea por linea, deserializa cada linea a un Usuario
// y lo inserta en la lista. Usa lambdas (requisito de la rubrica).
void ArchivoManager::cargarUsuarios(ListaDoble<Usuario>& usuarios) {
    cargarArchivo(
        rutaUsuarios,
        [](string linea) { return Usuario::deserializar(linea); },  
        [&usuarios](Usuario u) { usuarios.insertarFinal(u); }       //LAMBDA
    );
}

// Recorre la lista y escribe cada usuario serializado en usuarios.txt.
void ArchivoManager::guardarUsuarios(ListaDoble<Usuario>& usuarios) {
    guardarArchivo(
        &usuarios,
        rutaUsuarios,
        [](Usuario u) { return u.serializar(); }                    //LAMBDA
    );
}

// ---------------------------------------------------------------------
//  Ranking
// ---------------------------------------------------------------------
void ArchivoManager::guardarRanking(Lista<Ranking>& ranking) {
    guardarArchivo(
        &ranking,
        rutaRanking,
        [](Ranking r) { return r.serializar(); }
    );
}

// inlges 
void ArchivoManager::guardarNivelesIngles(ListaDoble<Usuario>& usuarios) {
    guardarArchivo(
        &usuarios,
        rutaIngles,
        [](Usuario u) {
            return u.getNombre() + ";" +
                to_string(u.getNivelIngles());
        }
    );
}


// italiano
void ArchivoManager::guardarNivelesItaliano(ListaDoble<Usuario>& usuarios) {
    guardarArchivo(
        &usuarios,
        rutaItaliano,
        [](Usuario u) {
            return u.getNombre() + ";" +
                to_string(u.getNivelItaliano());
        }
    );
}

// portugues 
void ArchivoManager::guardarNivelesPortugues(ListaDoble<Usuario>& usuarios) {
    guardarArchivo(
        &usuarios,
        rutaPortugues,
        [](Usuario u) {
            return  u.getNombre() + ";" +
                to_string(u.getNivelPortugues());
        }
    );
}

// portugues 
void ArchivoManager::guardarNivelesRacha(ListaDoble<Usuario>& usuarios) {
    guardarArchivo(
        &usuarios,
        rutaRacha,
        [](Usuario u) {
            return u.getNombre() + ";" +
                to_string(u.obtenerProgreso()->getRacha()->getMaxima());
        }
    );
}