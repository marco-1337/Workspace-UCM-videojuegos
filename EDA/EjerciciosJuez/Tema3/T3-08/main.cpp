// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

bool esValida(vector<int>& sol, int k, int n, int i, int consumoMax, int consumoTotal, vector<int>& utilizadas)
{
    if 
    (
        (k > 1 && sol[k-1] == i && sol[k-2] == i) || consumoTotal > consumoMax || 
        (consumoTotal == consumoMax && k < n-1)
    )
        return false;

    int otrosColores = 0;

    for (int j = 0; j < i; ++j)
    {
        otrosColores += utilizadas[j];
    }

    for (int j = i+1; j < utilizadas.size(); ++j)
    {
        otrosColores += utilizadas[j];
    }

    if (utilizadas[i] > otrosColores) 
        return false;

    return true;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, int consumoMax, int consumoTotal, 
    const vector<int>& listaConsumo, vector<int>& utilizadas, int& nSols) {
    
    for (int i = 0; i < listaConsumo.size(); ++i)
    {
        sol[k] = i;

        consumoTotal += listaConsumo[i];

        if (esValida(sol, k, n, i, consumoMax, consumoTotal, utilizadas))
        {
            ++utilizadas[i];

            if (k == n-1)
            {
                ++nSols;
            }
            else
                resolver(sol, n, k+1, consumoMax, consumoTotal, listaConsumo, utilizadas, nSols);

            --utilizadas[i];
        }

        consumoTotal -= listaConsumo[i];
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n, bombillas, consumoMax;

    cin >> n;

    if (n == 0)
        return false;
    
    cin >> bombillas;
    cin >> consumoMax;

    vector<int> sol(n);
    vector<int> listaConsumo(bombillas);
    vector<int> utilizadas(bombillas, 0);

    for (int i = 0; i < bombillas; ++i)
    {
        cin >> listaConsumo[i];
    }

    int nSols = 0;

    resolver(sol, n, 0, consumoMax, 0, listaConsumo, utilizadas, nSols);
    
    cout << nSols << "\n";
    // escribir sol
    
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
