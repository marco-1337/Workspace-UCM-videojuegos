
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

 

 - Coste temporal:    sea N el número de instrucciones, O(N log N)
 
 - Coste espacial:    sea N el número de instrucciones, O(N)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Tarea {
    int start;
    int end;
    int periodo = 0;
};

bool operator<(const Tarea &a, const Tarea &b) {
    return a.start < b.start;
}

bool operator>(const Tarea &a, const Tarea &b) {
    return b < a;
}

bool resuelveCaso() {

	// leer los datos de la entrada
    int nFijos, nPeriodicos;
    int secs;
    cin >> nFijos >> nPeriodicos >> secs;

	if (!std::cin)  // fin de la entrada
		return false;

    Tarea tareaAux;

    priority_queue<Tarea, vector<Tarea>, greater<Tarea>> colaTareas;

    for (int i = 0; i < nFijos; ++i) {
        cin >> tareaAux.start;
        cin >> tareaAux.end;

        if (tareaAux.start < secs) {
            colaTareas.push(tareaAux);   
        }
    }

    int periodo;
    
    for (int i = 0; i < nPeriodicos; ++i) {
        
        cin >> tareaAux.start;
        cin >> tareaAux.end;
        cin >> tareaAux.periodo;

        if (tareaAux.start < secs) {
            colaTareas.push(tareaAux);   
        }
    }

    bool noSolapamiento = true;
    int timestamp = 0,
        lastStartTimestamp = 0;
    int currentSecs = 0;

    if (!colaTareas.empty()) lastStartTimestamp = colaTareas.top().start;

    // resolver el caso posiblemente llamando a otras funciones
    while (secs > timestamp && !colaTareas.empty()) {

        tareaAux = colaTareas.top();

        if (tareaAux.start < timestamp) {
            noSolapamiento = false;
            lastStartTimestamp = secs;
        } else {
            timestamp = tareaAux.end;
            
            colaTareas.pop();
            
            if (tareaAux.periodo > 0) {
                tareaAux.start += tareaAux.periodo;
                tareaAux.end += tareaAux.periodo;
                colaTareas.push(tareaAux);
            }

            lastStartTimestamp = colaTareas.top().start;
        }
    }

    cout << ((noSolapamiento) ? "NO" : "SI") << "\n";

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
