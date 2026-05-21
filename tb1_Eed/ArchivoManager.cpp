#include "pch.h"
#include "ArchivoManager.h"
#include <iostream>
using namespace std;

ArchivoManager::ArchivoManager() {
    // inicialización básica
    cout << "ArchivoManager creado." << endl;
}

ArchivoManager::~ArchivoManager() {
    cout << "ArchivoManager destruido." << endl;
}

void ArchivoManager::guardarDatos() {
    cout << "Guardando datos..." << endl;
}

void ArchivoManager::cargarDatos() {
    cout << "Cargando datos..." << endl;
}
