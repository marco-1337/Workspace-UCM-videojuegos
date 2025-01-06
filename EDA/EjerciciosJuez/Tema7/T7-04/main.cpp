// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <unordered_map>
#include <vector>

using namespace std;

// función que resuelve el problema
int resolver(vector<int> listaCapitulos, int n) {

    int reinicio = 0;

    int distancia = -1;

    unordered_map<int, int> capitulos;

    for (int i = 0; i < n; ++i)
    {
        auto it = capitulos.find(listaCapitulos[i]);

        if (it != capitulos.end() && it->second >= reinicio)
        {
            distancia = max(distancia, i - reinicio);
            reinicio = it->second +1;
        }

        capitulos[listaCapitulos[i]] = i ;
    }

    return max(distancia, n - reinicio);

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    
    cin >> n;

    vector<int> listaCapitulos(n);

    int c;

    for (int i = 0; i < n; ++i)
    {
        cin >> listaCapitulos[i];
    }
    
    int sol = resolver(listaCapitulos, n);
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