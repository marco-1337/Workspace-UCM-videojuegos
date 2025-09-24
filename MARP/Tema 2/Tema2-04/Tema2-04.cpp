
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

struct PacienteEsperando {
    string nombre;
    long turno;
    long gravedad;
};

bool operator<(const PacienteEsperando &a, const PacienteEsperando &b){
    return (a.gravedad < b.gravedad) || 
        // importante aquí el > en el turno
        (a.turno > b.turno && a.gravedad == b.gravedad);
}

bool resuelveCaso() {
	// leer los datos de la entrada

    long n;
    cin >> n;

	if (n == 0)
		return false;

    char caso;

    priority_queue<PacienteEsperando, vector<PacienteEsperando>> colaPacientes;

    PacienteEsperando paciente;

	// resolver el caso posiblemente llamando a otras funciones

    for (long i = 0; i < n; ++i) {

        cin >> caso;
        if (caso == 'I') {
            cin >> paciente.nombre >> paciente.gravedad;
            paciente.turno = i;
            colaPacientes.push(paciente);
        }
        else {
            // escribir la solución
            cout << colaPacientes.top().nombre << "\n";
            colaPacientes.pop();
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
