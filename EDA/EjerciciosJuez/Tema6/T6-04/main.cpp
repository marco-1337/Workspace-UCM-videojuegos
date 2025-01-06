// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

using namespace std;

bool esPrimo(int n)
{
    int half = n/2;

    if (n == 0 || n == 1)
        return false;

    for (int i = 2; i <= half; ++i) 
    {
        if (n % i == 0) 
            return false;
    }

    return true;
}

// función que resuelve el problema
pair<int, int> resolver(bintree<int> tree, int p, int& bestP) {
    if (tree.empty() || esPrimo(tree.root()))
    {
        return {-1, -1};
    }
    else
    {
        if (tree.root() % 7 == 0)
        {
            bestP = p;
            return {tree.root(), p};
        }
        else if (bestP == -1 || p+1 < bestP)
        {
            pair<int, int> leftResult, rightResult;

            leftResult = resolver(tree.left(), p+1, bestP);
            rightResult = resolver(tree.right(), p+1, bestP);

            if (leftResult.first == -1 && rightResult.first == -1)
            {
                return {-1, -1};
            }
            else if (leftResult.first == -1)
            {
                return rightResult;
            }
            else if (rightResult.first == -1)
            {
                return leftResult;
            }
            else
            {
                if (leftResult.second > rightResult.second)
                    return rightResult;
                else
                    return leftResult;
            }
        }
        else
        {
            return {-1, -1};
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    
    int bestP = -1;
    
    pair<int, int> sol = resolver(tree, 1, bestP);

    // escribir sol
    
    if (sol.first == -1)
        cout << "NO HAY";
    else
        cout << sol.first << " " << sol.second;

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
     system("PAUSE");
     #endif
    
    return 0;
}