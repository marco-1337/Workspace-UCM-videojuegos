// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

/*
Esto comprueba en todo, no solo en las dos primeras mitades

bool comprobarDispersion(const vector<int>& datos, const int& dispersion, int ini, int fin, int& primero, int& medio, int& ultimo)
{
    int n = fin - ini;
    if (n == 1) 
    {
        primero = datos[ini];
        ultimo = datos[ini];
        medio  = datos[ini];
        return true;
    }

    int indexMedio = (ini + fin) / 2;

    int primeroIzquierda, medioIzquierda, ultimoIzquierda, 
        primeroDerecha, medioDerecha, ultimoDerecha;

    bool izquierda = comprobarDispersion(datos, dispersion, ini, indexMedio, primeroIzquierda, medioIzquierda, ultimoIzquierda);
    bool derecha = comprobarDispersion(datos, dispersion, indexMedio, fin, primeroDerecha, medioDerecha, ultimoDerecha);

    if (izquierda && derecha) 
    {
        bool a = abs(primeroIzquierda - primeroDerecha) >= dispersion; 
        bool b = abs(ultimoIzquierda - ultimoDerecha) >= dispersion;
        bool c = abs(medioIzquierda - medioDerecha) >= dispersion;
        bool d = abs(primeroIzquierda - ultimoDerecha) >= dispersion;
        if ( a && b && c && d) 
        {
            primero = primeroIzquierda;
            medio = datos[indexMedio];
            ultimo = ultimoDerecha;
            return true;
        }
    }
    return false;
}
*/

bool comprobarDispersion(const vector<int>& datos, const int& dispersion, int ini, int fin, int recursiones)
{
    int n = fin - ini;
    if (n == 0) 
    {

    }

    int indexMedio = (ini + fin) / 2;

    return false;
}

// función que resuelve el problema
bool resolver(const vector<int>& datos, int& dispersion) {
    int primero, medio, ultimo;
    return comprobarDispersion(datos, dispersion, 0, datos.size(), primero, medio,ultimo);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int casos, dispersion;

    cin >> casos >> dispersion;

    vector<int> datos(casos);

    for (int& c : datos)
    {
        cin >> c;
    }

    if (! std::cin)
        return false;
    
    // escribir sol
    cout << ((resolver(datos, dispersion)) ? "SI" : "NO" ) << "\n";
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}