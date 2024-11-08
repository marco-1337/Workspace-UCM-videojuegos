// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
T getMax(T uno, T otro)
{
    if(uno >= otro)
        return uno;
    else
        return otro;
}


// n nodos, hojas, altura, en ese orden
template <class T>
tuple<int, int, int> treeData(bintree<T> const& tree){

    if (tree.empty())
    {
        return {0, 0, 0};
    }

    tuple <int, int, int> izq = treeData(tree.left());
    tuple <int, int, int> der = treeData(tree.right());

    return 
    {
        get<0>(izq) + get<0>(der) + 1, 
        ((get<1>(izq)+get<1>(der) > 0) ? get<1>(izq)+get<1>(der) : get<1>(izq) + get<1>(der) + 1),
        ((get<2>(izq)+get<2>(der) > 0) ? getMax(get<2>(izq), get<2>(der)) + 1 : 1)
    };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    bintree<char> tree;
    tree = leerArbol('.');

    tuple<int, int, int> datos = treeData(tree);

    cout << get<0>(datos) << " " << get<1>(datos) << " " << get<2>(datos) << endl;
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
