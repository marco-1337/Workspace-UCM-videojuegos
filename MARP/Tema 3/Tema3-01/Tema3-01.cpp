
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

 Separa los pajaros en dos monticulos, los mayores del mediano y los menores.
 Los mayores siendo un monticulo de minimos y los menores de maximo, teniendo
 entonces acceso a los dos elementos inmediatos de la bandada.

 Solo es cuestión de comparar tamaños en los monticulos y mover los inmediatos
 que correspondan a que sean la cabeza

 - Coste temporal:    sea N el número de parejas, O(N log N)
 
 - Coste espacial:    sea K el número de pájaros, O(M)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
    long mid, n, a, b;
    cin >> mid >> n;

	if (mid == 0 && n == 0)  // fin de la entrada
		return false;

    priority_queue<long, vector<long>> menores;
    priority_queue<long, vector<long>, greater<long>> mayores;

    while (n--) {

        cin >> a >> b;

        // Todo esto se podría poner en una función y llamarla 2 veces,
        // pero no quiero, un saludo

        // resolver el caso posiblemente llamando a otras funciones

        if (a < mid) menores.push(a); 
        else mayores.push(a);
        if (b < mid) menores.push(b); 
        else mayores.push(b);

        if (menores.size() > mayores.size()) {
            mayores.push(mid);
            mid = menores.top();
            menores.pop();
        } else if (menores.size() < mayores.size()) {
            menores.push(mid);
            mid = mayores.top();
            mayores.pop();
        }

        // escribir solución
        cout << mid << " ";
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
