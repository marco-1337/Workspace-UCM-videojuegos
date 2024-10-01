// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad O(log n) siendo n la cantidad de datos (tamaño de vector v)
bool elemento_situado ( const vector<int>& v , int ini , int fin )
{
    int n = fin - ini;
    if (n == 0)
        return false;
    if(n == 1)
    {
        if(v[ini] == ini)
            return true;
        return false;
    }

    int medio = (ini + fin) / 2;

    bool sol = false;

    if(v[medio] == medio)
    {
        sol = true;
    }
    else if (v[medio] > medio)
    {
        sol = elemento_situado(v, ini, medio);
    }
    else 
    {
        sol = elemento_situado(v, medio, fin);
    }

    return sol;
}

// función que resuelve el problema
bool resolver(const vector<int>& v, int ini, int fin) {
    return elemento_situado(v, ini, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (resolver(sec,0,n) ? "SI" : "NO") << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
