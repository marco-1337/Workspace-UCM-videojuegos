// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, const vector<vector<int>>& satisfaccion, 
    vector<bool>& disponibilidad, int satisfaccionTotal, int& mejorSol) {
    
    for (int i = 0; i < disponibilidad.size(); ++i)
    {
        sol[k] = i;

        if (disponibilidad[i])
        {
            disponibilidad[i] = false;

            satisfaccionTotal += satisfaccion[k][i];

            if (k == n-1)
            {
                if (satisfaccionTotal > mejorSol)
                {
                    mejorSol = satisfaccionTotal;
                }
            }
            else
            {
                resolver(sol, n, k+1, satisfaccion, disponibilidad, satisfaccionTotal, mejorSol);
            }

            satisfaccionTotal -= satisfaccion[k][i];

            disponibilidad[i] = true;
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int nJuguetes, n;
    cin >> nJuguetes;

    if (! std::cin)
        return false;
    
    cin >> n;

    vector<vector<int>> satisfaccion(n, vector<int>(nJuguetes));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < nJuguetes; ++j)
        {
            cin >> satisfaccion[i][j];
        }
    }

    int mejorSol = 0;
    
    vector<int> sol(n);

    vector<bool> disponibilidad(nJuguetes, true);

    resolver(sol, n, 0, satisfaccion, disponibilidad, 0, mejorSol);

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