// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

using namespace std;

// función que resuelve el problema
// O(n) siendo n el numero de nodos del arbol
bool resolver(bintree<char> leftTree, bintree<char> rightTree) {
    if (leftTree.empty() && rightTree.empty())
        return true;

    if (!leftTree.empty() && !rightTree.empty())
    {
        return resolver(leftTree.left(), rightTree.right()) && 
            resolver(leftTree.right(), rightTree.left());
    }
    else return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');

    bool sol = resolver(tree.left(), tree.right());
    // escribir sol
    
    cout << ((sol) ? "SI" : "NO") << "\n";
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