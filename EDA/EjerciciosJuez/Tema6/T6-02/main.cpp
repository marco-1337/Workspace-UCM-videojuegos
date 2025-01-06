// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>

#include "bintree_eda.h"

#include <vector>

using namespace std;


template <class T>
class bintree_plus : public bintree<T>
{
    using TreeNode = typename bintree<T>::TreeNode;
    using Link = std::shared_ptr<TreeNode>;
public:
    bintree_plus<T>(const bintree<T>& other): bintree<T>(other){}

    vector<T> calcularFrontera() const
    {
        vector<T> salida;
        if (this->raiz != nullptr)
            calcularFronteraInterno(salida, this->raiz);

        return salida;

    }
private:
    void calcularFronteraInterno(vector<T>& sol, Link node) const
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            sol.push_back(node->elem);
        }
        else
        {
            if (node->left != nullptr)
            {
                calcularFronteraInterno(sol, node->left);
            }
            if (node->right != nullptr)
            {
                calcularFronteraInterno(sol, node->right);
            }
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree_plus<int> tree(leerArbol(-1));

    vector<int> sol = tree.calcularFrontera();

    for (int e : sol)
    {
        cout << e << " ";
    }
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
