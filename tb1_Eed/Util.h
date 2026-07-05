#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "Banner.h"

using namespace std;


// ═══════════════════════════════════════════════════════════════
//  Util.h
//  Funciones auxiliares para guardar y cargar estructuras desde
//  archivos de texto. Disenado para servir a:
//      - Lista        (inicio() + nodo->sig terminado en nullptr)
//      - Pila         (inicio() + nodo->sig terminado en nullptr)
//      - Cola         (inicio() + nodo->sig terminado en nullptr)
//      - ListaDoble   (inicio() + nodo->sig terminado en nullptr)
//      - ListaCircular (primero() + recorrido por cantidad de nodos)
//
//  No incluye ninguno de esos headers: usa templates con duck typing,
//  asi puedes incluir Util.h junto a la estructura que estes usando.
//
//  Para guardar:
//      - Estructuras lineales -> guardarArchivo(...)
//      - Estructura circular  -> guardarArchivoCircular(...)
//
//  Para cargar:
//      - cargarArchivo(...) recibe un callback "agregar" para que
//        cada estructura use su propio metodo (insertarFinal,
//        encolar, apilar, etc.).
// ═══════════════════════════════════════════════════════════════


// ═══════════════════════════════════════════════════════════════
//  guardarArchivo (estructuras lineales)
//  Recorre nodo a nodo desde est->inicio() hasta nullptr y escribe
//  cada elemento serializado en una linea del archivo.
//  Funciona con Lista, Pila, Cola y ListaDoble.
// ═══════════════════════════════════════════════════════════════
template <typename Estructura, typename FuncSerializar>
void guardarArchivo(Estructura* est, string ruta, FuncSerializar serializar) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        Banner::lineaCentrada("No se pudo abrir el archivo.", "\033[38;2;200;40;40m");
        return;
    }
    auto aux = est->inicio();
    while (aux != nullptr) {
        archivo << serializar(aux->elem) << endl;
        aux = aux->sig;
    }
    archivo.close();
  
}


// ═══════════════════════════════════════════════════════════════
//  guardarArchivoCircular (estructura circular)
//  Para ListaCircular: el recorrido nunca llega a nullptr, por eso
//  iteramos exactamente est->tam() veces a partir de primero().
// ═══════════════════════════════════════════════════════════════
template <typename Estructura, typename FuncSerializar>
void guardarArchivoCircular(Estructura* est, string ruta, FuncSerializar serializar) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        Banner::lineaCentrada("No se pudo abrir el archivo.", "\033[38;2;200;40;40m");
        return;
    }
    auto aux = est->primero();
    unsigned int n = est->tam();
    for (unsigned int i = 0; i < n; i++) {
        archivo << serializar(aux->elem) << endl;
        aux = aux->sig;
    }
    archivo.close();
}


// ═══════════════════════════════════════════════════════════════
//  cargarArchivo
//  Lee linea por linea, deserializa cada una y delega la insercion
//  al callback "agregar". Asi cada estructura usa su propio metodo:
//
//      Lista:         [&l](int n){ l.insertarFinal(n); }
//      Pila:          [&p](int n){ p.apilar(n); }
//      Cola:          [&c](int n){ c.encolar(n); }
//      ListaDoble:    [&ld](int n){ ld.insertarFinal(n); }
//      ListaCircular: [&lc](int n){ lc.insertarFinal(n); }
// ═══════════════════════════════════════════════════════════════
template <typename FuncDeserializar, typename FuncAgregar>
void cargarArchivo(string ruta, FuncDeserializar deserializar, FuncAgregar agregar) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        Banner::lineaCentrada("No se pudo abrir el archivo.", "\033[38;2;200;40;40m");
        return;
    }
    string linea;
    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        agregar(deserializar(linea));
        cargados++;
    }
    archivo.close();
    Banner::lineaCentrada(to_string(cargados) + " elementos cargados desde " + ruta, "\033[38;2;55;55;55m");
}