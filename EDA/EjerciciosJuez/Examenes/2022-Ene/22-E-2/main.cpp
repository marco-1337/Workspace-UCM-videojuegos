// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

using namespace std;

// O(n) siendo n el numero de nodos en el arbol
// Espacial: O(1)
int resolver(bintree<int> tree, int nTop, int& singulares) {
    if (tree.empty())
        return 0;
    
    int izq = resolver(tree.left(), nTop + tree.root(), singulares);
    int der = resolver(tree.right(), nTop + tree.root(), singulares);

    if (nTop == izq + der)
        ++ singulares;

    return izq + der + tree.root();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> arbol;
    arbol = leerArbol(-1);
    
    int singulares = 0;

    resolver(arbol, 0, singulares);
    // escribir sol
    
    cout << singulares << "\n";
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