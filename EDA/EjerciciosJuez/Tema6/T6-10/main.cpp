// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include "bintree_eda.h"

using namespace std;

// O(n) siendo n el numero de nodos en el arbol
pair<string, int> enanos(bintree<string> const& tree){
    if (tree.empty())
    {
        return {"", 0};
    }
    else if (tree.left().empty() && tree.right().empty())
    {
        return {tree.root(), 1};
    }

    pair<string, int> izq = enanos(tree.left());
    pair<string, int> der = enanos(tree.right());

    string lider;
    int enanos;

    if (izq.second > der.second) 
    {
        lider = izq.first;
    }
    else if (izq.second < der.second)
    {
        lider = der.first;
    }
    else
    {
        lider = min(izq.first, der.first);
    }

    enanos = izq.second + der.second;

    if (tree.root() == "Orcos")
    {
        enanos /= 2;
    }

    return {lider, enanos};
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    bintree<string> tree;
    string elemVacio = ".";
    tree = leerArbol(elemVacio);
    pair<string, int> sol = enanos(tree);

    if (sol.second > 0)
        cout << sol.first << " " << sol.second;
    else
        cout << "Ninguno";
    cout << "\n";
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
