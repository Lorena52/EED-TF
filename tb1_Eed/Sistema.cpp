#include "pch.h"
#include "Sistema.h"
#include <iostream>


//COLORES AGREGADOS GRACIAS A LA IA
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

using namespace std;

Sistema::Sistema() : idiomaSeleccionado(nullptr), usuarioActivo(nullptr) {
    //LAMBDAS
    cargarArchivo("usuarios.txt",
        [](string linea) { return Usuario::deserializar(linea); },
        [this](Usuario u) { usuarios.insertarFinal(u); });
}
Sistema::~Sistema() {
    if (idiomaSeleccionado) {
        delete idiomaSeleccionado;
        idiomaSeleccionado = nullptr;
    }
}

void Sistema::iniciar() {
    cout << CYAN << BOLD;
    cout << "=========================================\n";
    cout << "===    Bienvenido a AprendeGo! C++    ===\n";
    cout << "=========================================\n" << RESET;
    menuPrincipal();
}


void Sistema::menuPrincipal() {
    int opcion;
    do {
        cout << YELLOW << "\n--- Menu Principal ---" << RESET << endl;
        cout << GREEN << "1. Registrar usuario" << RESET << endl;
        cout << GREEN << "2. Seleccionar idioma" << RESET << endl;
        cout << GREEN << "3. Ver progreso" << RESET << endl;
        cout << GREEN << "4. Actualizar nivel de usuario" << RESET << endl;
        cout << GREEN << "5. Ver ranking de rachas" << RESET << endl;
        cout << GREEN << "6. Ordenar usuarios por nombre ascendente" << RESET << endl;
        cout << RED << "7. Salir" << RESET << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: registrarUsuario(); break;
        case 2: seleccionarIdioma(); break;
        case 3: verProgreso(); break;
        case 4: actualizarNivelUsuario(); break;
        case 5: mostrarRankingRachas(); break;
        case 6: ordenarUsuariosPorNombreAsc(); break;
        case 7: cout << RED << "Saliendo..." << RESET << endl; break;
        default: cout << RED << "Opción inválida." << RESET << endl;
        }
    } while (opcion != 7);
}

//RECURSIVIDAD
void Sistema::mostrarBarraProgreso(int progreso, int total) {
    int ancho = 30;
    int completado = (progreso * ancho) / total;

    cout << BLUE << "[";
    cout << GREEN; // activar color una sola vez
    for (int i = 0; i < completado; i++) {
        cout << "#";
    }
    cout << RESET; //cerrar color después de los completados
    for (int i = completado; i < ancho; i++) {
        cout << "-";
    }
    cout << BLUE << "] " << RESET;
    cout << (progreso * 100 / total) << "%" << endl;

    // Cuando llega al 100%, felicitar y regresar al menú
    if (progreso == total) {
        cout << MAGENTA << "\n¡Felicitaciones! Has completado la lección al 100% " << RESET << endl;
        cout << CYAN << "Regresando al menú principal..." << RESET << endl;
        menuPrincipal();
    }
}



void Sistema::registrarUsuario() {
    string nombre, email;
    int ni, np, ni2;

    cout << "Ingrese nombre: ";
    cin >> nombre;

    ListaDoble<Usuario>::Nodo* aux = usuarios.inicio();

    while (aux != nullptr) {
        if (aux->elem.getNombre() == nombre) {
            cout << "Ya existe un usuario con ese nombre. Intente otro." << endl;
            return;
        }
        aux = aux->sig;
    }

    cout << "Ingrese email: ";
    cin >> email;

    cout << "Nivel de Inglés (1-3): ";
    cin >> ni;
    cout << "Nivel de Portugués (1-3): ";
    cin >> np;
    cout << "Nivel de Italiano (1-3): ";
    cin >> ni2;

    Usuario nuevo(usuarios.tam() + 1, nombre, email, ni, np, ni2);
    usuarios.insertarFinal(nuevo);

    //LAMBDA
    guardarArchivo(&usuarios, "usuarios.txt",
        [](Usuario u) { return u.serializar(); });

    cout << "Usuario registrado con éxito." << endl;
}


void Sistema::seleccionarIdioma() {
    if (usuarios.estaVacia()) {
        cout << RED << "Primero registre un usuario." << RESET << endl;
        return;
    }

    string nombreBuscado;
    cout << "Ingrese su nombre para continuar: ";
    cin >> nombreBuscado;

    ListaDoble<Usuario>::Nodo* aux = usuarios.inicio();
    Usuario* usuarioEncontrado = nullptr;

    while (aux != nullptr) {
        if (aux->elem.getNombre() == nombreBuscado) {
            usuarioEncontrado = &(aux->elem);
            usuarioActivo = usuarioEncontrado;
            break;
        }
        aux = aux->sig;
    }

    if (!usuarioEncontrado) {
        cout << RED << "No existe un usuario con ese nombre." << RESET << endl;
        return;
    }

    cout << GREEN << "Bienvenida(o), " << usuarioEncontrado->getNombre() << "!" << RESET << endl;

    int opcion;
    cout << BLUE << "\nSeleccione idioma:" << RESET << endl;
    cout << "1. Inglés [EN]" << endl;
    cout << "2. Portugués [PT]" << endl;
    cout << "3. Italiano [IT]" << endl;
    cin >> opcion;

    delete idiomaSeleccionado;

    switch (opcion) {
    case 1:
        idiomaSeleccionado = new Ingles();
        idiomaSeleccionado->setNivel(usuarioEncontrado->getNivelIngles());
        idiomaSeleccionado->cargarVocabulario();
        break;
    case 2:
        idiomaSeleccionado = new Portugues();
        idiomaSeleccionado->setNivel(usuarioEncontrado->getNivelPortugues());
        idiomaSeleccionado->cargarVocabulario();
        break;
    case 3:
        idiomaSeleccionado = new Italiano();
        idiomaSeleccionado->setNivel(usuarioEncontrado->getNivelItaliano());
        idiomaSeleccionado->cargarVocabulario();
        break;
    default:
        cout << RED << "Opción inválida." << RESET << endl;
        return;
    }

    iniciarLecciones();
}

//Función auxiliar: ver progreso rachaaaaaaaaaaaaaaaaaa
void Sistema::verProgreso() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    // Pide nombre igual que seleccionarIdioma
    string nombreBuscado;
    cout << "Ingrese su nombre: ";
    cin >> nombreBuscado;

    auto* aux = usuarios.inicio();
    Usuario* encontrado = nullptr;
    while (aux != nullptr) {
        if (aux->elem.getNombre() == nombreBuscado) {
            encontrado = &(aux->elem);
            break;
        }
        aux = aux->sig;
    }
    if (!encontrado) { cout << "Usuario no encontrado." << endl; return; }

    cout << "\n========== Progreso de " << encontrado->getNombre()
        << " ==========" << endl;

    // Niveles guardados del usuario
    cout << "Niveles registrados:" << endl;
    cout << "  Ingles:    " << encontrado->getNivelIngles() << endl;
    cout << "  Portugues: " << encontrado->getNivelPortugues() << endl;
    cout << "  Italiano:  " << encontrado->getNivelItaliano() << endl;

    Progreso* prog = encontrado->obtenerProgreso();

    /*cout << "\nPorcentaje de aciertos: "
        << prog->getPorcentaje() << "%" << endl;

    cout << "Lecciones completadas:  "
        << prog->getLeccionesComp() << endl;*/

    
    cout << "\n--- Racha ---" << endl;
    prog->mostrarRacha();

    
    prog->mostrarHistorialErrores();

    cout << "=================================" << endl;
}

void Sistema::iniciarLecciones() {
    if (!idiomaSeleccionado) return;

    int modo;
    cout << CYAN << "\n¿Qué desea hacer?" << RESET << endl;
    cout << "1. Repaso continuo de palabras" << endl;
    cout << "2. Iniciar lección" << endl;
    cout << "3. Ver diccionario" << endl;
    cin >> modo;

    if (modo == 1) {
        idiomaSeleccionado->repasoContinuo(*(usuarioActivo->obtenerProgreso()));
    }
    else if (modo == 2) {
        idiomaSeleccionado->mostrarTeoria();
        //Ahora iniciarEjercicios maneja todo el flujo y la barra
        idiomaSeleccionado->iniciarEjercicios(*(usuarioActivo->obtenerProgreso()));

        cout << endl << MAGENTA << "=== ¡Lección completada! ===" << RESET << endl;
    }
    else if (modo == 3) {
        idiomaSeleccionado->diccionario();
    }
    else {
        cout << RED << "Opción inválida." << RESET << endl;
    }

    guardarArchivo(&usuarios, "usuarios.txt",
        [](Usuario u) { return u.serializar(); });
}


void Sistema::actualizarNivelUsuario() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    string nombreBuscado;
    cout << "Ingrese el nombre del usuario: ";
    cin >> nombreBuscado;

    auto aux = usuarios.inicio();
    Usuario* usuarioEncontrado = nullptr;

    while (aux != nullptr) {
        if (aux->elem.getNombre() == nombreBuscado) {
            usuarioEncontrado = &(aux->elem);
            break;
        }
        aux = aux->sig;
    }

    if (!usuarioEncontrado) {
        cout << "Usuario no encontrado." << endl;
        return;
    }

    cout << "Usuario encontrado: " << usuarioEncontrado->getNombre() << endl;
    cout << "Niveles actuales:" << endl;
    cout << "Inglés: " << usuarioEncontrado->getNivelIngles() << endl;
    cout << "Portugués: " << usuarioEncontrado->getNivelPortugues() << endl;
    cout << "Italiano: " << usuarioEncontrado->getNivelItaliano() << endl;

    int opcionIdioma, nuevoNivel;
    cout << "\nSeleccione idioma a actualizar:" << endl;
    cout << "1. Inglés" << endl;
    cout << "2. Portugués" << endl;
    cout << "3. Italiano" << endl;
    cin >> opcionIdioma;

    cout << "Ingrese nuevo nivel (1=Base, 2=Intermedio, 3=Avanzado): ";
    cin >> nuevoNivel;

    switch (opcionIdioma) {
    case 1:
        usuarioEncontrado->setNivelIngles(nuevoNivel);
        if (idiomaSeleccionado != nullptr) {
            idiomaSeleccionado->setNivel(nuevoNivel);
            idiomaSeleccionado->cargarVocabulario();
        }
        break;
    case 2:
        usuarioEncontrado->setNivelPortugues(nuevoNivel);
        if (idiomaSeleccionado) {
            idiomaSeleccionado->setNivel(nuevoNivel);
            idiomaSeleccionado->cargarVocabulario();
        }        break;
    case 3:
        usuarioEncontrado->setNivelItaliano(nuevoNivel);
        if (idiomaSeleccionado) {
            idiomaSeleccionado->setNivel(nuevoNivel);
            idiomaSeleccionado->cargarVocabulario();
        }
        break;
    default:
        cout << "Opción inválida." << endl;
        return;
    }

    // Guardar cambios en archivo
    guardarArchivo(&usuarios, "usuarios.txt",
        [](Usuario u) { return u.serializar(); });

    cout << "Nivel actualizado correctamente." << endl;
}
bool compararRacha(Ranking a, Ranking b) {

    return a.getMejorRacha() > b.getMejorRacha();
}

void Sistema::mostrarRankingRachas() {

    if (usuarios.estaVacia()) {

        cout << "No hay usuarios registrados." << endl;
        return;
    }

    Lista<Ranking> ranking;

    auto* aux = usuarios.inicio();

    while (aux != nullptr) {

        Usuario u = aux->elem;

        ranking.insertarFinal(

            Ranking(u.getNombre(), u.obtenerProgreso()->getRacha()->getMaxima()
            )
        );

        aux = aux->sig;
    }

    //  ORDENAMIENTO
    Ordenamiento<Ranking>::selection( &ranking,compararRacha);
    
    //LAMBDA
    guardarArchivo(&ranking,"ranking.txt",  [](Ranking r) {
         return r.serializar();
        }
    );
    cout << "Ranking guardado correctamente." << endl;
    cout << "\n====== RANKING DE RACHAS ======" << endl;

    auto* r = ranking.inicio();

    int pos = 1;

    while (r != nullptr) {

        cout << pos++ << ". "
            << r->elem.getNombre()
            << " -> "
            << r->elem.getMejorRacha()
            << endl;

        r = r->sig;
    }

    cout << "===============================" << endl;
}


void Sistema::ordenarUsuariosPorNombreAsc() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

	//LAMBDA para comparar por nombre
    usuarios.ordenar([](const Usuario& a, const Usuario& b) {
        return a.getNombre() < b.getNombre();
        });

    cout << "\n=== Usuarios ordenados por nombre (ascendente) ===" << endl;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        cout << aux->elem.getNombre() << " - " << aux->elem.getEmail() << endl;
        aux = aux->sig;
    }
}

