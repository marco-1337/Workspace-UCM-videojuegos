// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
// O(log n) siendo n el numero de elementos de sec
int resolver(const vector<int>& sec, int ini, int fin) {
    int n = fin - ini;
    if(n==1)
    {
        return ini;    
    }

    int mitad = (ini + fin) / 2;

    if (mitad % 2 != 0) 
    {
        if(sec[mitad-1] == sec[mitad])
        {
            return resolver(sec, mitad + 1, fin);
        }
        else
        {
            return resolver(sec, ini, mitad);
        }
    }
    else
    {
        if(sec[mitad] == sec[mitad+1])
        {
            return resolver(sec, mitad + 2, fin);
        }
        else
        {
            return resolver(sec, ini, mitad + 1);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;
    
    // Llamada a la función resolver
    int sol = resolver(v, 0, v.size());

    // Mostrar el resultado
    cout << sol << "\n";
}


//#define DOMJUDGE
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