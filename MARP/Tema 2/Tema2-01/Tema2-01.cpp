
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Se van buscando siempre los costes de sumado mas pequeño, ordenandolos por el 
 mas pequeño en la cola de prioridad. Se suman los mas pequeños, se extraen,
 y se registra ese coste en el medidor de coste total y de vuelta a la cola.

 Coste temporal: sea n el numero de elementos de la cola, O(n log n)
 Coste espacial: sea n el numero de elementos de la cola, O(n)


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada

    long n;
    cin >> n;

	if (n == 0)
		return false;

    priority_queue<long long, vector<long long>, greater<long long>> minPriorityQueue;

    long long sumando;

    for (long i = 0; i < n; ++i) {
        cin >> sumando;
        minPriorityQueue.push(sumando);
    }

	// resolver el caso posiblemente llamando a otras funciones

    long long   costeFinal = 0, 
                segundoSumando;

    while (--n)
    {
        sumando = minPriorityQueue.top();
        minPriorityQueue.pop();
        segundoSumando = minPriorityQueue.top();
        minPriorityQueue.pop();
        costeFinal += sumando + segundoSumando;
        minPriorityQueue.push(sumando + segundoSumando);
    }

	// escribir la solución
    cout << costeFinal << "\n";

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
