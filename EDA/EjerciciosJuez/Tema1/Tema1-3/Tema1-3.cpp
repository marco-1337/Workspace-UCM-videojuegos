// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
string resolver(vector<int> datos, int posicion) {

    int mayorPrimeraMitad = datos[0];

    for (size_t i = 1; i <= posicion; i++)
    {
        if ( datos[i] > mayorPrimeraMitad )
            mayorPrimeraMitad = datos[i];
    }

    for (size_t i = posicion + 1; i < datos.size(); i++)
    {
        if ( datos[i] <= mayorPrimeraMitad ) 
            return "NO";
    }
    return "SI";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, posicion;
    cin >> n >> posicion;

    vector<int> datos(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> datos[i];
    }

    string sol = resolver(datos, posicion);
    // escribir sol
    cout << sol << "\n";
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}