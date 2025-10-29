
/*@ <authors>
 *
 * Marco González Campo, MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "DijkstraIndirecto.h"

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

    GrafoValorado<int> grafo = GrafoValorado<int>(cin, 1);

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
    int casos, v, w;
    cin >> casos;
    Camino<int> camino;

    for (int i = 0; i < casos; ++i) {
        cin >> v >> w;

        --v; --w;

        DijkstraIndirecto<int> dijkstra = DijkstraIndirecto<int>(grafo, v);

        // escribir la solución
        if (dijkstra.hayCamino(w)) {

            cout << dijkstra.distancia(w) << ": ";
            camino = dijkstra.camino(w);

            v = camino.size();

            for (int j = 1; j < v; ++j) {
                cout << camino.front() + 1 << " -> ";
                camino.pop_front();
            }

            cout << camino.front() + 1;
        }
        else {
            cout << "NO LLEGA";
        }
        
        cout << "\n";
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
