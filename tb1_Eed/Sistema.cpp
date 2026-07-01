#include "pch.h"
#include "Sistema.h"
#include "Tabla.h"
#include "Banner.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>   


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
    mallaLecciones.cargarDatos();
}

Sistema::~Sistema() {
    if (idiomaSeleccionado) {
        delete idiomaSeleccionado;
        idiomaSeleccionado = nullptr;
    }
}

void Sistema::limpiarPantalla() {
    system("cls");
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
        system("cls");
       
        Banner::dibujar();
        const string VERDE_T = "[38;2;46;125;50m";
        const string GRIS_T = "[38;2;55;55;55m";
        const string ROJO_T = "[38;2;200;40;40m";
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
        Banner::lineaCentrada("9. Buscar usuario por nombre (Hash)", VERDE_T);
        Banner::lineaCentrada("10. Ranking XP con MergeSort", VERDE_T);
        Banner::lineaCentrada("11. Ordenar por nombre con QuickSort", VERDE_T);
        Banner::lineaCentrada("12. Top 3 usuarios con mayor racha (Heap)", VERDE_T);
        Banner::lineaCentrada("13. Mapa de aprendizaje (Grafo)", VERDE_T);
        Banner::lineaCentrada("14. Salir", ROJO_T);
        Diseño::mostrar();
        Banner::lineaVacia();
        Banner::promptCentrado("Seleccione una opcion y presione ENTER: ");
        cin >> opcion;
       
       
        system("pause");
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
        case 9: limpiarPantalla(); buscarUsuarioHash(); break;
        case 10: limpiarPantalla(); rankingXpMergeSort(); break;
        case 11: limpiarPantalla(); rankingNombreQuickSort(); break;
        case 12: limpiarPantalla(); top3RachasHeap(); break;
        case 13: limpiarPantalla(); verMallaAprendizaje(); break;
        case 14: Banner::lineaCentrada("Saliendo...", "\033[38;2;55;55;55m"); break;
        default: Banner::lineaCentrada("Opcion invalida.", "\033[38;2;200;40;40m");
        }
        if (opcion != 14) pausar();
    } while (opcion != 14);
}


void Sistema::mostrarBarraProgreso(int progreso, int total) {
    if (total <= 0) total = 1;
    int ancho = 30;
    int completado = (progreso * ancho) / total;
    string barra = "[";
    for (int i = 0; i < completado; i++) barra += "#";
    for (int i = completado; i < ancho; i++) barra += "-";
    barra += "] " + to_string(progreso * 100 / total) + "%";
    Banner::lineaCentrada(barra, "[38;2;46;125;50m");
    if (progreso == total)
        Banner::lineaCentrada("Felicitaciones! Completado al 100%", "[38;2;46;125;50m");
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
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("Primero registre un usuario.", "\033[38;2;55;55;55m");
        return;
    }

    string nombreBuscado;
    Banner::promptCentrado("Ingrese su nombre para continuar: ");
    cin >> nombreBuscado;

    Usuario* usuarioEncontrado = buscarUsuario(nombreBuscado);
    if (!usuarioEncontrado) {
        Banner::lineaCentrada("No existe un usuario con ese nombre.", "\033[38;2;55;55;55m");
        return;
    }

    usuarioActivo = usuarioEncontrado;   // <-- AGREGA ESTA LINEA

    Banner::lineaCentrada("Bienvenida(o), " + usuarioEncontrado->getNombre() + "!", "\033[38;2;46;125;50m");

    int opcion;
    Banner::lineaCentrada("Seleccione idioma:", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("1. Ingles [EN]", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("2. Portugues [PT]", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("3. Italiano [IT]", "\033[38;2;55;55;55m");
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
        Banner::lineaCentrada("Opcion invalida.", "\033[38;2;200;40;40m");
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

    Banner::lineaCentrada("--- Racha ---", "\033[38;2;55;55;55m");
    prog->mostrarRacha();

    // Puntaje acumulado de la racha (1+2+...+actual)
    Banner::lineaCentrada("Puntaje por racha: " + to_string(prog->getRacha()->puntajeAcumulado()), "\033[38;2;55;55;55m");


    prog->mostrarHistorialErrores();

    //Total de errores contados recursivamente sobre la pila
    Banner::lineaCentrada("Total de errores cometidos: " + to_string(prog->contarErrores()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Nivel global: " + to_string(encontrado->nivelGlobal()), "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Porcentaje de avance: " + to_string(prog->calcularPorcentaje(prog->getLeccionesComp(), prog->getLeccionesComp() + prog->contarErrores())) + "%", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("Errores en repaso (ejercicio 0): " + to_string(prog->contarErroresDeEjercicio(0)), "\033[38;2;55;55;55m");


    Banner::lineaCentrada("=================================", "\033[38;2;55;55;55m");
}

void Sistema::iniciarLecciones() {
    if (!idiomaSeleccionado) return;

    int modo;
    Banner::lineaCentrada("Que desea hacer?", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("1. Repaso continuo de palabras", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("2. Iniciar leccion", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("3. Ver diccionario", "\033[38;2;55;55;55m");
    cin >> modo;
    limpiarPantalla();

    if (modo == 1) {
        idiomaSeleccionado->repasoContinuo(*(usuarioActivo->obtenerProgreso()));
    }
    else if (modo == 2) {
        idiomaSeleccionado->mostrarTeoria();
        //Ahora iniciarEjercicios maneja todo el flujo y la barra
        idiomaSeleccionado->iniciarEjercicios(*(usuarioActivo->obtenerProgreso()));

        Banner::lineaCentrada("=== Leccion completada! ===", "\033[38;2;46;125;50m");
    }
    else if (modo == 3) {
        idiomaSeleccionado->diccionario();
    }
    else {
        Banner::lineaCentrada("Opcion invalida.", "\033[38;2;200;40;40m");
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
    Banner::lineaCentrada("Seleccione idioma a actualizar:", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("1. Ingles", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("2. Portugues", "\033[38;2;55;55;55m");
    Banner::lineaCentrada("3. Italiano", "\033[38;2;55;55;55m");
    cin >> opcionIdioma;

    Banner::promptCentrado("Ingrese nuevo nivel (1=Base, 2=Intermedio, 3=Avanzado): ");
    cin >> nuevoNivel;
    // aqui bloquedo si es que quiere un nivel nuevo o ses de un nivel 1  a 4 
    {
        string nombreIdiomaSel = (opcionIdioma == 1) ? "Ingles" : (opcionIdioma == 2) ? "Portugues" : (opcionIdioma == 3) ? "Italiano" : "";
        int idiomaIdx = mallaLecciones.idiomaIdxPorNombre(nombreIdiomaSel);
        int nivelActualIdioma = (opcionIdioma == 1) ? usuarioEncontrado->getNivelIngles()
            : (opcionIdioma == 2) ? usuarioEncontrado->getNivelPortugues()
            : (opcionIdioma == 3) ? usuarioEncontrado->getNivelItaliano()
            : -1;
        if (idiomaIdx != -1 && !mallaLecciones.esNivelDesbloqueado(idiomaIdx, nivelActualIdioma, nuevoNivel)) {
            Banner::lineaCentrada("===== NIVEL BLOQUEADO =====", "\033[38;2;200;40;40m");
            cout << mallaLecciones.mensajeBloqueo(idiomaIdx, nivelActualIdioma, nuevoNivel);
            return;
        }
    }

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

    //  ORDENAMIENTO
    Ordenamiento<Ranking>::selection(&ranking, compararRacha);

    archivoMgr.guardarRanking(ranking);
    archivoMgr.guardarNivelesRacha(usuarios);
    Banner::lineaCentrada("Ranking guardado correctamente.", "[38;2;46;125;50m");

    // ESTRUCTURA DE DATOS: ARBOL BINARIO DE BUSQUEDA (ABB)
    // Cada Ranking entra al ABB con criterio "mayor racha primero";
    // el recorrido inorden devuelve el ranking ya ordenado.
    ArbolBinario<Ranking> arbolRanking(compararRacha);
    auto* nodoLista = ranking.inicio();
    while (nodoLista != nullptr) {
        arbolRanking.insertar(nodoLista->elem);
        nodoLista = nodoLista->sig;
    }

    vector<vector<string>> filasRanking;
    int pos = 1;
    arbolRanking.inorden([&pos, &filasRanking](Ranking r) {
        filasRanking.push_back({
            to_string(pos++),
            r.getNombre(),
            to_string(r.getMejorRacha()),
            r.clasificacion()
            });
        });

    Tabla::imprimir("RANKING DE RACHAS",
        { "#", "Usuario", "Racha", "Categoria" }, filasRanking);

    Banner::lineaCentrada("Altura del arbol: " + to_string(arbolRanking.altura())
        + " | Nodos: " + to_string(arbolRanking.tam()), "[38;2;55;55;55m");

    int oro = arbolRanking.contarSi([](Ranking r) { return r.clasificacion() == "Oro"; });
    Banner::lineaCentrada("Usuarios en categoria Oro (racha >= 10): " + to_string(oro), "[38;2;55;55;55m");

    Banner::lineaCentrada("Usuarios que alcanzaron nivel avanzado (3): "
        + to_string(contarUsuariosConNivel(3)), "[38;2;55;55;55m");
    Banner::lineaCentrada("Usuarios en nivel intermedio o mas (2): "
        + to_string(contarUsuariosConNivel(2)), "[38;2;55;55;55m");
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

    Banner::lineaCentrada("=== Usuarios ordenados por nombre (ascendente) ===", "\033[38;2;55;55;55m");
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        Banner::lineaCentrada(aux->elem.getNombre() + " - " + aux->elem.getEmail(), "\033[38;2;55;55;55m");
        aux = aux->sig;
    }
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

    Banner::lineaCentrada("=== Usuarios de nivel avanzado ===", "\033[38;2;55;55;55m");
    int contador = 0;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        if (esAvanzado(aux->elem)) {       // se usa la lambda
            Banner::lineaCentrada("- " + aux->elem.getNombre(), "\033[38;2;55;55;55m");
            contador++;
        }
        aux = aux->sig;
    }

    if (contador == 0)
        Banner::lineaCentrada("Ningun usuario ha alcanzado nivel avanzado todavia.", "\033[38;2;55;55;55m");
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

    Banner::lineaCentrada("=== Usuarios por nivel global (mayor a menor) ===", "\033[38;2;55;55;55m");
    for (unsigned int i = 0; i < copia.tam(); i++) {
        Usuario u = copia.obtener(i);
        Banner::lineaCentrada("- " + u.getNombre() + " (nivel global: " + to_string(u.nivelGlobal()) + ")", "\033[38;2;55;55;55m");
    }
}
// NUEVA: busca un usuario por nombre usando una tabla hash (HashMap).
// A diferencia de buscarUsuario (que recorre la lista nodo por nodo, O(n)),
// aqui se indexa cada usuario por su nombre y la busqueda es O(1) en promedio.
// ===============================================================
// ANALISIS BIG O
// Complejidad temporal: O(n)
//
// Explicacion:
// 1. Se recorre la lista de usuarios una sola vez para construir
//    un indice utilizando un HashMap, insertando cada usuario
//    segun su nombre como clave. Este recorrido tiene costo O(n).
//
// 2. Una vez construido el HashMap, la busqueda del usuario por
//    nombre tiene una complejidad promedio de O(1), ya que el
//    acceso a una tabla hash es constante en promedio.
//
// 3. Las operaciones de impresion de datos son constantes O(1).
//
// Por lo tanto, la complejidad total de la funcion esta dominada
// por el recorrido inicial de todos los usuarios:
//
//              O(n) + O(1) + O(1) = O(n)
//
// Estructura de datos utilizada:
// - ListaDoble<Usuario> para recorrer los usuarios.
// - HashMap<string, Usuario*> para realizar la busqueda eficiente.
// ===============================================================
void Sistema::buscarUsuarioHash() {
    Banner::lineaCentrada("--- Buscar usuario por nombre (Hash) ---", "\033[38;2;55;55;55m");

    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    // 1) Construyo el indice: clave = nombre, valor = puntero al Usuario.
    HashMap<string, Usuario*> indice;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        indice.insertar(aux->elem.getNombre(), &aux->elem);
        aux = aux->sig;
    }

    // 2) Pido el nombre a buscar.
    string nombreBuscado;
    Banner::promptCentrado("Ingrese el nombre del usuario: ");
    cin.ignore();
    getline(cin, nombreBuscado);

    // 3) Busqueda directa en la tabla hash.
    Usuario* encontrado = nullptr;
    if (indice.buscar(nombreBuscado, encontrado) && encontrado != nullptr) {
        Banner::lineaCentrada("Usuario encontrado:", "\033[38;2;46;125;50m");
        Banner::lineaCentrada("Nombre: " + encontrado->getNombre(), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Email: " + encontrado->getEmail(), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Puntaje total: " + to_string(encontrado->getPuntajeTotal()), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Nivel Ingles: " + to_string(encontrado->getNivelIngles()), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Nivel Portugues: " + to_string(encontrado->getNivelPortugues()), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Nivel Italiano: " + to_string(encontrado->getNivelItaliano()), "\033[38;2;55;55;55m");
        Banner::lineaCentrada("Nivel global: " + to_string(encontrado->nivelGlobal()), "\033[38;2;55;55;55m");
    }
    else {
        Banner::lineaCentrada("No se encontro ningun usuario con ese nombre.", "\033[38;2;200;40;40m");
    }
}

// MERGE SORT: ranking por XP 
bool compararPorXpDesc(Usuario a, Usuario b) {
    return a.obtenerProgreso()->getPuntosTotales() > b.obtenerProgreso()->getPuntosTotales();
}
// ===============================================================
// ANALISIS BIG O
// Complejidad temporal: O(n log n)
//
// Explicacion:
// 1. Primero se recorren todos los usuarios para copiarlos desde
//    la ListaDoble hacia un vector. Este recorrido tiene un costo
//    de O(n).
//
// 2. Luego el vector es ordenado mediante el algoritmo MergeSort,
//    cuya complejidad temporal es O(n log n), ya que divide el
//    conjunto de datos en mitades y posteriormente las fusiona
//    de manera ordenada.
//
// 3. Finalmente se recorre el vector ordenado para mostrar el
//    ranking de usuarios, lo cual requiere O(n).
//
// La complejidad dominante corresponde al algoritmo MergeSort:
//
//          O(n) + O(n log n) + O(n)
//                  = O(n log n)
//
// Estructuras de datos utilizadas:
// - ListaDoble<Usuario>
// - Vector<Usuario>
// - Algoritmo MergeSort
// =============================================================== 
void Sistema::rankingXpMergeSort() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }


    vector<Usuario> vec;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        vec.push_back(aux->elem);
        aux = aux->sig;
    }

    mergeSort(vec, compararPorXpDesc);


    Banner::lineaCentrada("=== Ranking XP (MergeSort - mayor a menor) ===", "\033[38;2;46;125;50m");
    for (int i = 0; i < (int)vec.size(); i++) {
        Banner::lineaCentrada(to_string(i + 1) + ". " + vec[i].getNombre() + "  |  XP: " + to_string(vec[i].obtenerProgreso()->getPuntosTotales()), "\033[38;2;55;55;55m");
    }
}

//QUICK SORT: ordenar usuarios por nombre alfabeticamente 

bool compararPorNombreAlfabetico(Usuario a, Usuario b) {
    return a.getNombre() < b.getNombre();
}

bool compararRachaHeap(Usuario a, Usuario b)
{
    return a.obtenerProgreso()->getRacha()->getMaxima() >
        b.obtenerProgreso()->getRacha()->getMaxima();
}
// ===============================================================
// ANALISIS BIG O
// Complejidad temporal:
// - Caso promedio: O(n log n)
// - Peor caso: O(n²)
//
// Explicacion:
// 1. Se copian los usuarios desde la ListaDoble hacia un vector,
//    lo que requiere un recorrido O(n).
//
// 2. El vector se ordena mediante QuickSort utilizando el nombre
//    del usuario como criterio de comparación. En promedio,
//    QuickSort trabaja en O(n log n); sin embargo, en el peor
//    caso puede alcanzar O(n²) dependiendo de la elección del
//    pivote.
//
// 3. Finalmente se imprime el ranking ordenado recorriendo el
//    vector una sola vez (O(n)).
//
// La complejidad dominante es:
//
//          O(n log n)
//
// Estructuras utilizadas:
// - ListaDoble<Usuario>
// - Vector<Usuario>
// - Algoritmo QuickSort
// ===============================================================
void Sistema::rankingNombreQuickSort() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    // 1. Volcar ListaDoble -> vector
    vector<Usuario> vec;
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {
        vec.push_back(aux->elem);
        aux = aux->sig;
    }

    // 2. Ordenar con QuickSort (plantilla del profe)
    quickSort(vec, compararPorNombreAlfabetico);

    // 3. Mostrar resultado
    Banner::lineaCentrada("=== Usuarios por nombre (QuickSort - A-Z) ===", "\033[38;2;46;125;50m");
    for (int i = 0; i < (int)vec.size(); i++) {
        Banner::lineaCentrada(to_string(i + 1) + ". " + vec[i].getNombre() + "  |  Nivel global: " + to_string(vec[i].nivelGlobal()), "\033[38;2;55;55;55m");
    }
}
//heap : 
// ===============================================================
// ANALISIS BIG O
// Complejidad temporal: O(n log n)
//
// Explicacion:
// 1. Se recorre la ListaDoble de usuarios para insertar cada uno
//    dentro de un Heap. Cada insercion requiere O(log n), por lo
//    que insertar los n usuarios tiene un costo total de
//    O(n log n).
//
// 2. Una vez construido el Heap, se extraen los tres usuarios con
//    mayor racha. Cada extraccion tiene una complejidad O(log n),
//    por lo que las tres extracciones requieren
//    3 * O(log n), equivalente a O(log n).
//
// 3. La complejidad total esta dominada por la construccion del
//    Heap, por lo que:
//
//          O(n log n) + O(log n)
//                  = O(n log n)
//
// Estructuras de datos utilizadas:
// - ListaDoble<Usuario> para recorrer los usuarios.
// - Heap (cola de prioridad) para mantener ordenados los usuarios
//   segun su mejor racha y obtener rapidamente los de mayor valor.
// ===============================================================
void Sistema::top3RachasHeap()
{
    if (usuarios.estaVacia())
    {
        Banner::lineaCentrada(
            "No hay usuarios registrados.",
            "\033[38;2;200;40;40m");
        return;
    }

    Heap<Usuario> heap(compararRachaHeap);

    auto* aux = usuarios.inicio();

    while (aux != nullptr)
    {
        heap.insertar(aux->elem);
        aux = aux->sig;
    }

    Banner::lineaCentrada( "===== TOP 3 USUARIOS CON MAYOR RACHA =====", "\033[38;2;46;125;50m");

    int puesto = 1;

    while (!heap.estaVacia() && puesto <= 3)
    {
        Usuario u = heap.extraer();

        Banner::lineaCentrada( to_string(puesto) + ". " + u.getNombre() +  "  |  Mejor racha: " + to_string( u.obtenerProgreso()->getRacha()->getMaxima() ), "\033[38;2;55;55;55m" );

        puesto++;
    }
}
// hito 2 esta guiado por ordenar - completra - traduccion avanzada 

void Sistema::verMallaAprendizaje() {
    int opcion = -1;
    do {
        Banner::lineaCentrada("===== MAPA DE APRENDISAJE =====", "\033[38;2;46;125;50m");
        Banner::lineaVacia();
        mallaLecciones.listarLecciones();
        Banner::lineaVacia();
        cout << "   1. Ver orden sugerido de aprendisaje \n";
        
        cout << "   2. Ver prerrequisitos de una leccion\n";
        cout << "   0. Volver al menu principal\n";
        cout << "   Opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            mallaLecciones.ordenSugerido();
            break;
        case 2: {
            int n;
            cout << "Ingrese la leccion: ";
            cin >> n;
            if (n >= 0 && n < mallaLecciones.cantidadNodos())
                mallaLecciones.prerrequisitosDe(n);
            else
                cout << "Leccion invalida.\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }
        if (opcion != 0)
            pausar();
    } while (opcion != 0);
}
