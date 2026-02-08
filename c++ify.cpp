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
    bool favorito;
    Cancion *sig;
    Cancion *ant;
};

// ======================================================
// BLOQUE A: ESTRUCTURAS DE DATOS (PROGRAMADOR A)
// No tocar si eres el Programador B
// ======================================================

void agregarCancion(Cancion* &p, Cancion* &f, string t, string a, string al) {
  Cancion* nuevo = new Cancion;
    nuevo->titulo = t;
    nuevo->artista = a;
    nuevo->archivoLetra = al;

    if (p == NULL) {
        p = f = nuevo;
        nuevo->sig = nuevo;  
        nuevo->ant = nuevo;
    } 
    else {
        
        nuevo->sig = p;      
        nuevo->ant = f;      
        f->sig = nuevo;      
        p->ant = nuevo;      
        f = nuevo;           
    }
}

void eliminarCancion(Cancion* &p, Cancion* &f, string titulo) {
    if (p == NULL) {
        cout << "La lista está vacía.\n";
        return;
    }

    Cancion* aux = p;

    do {
        if (aux->titulo == titulo) {

            
            if (p == f) {
                delete aux;
                p = f = NULL;
            }
            
            else if (aux == p) {
                p = p->sig;
                p->ant = f;
                f->sig = p;
                delete aux;
            }
           
            else if (aux == f) {
                f = f->ant;
                f->sig = p;
                p->ant = f;
                delete aux;
            }
            
            else {
                aux->ant->sig = aux->sig;
                aux->sig->ant = aux->ant;
                delete aux;
            }

            cout << "Canción eliminada correctamente.\n";
            return;
        }

        aux = aux->sig;

    } while (aux != p);

    cout << "Canción no encontrada.\n";
}

void buscarXArtista(Cancion* p, string artista) {
   if (p == NULL) {
        cout << "No hay canciones registradas.\n";
        return;
    }

    Cancion* aux = p;
    bool encontrado = false;

    do {
        if (aux->artista == artista) {
            cout << "Título: " << aux->titulo << endl;
            cout << "Artista: " << aux->artista << endl;
            cout << "Archivo de letra: " << aux->archivoLetra << endl;
            cout << "-----------------------------\n";
            encontrado = true;
        }
        aux = aux->sig;
    } while (aux != p);

    if (!encontrado) {
        cout << "No se encontraron canciones de ese artista.\n";
    }
}
void agregarAFavoritos(Cancion* p, string titulo) {
    if (p == NULL) {
        cout << "No hay canciones registradas.\n";
        return;
    }

    Cancion* aux = p;

    do {
        if (aux->titulo == titulo) {
            aux->favorito = true;
            cout << "La canción '" << titulo << "' fue agregada a favoritos.\n";
            return;
        }
        aux = aux->sig;
    } while (aux != p);

    cout << "Canción no encontrada.\n";
}
void mostrarFavoritos(Cancion* p) {
    if (p == NULL) {
        cout << "No hay canciones.\n";
        return;
    }

    Cancion* aux = p;
    bool hayFavoritos = false;

    do {
        if (aux->favorito) {
            cout << "🎵 " << aux->titulo 
                 << " - " << aux->artista << endl;
            hayFavoritos = true;
        }
        aux = aux->sig;
    } while (aux != p);

    if (!hayFavoritos) {
        cout << "No hay canciones favoritas.\n";
    }
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
    int opcion;
    string titulo, artista, archivo;

    do {
        cout << "\n===== MENU DE CANCIONES =====\n";
        cout << "1. Agregar cancion\n";
        cout << "2. Eliminar cancion\n";
        cout << "3. Buscar canciones por artista\n";
        cout << "4. Agregar cancion a favoritos\n";
        cout << "5. Mostrar favoritos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {

        case 1:
            cout << "Titulo: ";
            getline(cin, titulo);
            cout << "Artista: ";
            getline(cin, artista);
            cout << "Archivo de la letra: ";
            getline(cin, archivo);

            agregarCancion(p, f, titulo, artista, archivo);
            cout << "Cancion agregada correctamente.\n";
            break;

        case 2:
            cout << "Titulo de la cancion a eliminar: ";
            getline(cin, titulo);
            eliminarCancion(p, f, titulo);
            break;

        case 3:
            cout << "Nombre del artista: ";
            getline(cin, artista);
            buscarXArtista(p, artista);
            break;

        case 4:
            cout << "Titulo de la cancion a agregar a favoritos: ";
            getline(cin, titulo);
            agregarAFavoritos(p, titulo);
            break;

        case 5:
            cout << "\n=== CANCIONES FAVORITAS ===\n";
            mostrarFavoritos(p);
            break;

        case 0:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
    
    return 0;
}
