// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, vector<int>& frecuenciaSupermercado, 
    vector<vector<int>>& precios, int precio, int& precioMinimo) 
{
    for(int i = 0; i < precios.size(); ++i)
    {
        sol[k] = i;
        
        if (frecuenciaSupermercado[i] < 3)
        {
            ++frecuenciaSupermercado[i];
            precio += precios[i][k];

            if (k == n-1)
            {
                if (precio < precioMinimo)
                    precioMinimo = precio;
            }
            else
            {
                resolver(sol, n, k+1, frecuenciaSupermercado, precios, precio, precioMinimo);
            }

            --frecuenciaSupermercado[i];
            precio -= precios[i][k];
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

    int precioMinimo = 0;

    for (int i = 0; i < nSupermercados; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> precios[i][j];

            if (precios[i][j] > precioMinimo) precioMinimo = precios[i][j]; 
        }
    }
    
    precioMinimo *= n;

    vector<int> sol(n);

    resolver(sol, n, 0, frecuenciaSupermercado, precios, 0, precioMinimo);

    cout << precioMinimo << "\n";    
    
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