
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Se usa una cola de indices para modificar los puntos de los paises.
 Se ha expandido IndexPQ para que en caso de empate use un comparador
 que tiene en cuenta tanto el valor indice como la prioridad.

 - Coste temporal:    sea N el número de instrucciones, O(N log N)
 
 - Coste espacial:    sea N el número de instrucciones, O(N)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename T>
struct LexicographicTiebreaker{
    bool operator()(const string& aK, const string& bK, const T& aV, const T& bV) const{
        return aV == bV && aK < bK;
    }
};

bool resuelveCaso() {

	// leer los datos de la entrada
    long casos;
    cin >> casos;

	if (!std::cin)  // fin de la entrada
		return false;

    string instruccion;
    long puntos;

    IndexPQ<string, long, greater<long>, LexicographicTiebreaker<long>> colaMaxPaises;

    // resolver el caso posiblemente llamando a otras funciones
    while (casos--) {
        cin >> instruccion;

        if (instruccion == "?") {
            // escribir solución
            cout << colaMaxPaises.top().elem << " " << colaMaxPaises.top().prioridad << "\n";
        } else {

            cin >> puntos;
            if (colaMaxPaises.contains(instruccion)) puntos += colaMaxPaises.priority(instruccion);
            colaMaxPaises.update(instruccion, puntos);
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
