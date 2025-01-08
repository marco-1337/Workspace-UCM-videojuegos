// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

// O(log n) siendo n el numero de elementos de cada vector (no la suma). En cada iteracion el problema se reduce /2
// función que resuelve el problema
void resolver(const vector<int>& f1, const vector<int>& f2, int ini, int fin) {
    
    int n = fin-ini;

    if (n == 1)
    {
        if (f1[ini] == f2[ini])
            cout << "SI " << ini;
        else 
        {
            cout << "NO ";
            if (f1[ini] < f2[ini])
                cout << ini << " " << ini+1;
            else
                cout << ini-1 << " " << ini;
        }
        cout << "\n";
    }
    else
    {
        int mitad = (fin+ini)/2;

        if (f1[mitad] > f2[mitad])
            resolver(f1, f2, ini, mitad);
        else
            resolver(f1, f2, mitad, fin);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n;
    cin >> n;

    if (n == 0)
        return false;
    
    vector<int> f1(n);
    vector<int> f2(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> f1[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> f2[i];
    }

    // escribir sol
    resolver(f1, f2, 0, n);
    
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}