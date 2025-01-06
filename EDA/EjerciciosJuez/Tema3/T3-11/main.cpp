// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

int estimacionOptimista(int k, int n, int satisfaccionTotal, const vector<int>& satisfaccionesMaximas)
{
    int estimacion = satisfaccionTotal;

    for (int i = k; i < n; ++i)
    {
        estimacion += satisfaccionesMaximas[i];
    }

    return estimacion;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, const vector<vector<int>>& satisfaccion, 
    vector<bool>& disponibilidad, const vector<int>& satisfaccionesMaximas, 
    int satisfaccionTotal, int& mejorSol) 
{
    for (int i = 0; i < disponibilidad.size(); ++i)
    {
        sol[k] = i;

        if (disponibilidad[i]) // es valida
        {
            disponibilidad[i] = false;

            satisfaccionTotal += satisfaccion[k][i];

            if (k == n-1) // es solucion
            {
                if (satisfaccionTotal > mejorSol)
                    mejorSol = satisfaccionTotal;
            }
            else
            {
                if (estimacionOptimista(k+1, n, satisfaccionTotal, satisfaccionesMaximas) > mejorSol)
                    resolver(sol, n, k+1, satisfaccion, disponibilidad, satisfaccionesMaximas, satisfaccionTotal, mejorSol);
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

    vector<int> satisfaccionesMaxima(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> satisfaccion[i][0];
        int max = satisfaccion[i][0];

        for (int j = 1; j < nJuguetes; ++j)
        {
            cin >> satisfaccion[i][j];
            if (satisfaccion[i][j] > max) max = satisfaccion[i][j];
        }

        satisfaccionesMaxima[i] = max;
    }

    int mejorSol = 0;
    
    vector<int> sol(n);

    vector<bool> disponibilidad(nJuguetes, true);

    resolver(sol, n, 0, satisfaccion, disponibilidad, satisfaccionesMaxima, 0, mejorSol);

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