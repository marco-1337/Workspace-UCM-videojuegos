// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

struct ValidezTablero
{
    vector<bool> cols;

    vector<bool> diagonalLeft;
    vector<bool> diagonalRight;
};

bool compruebaValidez(ValidezTablero& infoValidez, int x, int y, int n)
{
    int diagLeft = (n-1) - (x - y);
    int diagRight = x+y;
    return infoValidez.cols[x] == false &&
        infoValidez.diagonalLeft[diagLeft] == false && infoValidez.diagonalRight[diagRight] == false;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, int& nSoluciones, ValidezTablero& infoValidez) {
    
    for (int i = 0; i < n; ++i)
    {
        sol[k] = i;

        if (compruebaValidez(infoValidez, i, k, n))
        {
            if (k == n-1) //es solucion
                ++nSoluciones;
            else
            {
                ValidezTablero original = infoValidez;

                infoValidez.cols[i] = true;

                infoValidez.diagonalLeft[(n-1) - (i - k)] = true;
                infoValidez.diagonalRight[i+k] = true;

                resolver(sol, n, k+1, nSoluciones, infoValidez);
                infoValidez = original;
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    
    vector<int> datos(n, false);
    ValidezTablero tableroValidez;

    tableroValidez.cols = vector<bool>(n, false);
    tableroValidez.diagonalLeft = tableroValidez.diagonalRight = vector<bool>((n-1)+n, false);

    int nSoluciones = 0;

    resolver(datos, n, 0, nSoluciones, tableroValidez);
    // escribir sol
    
    cout << nSoluciones << "\n";
    
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