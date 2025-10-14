
/*@ <authors>
 *
 * Marco González Campo MARP23
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <list>
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

    Cada caja de pilas se representa con una cola de prioridad,
    cada vez que se pone a volar un dron se utilizan las pilas con
    mas carga y en caso de que quede alguna pila con algo de carga
    se devuelve a su caja correspondiente al final del día, puesto
    que como los drones solo vuelan una vez por día y salen todos 
    a la vez no se comparten pilas el mismo día.

 - Coste temporal:    sea N el número de pilas menor y K el número de drones, O(N * M log N)
 - Coste espacial:    sea N el número de pilas total, O(N)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
    int nDrones, pilasA, pilasB, aux, diff;
    cin >> nDrones >> pilasA >> pilasB;

	if (!std::cin)  // fin de la entrada
		return false;

    priority_queue<int, vector<int>> cajaA;
    priority_queue<int, vector<int>> cajaB;

    list<int> pilasUsadas;
    int i;

    for (i = 0; i < pilasA; ++i) {
        cin >> aux;
        cajaA.push(aux);
    }

    for (i = 0; i < pilasB; ++i) {
        cin >> aux;
        cajaB.push(aux);
    }   

    while (!cajaA.empty() && !cajaB.empty()) {
        i = 0;
        aux = 0;
        while(!cajaA.empty() && !cajaB.empty() && nDrones > i++) {
            
            diff = cajaA.top() - cajaB.top();
            
            if (diff != 0) pilasUsadas.push_back(diff);

            aux += min(cajaA.top(), cajaB.top());
            cajaA.pop(); 
            cajaB.pop();
        }

        while (!pilasUsadas.empty()) {
            if (pilasUsadas.front() > 0) cajaA.push(pilasUsadas.front()); 
            else cajaB.push(-pilasUsadas.front());
            pilasUsadas.pop_front();
        }

        cout << aux << " ";
    }

    cout << "\n";

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
