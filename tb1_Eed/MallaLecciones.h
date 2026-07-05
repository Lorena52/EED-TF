#pragma once
#include "Grafo.hpp"
#include "NodoLeccion.h"
#include <string>
using namespace std;

// =====================================================================
//  MallaLecciones
//  Modela como GRAFO DIRIGIDO Y PONDERADO la progresion de niveles de
//  los TRES idiomas reales de la app: Ingles, Italiano y Portugues.
//
//  9 nodos = 3 idiomas x 3 niveles:
//    0,1,2 -> Ingles    nivel 1,2,3
//    3,4,5 -> Italiano  nivel 1,2,3
//    6,7,8 -> Portugues nivel 1,2,3
//
//  Cada idioma forma su propia cadena de prerrequisitos:
//    nivel 1 -> nivel 2 -> nivel 3
//  (no puedes hacer "completarOracion" sin haber pasado por
//  "ordenarOracion", igual que ya se exige en Idioma::iniciarEjercicios).
//  El peso de cada conexion son los minutos estimados para avanzar
//  de un nivel al siguiente.
//
//  Funcionalidades (algoritmos de Grafo.hpp):
//    - ordenSugerido()        -> orden topologico de TODAS las lecciones
//    - recorrerIdioma(nombre) -> DFS: revisa a fondo un idioma completo
//    - rutaMasRapida(origen)  -> Dijkstra: minutos minimos a cada nodo
//    - prerrequisitosDe(n)    -> que nivel(es) hay que dominar antes
// =====================================================================
class MallaLecciones {
private:
    Grafo<NodoLeccion, int>* g;

    static const int IDIOMAS = 3;
    static const int NIVELES = 3;
    string nombresIdioma[IDIOMAS] = { "Ingles", "Italiano", "Portugues" };
    //este el el indice de nuestro niveles para que el grafo lo entienda 
    int indice(int idiomaIdx, int nivel) const;   

public:
    MallaLecciones();
    ~MallaLecciones();

    void cargarDatos();  //constrimos        
    void listarLecciones();

    void ordenSugerido();                 
    //void recorrerIdioma(int idiomaIdx);   // DFS dentro de un idioma
    //void rutaMasRapida(int origen);       // Dijkstra
    void prerrequisitosDe(int nodo);      // prerrequisitos directos

   
    bool esNivelDesbloqueado(int idiomaIdx, int nivelActual, int nivelDeseado);
  
    string mensajeBloqueo(int idiomaIdx, int nivelActual, int nivelDeseado);
    int  idiomaIdxPorNombre(const string& nombre) const;  

    int  cantidadNodos() const;
    void mostrarMenuIdiomas();     

    // Usa la matriz de adyacencia del GRAFO para averiguar cual es
    // el siguiente nivel desde (idiomaIdx, nivelActual).
    // Devuelve el nuevo nivel (2 o 3), o -1 si ya esta en el maximo.
    int siguienteNivel(int idiomaIdx, int nivelActual);

    // Detalle textual del nodo (idioma, nivel) para el mensaje al usuario.
    string detalleNodo(int idiomaIdx, int nivel);
};
