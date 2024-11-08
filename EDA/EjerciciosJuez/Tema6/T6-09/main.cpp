// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"

using namespace std;

// O(n) siendo n el numero de nodos en el arbol
int rescateExcursionistas(const bintree<int> tree, int& nEquiposRescate, bool& indicadorRescate)
{
    //caso base
    if (tree.empty())
    {
        indicadorRescate = false;
        return 0;
    }

    bool indicadorIzq, indicadorDer;

    int izq = rescateExcursionistas(tree.left(), nEquiposRescate, indicadorIzq);
    int der = rescateExcursionistas(tree.right(), nEquiposRescate, indicadorDer);

    indicadorRescate = indicadorIzq || indicadorDer;

    if (!indicadorRescate && tree.root() > 0)
    {
        nEquiposRescate++;
        indicadorRescate = true;
    }
    
    return (tree.root() + max(izq, der));
}

pair<int, int> rescateExcursionistas(const bintree<int> tree)
{
    int i;
    bool b;
    int n = 0;

    int camino = rescateExcursionistas(tree, n, b);

    return {n, camino};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso(){
	bintree<int> arb;
	arb = leerArbol(-1); // -1 es la repr. de arbol vacio
	
    pair <int, int> sol = rescateExcursionistas(arb);

    cout << sol.first << " " << sol.second << "\n";
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

