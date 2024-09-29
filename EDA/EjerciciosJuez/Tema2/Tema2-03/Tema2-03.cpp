// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Según la plantilla de calculo de complejidad en reducción por división
// el coste sería O(n) siendo n el número de elementos en el vector inicial
bool parcialmenteOrdenado(const vector<int>& v, int ini, int fin, int& min, int& max) {
    
    int n = fin - ini;

    if( n == 1) {
        min = v[ini];
        max = v[ini];
        return true;
    }

    int mitad = (ini+fin)/2;
    
    int minIzquierda, minDerecha, maxIzquierda, maxDerecha;

    bool izquierdaOrdenado = parcialmenteOrdenado(v, ini, mitad, minIzquierda, maxIzquierda);
    bool derechaOrdenado = parcialmenteOrdenado(v, mitad, fin, minDerecha, maxDerecha);

    if (izquierdaOrdenado && derechaOrdenado)
    {
        if ( maxDerecha >= maxIzquierda && minIzquierda <= minDerecha)
        {
            max = maxDerecha;
            min = minIzquierda;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool parcialmenteOrdenado(const vector<int>& v) {
    int min, max;
    return parcialmenteOrdenado(v,0,v.size(),min,max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int e;
    cin >> e;
    if (e == 0) return false;
    vector<int> sec;
    while (e != 0) {
        sec.push_back(e);
        cin >> e;
    }
    cout << (parcialmenteOrdenado(sec)? "SI" : "NO") << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}