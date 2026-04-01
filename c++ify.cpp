#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

struct Cancion {
    string titulo;
    string artist;
    string archivoLetra;
    string archivoMusica;
    bool favorito;
    Cancion *sig;
    Cancion *ant;
};

// ======================================================
// BLOQUE A: ESTRUCTURA CIRCULAR
// ======================================================

void agregarCancion(Cancion* &p, Cancion* &f, string t, string a, string al, string am) {
    Cancion* nuevo = new Cancion;
    nuevo->titulo = t;
    nuevo->artist = a;
    nuevo->archivoLetra = al;
    nuevo->archivoMusica = am;
    nuevo->favorito = false;
    
    if (p == NULL) {
        p = f = nuevo;
        nuevo->sig = nuevo->ant = nuevo;
    } else {
        nuevo->sig = p;
        nuevo->ant = f;
        f->sig = nuevo;
        p->ant = nuevo;
        f = nuevo;
    }
}

void eliminarActual(Cancion* &actual, Cancion* &p, Cancion* &f) {
    if (!actual) return;
    Cancion* eliminar = actual;
    
    if (actual->sig == actual) { // Solo queda una canción en la lista
        p = f = actual = NULL;
    } else {
        actual->ant->sig = actual->sig;
        actual->sig->ant = actual->ant;
        if (actual == p) p = actual->sig;
        if (actual == f) f = actual->ant;
        actual = actual->sig; // Mover al siguiente tras borrar
    }
    delete eliminar; 
    PlaySound(NULL, 0, 0); 
    cout << "\n[!] Cancion eliminada de tu biblioteca.\n";
}

void irAPosicion(Cancion* &actual, Cancion* p, int posicion) {
    if (!p) return;
    Cancion* aux = p;
    int cont = 1;
    
    do {
        if (cont == posicion) {
            actual = aux;
            return;
        }
        aux = aux->sig;
        cont++;
    } while (aux != p);
    
    cout << "\n[!] Posicion fuera de rango.\n";
}

// ======================================================
// BLOQUE B: LÓGICA DE INTERFAZ E I/O
// ======================================================

bool login() {
    string u, pas;
    for(int i = 1; i <= 3; i++) {
        cout << "\n[C++IFY LOGIN - Intento " << i << "/3]\nUser: "; cin >> u;
        cout << "Pass: "; cin >> pas;
        if(u == "admin" && pas == "1234") return true;
        cout << "Acceso denegado. Intentalo de nuevo.\n";
    }
    return false;
}

void mostrarLetra(string archivo) {
    ifstream f(archivo.c_str()); 
    string l;
    if(f.is_open()){
        cout << "\n--- LYRICS (LETRA) ---\n";
        while(getline(f, l)) cout << l << endl;
        f.close();
    } else cout << "[!] No se encontro el archivo .txt de la letra.\n";
}

void reproducir(Cancion* actual) {
    if(!actual) {
        cout << "\n[!] La biblioteca esta vacia.\n";
        return;
    }
    PlaySound(NULL, 0, 0); // Detener audio anterior
    cout << "\n>>> REPRODUCIENDO: " << actual->titulo << " - " << actual->artist << " <<<\n";
    mostrarLetra(actual->archivoLetra); 
    PlaySound(actual->archivoMusica.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

// ======================================================
// MAIN
// ======================================================

int main() {
    srand(time(NULL));
    if(!login()) {
        cout << "\nSistema bloqueado. Adios.\n";
        return 0;
    }

    Cancion *p = NULL, *f = NULL;
    
    // CARGA DE DATOS 
    agregarCancion(p, f, "Tetoris", "Hiragi", "Letra1.txt", "Cancion1.wav");
    agregarCancion(p, f, "Step Back", "GOT the beat", "Letra2.txt", "Cancion2.wav");
    agregarCancion(p, f, "Check", "bbno$", "Letra3.txt", "Cancion3.wav");
    agregarCancion(p, f, "Take Me to the Beach", "Imagine Dragons", "Letra4.txt", "Cancion4.wav");
    agregarCancion(p, f, "Ilegal", "La Santa Grifa", "Letra5.txt", "Cancion5.wav");
    agregarCancion(p, f, "IA Podcast", "AI Voices", "Letra6.txt", "Cancion6.wav");

    Cancion* actual = p;
    int op;

    do {
        cout << "\n======= MENU C++IFY =======";
        cout << "\nCancion actual: " << (actual ? actual->titulo : "Ninguna");
        cout << "\n1. Play/Lyrics | 2. Pausa | 3. Siguiente | 4. Anterior";
        cout << "\n5. ELIMINAR    | 6. Like  | 7. Favoritos | 8. Shuffle | 9. Ir a N | 0. Salir";
        cout << "\nOpcion: ";
        cin >> op;

        switch(op) {
            case 1: reproducir(actual); break;
            case 2: PlaySound(NULL, 0, 0); cout << "\n[PAUSA]\n"; break;
            case 3: if(actual) { actual = actual->sig; reproducir(actual); } break;
            case 4: if(actual) { actual = actual->ant; reproducir(actual); } break;
            case 5: eliminarActual(actual, p, f); if(actual) reproducir(actual); break;
            case 6: if(actual) { actual->favorito = true; cout << "\nAgregada a 'Me gusta'.\n"; } break;
            case 7: {
                Cancion* aux = p; bool hay = false;
                cout << "\n--- TUS LIBRERIAS: ME GUSTA ---\n";
                if(p) { 
                    do { 
                        if(aux->favorito) { cout << "[?] " << aux->titulo << " - " << aux->artist << endl; hay = true; } 
                        aux = aux->sig; 
                    } while(aux != p); 
                }
                if(!hay) cout << "No tienes canciones marcadas como favoritas.\n"; 
                break;
            }
            case 8: // Reproducción Aleatoria (Shuffle)
                if(actual) {
                    int saltos = rand() % 6 + 1;
                    for(int i = 0; i < saltos; i++) actual = actual->sig;
                    reproducir(actual);
                }
                break;
            case 9: {
                int pos;
                cout << "\nIngresa el numero de la cancion: ";
                cin >> pos;
                Cancion* temp = actual;
                irAPosicion(actual, p, pos);
                if (actual != temp || pos == 1) reproducir(actual);
                break;
            }
        }
    } while(op != 0);

    PlaySound(NULL, 0, 0); // Detener todo al salir
    return 0;
}
