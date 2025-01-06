// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

using namespace std;

// función que resuelve el problema
bool resolver(bintree<int> tree, int& min, int& max) {
    if (tree.empty())
    {
        return true;
    }
    else
    {
        int minIzq = tree.root(), minDer = tree.root() + 1, maxIzq = tree.root() - 1, maxDer = tree.root();

        bool izq = resolver(tree.left(), minIzq, maxIzq);
        bool der = resolver(tree.right(), minDer, maxDer);

        min = minIzq;
        max = maxDer;

        return izq && der && maxIzq < tree.root() && minDer > tree.root();
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    
    int aux = 0;

    bool sol = resolver(tree, aux, aux);

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