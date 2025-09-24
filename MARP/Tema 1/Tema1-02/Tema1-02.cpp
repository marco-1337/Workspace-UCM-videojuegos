
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada

	int n, val;
	cin >> n;
	Set<int> set;

	if (n == 0)
		return false;

	for (int i = 0; i < n; ++i) {
		cin >> val;
		set.insert(val);
	}

	cin >> n;

	for (int i = 0; i < n; ++i) {

		cin >> val;

		try {
			// resolver el caso posiblemente llamando a otras funciones
			// escribir la solución
			cout << set.kesimo(val) << "\n";
		} catch (...) {
			cout << "??\n";
		}
	}

	cout << "---\n";

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
