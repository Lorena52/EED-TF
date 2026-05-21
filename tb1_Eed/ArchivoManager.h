#pragma once
#include <iostream>
#include <string>
#include "Usuario.h"
#include "Idioma.h"
#include "Leccion.h"
#include "Lista.hpp"

using namespace std;


class ArchivoManager
{
private:
	string rutaBase;
public:
    ArchivoManager();
	~ArchivoManager();


	void guardarDatos();
	void cargarDatos();


    //string getRutaBase();


	//Lista<Usuario> cargarUsuarios();
	//Lista<Idiomas> cargarIdiomas();
	//void guardarProgreso(Usuario* usuario);
	//Lista<Lecciones> cargarLecciones();
	//void exportarReporte();
};

