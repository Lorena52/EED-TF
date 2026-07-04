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
    pantallaBienvenida();
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
        Diseño::Pinguino();
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

   
    ArbolBinario<Ranking> arbolRanking(compararRacha);     // (1) O(1)
    auto* nodoLista = ranking.inicio();
    while (nodoLista != nullptr) {                         // (2) O(n log n) prom. / O(n²) peor caso
        arbolRanking.insertar(nodoLista->elem);            // cada insertar: O(log n) prom. / O(n) peor caso
        nodoLista = nodoLista->sig;
    }

    vector<vector<string>> filasRanking;
    int pos = 1;
    arbolRanking.inorden([&pos, &filasRanking](Ranking r) {       // (3) O(n)
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
        + " | Nodos: " + to_string(arbolRanking.tam()), "[38;2;55;55;55m");  //// (4) O(n) cada una (si recorren el árbol)

    int oro = arbolRanking.contarSi([](Ranking r) { return r.clasificacion() == "Oro"; });    // (5) O(n)
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

void Sistema::buscarUsuarioHash() {
    Banner::lineaCentrada("--- Buscar usuario por nombre (Hash) ---", "\033[38;2;55;55;55m");

    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

   
    HashMap<string, Usuario*> indice;                                                 // (1) O(1)
    auto* aux = usuarios.inicio();                                                    // (2) O(1)  
    while (aux != nullptr) {                                                          // (3) O(n)
        indice.insertar(aux->elem.getNombre(), &aux->elem);                           // (4) O(1) promedio
        aux = aux->sig;                                                               // (5) O(1)
    }


    string nombreBuscado;
    Banner::promptCentrado("Ingrese el nombre del usuario: ");
    cin.ignore();
    getline(cin, nombreBuscado);                                                      // (6) O(1)

    Usuario* encontrado = nullptr;
    if (indice.buscar(nombreBuscado, encontrado) && encontrado != nullptr) {         // (7) O(1) promedio
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


bool compararPorXpDesc(Usuario a, Usuario b) {
    return a.obtenerProgreso()->getPuntosTotales() > b.obtenerProgreso()->getPuntosTotales();
}

void Sistema::rankingXpMergeSort() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }


    vector<Usuario> vec;                                                     // (1) O(1)
    auto* aux = usuarios.inicio();
    while (aux != nullptr) {                                                 // (2) O(n)
        vec.push_back(aux->elem);
        aux = aux->sig;
    }

    mergeSort(vec, compararPorXpDesc);                                      // (3) O(n log n)


    Banner::lineaCentrada("=== Ranking XP (MergeSort - mayor a menor) ===", "\033[38;2;46;125;50m");
    for (int i = 0; i < (int)vec.size(); i++) {                              // (4) O(n)
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
void Sistema::rankingNombreQuickSort() {
    if (usuarios.estaVacia()) {
        Banner::lineaCentrada("No hay usuarios registrados.", "\033[38;2;200;40;40m");
        return;
    }

    vector<Usuario> vec;                                         // (1) O(1)
    auto* aux = usuarios.inicio();                               // (2) O(n)
    while (aux != nullptr) {
        vec.push_back(aux->elem);
        aux = aux->sig;
    }
    quickSort(vec, compararPorNombreAlfabetico);                 // (3) O(n log n) prom. / O(n²) peor caso
    Banner::lineaCentrada("=== Usuarios por nombre (QuickSort - A-Z) ===", "\033[38;2;46;125;50m");
    for (int i = 0; i < (int)vec.size(); i++) {                 // (4) O(n)
        Banner::lineaCentrada(to_string(i + 1) + ". " + vec[i].getNombre() + "  |  Nivel global: " + to_string(vec[i].nivelGlobal()), "\033[38;2;55;55;55m");
    }
}
void Sistema::top3RachasHeap()
{
    if (usuarios.estaVacia())
    {
        Banner::lineaCentrada(
            "No hay usuarios registrados.",
            "\033[38;2;200;40;40m");
        return;
    }

    Heap<Usuario> heap(compararRachaHeap);                          // (1) O(1)

    auto* aux = usuarios.inicio();

    while (aux != nullptr)                                         // (2) O(n log n)
    {
        heap.insertar(aux->elem);
        aux = aux->sig;
    }

    Banner::lineaCentrada( "===== TOP 3 USUARIOS CON MAYOR RACHA =====", "\033[38;2;46;125;50m");

    int puesto = 1;

    while (!heap.estaVacia() && puesto <= 3)                        // (3) O(log n)
    {
        Usuario u = heap.extraer();                                //     3 extracciones, cada una O(log n)

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

//interfaz
void Sistema::pantallaBienvenida() {

    system("cls");
    cout << "\n\n";
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    Diseño::Logo();

    


   
    Banner::lineaVacia();
    Banner::lineaCentrada("Bienvenido a AprendeGo!", "\033[38;2;46;125;50m");
    Banner::lineaCentrada("Cargando...", "\033[38;2;46;125;50m");

  

    cout << "                                  [";

    for (int i = 0; i < 20; i++) {
        cout << "\033[42m  \033[0m";   
        _sleep(120);
    }

    cout << "]";

    _sleep(500);
    system("cls");
}