// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>

#include "bintree_eda.h"

using namespace std;

// función que resuelve el problema
int resolver(bintree<int> tree, int& nDrags) {
    if (tree.empty())
    {
        return -1;
    }
    else if (tree.left().empty() && tree.right().empty())
    {
        return tree.root();
    }

    int izq, der, dragsIzq = 0, dragsDer = 0;

    izq = resolver(tree.left(), dragsIzq);
    der = resolver(tree.right(), dragsDer);

    bool dragon = (tree.root() == 1) ? true : false;

    nDrags += dragon;

    if (izq == -1)
    {
        nDrags += dragsDer;
        return der;
    }
    else if (der == -1)
    {
        nDrags += dragsIzq;
        return izq;
    }
    else
    {
        bool comp = dragsDer < dragsIzq;
        nDrags += (comp) ? dragsDer : dragsIzq;
        return (comp) ? der : izq;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    
    int nDrags;

    int sol = resolver(tree, nDrags);
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