// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <list>

using namespace std;

// Temporal: O(n) siendo n el numero de elementos en la lista
// Espacial: O(1)
// función que resuelve el problema
void resolver(list<char>& datos, int n, int pos, int lon, int k) {
    if (n > 0 && lon != 0 && k != 0 && pos - k >= 0 && pos < n)
    {
        if (pos + lon >= n)
            lon = n - pos;
        int pasosHastaK = pos - k;

        for (int i = 0; i < pasosHastaK; ++i)
        {
            datos.push_back(datos.front());
            datos.pop_front();
        }

        auto it = datos.begin();
        int pasosHastaPos = pos - pasosHastaK;

        for (int i = 0; i < pasosHastaPos; ++i)
        {
            ++it;
        }

        for (int i = 0; i < lon; ++i)
        {
            datos.push_back(*it);
            ++it;
        }

        for (int i = 0; i < pasosHastaPos; ++i)
        {
            datos.push_back(datos.front());
            datos.pop_front();
        }

        for (int i = 0; i < lon; ++i)
        {
            datos.pop_front();
        }

        int rest = n - (pos+lon);

        for (int i = 0; i < rest; ++i)
        {
            datos.push_back(datos.front());
            datos.pop_front();
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, pos, lon, k;
    
    cin >> n >> pos >> lon >> k;

    char in;
    list<char> datos;

    for (int i = 0; i<n; ++i)
    {
        cin >> in;
        datos.push_back(in);
    } 

    resolver(datos, n, pos, lon, k);
    // escribir sol
    
    for (char e : datos)
    {
        cout << e << " ";
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