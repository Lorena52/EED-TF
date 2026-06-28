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
    // Tras limpiar, pinta el fondo blanco del "Form" para que TODAS las
    // pantallas tengan el mismo fondo (la matriz/Form) de forma uniforme.
    Banner::fondoForm();
}

void Sistema::pausar() {
    Banner::lineaVacia();
    Banner::promptCentrado("Presione ENTER para continuar...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << RESET;
}

void Sistema::iniciar() {
    menuPrincipal();
}


void Sistema::menuPrincipal() {
    int opcion;
    do {
        system("cls");   // Banner::dibujar() ya pinta el fondo blanco + logo
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
    if (total <= 0) total = 1;
    int ancho = 30;
    int completado = (progreso * ancho) / total;

    // Construir la barra como texto: [#####-----] NN%
    string barra = "[";
    for (int i = 0; i < completado; i++) barra += "#";
    for (int i = completado; i < ancho; i++) barra += "-";
    barra += "] " + to_string(progreso * 100 / total) + "%";

    // Centrada sobre el fondo blanco, en verde oscuro.
    Banner::lineaCentrada(barra, "\033[38;2;46;125;50m");

    if (progreso == total) {
        Banner::lineaCentrada("Felicitaciones! Completado al 100%",
            "\033[38;2;46;125;50m");
    }
}

void Sistema::registrarUsuario() {
    string nombre, email;
    int ni, np, ni2;

    Banner::promptCentrado("Ingrese nombre: ");
    cin >> nombre;

    ListaDoble<Usuario>::Nodo* aux = usuarios.inicio();

    while (aux != nullptr) {
        if (aux->elem.getNombre() == nombre) {
            Banner::lineaCentrada("Ya existe un usuario con ese nombre. Intente otro.", "\033[38;2;200;40;40m");
            return;
        }
        aux = aux->sig;
    }

    Banner::promptCentrado("Ingrese email: ");
    cin >> email;

    Banner::promptCentrado("Nivel de Ingles (1-3): ");
    cin >> ni;
    Banner::promptCentrado("Nivel de Portugues (1-3): ");
    cin >> np;
    Banner::promptCentrado("Nivel de Italiano (1-3): ");
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
    Banner::lineaCentrada("Usuario registrado con exito.", "\033[38;2;55;55;55m");
}


void Sistema::seleccionarIdioma() {
    const string VERDE_T = "\033[38;2;46;125;50m";
    const string GRIS_T = "\033[38;2;55;55;55m";
    const string ROJO_T = "\033[38;2;200;40;40m";

    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("Primero registre un usuario.", ROJO_T);
        return;
    }

    Banner::lineaCentrada("--- Seleccionar idioma ---", VERDE_T);
    Banner::lineaVacia();

    string nombreBuscado;
    Banner::promptCentrado("Ingrese su nombre para continuar: ");
    cin >> nombreBuscado;

    Usuario* usuarioEncontrado = buscarUsuario(nombreBuscado);
    if (!usuarioEncontrado) {
        Banner::lineaVacia();
        Banner::lineaCentrada("No existe un usuario con ese nombre.", ROJO_T);
        return;
    }

    usuarioActivo = usuarioEncontrado;

    Banner::lineaVacia();
    Banner::lineaCentrada("Bienvenida(o), " + usuarioEncontrado->getNombre() + "!", VERDE_T);
    Banner::lineaVacia();

    int opcion;
    Banner::lineaCentrada("Seleccione idioma:", GRIS_T);
    Banner::lineaCentrada("1. Ingles [EN]", VERDE_T);
    Banner::lineaCentrada("2. Portugues [PT]", VERDE_T);
    Banner::lineaCentrada("3. Italiano [IT]", VERDE_T);
    Banner::lineaVacia();
    Banner::promptCentrado("Opcion: ");
    cin >> opcion;
    cout << RESET;

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
        Banner::lineaCentrada("Opcion invalida.", ROJO_T);
        return;
    }

    iniciarLecciones();
}

void Sistema::verProgreso() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    // Pide nombre igual que seleccionarIdioma
    string nombreBuscado;
    Banner::promptCentrado("Ingrese su nombre: ");
    cin >> nombreBuscado;

    Usuario* encontrado = buscarUsuario(nombreBuscado);
    if (!encontrado) { Banner::lineaCentrada("Usuario no encontrado.", "\033[38;2;200;40;40m"); return; }

    Banner::lineaCentrada("========== Progreso de " + encontrado->getNombre() + " ==========", "\033[38;2;55;55;55m");

    // Niveles guardados del usuario
    Banner::lineaCentrada("Niveles registrados:", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Ingles:    " + to_string(encontrado->getNivelIngles()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Portugues: " + to_string(encontrado->getNivelPortugues()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Italiano:  " + to_string(encontrado->getNivelItaliano()), "\033[38;2;55;55;55m");

    Progreso* prog = encontrado->obtenerProgreso();

    Banner::lineaCentrada("\n--- Racha ---", "\033[38;2;55;55;55m");
    prog->mostrarRacha();

    // Puntaje acumulado de la racha (1+2+...+actual)
    Banner::lineaCentrada("Puntaje por racha: " + to_string(prog->getRacha()->puntajeAcumulado()), "\033[38;2;55;55;55m");


    prog->mostrarHistorialErrores();

    //Total de errores contados recursivamente sobre la pila
    Banner::lineaCentrada("Total de errores cometidos: " + to_string(prog->contarErrores()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Nivel global: " + to_string(encontrado->nivelGlobal()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Porcentaje de avance: "
        + to_string(prog->calcularPorcentaje(prog->getLeccionesComp(), prog->getLeccionesComp() + prog->contarErrores()))
        + "%", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Errores en repaso (ejercicio 0): "
        + to_string(prog->contarErroresDeEjercicio(0)), "\033[38;2;55;55;55m");


    Banner::lineaCentrada("=================================", "\033[38;2;55;55;55m");
}

void Sistema::iniciarLecciones() {
    if (!idiomaSeleccionado) return;
    const string VERDE_T = "\033[38;2;46;125;50m";
    const string GRIS_T = "\033[38;2;55;55;55m";
    const string ROJO_T = "\033[38;2;200;40;40m";

    int modo;
    Banner::lineaVacia();
    Banner::lineaCentrada("Que desea hacer?", GRIS_T);
    Banner::lineaCentrada("1. Repaso continuo de palabras", VERDE_T);
    Banner::lineaCentrada("2. Iniciar leccion", VERDE_T);
    Banner::lineaCentrada("3. Ver diccionario", VERDE_T);
    Banner::lineaVacia();
    Banner::promptCentrado("Opcion: ");
    cin >> modo;
    cout << RESET;
    limpiarPantalla();

    if (modo == 1) {
        idiomaSeleccionado->repasoContinuo(*(usuarioActivo->obtenerProgreso()));
    }
    else if (modo == 2) {
        idiomaSeleccionado->mostrarTeoria();
        //Ahora iniciarEjercicios maneja todo el flujo y la barra
        idiomaSeleccionado->iniciarEjercicios(*(usuarioActivo->obtenerProgreso()));

        Banner::lineaVacia();
        Banner::lineaCentrada("=== Leccion completada! ===", VERDE_T);
    }
    else if (modo == 3) {
        idiomaSeleccionado->diccionario();
    }
    else {
        Banner::lineaCentrada("Opcion invalida.", ROJO_T);
    }

    archivoMgr.guardarUsuarios(usuarios);
    archivoMgr.guardarNivelesRacha(usuarios);
}


void Sistema::actualizarNivelUsuario() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    string nombreBuscado;
    Banner::promptCentrado("Ingrese el nombre del usuario: ");
    cin >> nombreBuscado;

    Usuario* usuarioEncontrado = buscarUsuario(nombreBuscado);   // <-- ESTA linea

    if (!usuarioEncontrado) {
        Banner::lineaCentrada("Usuario no encontrado.", "\033[38;2;200;40;40m");
        return;
    }

    Banner::lineaCentrada("Usuario encontrado: " + usuarioEncontrado->getNombre(), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Niveles actuales:", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Ingles: " + to_string(usuarioEncontrado->getNivelIngles()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Portugues: " + to_string(usuarioEncontrado->getNivelPortugues()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Italiano: " + to_string(usuarioEncontrado->getNivelItaliano()), "\033[38;2;55;55;55m");

    int opcionIdioma, nuevoNivel;
    Banner::lineaCentrada("\nSeleccione idioma a actualizar:", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("1. Ingles", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("2. Portugues", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("3. Italiano", "\033[38;2;55;55;55m");
    cin >> opcionIdioma;

    Banner::promptCentrado("Ingrese nuevo nivel (1=Base, 2=Intermedio, 3=Avanzado): ");
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
        Banner::lineaCentrada("Opcion invalida.", "\033[38;2;200;40;40m");
        return;
    }

    archivoMgr.guardarUsuarios(usuarios);
    //ingles txt
    archivoMgr.guardarNivelesIngles(usuarios);
    //ita
    archivoMgr.guardarNivelesItaliano(usuarios);
    //port

    archivoMgr.guardarNivelesPortugues(usuarios);

    Banner::lineaCentrada("Nivel actualizado correctamente.", "\033[38;2;55;55;55m");
}
bool compararRacha(Ranking a, Ranking b) {

    return a.getMejorRacha() > b.getMejorRacha();
}
bool compararPorNivelGlobal(Usuario a, Usuario b) {
    return a.nivelGlobal() > b.nivelGlobal();
}

void Sistema::mostrarRankingRachas() {

    if (usuarios.estaVacia()) {

        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
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
    Banner::lineaCentrada("Ranking guardado correctamente.", "\033[38;2;55;55;55m");

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

    Banner::lineaCentrada("====== RANKING DE RACHAS (ABB inorden) ======", "\033[38;2;46;125;50m");

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

    Banner::lineaCentrada("Altura del arbol: " + to_string(arbolRanking.altura())
        + " | Nodos: " + to_string(arbolRanking.tam()), "\033[38;2;55;55;55m");

    // Lambda usada con contarSi del arbol: cuantos llegaron a categoria Oro.
    int oro = arbolRanking.contarSi([](Ranking r) {
        return r.clasificacion() == "Oro";
        });
    Banner::lineaCentrada("Usuarios en categoria Oro (racha >= 10): " + to_string(oro), "\033[38;2;55;55;55m");

    // Estadistica usando la lambda contarUsuariosConNivel
    Banner::lineaCentrada("Usuarios que alcanzaron nivel avanzado (3): "
        + to_string(contarUsuariosConNivel(3)), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Usuarios en nivel intermedio o mas (2): "
        + to_string(contarUsuariosConNivel(2)), "\033[38;2;55;55;55m");
}


void Sistema::ordenarUsuariosPorNombreAsc() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    //LAMBDA 1 para comparar por nombre
    usuarios.ordenar([](const Usuario& a, const Usuario& b) {
        return a.getNombre() < b.getNombre();
        });

    Banner::lineaCentrada("=== Usuarios ordenados por nombre (ascendente) ===", "\033[38;2;46;125;50m");
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
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    // LAMBDA 2: criterio de "usuario avanzado" (algun idioma en nivel 3)
    auto esAvanzado = [](const Usuario& u) {
        return u.getNivelIngles() == 3
            || u.getNivelPortugues() == 3
            || u.getNivelItaliano() == 3;
        };

    Banner::lineaCentrada("=== Usuarios de nivel avanzado ===", "\033[38;2;46;125;50m");
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
        Banner::lineaCentrada("Ningun usuario ha alcanzado nivel avanzado todavia.", "\033[38;2;55;55;55m");
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
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
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

    Banner::lineaCentrada("=== Usuarios por nivel global (mayor a menor) ===", "\033[38;2;46;125;50m");
    vector<vector<string>> filas;
    for (unsigned int i = 0; i < copia.tam(); i++) {
        Usuario u = copia.obtener(i);
        filas.push_back({ u.getNombre(), to_string(u.nivelGlobal()) });
    }
    Tabla::imprimir("USUARIOS POR NIVEL GLOBAL (Shell Sort)",
        { "Nombre", "Nivel global" }, filas);
}