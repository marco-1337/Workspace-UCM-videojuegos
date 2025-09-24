
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

 Se van añadiendo los pacientes ingresados a la cola de prioridad y se les asigna
 el turno de entrada, el turno asciende por cada caso completado.

 Según el número de atenciones médicas se va consumiendo la cola.

 - Coste temporal:    sea N el numero de casos, O(N log N)
 
 - Coste espacial:    sea N el numero de casos, O(N)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct DatosPilas {
    long top;
    int index;
};

bool operator<(const DatosPilas &a, const DatosPilas &b){
    return (a.top < b.top);
}

bool operator>(const DatosPilas &a, const DatosPilas &b){
    return b < a;
}

bool resuelveCaso() {

	// leer los datos de la entrada
    int n, k;
    cin >> n;

	if (!std::cin)  // fin de la entrada
		return false;
    
    long valor, minVal, nElements = 1;

    priority_queue<DatosPilas, vector<DatosPilas>, greater<DatosPilas>> colaPrioridadPilasComics;
    vector<stack<long>> pilas;
    DatosPilas pDatos;

    cin >> k;
    stack<long> comics = stack<long>();

    cin >> valor;
    minVal = valor;
    comics.push(valor);

    for (int j = 1; j < k; ++j) {
        cin >> valor;
        if (valor < minVal) minVal = valor;
        comics.push(valor);

        ++nElements;
    }

    pilas.push_back(comics);
    pDatos = {comics.top(), 0};
    colaPrioridadPilasComics.push(pDatos);

    for (int i = 1; i < n; ++i) {
        cin >> k;

        comics = stack<long>();
        
        for (int j = 0; j < k; ++j) {
            
            cin >> valor;
            if (valor < minVal) minVal = valor;
            comics.push(valor);

            ++nElements;
        }

        pilas.push_back(comics);
        pDatos = {comics.top(), i};
        colaPrioridadPilasComics.push(pDatos);
    }

	// resolver el caso posiblemente llamando a otras funciones

    long pos = 1;
    bool inCondition = true;

    while(inCondition && nElements--) {
        
        if (colaPrioridadPilasComics.top().top == minVal) inCondition = false;
        else {
            ++pos;
            pDatos = colaPrioridadPilasComics.top();
            pilas[pDatos.index].pop();
            colaPrioridadPilasComics.pop();

            if (!pilas[pDatos.index].empty()) {
                pDatos.top = pilas[pDatos.index].top();
                colaPrioridadPilasComics.push(pDatos);
            }
        }
    }

    cout << pos << "\n";

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
