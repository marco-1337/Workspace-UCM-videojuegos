// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <algorithm>

using namespace std;

bool esValida(const vector<int>& sol, const vector<int>& tareasAsignadas, int maxTareas, int i, int k)
{
    if (k % 2 != 0)
    {
        if (sol[k-1] == i)
            return false;
    }

    return tareasAsignadas[i] <= maxTareas;
}

int estimacionOptimista(int k, int n, const vector<int>& mejoresPreferencias)
{
    int out = 0;

    if (k == 0)
    {
        out += mejoresPreferencias[k];
    }
    else if (k % 2 == 0)
    {
        out += mejoresPreferencias[k/2] - mejoresPreferencias[k/2 - 1];
    }

    out += (mejoresPreferencias[n-1] - mejoresPreferencias[k/2]) * 2;

    return out;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, int a, const vector<vector<int>>& preferencias, 
    int maxTareas, vector<int> tareasAsignadas, int puntuacion, int& mejorSol, const vector<int>& mejoresPreferencias) {
    
    for (int i = 0; i < a; ++i)
    {
        sol[k] = i;
        ++tareasAsignadas[i];

        if (esValida(sol, tareasAsignadas, maxTareas, i, k))
        {
            puntuacion += preferencias[i][k/2];

            if (k == n*2 - 1)
            {
                mejorSol = max(mejorSol, puntuacion);
            }
            else if (estimacionOptimista(k, n, mejoresPreferencias) + puntuacion > mejorSol)
            {
                resolver(sol, n, k+1, a, preferencias, maxTareas, 
                    tareasAsignadas, puntuacion, mejorSol, mejoresPreferencias);
            }

            puntuacion -= preferencias[i][k/2];
        }

        --tareasAsignadas[i];
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n, a, t;

    cin >> n >> a >> t;

    if (n == 0 && a == 0 && t == 0)
        return false;
        
    vector<int> sol(n*2);
    vector<int> tareasAsignadas(a, 0);
    vector<vector<int>> preferencias(a, vector<int>(n));

    vector<int> mejoresPreferencias(n, 0);

    for (int i = 0; i < a; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> preferencias[i][j];
            mejoresPreferencias[j] = max(mejoresPreferencias[j], preferencias[i][j]);
        }
    }

    for (int i = 1; i < n; ++i)
    {
        mejoresPreferencias[i] += mejoresPreferencias[i-1]; 
    }

    int mejorSol = 0;

    resolver(sol, n, 0, a, preferencias, t, tareasAsignadas, 0, mejorSol, mejoresPreferencias);
    
    // escribir sol
    cout << mejorSol << "\n";

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
