// Nombre del alumno Marco Gonzalez Campo
// Usuario del Juez EDA-GDV30


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

int encontrarImpar(const vector<int>& sec, int ini, int fin) {
    int n = fin - ini;

    if(n == 1) return sec[ini];

    int mitad = (ini + fin) / 2;

    if(sec[mitad] % 2 == 1)
        return sec[mitad];

    int medioEsperado = sec[0] + mitad * 2;

    if(medioEsperado != sec[mitad])
        return encontrarImpar(sec, ini, mitad);
    else    
        return encontrarImpar(sec, mitad, fin);
}

// función que resuelve el problema
int resolver(const vector<int>& sec, int ini, int fin) {
    return encontrarImpar(sec, ini, fin);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << resolver(sec,0,n) << endl;
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