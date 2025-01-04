// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

bool esValida(const vector<int>& sol, int k, int i, 
    const vector<int>& bloquesDisponibles, const vector<int>& bloquesUsados)
{
    bool todosPositivos = true;
    int j = 0;
    while (todosPositivos && j < bloquesDisponibles.size())
    {
        todosPositivos = bloquesDisponibles[j] > -1;
        ++j;
    }

    return (sol[k-1] != 2 || i != 2) && bloquesUsados[2] <= bloquesUsados[0] && todosPositivos;

}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, vector<int>& bloquesDisponibles, vector<int>& bloquesUsados, int& nSols) {


        for(int i = 0; i < 3; ++i)
        {
            sol[k] = i;

            --bloquesDisponibles[i];
            ++bloquesUsados[i];

            if (esValida(sol, k, i, bloquesDisponibles, bloquesUsados)) // es solucion
            {
                if ( k == n-1)
                {
                    if (bloquesUsados[1] > bloquesUsados[0] + bloquesUsados[2]) // es solucion valida
                    {
                        ++nSols;

                        for (int e : sol)
                        {
                            switch (e)
                            {
                            case 0:
                                cout << "azul";
                                break;
                            case 1:
                                cout << "rojo";
                                break;
                            case 2:
                                cout << "verde";
                                break;
                            default:
                                cout << "ERROR";
                                break;
                            }

                            cout << " ";
                        }
                        cout << "\n";
                    }
                }
                else
                {
                    if (k < n/2 || !(bloquesUsados[0] + bloquesUsados[2] > n/2+1))
                    {
                        resolver(sol, n, k+1, bloquesDisponibles, bloquesUsados, nSols);
                    }
                }
            }

            ++bloquesDisponibles[i];
            --bloquesUsados[i];
        }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    vector<int> bloquesUsados(3, 0);
    vector<int> bloquesDisponibles(3);

    int n;
    cin >> n;

    for (int i = 0; i < 3; ++i)
    {
        cin >> bloquesDisponibles[i];
    }

    int i = 0;
    bool todoCeros = true;

    while (i < n && todoCeros)
    {
        todoCeros = bloquesDisponibles[i] != 0;
        ++i;
    }

    if (n == 0 && todoCeros)
        return false;
    
    vector<int> sol(n, -1);

    sol[0] = 1;
    if (bloquesDisponibles[1] > 0)
    {
        --bloquesDisponibles[1];
        ++bloquesUsados[1];
    }

    int nSols = 0;

    resolver(sol, n, 1, bloquesDisponibles, bloquesUsados, nSols);

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