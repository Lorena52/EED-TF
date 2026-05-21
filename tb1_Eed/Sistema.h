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

using namespace std;

class Sistema {
private:   
    ListaDoble<Usuario> usuarios;  
    ArchivoManager archivoMgr;     
    Idioma* idiomaSeleccionado;  
  
    Usuario* usuarioActivo;
    
public:
  
    Sistema();
    ~Sistema();

    
    void iniciar();         
    void menuPrincipal(); 



    void registrarUsuario();
    void seleccionarIdioma();
    void iniciarLecciones();
    void verProgreso();
    void actualizarNivelUsuario();

    void ordenarUsuariosPorNombreAsc();
    void mostrarRankingRachas();

    void mostrarBarraProgreso(int progreso, int total);
};
