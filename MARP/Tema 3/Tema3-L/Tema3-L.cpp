
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

    Se tienen dos colas para ver el canal con mas espectadores y el canal con
    mas minutos en primetime. En cada segmento se actualiza el prime time del
    de mas espectadores hasta el segmento y luego se actualizan los espectadores.

 - Coste temporal:    sea N el número de segmentos de tiemp y K el numero de canales O(N * K log K)
 - Coste espacial:    sea K el número de canales, O(K)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
    int nFranja, nCanales, nSegmentos, viewers, index, prevT = 0, currT, i;
    cin >> nFranja >> nCanales >> nSegmentos;

	if (!std::cin)  // fin de la entrada
		return false;

    IndexPQ<int, int, greater<int>> audiencia;
    unordered_map<int, int> minutos;

    for (i = 0; i < nCanales; ++i) {
        cin >> viewers;
        audiencia.push(i+1, viewers);
    }

    int a = audiencia.top().prioridad;

    for (i = 0; i < nSegmentos; ++i) {
        cin >> currT >> index;
        if (index != -1) {

            minutos[audiencia.top().elem] += currT - prevT;

            while (index != -1) {
                cin >> viewers;
                audiencia.update(index, viewers);
                cin >> index;
            }

            prevT = currT;
        }
    }
    
    minutos[audiencia.top().elem] += nFranja - prevT;

    vector<pair<int, int>> orderedMins(minutos.begin(), minutos.end());
    sort(orderedMins.begin(), orderedMins.end(), []
        (const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        }
    );

    for (i = 0; i < orderedMins.size(); ++i) {
        cout << orderedMins[i].first << " " << orderedMins[i].second << "\n";
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
