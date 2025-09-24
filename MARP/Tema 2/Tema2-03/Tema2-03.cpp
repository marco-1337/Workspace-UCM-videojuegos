
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

 Cada caja tiene su tiempo de uso y su id. Se va agregando al tiempo de
 la caja disponible el nuevo tiempo de trabajo según el cliente que sea su turno.

 - Coste temporal:    sea N el numero de cajas y K el numero de clientes, O(N log N + K log N)
 
 - Coste espacial:    sea N el numero de cajas y K el numero de clientes, O(N + K)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct DatosCaja {
    int numCaja;
    int tiempoTrabajo;
};

bool operator<(const DatosCaja &a, const DatosCaja &b){
    return (a.tiempoTrabajo < b.tiempoTrabajo) || 
        (a.numCaja < b.numCaja && a.tiempoTrabajo == b.tiempoTrabajo);
}

bool operator>(const DatosCaja &a, const DatosCaja &b){
    return b < a;
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int nCajas, nClientes;
    cin >> nCajas;

	if (nCajas == 0)
		return false;

    cin >> nClientes;

    vector<int> tiempoClientes(nClientes);

    for (int i = 0; i < nClientes; ++i) cin >> tiempoClientes[i];

    priority_queue<DatosCaja, vector<DatosCaja>, greater<DatosCaja>> colaCajas;

    DatosCaja caja;
    caja.tiempoTrabajo = 0;

    for (long i = 0; i < nCajas; ++i) {
        caja.numCaja = i+1;
        colaCajas.push(caja);
    }

	// resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < nClientes; ++i)
    {
        caja = colaCajas.top();
        colaCajas.pop();
        caja.tiempoTrabajo += tiempoClientes[i];
        colaCajas.push(caja);
    }

	// escribir la solución
    cout << colaCajas.top().numCaja << "\n";

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
