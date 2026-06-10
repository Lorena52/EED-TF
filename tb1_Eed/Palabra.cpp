#include "pch.h"
#include "Palabra.h"

using namespace std;

// ---------------------------------------------------------------------
//  Constructores
// ---------------------------------------------------------------------

// Constructor por defecto: palabra vacia de nivel basico.
Palabra::Palabra()
    : termino(""), traduccion(""), categoria("general"),
    nivel(1), vecesRepasada(0) {
}

// Constructor de 3 argumentos.
// BUGFIX: antes 'categoria' quedaba SIN inicializar, por eso el
// diccionario mostraba "(  )" vacio. Ahora recibe un valor por defecto.
Palabra::Palabra(string termino, string traduccion, int nivel)
    : termino(termino), traduccion(traduccion), categoria("general"),
    nivel(nivel), vecesRepasada(0) {
}

// Constructor completo: permite indicar la categoria explicitamente.
Palabra::Palabra(string termino, string traduccion, string categoria, int nivel)
    : termino(termino), traduccion(traduccion), categoria(categoria),
    nivel(nivel), vecesRepasada(0) {
}

// ---------------------------------------------------------------------
//  Getters
// ---------------------------------------------------------------------
string Palabra::getTermino()    const { return termino; }
string Palabra::getTraduccion() const { return traduccion; }
string Palabra::getCategoria()  const { return categoria; }
int    Palabra::getNivel()      const { return nivel; }
int    Palabra::getVeces()      const { return vecesRepasada; }

// ---------------------------------------------------------------------
//  Setters
// ---------------------------------------------------------------------
void Palabra::setCategoria(string categoria) { this->categoria = categoria; }

// ---------------------------------------------------------------------
//  Logica propia
// ---------------------------------------------------------------------
void Palabra::incrementarRepaso() { vecesRepasada++; }

// Se considera "dificil" si todavia no se ha repasado al menos 3 veces.
bool Palabra::esDificil() const { return vecesRepasada < 3; }

// ---------------------------------------------------------------------
//  Presentacion
// ---------------------------------------------------------------------
void Palabra::mostrar() const {
    cout << "  [ " << termino << " ]  -->  " << traduccion
        << "  (" << categoria << ")\n";
}