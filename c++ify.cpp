//pvto el que lo lea 

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cancion {
    string titulo;
    string artista;
    string archivoLetra;
    Cancion *sig;
    Cancion *ant;
};

// ======================================================
// BLOQUE A: ESTRUCTURAS DE DATOS (PROGRAMADOR A)
// No tocar si eres el Programador B
// ======================================================

void agregarCancion(Cancion* &p, Cancion* &f, string t, string a, string al) {
    // ... tu codigo aqui ...
}

void eliminarCancion(Cancion* &p, Cancion* &f, string titulo) {
    // TAREA A: Cuidado con la circularidad aqui.
    // Si p == f y borras, p y f deben ser NULL.
}

void buscarXArtista(Cancion* p, string artista) {
    // TAREA A: Recorre con un do-while hasta volver a p.
}

// ======================================================
// BLOQUE B: INTERFAZ Y ARCHIVOS (PROGRAMADOR B)
// No tocar si eres el Programador A
// ======================================================

void sistemaLogin() {
    // TAREA B: 3 intentos de login aqui.
}

void mostrarLetra(string archivo) {
    // TAREA B: ifstream para leer el .txt
}

void menuSpotify(Cancion* &p, Cancion* &f) {
    // TAREA B: El switch case con las opciones del pizarron.
}

// ======================================================
// UNIÓN DE CÓDIGO (EL PUNTO DE ENCUENTRO)
// ======================================================
int main() {
    Cancion *p = NULL, *f = NULL;
    // Aqui solo llaman a las funciones de arriba
    return 0;
}
