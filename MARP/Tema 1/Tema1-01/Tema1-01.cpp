/*@ <authors>
 *
 * Marco González Campo, MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
//#include <...>

using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename T>
bool recursiveAVLCheck(const BinTree<T>& tree, int& height, T& min, T& max){

	// Parámetros de salida en la recursión
    int leftHeight, rightHeight;
    T minVal, maxVal;

	// Se comprueba previamente que los hijos no sean vacíos, esto se hace para no tener que lidiar con min y max
	// en el caso base de arbol vacío

	// Recursión hijo izquierdo
    if (tree.left().empty()) {

		leftHeight = 0;
		min = tree.root();

	} else {

		if (!(recursiveAVLCheck(tree.left(), leftHeight, minVal, maxVal) && maxVal < tree.root()))
			return false; // salida preventiva, no tiene seguido continuar
		min = minVal;
	}

	// Recursión hijo derecho
	if (tree.right().empty()) {

		rightHeight = 0;
		max = tree.root();

	} else {

		if (!(recursiveAVLCheck(tree.right(), rightHeight, minVal, maxVal) && minVal > tree.root()))
			return false; // salida preventiva, no tiene seguido continuar
		max = maxVal;
	}

	height = std::max(leftHeight, rightHeight) + 1;

	// Los 2 returns de las recursiones aseguran 
	return (abs(leftHeight - rightHeight) <= 1);
}

// funcion carcasa 
template <typename T>
bool esAVL() {
    BinTree<T> tree;
    tree = read_tree<T>(cin);

	// Externalizado caso vacío para no comprobar en cada vuelta
	if (tree.empty()) return true;

    int n;
	T disposable = tree.root();

    return recursiveAVLCheck<T>(tree, n, disposable, disposable);
}

bool resuelveCaso() {
	// leer los datos de la entrada

	char tipo;
	cin >> tipo;

	if (!cin)  // fin de la entrada
		return false;

    // resolver el caso posiblemente llamando a otras funciones
    bool res = (tipo == 'N') ? esAVL<int>() : esAVL<string>();

	// escribir la solución
    cout << (res ? "SI" : "NO") << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
