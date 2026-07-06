#pragma once
#include <string>
#include "Usuario.h"
#include "Ranking.h"
#include "ListaDoble.hpp"
#include "Lista.hpp"

using namespace std;

//  ArchivoManager
//  UNICA clase responsable de la persistencia en disco. Sabe los
//  nombres de los archivos y como serializar/deserializar cada entidad.
//
//  El resto del programa (Sistema) NO abre archivos directamente:
//  siempre pasa por aqui. Asi se cumple el requisito de tener un
//  manejador de archivos por las clases principales.
//
//  Archivos que administra:
//    - usuarios.txt -> lista de usuarios (clase Usuario)
//    - ranking.txt  -> ranking de rachas (clase Ranking)
class ArchivoManager {
private:
    string rutaUsuarios;
    string rutaRanking;
    string rutaIngles;
    string rutaItaliano;
    string rutaPortugues;
    string rutaRacha;
public:
    ArchivoManager();
    ~ArchivoManager();

    // Carga los usuarios del archivo dentro de la lista recibida.
    void cargarUsuarios(ListaDoble<Usuario>& usuarios);
    // Guarda todos los usuarios de la lista en el archivo.
    void guardarUsuarios(ListaDoble<Usuario>& usuarios);

    void guardarRanking(Lista<Ranking>& ranking);

    void guardarNivelesIngles(ListaDoble<Usuario>& usuarios);
    void guardarNivelesItaliano(ListaDoble<Usuario>& usuarios);
    void guardarNivelesPortugues(ListaDoble<Usuario>& usuarios);
    // racha
    void guardarNivelesRacha(ListaDoble<Usuario>& usuarios);
};