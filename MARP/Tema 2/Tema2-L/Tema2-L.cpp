
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Como mínimo se quita de las partituras 1 por cada grupo de instrumento.
 Cada vez que se entrega una partitura se entrega al grupo con menos 
 partituras por musicos, es decir, ese grupo se elimina y se crean dos 
 grupos de sus mitades.

 De esta forma las partituras se distribuyen de forma equitativa + minimo 1 por instrumento

 - Coste temporal:    sea N el número de partituras a repartir y K el numero de musicos, O(N log M/2)
 
 - Coste espacial:    sea K el número de músicos, O(N)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct GrupoInstrumentos {
    long musicos;
    long partituras;
};

bool operator< (const GrupoInstrumentos& a, const GrupoInstrumentos& b) {
    return (a.musicos * b.partituras) < (b.musicos * a.partituras);
}

bool resuelveCaso() {

	// leer los datos de la entrada
    long p, n, halfAux;
    cin >> p;

	if (!std::cin)  // fin de la entrada
		return false;

    cin >> n;

    priority_queue<GrupoInstrumentos, vector<GrupoInstrumentos>> colaPrioridadInstrumentos;
    GrupoInstrumentos aux = {0, 1};

    for (long i = 0; i < n; ++i) {
        cin >> aux.musicos;
        colaPrioridadInstrumentos.push(aux);
    }

	// resolver el caso posiblemente llamando a otras funciones

    p -= n;

    while (p--) {
        aux = colaPrioridadInstrumentos.top();
        if (aux.partituras < aux.musicos) {
            colaPrioridadInstrumentos.pop();
            ++aux.partituras;
            colaPrioridadInstrumentos.push(aux);
        } else p = 0;
    }

    aux = colaPrioridadInstrumentos.top();

    cout << (aux.musicos / aux.partituras) + ((aux.musicos % aux.partituras) > 0 ? 1 : 0) << "\n";

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
