// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

// O(n) siendo n el numero de nodos en el arbol
void calcularAfluente(const bintree<int> tree, int& tramosNavegables, int& afluencia)
{
    //caso base
    if (tree.empty())
        afluencia = -1;
    else
    {
        int afluenciaIzq, afluenciaDer;

        calcularAfluente(tree.left(), tramosNavegables, afluenciaIzq);
        calcularAfluente(tree.right(), tramosNavegables, afluenciaDer);

        if (afluenciaIzq == -1 && afluenciaDer == -1)
            afluencia = 1;
        else if (afluenciaIzq == -1)
            afluencia = afluenciaDer - tree.root();
        else if (afluenciaDer == -1)
            afluencia = afluenciaIzq - tree.root();
        else
            afluencia = (afluenciaIzq + afluenciaDer) - tree.root();

        if (afluenciaIzq > 2)
            tramosNavegables++;
        if (afluenciaDer > 2)
            tramosNavegables++;

        if (afluencia < 0)
            afluencia = 0;
    }
}

int calcularAfluente(const bintree<int> tree)
{
    int trash;
    int n = 0;

    calcularAfluente(tree, n, trash);

    return n;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso(){
	bintree<int> arb;
	arb = leerArbol(-1); // -1 es la repr. de arbol vacio
	
    int sol = calcularAfluente(arb);

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
    //system("PAUSE");
#endif

    return 0;
}

