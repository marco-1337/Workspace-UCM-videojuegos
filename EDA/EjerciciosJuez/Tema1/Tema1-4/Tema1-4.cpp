// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
vector<long long int> resolver(const vector<long long int>& datos) {

    vector<long long int> sinImpares(datos.size());

    int ultimoIndexUtil = 0;

    for (size_t i = 0; i < datos.size(); i++)
    {
        if ( datos[i] % 2 == 0 )
        {
            sinImpares[ultimoIndexUtil] = datos[i];
            ultimoIndexUtil++;
        }
    }

    sinImpares.resize(ultimoIndexUtil);

    return sinImpares;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n; 
    vector<long long int> datos(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> datos[i];
    }
    
    vector<long long int> sol = resolver(datos);
    // escribir sol

    for (size_t i = 0; i < sol.size(); i++)
    {
        cout << sol[i] << " ";
    }
    
    cout << "\n";
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