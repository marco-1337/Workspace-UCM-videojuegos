// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <unordered_set>

using namespace std;

// función que resuelve el problema
void resolver
(
    vector<int>& sol, int n, int k, 
    const vector<vector<int>>& recaudacion, const vector<vector<bool>>& preferencias,
    unordered_set<int>& usados
)
{
    for (int i = 0; i < n; ++i)
    {
        sol[k] = i;

        if (!usados.contains(i))
        {
            usados.insert(i);
            if ((k == 0 || preferencias[i][sol[k-1]])) // es valida
            {
                if (k == n-1)
                {
                    for (int item : sol)
                    {
                        cout << item << " ";
                    }
                    cout << "\n";
                }
                else
                {
                    resolver(sol, n, k+1, recaudacion, preferencias, usados);
                }
            }
            usados.erase(i);
        }
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    int n;

    cin >> n;

    unordered_set<int> usados;

    vector<vector<int>> recaudacion(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> recaudacion[i][j];
        }
    }

    vector<vector<bool>> preferencias(n, vector<bool>(n));

    int aux;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> aux;
            preferencias[i][j] = aux;
        }
    }

    vector<int> sol(n);
    
    resolver(sol, n, 0, recaudacion, preferencias, usados);
    // escribir sol
    
    
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