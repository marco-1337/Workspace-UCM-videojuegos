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

vector<int> checkLevel(ValidezTablero& infoValidez, int k)
{
    vector<int> out;

    int n = infoValidez.cols.size();

    for (int i = 0; i < n; ++i)
    {
        if (
            infoValidez.cols[i] == false && 
            infoValidez.diagonalLeft[i + n - k - 1] == false &&
            infoValidez.diagonalRight[i + k] == false
            )
        {
            out.push_back(i);
        }
    }

    return out;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int n, int k, int& nSoluciones, ValidezTablero& infoValidez) {
    
    // poda anticipada, solo comprobará los casos en los que se pueda poner una reina
    // descartará la rama si no hay casos
    vector<int> casos = checkLevel(infoValidez, k);

    for (int i : casos)
    {
        sol[k] = i;

        // no compruebo si es valido o no ya que arriba genero los casos validos y es sobre los que itero

        if (k == n-1) //es solucion
            ++nSoluciones;
        else
        {
            int leftDiagIndex = i + (n - k) - 1;
            int rightDiagIndex = i+k;

            infoValidez.cols[i] = true;
            infoValidez.diagonalLeft[leftDiagIndex] = true;
            infoValidez.diagonalRight[rightDiagIndex] = true;

            resolver(sol, n, k+1, nSoluciones, infoValidez);
            
            infoValidez.cols[i] = false;
            infoValidez.diagonalLeft[leftDiagIndex] = false;
            infoValidez.diagonalRight[rightDiagIndex] = false;
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