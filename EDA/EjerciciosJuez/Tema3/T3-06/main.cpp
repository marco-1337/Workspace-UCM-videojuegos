// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, int prev) {

    if ( k == n)
    {
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
    else
    {
        for(int i = 0; i < 3; ++i)
        {
            sol[k] = i;

            if (prev != 2 || i != 2)
                resolver(sol, n, k+1, i);
        }
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
    
    vector<int> sol(n);

    sol[0] = 1;

    resolver(sol, n, 1, 1);
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