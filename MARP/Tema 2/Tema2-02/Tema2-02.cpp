
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

 Cada vez que se envia informacion, se suma al tiempo total hasta la siguiente
 el periodo. 

 - Coste temporal:    sea n el numero de elementos de la cola y k el numero de mensajes, 
                    O(n * log n + k * log n)
 
 - Coste espacial:    sea n el numero de elementos de la cola, O(n)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct DatosAlumno {
    long id;
    int periodo;
    long long tiempoActual;
};

bool operator<(const DatosAlumno &a, const DatosAlumno &b){
    return (a.tiempoActual < b.tiempoActual) || 
        (a.id < b.id && a.tiempoActual == b.tiempoActual);
}

bool operator>(const DatosAlumno &a, const DatosAlumno &b){
    return b < a;
}

bool resuelveCaso() {
	// leer los datos de la entrada

    long n;
    cin >> n;

	if (n == 0)
		return false;

    priority_queue<DatosAlumno, vector<DatosAlumno>, greater<DatosAlumno>> colaAlumnos;

    DatosAlumno alumno;
    alumno.tiempoActual = 0;

    for (long i = 0; i < n; ++i) {
        cin >> alumno.id >> alumno.periodo;
        alumno.tiempoActual = alumno.periodo;
        colaAlumnos.push(alumno);
    }

    long k;
    cin >> k;

	// resolver el caso posiblemente llamando a otras funciones
    while (k--)
    {
        alumno = colaAlumnos.top();
        colaAlumnos.pop();
        alumno.tiempoActual += alumno.periodo;
        colaAlumnos.push(alumno);

        // escribir la solución
        cout << alumno.id << "\n";
    }

	// escribir la solución
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
