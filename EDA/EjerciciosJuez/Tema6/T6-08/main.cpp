// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

using namespace std;

// función que resuelve el problema
int resolver(bintree<char> tree, int& weight) {
    if (tree.empty())
    {
        return 0;
    }
    else if (tree.left().empty() && tree.right().empty())
    {
        ++weight;
        return 1;
    }
    else
    {
        int weightIzq = 0, weightDer = 0;

        int izq = resolver(tree.left(), weightIzq);
        int der = resolver(tree.right(), weightDer);

        weight = max(weightIzq, weightDer) + 1;

        int sol = max(izq, der);

        return max(sol, weightIzq + weightDer +1);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');
    
    int aux = 0;

    int sol = resolver(tree, aux);

    // escribir sol
    
    cout << sol << "\n";
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
     system("PAUSE");
     #endif
    
    return 0;
}