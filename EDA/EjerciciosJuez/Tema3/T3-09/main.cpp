// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

bool esValida(vector<int>& sol, int n, int k, const vector<string>& tipos)
{
    if (k % 2 == 0)
    {
        if (sol[k] == tipos.size() - 1)
            return false;
    }
    else
    {
        if ((tipos[sol[k]] == tipos[sol[k-1]]) || sol[k] < sol[k-1])
            return false;
    }

    return true;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, const vector<string>& tipos, int& nSols) {
    
    for (int i = 0; i < tipos.size(); ++i)
    {
        sol[k] = i;

        if (esValida(sol, n, k, tipos))
        {
            if (k == n-1)
            {
                for (int e : sol)
                {
                    cout << e << " ";
                }
                cout << "\n";

                ++nSols;
            }
            else
            {
                resolver(sol, n, k+1, tipos, nSols);
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int nTipos, n;
    cin >> nTipos;

    if (! std::cin)
        return false;
    
    vector<string> tipos(nTipos);
    cin >> n;

    for (int i = 0; i < nTipos; ++i)
    {
        cin >> tipos[i];
    }

    vector<int> sol(n*2);

    int nSols = 0;

    resolver(sol, n*2, 0, tipos, nSols);
    
    if (nSols == 0) 
    {
        cout << "SIN SOLUCION\n";
    }

    cout << "\n";
    
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