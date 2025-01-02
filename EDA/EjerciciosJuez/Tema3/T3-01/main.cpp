// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

const char START_CHAR = 'a';
const char END_CHAR = 'z'+1;

// función que resuelve el problema
void resolver(vector<char>& sol, int n, int k, int kMax) {
    for (int i = 0; i < kMax && i < END_CHAR; i++)
    {
        sol[k] = START_CHAR + i;

        if (k == n-1)
        {
            for(char& c : sol)
            {
                cout << c;
            }
            cout << '\n';
        }
        else
        {
            resolver(sol, n, k+1, kMax);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int nLetras, n;

    cin >> nLetras;
    cin >> n;

    if (! std::cin)
        return false;
    
    vector<char> sol(n);

    resolver(sol, n, 0, nLetras);
    cout << '\n';
    
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