#pragma once
#include <string>
#include "ListaDoble.hpp"
#include "Usuario.h"
#include "Ingles.h"
#include "Util.h"
#include "Idioma.h"
#include "Leccion.h"
#include "Lista.hpp"
#include "Portugues.h"
#include "Italiano.h"
#include "Palabra.h"
#include "Progreso.h"
#include "ArchivoManager.h"
#include "Ranking.h"
#include "Ordenamiento.h"
#include "Ordenamiento2.hpp"
#include "HashMap.hpp"
#include "ArbolBinario.hpp"
#include "ArbolAVL.hpp"
#include "Banner.h"
#include "Heap.hpp"
#include "Diseño.h"
//piloto grafo 
#include "MallaLecciones.h"
using namespace std;

class Sistema {
private:
    ListaDoble<Usuario> usuarios;
    ArchivoManager archivoMgr;
    Idioma* idiomaSeleccionado;

    Usuario* usuarioActivo;
    Usuario* buscarUsuario(const std::string& nombre);

    int contarUsuariosConNivel(int nivelMin);

    // piloto grafo 
    MallaLecciones mallaLecciones;
public:

    Sistema();
    ~Sistema();

    void limpiarPantalla();
    void pausar();

    void iniciar();
    void menuPrincipal();



    void registrarUsuario();
    void seleccionarIdioma();
    void iniciarLecciones();
    void verProgreso();
    void actualizarNivelUsuario();

    void ordenarPorNombre();              // menu unificado (pregunta metodo)
    void ordenarUsuariosPorNombreAsc();   // interna 1: MergeSort de lista
    void mostrarRankingRachas();          // menu unificado (pregunta estructura)
    void rankingRachasABB();              // interna 1: Arbol Binario comun (ABB)
    void rankingRachasAVL();              // interna 2: Arbol AVL balanceado

    void mostrarUsuariosAvanzados();
    void mostrarTodosUsuarios();   // NUEVA: tabla con todos los usuarios registrados
    void ordenarUsuariosPorNivel();
    void buscarUsuarioHash();   // NUEVA: busca un usuario por nombre usando HashMap

    static void mostrarBarraProgreso(int progreso, int total);


    //implemntaciones hito 1 

    void rankingXpMergeSort();
    void rankingNombreQuickSort();
    //heap 
    void top3RachasHeap();
    //piloto grafo
    void verMallaAprendizaje();

    // GENERADOR DE DATASET: crea usuarios con datos aleatorios
    void generarDatasetAleatorio();
    // intefaz 
    void pantallaBienvenida();

};