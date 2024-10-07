// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>

using namespace std;

int sumarCuadrados(int n)
{
    int aux = 0;

    while(n > 0)
    {
        aux += ((n % 10) * (n % 10));
        n /= 10;
    }

    return aux;
}

// función que resuelve el problema
// O(n log n) siendo n  los numeros calculados hasta llegar a la conclusión de si es feliz o no
void resolver(const int dato) {
    set<int> conjunto;

    int n = dato;

    cout << n << " ";

    while(conjunto.find(n) == conjunto.end())
    {
        conjunto.insert(n);
        n = sumarCuadrados(n);
        cout << n << " ";
    }

    cout << ((n==1) ? "\n" : "0\n");
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int n;

    cin >> n;

    if (! std::cin)
        return false;
    
    // escribir sol
    resolver(n);
    
    
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