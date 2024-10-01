// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// complejidad de O(n) siendo n el tamaño del vector datos
bool comprobarDispersion(const vector<int>& datos, const int& dispersion, int ini, int fin)
{
    int n = fin - ini;
    if (n <= 1) 
    {
        return true;
    }

    int medio = (ini + fin) / 2;

    bool izquierda = comprobarDispersion(datos, dispersion, ini, medio);
    bool derecha = comprobarDispersion(datos, dispersion, medio, fin);

    return (izquierda && derecha && abs(datos[ini] - datos[fin-1]) >= dispersion);
}

// función que resuelve el problema
bool resolver(const vector<int>& datos, int& dispersion) {
    int primero, medio, ultimo;
    return comprobarDispersion(datos, dispersion, 0, datos.size());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int casos, dispersion;

    cin >> casos;

    if (! std::cin)
        return false;
    
    cin >> dispersion;

    vector<int> datos(casos);

    for (int& c : datos)
    {
        cin >> c;
    }
    
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