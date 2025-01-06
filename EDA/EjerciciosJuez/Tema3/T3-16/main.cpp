// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

enum CaraCasete
{
    Ninguna,
    A,
    B
};

void mochila(vector<CaraCasete>& sol, int n, int k, const vector<int>& p, const vector<int>& v, 
    int& pesoA, int& pesoB, int limite, int valor, int& mejorValor) 
{
    // Cara A

    sol[k] = A;
    pesoA += p[k];
    valor += v[k];

    if (pesoA <= limite) {
        if (k == n - 1) {
            if (valor > mejorValor) {
                mejorValor = valor;
            }
        } else {
            mochila(sol, n, k + 1, p, v, pesoA, pesoB, limite, valor, mejorValor);
        }
    }

    pesoA -= p[k];
    valor -= v[k];

    // Cara B

    sol[k] = B;
    pesoB += p[k];
    valor += v[k];

    if (pesoB <= limite) {
        if (k == n - 1) {
            if (valor > mejorValor) {
                mejorValor = valor;
            }
        } else {
            mochila(sol, n, k + 1, p, v, pesoA, pesoB, limite, valor, mejorValor);
        }
    }

    pesoB -= p[k];
    valor -= v[k];

    // No tomo el objeto k-ésimo

    sol[k] = Ninguna; // Al no tomarlo no hace falta actualizar peso y valor

    if (k == n - 1) { // Tampoco es necesario chequear peso <= P
        if (valor > mejorValor) {
            mejorValor = valor;
        }
    } else {
        mochila(sol, n, k + 1, p, v, pesoA, pesoB, limite, valor, mejorValor);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n, duracionCara;

    cin >> n;

    if (n == 0)
        return false;
    
    cin >> duracionCara;

    vector<int> duracion(n), puntuacion(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> duracion[i] >> puntuacion[i];
    }

    int pesoA = 0, pesoB = 0;

    vector<CaraCasete> sol(n, Ninguna);

    int mejorValor = 0;

    mochila(sol, n, 0, duracion, puntuacion, pesoA, pesoB, duracionCara, 0, mejorValor);
    
    // escribir sol
    cout << mejorValor << "\n";
    
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
