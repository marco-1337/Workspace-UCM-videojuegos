// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

int estimacionOptimista(int n, int k, int precioActual, const vector<int>& preciosMinimos)
{
    int estimacion = precioActual;
    for (int i = k; i < n; ++i)
    {
        estimacion += preciosMinimos[i];
    }

    return estimacion;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, vector<int>& frecuenciaSupermercado, 
    const vector<vector<int>>& precios, const vector<int>& preciosMinimos, 
    int precioActual, int& mejorSol) 
{
    for(int i = 0; i < precios.size(); ++i)
    {
        sol[k] = i;
        
        if (frecuenciaSupermercado[i] < 3)
        {
            ++frecuenciaSupermercado[i];
            precioActual += precios[i][k];

            if (k == n-1)
            {
                if (precioActual < mejorSol)
                    mejorSol = precioActual;
            }
            else
            {
                if (estimacionOptimista(n, k+1, precioActual, preciosMinimos) < mejorSol)
                    resolver(sol, n, k+1, frecuenciaSupermercado, precios, 
                        preciosMinimos, precioActual, mejorSol);
            }

            --frecuenciaSupermercado[i];
            precioActual -= precios[i][k];
        }
    }    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    int nSupermercados, n;

    cin >> nSupermercados >> n;

    vector<vector<int>> precios(nSupermercados, vector<int>(n));
    vector<int> frecuenciaSupermercado(nSupermercados, 0);

    int mejorSol = 0;

    vector<int> preciosMinimos(n);

    for (int j = 0; j < n; ++j)
    {
        cin >> precios[0][j];

        if (precios[0][j] > mejorSol) mejorSol = precios[0][j]; 

        preciosMinimos[j] = precios[0][j];
    }

    for (int i = 1; i < nSupermercados; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> precios[i][j];

            if (precios[i][j] > mejorSol) mejorSol = precios[i][j];

            if (preciosMinimos[j] > precios[i][j])
            {
                preciosMinimos[j] = precios[i][j];
            }
        }
    }
    
    mejorSol *= n;

    vector<int> sol(n);

    resolver(sol, n, 0, frecuenciaSupermercado, precios, preciosMinimos, 0, mejorSol);

    cout << mejorSol << "\n";    
    
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