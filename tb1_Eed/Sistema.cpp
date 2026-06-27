#include "pch.h"
#include "Sistema.h"
#include "Tabla.h"
#include "Banner.h"
#include <iostream>
#include <cstdlib>   
#include <vector>
#include <string>


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
    archivoMgr.cargarUsuarios(usuarios);
}

Sistema::~Sistema() {
    if (idiomaSeleccionado) {
        delete idiomaSeleccionado;
        idiomaSeleccionado = nullptr;
    }
}

void Sistema::limpiarPantalla() {
    system("cls");
}

void Sistema::pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Sistema::iniciar() {
    menuPrincipal();
}


void Sistema::menuPrincipal() {
    int opcion;
    do {
        limpiarPantalla();
        // Logo dibujado por MATRIZ de colores (estilo pixel-art),
        // mismo concepto que DibujarMatriz del proyecto Juego Splash.
        // Se redibuja en cada vuelta para que quede fijo arriba del menu.
        Banner::dibujar();
        // Menu centrado sobre el fondo blanco del "Form", con paleta tipo
        // Duolingo en tonos oscuros para que se lea bien sobre blanco.
        const string VERDE_T = "\033[38;2;46;125;50m";  // verde oscuro
        const string GRIS_T = "\033[38;2;55;55;55m";    // gris oscuro
        const string ROJO_T = "\033[38;2;200;40;40m";   // rojo oscuro (Salir)

        Banner::lineaCentrada("===    Bienvenido a AprendeGo! C++    ===", VERDE_T);
        Banner::lineaVacia();
        Banner::lineaCentrada("--- Menu Principal ---", GRIS_T);
        Banner::lineaCentrada("1. Registrar usuario", VERDE_T);
        Banner::lineaCentrada("2. Seleccionar idioma", VERDE_T);
        Banner::lineaCentrada("3. Ver progreso", VERDE_T);
        Banner::lineaCentrada("4. Actualizar nivel de usuario", VERDE_T);
        Banner::lineaCentrada("5. Ver ranking de rachas", VERDE_T);
        Banner::lineaCentrada("6. Ordenar usuarios por nombre ascendente", VERDE_T);
        Banner::lineaCentrada("7. Ver usuarios de nivel avanzado", VERDE_T);
        Banner::lineaCentrada("8. Ordenar usuarios por nivel (Shell)", VERDE_T);
        Banner::lineaCentrada("9. Salir", ROJO_T);
        Banner::lineaVacia();
        Banner::lineaCentrada("Seleccione una opcion y presione ENTER:", GRIS_T);
        cout << "\033[107m\033[38;2;75;75;75m";   // fondo blanco / texto gris al teclear
        cin >> opcion;
        cout << RESET;

        switch (opcion) {
        case 1: limpiarPantalla(); registrarUsuario(); break;
        case 2: limpiarPantalla(); seleccionarIdioma(); break;
        case 3: limpiarPantalla(); verProgreso(); break;
        case 4: limpiarPantalla(); actualizarNivelUsuario(); break;
        case 5: limpiarPantalla(); mostrarRankingRachas(); break;
        case 6: limpiarPantalla(); ordenarUsuariosPorNombreAsc(); break;
        case 7: limpiarPantalla(); mostrarUsuariosAvanzados(); break;
        case 8: limpiarPantalla(); ordenarUsuariosPorNivel(); break;   // NUEVA
        case 9: cout << RED << "Saliendo..." << RESET << endl; break;
        default: cout << RED << "Opcion invalida." << RESET << endl;
        }
        if (opcion != 9) pausar();
    } while (opcion != 9);
}


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

    // Mensaje de completado SOLO cuando llega al 100 %
    if (progreso == total) {
        cout << MAGENTA << "\nFelicitaciones! Completado al 100%" << RESET << endl;
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

    archivoMgr.guardarUsuarios(usuarios);
    //_____
    archivoMgr.guardarNivelesIngles(usuarios);
    //ita
    archivoMgr.guardarNivelesItaliano(usuarios);
    //port

    archivoMgr.guardarNivelesPortugues(usuarios);
    archivoMgr.guardarNivelesRacha(usuarios);
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

    Usuario* usuarioEncontrado = buscarUsuario(nombreBuscado);
    if (!usuarioEncontrado) {
        cout << RED << "No existe un usuario con ese nombre." << RESET << endl;
        return;
    }

    usuarioActivo = usuarioEncontrado;   // <-- AGREGA ESTA LINEA

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

void Sistema::verProgreso() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    // Pide nombre igual que seleccionarIdioma
    string nombreBuscado;
    cout << "Ingrese su nombre: ";
    cin >> nombreBuscado;

    Usuario* encontrado = buscarUsuario(nombreBuscado);
    if (!encontrado) { cout << "Usuario no encontrado." << endl; return; }

    cout << "\n========== Progreso de " << encontrado->getNombre()
        << " ==========" << endl;

    // Niveles guardados del usuario
    cout << "Niveles registrados:" << endl;
    cout << "  Ingles:    " << encontrado->getNivelIngles() << endl;
    cout << "  Portugues: " << encontrado->getNivelPortugues() << endl;
    cout << "  Italiano:  " << encontrado->getNivelItaliano() << endl;

    Progreso* prog = encontrado->obtenerProgreso();

    cout << "\n--- Racha ---" << endl;
    prog->mostrarRacha();

    // Puntaje acumulado de la racha (1+2+...+actual)
    cout << "Puntaje por racha: " << prog->getRacha()->puntajeAcumulado() << endl;


    prog->mostrarHistorialErrores();

    //Total de errores contados recursivamente sobre la pila
    cout << "\nTotal de errores cometidos: " << prog->contarErrores() << endl;
    cout << "Nivel global: " << encontrado->nivelGlobal() << endl;
    cout << "Porcentaje de avance: "
        << prog->calcularPorcentaje(prog->getLeccionesComp(), prog->getLeccionesComp() + prog->contarErrores())
        << "%" << endl;
    cout << "Errores en repaso (ejercicio 0): "
        << prog->contarErroresDeEjercicio(0) << endl;


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
    limpiarPantalla();

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

    archivoMgr.guardarUsuarios(usuarios);
    archivoMgr.guardarNivelesRacha(usuarios);
}


void Sistema::actualizarNivelUsuario() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    string nombreBuscado;
    cout << "Ingrese el nombre del usuario: ";
    cin >> nombreBuscado;

    Usuario* usuarioEncontrado = buscarUsuario(nombreBuscado);   // <-- ESTA linea

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

    archivoMgr.guardarUsuarios(usuarios);
    //ingles txt
    archivoMgr.guardarNivelesIngles(usuarios);
    //ita
    archivoMgr.guardarNivelesItaliano(usuarios);
    //port

    archivoMgr.guardarNivelesPortugues(usuarios);

    cout << "Nivel actualizado correctamente." << endl;
}
bool compararRacha(Ranking a, Ranking b) {

    return a.getMejorRacha() > b.getMejorRacha();
}
bool compararPorNivelGlobal(Usuario a, Usuario b) {
    return a.nivelGlobal() > b.nivelGlobal();
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

    //  ORDENAMIENTO (se conserva para el guardado en archivo)
    Ordenamiento<Ranking>::selection(&ranking, compararRacha);

    archivoMgr.guardarRanking(ranking);
    archivoMgr.guardarNivelesRacha(usuarios);
    cout << "Ranking guardado correctamente." << endl;

    // ---------------------------------------------------------------
    //  ESTRUCTURA DE DATOS: ARBOL BINARIO DE BUSQUEDA (ABB)
    //  Insertamos cada Ranking en un ABB generico usando como criterio
    //  "mayor racha primero". El recorrido inorden del arbol devuelve
    //  el ranking YA ORDENADO de mejor a peor, sin volver a ordenar.
    //  El criterio es el mismo puntero a funcion 'compararRacha'.
    // ---------------------------------------------------------------
    ArbolBinario<Ranking> arbolRanking(compararRacha);

    auto* nodoLista = ranking.inicio();
    while (nodoLista != nullptr) {
        arbolRanking.insertar(nodoLista->elem);
        nodoLista = nodoLista->sig;
    }

    cout << "\n====== RANKING DE RACHAS (ABB inorden) ======" << endl;

    // Recolectamos las filas durante el recorrido inorden del arbol
    // y luego las mostramos en una tabla con bordes.
    vector<vector<string>> filasRanking;
    int pos = 1;
    // Lambda libre que captura 'pos' y el vector por referencia.
    arbolRanking.inorden([&pos, &filasRanking](Ranking r) {
        filasRanking.push_back({
            to_string(pos++),
            r.getNombre(),
            to_string(r.getMejorRacha()),
            r.clasificacion()
            });
        });

    Tabla::imprimir("RANKING DE RACHAS",
        { "#", "Usuario", "Racha", "Categoria" },
        filasRanking);

    cout << "Altura del arbol: " << arbolRanking.altura()
        << " | Nodos: " << arbolRanking.tam() << endl;

    // Lambda usada con contarSi del arbol: cuantos llegaron a categoria Oro.
    int oro = arbolRanking.contarSi([](Ranking r) {
        return r.clasificacion() == "Oro";
        });
    cout << "Usuarios en categoria Oro (racha >= 10): " << oro << endl;

    // Estadistica usando la lambda contarUsuariosConNivel
    cout << "\nUsuarios que alcanzaron nivel avanzado (3): "
        << contarUsuariosConNivel(3) << endl;
    cout << "Usuarios en nivel intermedio o mas (2): "
        << contarUsuariosConNivel(2) << endl;
}


void Sistema::ordenarUsuariosPorNombreAsc() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    //LAMBDA 1 para comparar por nombre
    usuarios.ordenar([](const Usuario& a, const Usuario& b) {
        return a.getNombre() < b.getNombre();
        });

    cout << "\n=== Usuarios ordenados por nombre (ascendente) ===" << endl;
    vector<vector<string>> filas;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        filas.push_back({ aux->elem.getNombre(), aux->elem.getEmail() });
        aux = aux->sig;
    }
    Tabla::imprimir("USUARIOS (A-Z)", { "Nombre", "Email" }, filas);
}

void Sistema::mostrarUsuariosAvanzados() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    // LAMBDA 2: criterio de "usuario avanzado" (algun idioma en nivel 3)
    auto esAvanzado = [](const Usuario& u) {
        return u.getNivelIngles() == 3
            || u.getNivelPortugues() == 3
            || u.getNivelItaliano() == 3;
        };

    cout << "\n=== Usuarios de nivel avanzado ===" << endl;
    vector<vector<string>> filas;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        if (esAvanzado(aux->elem)) {       // se usa la lambda
            filas.push_back({
                aux->elem.getNombre(),
                to_string(aux->elem.getNivelIngles()),
                to_string(aux->elem.getNivelPortugues()),
                to_string(aux->elem.getNivelItaliano())
                });
        }
        aux = aux->sig;
    }

    if (filas.empty())
        cout << "Ningun usuario ha alcanzado nivel avanzado todavia." << endl;
    else
        Tabla::imprimir("NIVEL AVANZADO",
            { "Nombre", "Ingles", "Portugues", "Italiano" }, filas);
}

Usuario* Sistema::buscarUsuario(const std::string& nombre) {
    // LAMBDA 6: predicado de coincidencia por nombre
    auto coincideNombre = [&nombre](const Usuario& u) {
        return u.getNombre() == nombre;
        };
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        if (coincideNombre(aux->elem)) return &aux->elem;
        aux = aux->sig;
    }
    return nullptr;
}

int Sistema::contarUsuariosConNivel(int nivelMin) {
    // LAMBDA 7: filtro por nivel minimo en cualquier idioma
    auto alcanzaNivel = [nivelMin](const Usuario& u) {
        return u.getNivelIngles() >= nivelMin
            || u.getNivelPortugues() >= nivelMin
            || u.getNivelItaliano() >= nivelMin;
        };
    int total = 0;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        if (alcanzaNivel(aux->elem)) total++;
        aux = aux->sig;
    }
    return total;
}

void Sistema::ordenarUsuariosPorNivel() {
    if (usuarios.estaVacia()) {
        cout << "No hay usuarios registrados." << endl;
        return;
    }

    // Copiar usuarios a una Lista para ordenarlos sin alterar la lista doble principal
    Lista<Usuario> copia;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        copia.insertarFinal(aux->elem);
        aux = aux->sig;
    }

    // SHELL SORT: eficiente para volumenes medianos
    Ordenamiento<Usuario>::shell(&copia, compararPorNivelGlobal);

    cout << "\n=== Usuarios por nivel global (mayor a menor) ===" << endl;
    vector<vector<string>> filas;
    for (unsigned int i = 0; i < copia.tam(); i++) {
        Usuario u = copia.obtener(i);
        filas.push_back({ u.getNombre(), to_string(u.nivelGlobal()) });
    }
    Tabla::imprimir("USUARIOS POR NIVEL GLOBAL (Shell Sort)",
        { "Nombre", "Nivel global" }, filas);
}